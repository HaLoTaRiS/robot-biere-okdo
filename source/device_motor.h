/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_motor.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

//#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERA

/*******************************************************************************/
/* definitions & declarations */
/*******************************************************************************/

/****** INPUT / OUTPUT ******/
#ifndef BOARD_MOTOR_ENABLE_GPIO
#define BOARD_MOTOR_ENABLE_GPIO GPIO
#endif
#define BOARD_MOTOR_ENABLE_GPIO_PORT 0U
#ifndef BOARD_MOTOR_ENABLE_GPIO_PIN
#define BOARD_MOTOR_ENABLE_GPIO_PIN 16U
#endif

#ifndef BOARD_MOTOR_A_DIRECTION_GPIO
#define BOARD_MOTOR_A_DIRECTION_GPIO GPIO
#endif
#define BOARD_MOTOR_A_DIRECTION_GPIO_PORT 0U
#ifndef BOARD_MOTOR_A_DIRECTION_GPIO_PIN
#define BOARD_MOTOR_A_DIRECTION_GPIO_PIN 15U
#endif

#ifndef BOARD_MOTOR_B_DIRECTION_GPIO
#define BOARD_MOTOR_B_DIRECTION_GPIO GPIO
#endif
#define BOARD_MOTOR_B_DIRECTION_GPIO_PORT 1U
#ifndef BOARD_MOTOR_B_DIRECTION_GPIO_PIN
#define BOARD_MOTOR_B_DIRECTION_GPIO_PIN 26U
#endif

#define MOTOR_ENABLE_ON()                                             \
		GPIO_PortClear(BOARD_MOTOR_ENABLE_GPIO, BOARD_MOTOR_ENABLE_GPIO_PORT, \
				1U << BOARD_MOTOR_ENABLE_GPIO_PIN)

#define MOTOR_ENABLE_OFF()                                          \
		GPIO_PortSet(BOARD_MOTOR_ENABLE_GPIO, BOARD_MOTOR_ENABLE_GPIO_PORT, \
				1U << BOARD_MOTOR_ENABLE_GPIO_PIN)

#define MOTOR_A_DIRECTION_AVANT()                                             \
		GPIO_PortClear(BOARD_MOTOR_A_DIRECTION_GPIO, BOARD_MOTOR_A_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_A_DIRECTION_GPIO_PIN)

#define MOTOR_A_DIRECTION_ARRIERE()                                          \
		GPIO_PortSet(BOARD_MOTOR_A_DIRECTION_GPIO, BOARD_MOTOR_A_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_A_DIRECTION_GPIO_PIN)

#define MOTOR_B_DIRECTION_AVANT()                                             \
		GPIO_PortClear(BOARD_MOTOR_B_DIRECTION_GPIO, BOARD_MOTOR_B_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_B_DIRECTION_GPIO_PIN)

#define MOTOR_B_DIRECTION_ARRIERE()                                          \
		GPIO_PortSet(BOARD_MOTOR_B_DIRECTION_GPIO, BOARD_MOTOR_B_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_B_DIRECTION_GPIO_PIN)
