/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_switch.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#ifndef INC_DEVICE_SWITCH_H
#define INC_DEVICE_SWITCH_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************/
/* definitions & declarations */
/*******************************************************************************/

bool service_beer = false ; 	// Valeur état biere

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef BOARD_SWITCH_BIERE_GPIO
#define BOARD_SWITCH_BIERE_GPIO GPIO
#endif
#define BOARD_SWITCH_BIERE_GPIO_PORT 0U
#ifndef BOARD_SWITCH_BIERE_GPIO_PORT_PIN
#define BOARD_SWITCH_BIERE_GPIO_PORT_PIN 26U
#endif

#endif

