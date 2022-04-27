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

#ifndef BOARD_PINCE_TX_ENABLE_GPIO
#define BOARD_PINCE_TX_ENABLE_GPIO GPIO
#endif
#define BOARD_PINCE_TX_ENABLE_GPIO_PORT 1U
#ifndef BOARD_PINCE_TX_ENABLE_GPIO_PIN
#define BOARD_PINCE_TX_ENABLE_GPIO_PIN 31U
#endif

#define PINCE_TX_ENABLE()                                             \
		GPIO_PortClear(BOARD_PINCE_TX_ENABLE_GPIO, BOARD_PINCE_TX_ENABLE_GPIO_PORT, \
				1U << BOARD_PINCE_TX_ENABLE_GPIO_PIN)

#define PINCE_TX_DISABLED()                                          \
		GPIO_PortSet(BOARD_PINCE_TX_ENABLE_GPIO, BOARD_PINCE_TX_ENABLE_GPIO_PORT, \
				1U << BOARD_PINCE_TX_ENABLE_GPIO_PIN)
