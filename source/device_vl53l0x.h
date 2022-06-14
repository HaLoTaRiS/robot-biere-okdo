/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_vl53l0x.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#ifndef INC_DEVICE_VL53L0X_H
#define INC_DEVICE_VL53L0X_H

#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"	   // Task OS

struct Laser {
	uint16_t value;
};

extern struct Laser laser1;
extern struct Laser laser2;
extern struct Laser laser3;
extern struct Laser laser4;


/******** OUTPUT CONFIGURATION ********/
/* Declaration SENSOR_1_XSHUT on GPIO0_7 */
#ifndef BOARD_SENSOR_1_XSHUT_GPIO
#define BOARD_SENSOR_1_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_1_XSHUT_GPIO_PORT 0U
#ifndef BOARD_SENSOR_1_XSHUT_GPIO_PIN
#define BOARD_SENSOR_1_XSHUT_GPIO_PIN 7U
#endif

/* Declaration SENSOR_2_XSHUT on GPIO1_1 */
#ifndef BOARD_SENSOR_2_XSHUT_GPIO
#define BOARD_SENSOR_2_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_2_XSHUT_GPIO_PORT 0U
#ifndef BOARD_SENSOR_2_XSHUT_GPIO_PIN
#define BOARD_SENSOR_2_XSHUT_GPIO_PIN 31U
#endif

/* Declaration SENSOR_3_XSHUT on GPIO1_2 */
#ifndef BOARD_SENSOR_3_XSHUT_GPIO
#define BOARD_SENSOR_3_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_3_XSHUT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_3_XSHUT_GPIO_PIN
#define BOARD_SENSOR_3_XSHUT_GPIO_PIN 2U
#endif

/* Declaration SENSOR_4_XSHUT on GPIO1_5 */
#ifndef BOARD_SENSOR_4_XSHUT_GPIO
#define BOARD_SENSOR_4_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_4_XSHUT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_4_XSHUT_GPIO_PIN
#define BOARD_SENSOR_4_XSHUT_GPIO_PIN 8U
#endif

/********* SENSOR_2_XSHUT GPIO 0_7 *********/
#define SENSOR_1_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_1_XSHUT_GPIO, BOARD_SENSOR_1_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_1_XSHUT_GPIO_PIN)

#define SENSOR_1_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_1_XSHUT_GPIO, BOARD_SENSOR_1_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_1_XSHUT_GPIO_PIN)

/********* SENSOR_2_XSHUT GPIO 0_31 *********/
#define SENSOR_2_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_2_XSHUT_GPIO, BOARD_SENSOR_2_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_2_XSHUT_GPIO_PIN)

#define SENSOR_2_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_2_XSHUT_GPIO, BOARD_SENSOR_2_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_2_XSHUT_GPIO_PIN)

/********* SENSOR_3_XSHUT GPIO 1_2 *********/
#define SENSOR_3_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_3_XSHUT_GPIO, BOARD_SENSOR_3_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_3_XSHUT_GPIO_PIN)

#define SENSOR_3_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_3_XSHUT_GPIO, BOARD_SENSOR_3_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_3_XSHUT_GPIO_PIN)

/********* SENSOR_4_XSHUT GPIO 1_5 *********/
#define SENSOR_4_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_4_XSHUT_GPIO, BOARD_SENSOR_4_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_4_XSHUT_GPIO_PIN)

#define SENSOR_4_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_4_XSHUT_GPIO, BOARD_SENSOR_4_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_4_XSHUT_GPIO_PIN)

/*******************************************************************************/
/* Task priorities. */
/*******************************************************************************/
#define task_VL53L0X_PRIORITY (configMAX_PRIORITIES - 10)


/*******************************************************************************/
/* Stack Size */
/******************************************************************************/
#define STACK_SIZE_VL53L0X 400

/*******************************************************************************
 * Prototypes SHELL
 ******************************************************************************/
void init_vl53l0x(void);
void vTaskVL53L0X(void *pvParameters);


#endif
