/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : middleware_uart.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#include "middleware_uart.h"

#include "peripherals.h"

#include <stdbool.h>
#include "fsl_power.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FC2_UART          USART2
//#define FC2_UART_CLK_SRC  kCLOCK_Flexcomm2
//#define FC2_UART_CLK_FREQ CLOCK_GetFlexCommClkFreq(0U)

#define FC2_UART_CLK_FREQ (12000000U)
#define FC2_SIZE_FRAME   16U // Size

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_rxBuffer[FC2_SIZE_FRAME ] = {0};
uint8_t g_txBuffer[FC2_SIZE_FRAME ] = {0};

volatile bool txComplete               = false;
volatile bool rxComplete               = false;

usart_handle_t g_usartHandle;
usart_config_t Fc2UartConfig;

/*******************************************************************************
 * Code
 ******************************************************************************/

usart_config_t FLEXCOMM2_config = {
		.baudRate_Bps = 115200UL,
		.syncMode = kUSART_SyncModeDisabled,
		.parityMode = kUSART_ParityDisabled,
		.stopBitCount = kUSART_OneStopBit,
		.bitCountPerChar = kUSART_8BitsPerChar,
		.loopback = false,
		.txWatermark = kUSART_TxFifo0,
		.rxWatermark = kUSART_RxFifo1,
		.enableRx = true,
		.enableTx = true,
		.enableHardwareFlowControl = false,
		.enableMode32k = false,
		.clockPolarity = kUSART_RxSampleOnFallingEdge,
		.enableContinuousSCLK = false
};

/**** Fonction initialisation de l'uart ****/
void fc2_uart_init(void){
	// Récupère les valeurs par défauts
	USART_GetDefaultConfig(&Fc2UartConfig);

	/*** Parameter uart ***/
	//Fc2UartConfig.baudRate_Bps = 9600;
	 Fc2UartConfig.baudRate_Bps = 1000000U;	// Vitesse du TTL 2.0
	//Fc2UartConfig.baudRate_Bps = 115200U;

	//	Fc2UartConfig.enableRx     = true;
	//	Fc2UartConfig.stopBitCount = kUSART_OneStopBit;
	//	Fc2UartConfig.bitCountPerChar = kUSART_8BitsPerChar;
	//  Fc2UartConfig.parityMode = kUSART_ParityDisabled;
	//  Fc2UartConfig.stopBitCount = kUSART_OneStopBit;
	//  Fc2UartConfig.bitCountPerChar = kUSART_8BitsPerChar;
	//  Fc2UartConfig.loopback = false;
	//  Fc2UartConfig.enableTx = false;
	//  Fc2UartConfig.enableRx = false;

	// Initialise le périphérique
	USART_Init(FC2_UART, &Fc2UartConfig, FC2_UART_CLK_FREQ);
	/* Create usart handle. */
	USART_TransferCreateHandle(FC2_UART, &g_usartHandle, USART_UserCallback, NULL);
}

void fc2_uart_transmit(uint8_t *TxData, uint8_t size){
	/* Start receiving. */
	usart_transfer_t g_transmit_uart;
	g_transmit_uart.data     = TxData;
	g_transmit_uart.dataSize = size;
	USART_TransferSendNonBlocking(FC2_UART, &g_usartHandle, &g_transmit_uart);
}

void uart_read_xl320(uint8_t *RxData, uint8_t size){

	usart_transfer_t FLEXCOMM2_rxTransfer;
	FLEXCOMM2_rxTransfer.data     = RxData;
	FLEXCOMM2_rxTransfer.dataSize = size;
	USART_TransferReceiveNonBlocking(FC2_UART, &g_usartHandle, &FLEXCOMM2_rxTransfer, NULL);
	while (rxComplete == false)
	{
	}
}


// Documentation :
//    - https://emanual.robotis.com/docs/en/dxl/protocol2/
// 	  - https://emanual.robotis.com/docs/en/dxl/x/xl320/#control-table
void uart_write_xl320(uint8_t id, uint8_t xl320_addr, uint8_t *xl320_data, uint8_t size){
	uint16_t crc;
	uint8_t g_txXL320[13] = {0};

	g_txXL320[0] = 0xFF; 			// Header 1
	g_txXL320[1] = 0xFF; 			// Header 2
	g_txXL320[2] = 0xFD; 			// Header 3
	g_txXL320[3] = 0x00; 			// Reserve
	g_txXL320[4] = id;	 			// ID
	g_txXL320[5] = size+5;			// Size 1
	g_txXL320[6] = 0x00;			// Size 2
	g_txXL320[7] = UART_TTL_WRITE;
	g_txXL320[8] = xl320_addr;  	// Adresse
	g_txXL320[9] = 0x00;

	for(int i=0;i<size;i++)
	{
		g_txXL320[10+i] = xl320_data[i];
	}

	crc = update_crc(0,g_txXL320,10+size);

	g_txXL320[10+size] = crc & 0xFF;
	g_txXL320[11+size] = (crc>>8) & 0xFF;

	usart_transfer_t g_transmit_uart;
	g_transmit_uart.data     = g_txXL320;
	g_transmit_uart.dataSize = 12+size;

	USART_TransferSendNonBlocking(FC2_UART, &g_usartHandle, &g_transmit_uart);
	/* Waiting for transfer completion. */
	while (txComplete == false)
	{
	}
	txComplete = false;

}


/* USART user callback */
void USART_UserCallback(USART_Type *base, usart_handle_t *handle, status_t status, void *userData)
{
	if (kStatus_USART_TxIdle == status)
	{
		txComplete = true;
	}

	if (kStatus_USART_RxIdle == status)
	{
		rxComplete = true;
	}
}


/*** fonction CRC XL320****/
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
	unsigned short i, j;
	unsigned short crc_table[256] = {
			0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
			0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
			0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
			0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
			0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
			0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
			0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
			0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
			0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
			0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
			0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
			0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
			0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
			0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
			0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
			0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
			0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
			0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
			0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
			0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
			0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
			0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
			0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
			0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
			0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
			0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
			0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
			0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
			0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
			0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
			0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
			0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
	};

	for(j = 0; j < data_blk_size; j++)
	{
		i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
		crc_accum = (crc_accum << 8) ^ crc_table[i];
	}

	return crc_accum;
}

