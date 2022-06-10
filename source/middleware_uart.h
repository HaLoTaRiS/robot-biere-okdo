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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void fc2_uart_init(void);
void fc2_uart_transmit(uint8_t *TxData, uint8_t size);


void uart_read_xl320(uint8_t *RxData, uint8_t size);
void uart_write_xl320(uint8_t *TxData, uint8_t size);

unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);
void USART_UserCallback(USART_Type *base, usart_handle_t *handle, status_t status, void *userData);

#endif
