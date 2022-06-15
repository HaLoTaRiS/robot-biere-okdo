/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : appli_shell.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "device_xl320.h"
#include "middleware_uart.h"


void main_open(void){
	uint32_t temp;
	uint8_t data_tx_uart[2] = {0};

	temp = (uint32_t)(XL320_DATA_MOTOR_CLOSE) * 1023;
	temp /= 300;

	// Valeur sur deux bits
	data_tx_uart[0] = temp & 0xFF;
	data_tx_uart[1] = (temp >> 8) & 0xFF;

	// Transmission sur l'uart:
	XL320_TX_ENABLE();
	uart_write_xl320(0x01,0x1E,data_tx_uart,2);
	XL320_TX_DISABLED();

}


void main_close(void){
	uint32_t temp;
	uint8_t data_tx_uart[2] = {0};

	temp = (uint32_t)(XL320_DATA_MOTOR_OPEN) * 1023;
	temp /= 300;

	// Valeur sur deux bits
	data_tx_uart[0] = temp & 0xFF;
	data_tx_uart[1] = (temp >> 8) & 0xFF;

	// Transmission sur l'uart:
	XL320_TX_ENABLE();
	uart_write_xl320(0x01,0x1E,data_tx_uart,2);
	XL320_TX_DISABLED();
}
