/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : appli_shell.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


// PINCE_TX_ENABLE : >> GPIO1_31

#ifndef INC_DEVICE_XL320_H
#define INC_DEVICE_XL320_H

#ifndef BOARD_XL320_TX_ENABLE_GPIO
#define BOARD_XL320_TX_ENABLE_GPIO GPIO
#endif
#define BOARD_XL320_TX_ENABLE_GPIO_PORT 1U
#ifndef BOARD_XL320_TX_ENABLE_GPIO_PIN
#define BOARD_XL320_TX_ENABLE_GPIO_PIN 31U
#endif

#define XL320_TX_ENABLE()                                             \
		GPIO_PortClear(BOARD_XL320_TX_ENABLE_GPIO, BOARD_XL320_TX_ENABLE_GPIO_PORT, \
				1U << BOARD_XL320_TX_ENABLE_GPIO_PIN)

#define XL320_TX_DISABLED()                                          \
		GPIO_PortSet(BOARD_XL320_TX_ENABLE_GPIO, BOARD_XL320_TX_ENABLE_GPIO_PORT, \
				1U << BOARD_XL320_TX_ENABLE_GPIO_PIN)


// XL320 ADDRESS
#define XL320_ADDR_MODEL_NUMBER			0		// Sur deux bits
#define XL320_ADDR_FIRMWARE				2
#define XL320_ADDR_ID					3
#define XL320_ADDR_BAUD_RATE			4
#define XL320_ADDR_RETURN_DELAY			5
#define XL320_ADDR_CW_ANGLE_LIMIT		6		// sur deux bits
#define XL320_ADDR_CCW_ANGLE_LIMIT		8		// sur deux bits
#define XL320_ADDR_CONTROL_MODE			11
#define XL320_ADDR_TEMPERATURE_LIMIT	12
#define XL320_ADDR_MIN_VOLTAGE_LIMIT	13
#define XL320_ADDR_MAX_VOLTAGE_LIMIT	14
#define XL320_ADDR_MAX_TORQUE			15		// sur deux bits
#define XL320_ADDR_STATUS_RETUEN_LEVEL	17
#define XL320_ADDR_SHUT_DOWN			18

#define XL320_ADDR_TORQUE_ENABLE		24
#define XL320_ADDR_LED 					25
#define XL320_ADDR_D_GAIN				27
#define XL320_ADDR_I_GAIN				28
#define XL320_ADDR_P_GAIN				29
#define XL320_ADDR_GOAL_POSITION		30		// sur deux bits
#define XL320_ADDR_MOVING_SPEED			32		// sur deux bits
#define XL320_ADDR_TORQUE_LIMIT			35		// sur deux bits
#define XL320_ADDR_PRESENT_POSITION		37		// sur deux bits
#define XL320_ADDR_PRESENT_SPEED		39		// sur deux bits
#define XL320_ADDR_PRESENT_LOAD			41		// sur deux bits
#define XL320_ADDR_PRESENT_TEMPERATURE	45		// sur deux bits
#define XL320_ADDR_REGISTERED_INSTRUC	47
#define XL320_ADDR_MOBVING				49
#define XL320_ADDR_HARDWARE_ERROR		50
#define XL320_ADDR_PUNCH				51		// sur deux bits


// XL320 DATA BAUD RATE
#define XL320_DATA_BAUD_9600	0
#define XL320_DATA_BAUD_57600	1
#define XL320_DATA_BAUD_115200	2
#define XL320_DATA_BAUD_1000000	3

// XL320 DATA LED
#define XL320_DATA_LED_OFF 		0
#define XL320_DATA_LED_RED 		1
#define XL320_DATA_LED_GREEN 	2
#define XL320_DATA_LED_YELLOW	3
#define XL320_DATA_LED_BLUE		4
#define XL320_DATA_LED_PURPLE	5
#define XL320_DATA_LED_CYAN		6
#define XL320_DATA_LED_WHITE	7








#endif
