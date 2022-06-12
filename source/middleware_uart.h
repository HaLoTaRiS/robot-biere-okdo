/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : middleware_i2c.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_usart.h"


#ifndef INC_MIDDLEWARE_UART_H
#define INC_MIDDLEWARE_UART_H

//void Uart_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
//		status_t status, void *userData);


#define FC2_UART_CLK_FREQ (12000000U)
#define FLEXCOMM2_PERIPHERAL          USART2

// TTL definition
#define UART_TTL_PING			0x01
#define UART_TTL_READ			0x02
#define UART_TTL_WRITE			0x03
#define UART_TTL_REG_WRITE		0x04
#define UART_TTL_FACTORY_RESET	0x06
#define	UART_TTL_REBOOT			0x08
#define UART_TTL_CLEAR			0x10
#define	UART_TTL_CONTROL_BACKUP	0x20
#define UART_TTL_STATUS			0X55
#define UART_TTL_SYNC_READ		0x82
#define UART_TTL_SYNC_WRITE		0x83
#define UART_TTL_BULK_READ		0x92
#define UART_TTL_BULK_WRITE		0x93
#define UART_TTL_FAST_BULK_READ	0x9A

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void fc2_uart_init(void);
void fc2_uart_transmit(uint8_t *TxData, uint8_t size);


void uart_read_xl320(uint8_t *RxData, uint8_t size);

void uart_write_xl320(uint8_t id, uint8_t xl320_addr, uint8_t *xl320_data, uint8_t size);

unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);
void USART_UserCallback(USART_Type *base, usart_handle_t *handle, status_t status, void *userData);

#endif
