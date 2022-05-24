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

#include "fsl_usart.h"


#ifndef INC_MIDDLEWARE_UART_H
#define INC_MIDDLEWARE_UART_H

//void Uart_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
//		status_t status, void *userData);


#define FLEXCOMM2_CLOCK_SOURCE 12000000U

void uart_init_xl320(void);
void uart_read_xl320(uint8_t *RxData, uint8_t size);
void uart_write_xl320(uint8_t *TxData, uint8_t size);

#endif
