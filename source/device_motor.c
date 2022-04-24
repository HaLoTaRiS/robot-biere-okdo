/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_motor.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

/*******************************************************************************/
/* include files */
/*******************************************************************************/

#include "device_motor.h"

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

/*******************************************************************************/
/* definitions & declarations */
/*******************************************************************************/


// Init motor

//void init_motor(void){
//	CTIMER0_MOTOR_B_init();
//	CTIMER1_MOTOR_A_init();
//}
//
//void start_motor(void){
//	MOTOR_ENABLE_ON();
//	CTIMER_StartTimer(CTIMER0_MOTOR_A_config);
//	CTIMER_StartTimer(CTIMER0_MOTOR_B_config);
//}
//
//void stop_motor(void){
//	MOTOR_ENABLE_OFF();
//	CTIMER_StopTimer(CTIMER0_MOTOR_A_config);
//	CTIMER_StopTimer(CTIMER0_MOTOR_B_config);
//}


//PRINTF("3eme CTimer match example \r\n");
//
//CTIMER_GetDefaultConfig(&config);
//
//PRINTF("Frequence : %d \r\n", CTIMER_CLK_FREQ);
//
//CTIMER_Init(CTIMER, &config);
//
//matchConfig.enableCounterReset = true;
//matchConfig.enableCounterStop  = false;
//matchConfig.matchValue         = CTIMER_CLK_FREQ / 2;
//matchConfig.outControl         = kCTIMER_Output_Toggle;
//matchConfig.outPinInitState    = true;
//matchConfig.enableInterrupt    = false;
//CTIMER_SetupMatch(CTIMER, CTIMER_MAT_OUT, &matchConfig);
//CTIMER_StartTimer(CTIMER);

//const ctimer_config_t CTIMER1_MOTOR_A_config = {
//  .mode = kCTIMER_TimerMode,
//  .input = kCTIMER_Capture_0,
//  .prescale = 0
//};
//const ctimer_match_config_t CTIMER1_MOTOR_A_Match_0_config = {
//  .matchValue = 499,
//  .enableCounterReset = true,
//  .enableCounterStop = false,
//  .outControl = kCTIMER_Output_Toggle,
//  .outPinInitState = false,
//  .enableInterrupt = false
//};
//
//static void CTIMER1_MOTOR_A_init(void) {
//  /* CTIMER1 peripheral initialization */
//  CTIMER_Init(CTIMER1_MOTOR_A_PERIPHERAL, &CTIMER1_MOTOR_A_config);
//  /* Match channel 2 of CTIMER1 peripheral initialization */
//  CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER1_MOTOR_A_Match_0_config);
//}



void run_motor_A(uint32_t step){

	/* matchValue
	 * 2000			10
	 * 1800			9
	 * 1700
	 * 1600
	 * 1500
	 * 1400		12
	 * 1300
	 * 1200		11
	 * 1100
	 * 1000		10
	 *  900		9
	 *  800		8
	 *  700		7
	 *  600		6
	 *  500		5
	 *  400		4
	 *  300		3
	 *  200		2
	 *  100		1
	 *
	 */
//	static uint32_t motor_A_vitesse_ =  100*step;
//	CTIMER0_MOTOR_A_Match_0_config.matchValue = (motor_A_vitesse_*2)/1;
//	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER1_MOTOR_A_Match_0_config);
}

void run_motor_B(uint32_t step){
//	static uint32_t motor_B_vitesse_ =  100*step;
//	CTIMER0_MOTOR_B_Match_0_config.matchValue = (motor_B_vitesse_*2)/1;
//	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);

}


// Notion de vitesse à prendre en compte
