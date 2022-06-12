/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_interrupt.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "device_interrupt.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "task.h"

#define SHELL_Printf PRINTF

extern TaskHandle_t xHandleUltrasonEcho;
extern uint32_t count;

void callback_interrupt_pio0(void){
	if (GPIO_PinRead(BOARD_ULTRASON_2_ECHO_GPIO, BOARD_ULTRASON_2_ECHO_GPIO_PORT,BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN )){
		//		vTaskResume(xHandleUltrason2Echo);
		PRINTF("Interrupt pio 0 ECHO ! \r\n");
	}
}

void callback_interrupt_pio1(void){
	if (GPIO_PinRead(BOARD_ULTRASON_1_ECHO_GPIO, BOARD_ULTRASON_1_ECHO_GPIO_PORT,BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN )){
		count = 0 ;
		CTIMER_StartTimer(CTIMER2_ULTRASON_PERIPHERAL);
	}

	if (GPIO_PinRead(BOARD_ULTRASON_2_ECHO_GPIO, BOARD_ULTRASON_2_ECHO_GPIO_PORT,BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN )){
		count = 0 ;
		CTIMER_StartTimer(CTIMER2_ULTRASON_PERIPHERAL);
	}

}


/* Nota :
 *   - Ultrason 1 ECHO :  PIO 1 / 10
 *   - Ultrason 2 ECHO :  PIO 0 / 13
 *
 *
 */


void init_interrupt(void){
	GINT_Init(GINT0);
	GINT_Init(GINT1);

	GINT_SetCtrl(GINT0, kGINT_CombineOr, kGINT_TrigEdge, callback_interrupt_pio0);
	GINT_SetCtrl(GINT1, kGINT_CombineOr, kGINT_TrigEdge, callback_interrupt_pio1);

	/* Select pins & polarity */
	// Ultrason 1 Echo
	GINT_ConfigPins(GINT0, BOARD_PORT_GPIO_0, ULTRASON_2_ECHO_POL_MASK, ULTRASON_2_ECHO_ENA_MASK);
	// Ultrason 2 Echo
	GINT_ConfigPins(GINT1, BOARD_PORT_GPIO_1, ULTRASON_1_ECHO_POL_MASK, ULTRASON_1_ECHO_ENA_MASK);

	/* Enable callbacks for INT_SW203 & GINT1 */
	GINT_EnableCallback(GINT0);
	GINT_EnableCallback(GINT1);

}
