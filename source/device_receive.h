/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_receive.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#ifndef INC_DEVICE_RECEIVE_DATA_H
#define INC_DEVICE_RECEIVE_DATA_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define task_RECEIVE_DATA_PRIORITY (configMAX_PRIORITIES - 10)
#define STACK_SIZE_RECEIVE_DATA 300

struct Jetson {
	uint8_t id;
	uint16_t data;
	uint16_t memo_right;
	uint16_t memo_left;
	uint8_t sens_right;
	uint8_t sens_left;
	uint32_t vitesse_right;
	uint32_t vitesse_left;
};

extern struct Jetson jetson;


void init_receive_data(void);
void vTaskReceiveData(void *pvParameters);
uint16_t function_convert(uint16_t data_jetson);

#endif
