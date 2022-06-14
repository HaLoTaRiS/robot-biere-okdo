/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_vl53l0x.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "robot_shell.h"
#include "board.h"
#include "peripherals.h"

#include "fsl_i2c.h"
#include "device_vl53l0x.h"
#include "driver_vl53l0x.h"
#include "middleware_ic2.h"


#define VL53L0X_SINGLE


TaskHandle_t xHandleVL53L0X = NULL;

extern i2c_master_handle_t i2c_fc4_handle;

struct Laser laser1;
struct Laser laser2;
struct Laser laser3;
struct Laser laser4;


void init_vl53l0x(void) {

	BaseType_t xReturned;	// Pour création des tasks
	/**************** Task VL53L0X ****************/
	xReturned = xTaskCreate(
			vTaskVL53L0X,
			"Task I2C VL53L0X",
			STACK_SIZE_VL53L0X,
			(void *) NULL,
			task_VL53L0X_PRIORITY,
			&xHandleVL53L0X);

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task VL53L0X creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleVL53L0X); // On lance la tache pour lecture du capteur

}



/******************************************************************************/
/* Task VL53L0X	                                                          */
/******************************************************************************/
void vTaskVL53L0X(void *pvParameters)
{

	I2C_MasterTransferCreateHandle(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
			i2c_master_callback, NULL);
	bool success = vl53l0x_init();

	// Initialisation du bus I2C
	while (success) {
//		SENSOR_1_XSHUT_ON();
//		success = vl53l0x_read_range_single(&laser1.value);
//		SENSOR_1_XSHUT_OFF();
//		vTaskDelay(5/portTICK_PERIOD_MS);
//		SENSOR_2_XSHUT_ON();
//		success = vl53l0x_read_range_single(&laser2.value);
//		SENSOR_2_XSHUT_OFF();
//		vTaskDelay(5/portTICK_PERIOD_MS);
//		SENSOR_3_XSHUT_ON();
//		success = vl53l0x_read_range_single(&laser3.value);
//		SENSOR_3_XSHUT_OFF();
//		vTaskDelay(5/portTICK_PERIOD_MS);
//		SENSOR_4_XSHUT_ON();
//		success = vl53l0x_read_range_single(&laser4.value);
//		SENSOR_4_XSHUT_OFF();
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}
