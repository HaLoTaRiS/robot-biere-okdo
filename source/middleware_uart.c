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
#include "fsl_usart.h"
#include "peripherals.h"

//extern usart_handle_t FLEXCOMM2_handle;

// Récupérer la configuration périphérals.c
//extern usart_transfer_t FLEXCOMM2_rxTransfer;
//extern usart_transfer_t FLEXCOMM2_txTransfer;



#define FLEXCOMM2_PERIPHERAL          USART0

//uint8_t g_txBuffer[TRANSFER_SIZE * 2U] = {0};
//uint8_t g_rxBuffer[TRANSFER_SIZE + 1U] = {0};
volatile bool txComplete               = false;
volatile bool rxComplete               = false;

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

usart_handle_t FLEXCOMM2_handle;

//uint8_t FLEXCOMM2_rxBuffer[FLEXCOMM2_RX_BUFFER_SIZE];
//usart_transfer_t FLEXCOMM2_rxTransfer = {
//  .rxData = FLEXCOMM2_rxBuffer,
//  .dataSize = FLEXCOMM2_RX_BUFFER_SIZE
//};
//
//uint8_t FLEXCOMM2_txBuffer[FLEXCOMM2_TX_BUFFER_SIZE];
//usart_transfer_t FLEXCOMM2_txTransfer = {
//  .data = FLEXCOMM2_txBuffer,
//  .dataSize = FLEXCOMM2_TX_BUFFER_SIZE
//};

void uart_init_xl320(void){
	  USART_Init(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_config, FLEXCOMM2_CLOCK_SOURCE);
	  USART_TransferCreateHandle(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_handle, NULL, NULL);
}

void uart_read_xl320(uint8_t *RxData, uint8_t size){

	usart_transfer_t FLEXCOMM2_rxTransfer;
	FLEXCOMM2_rxTransfer.data     = RxData;
	FLEXCOMM2_rxTransfer.dataSize = size;
    USART_TransferReceiveNonBlocking(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_handle, &FLEXCOMM2_rxTransfer, NULL);
    while (rxComplete == false)
    {
    }
}



void uart_write_xl320(uint8_t *TxData, uint8_t size){
	usart_transfer_t FLEXCOMM2_txTransfer;
	FLEXCOMM2_txTransfer.data     = TxData;
	FLEXCOMM2_txTransfer.dataSize = size;

    USART_TransferSendNonBlocking(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_handle, &FLEXCOMM2_txTransfer);
    /* Waiting for transfer completion. */
    while (txComplete == false)
    {
    }
    txComplete = false;


}


