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


#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include "fsl_gint.h"

#include "fsl_common.h"
#include "fsl_power.h"
#include "fsl_debug_console.h"
#include "fsl_shell.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_GINT0_PORT kGINT_Port0
#define DEMO_GINT1_PORT kGINT_Port1

/* Select one input, active low for GINT0 */
#define DEMO_GINT0_POL_MASK ~(1U << BOARD_SW1_GPIO_PIN)
#define DEMO_GINT0_ENA_MASK (1U << BOARD_SW1_GPIO_PIN)

/* Select two inputs, active low for GINT1. SW2 & SW3 must be connected to the same port */
#define DEMO_GINT1_POL_MASK ~((1U << BOARD_SW2_GPIO_PIN) | (1U << BOARD_SW3_GPIO_PIN))
#define DEMO_GINT1_ENA_MASK ((1U << BOARD_SW2_GPIO_PIN) | (1U << BOARD_SW3_GPIO_PIN))


/*******************************************************************************
 * Fonction interruption
 ******************************************************************************/
void gint0_callback(void)
{

//	printf("SYSTEM >> Robot Biere\r\n");

}

void gint1_callback(void)
{

//	printf("SYSTEM >> Robot Biere\r\n");

}

void init_GINT_SENSOR(void){
	GINT_Init(GINT0);
	GINT_Init(GINT1);
}

