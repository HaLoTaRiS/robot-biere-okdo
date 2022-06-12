/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_interrupt.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#ifndef INC_DEVICE_INTERRUPT_H
#define INC_DEVICE_INTERRUPT_H

#include "fsl_gint.h" 			// Library interrupt
#include "driver_ultrason.h"	// Gpio ultrason
								// Gpio laser

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BOARD_PORT_GPIO_0 kGINT_Port0	// GPIO0
#define BOARD_PORT_GPIO_1 kGINT_Port1	// GPIO1



/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void init_interrupt(void);
void callback_interrupt_pio0(void);
void callback_interrupt_pio1(void);

#endif
