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
#include "fsl_shell.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"
#include "fsl_power.h"

/*******************************************************************************/
/* definitions & declarations */
/*******************************************************************************/

// Donne la fréquence du timer 0 et 1 (voir arbre des horloges) ou clock_config
//#define CLK_TIMER0 CLOCK_GetCTimerClkFreq(0U) // 1 Mhz
//#define CLK_TIMER1 CLOCK_GetCTimerClkFreq(1U) // 1 Mhz


//uint32_t CLOCK_TIMER0 = 1;
//uint32_t CLOCK_TIMER1 = 1;

// Enable des timers en fonction du prescaler
// Nota : ici les pescalers sont laissés à 0.
//uint32_t enable_timer0 = CLOCK_TIMER0 / (CTIMER0_MOTOR_B_config.prescale +1);


//CTIMER0_MOTOR_B_PERIPHERAL
//CTIMER1_MOTOR_A_PERIPHERAL


// Réutilisation des variables initialisés dans peripherals.c
// CTIMER0_MOTOR_B_config // Config du timer 0
// CTIMER1_MOTOR_A_config // Config du timer 1

//CTIMER0_MOTOR_B_Match_0_config
//CTIMER0_MOTOR_A_Match_1_config



//CTIMER_SetupMatch(CTIMER0_MOTOR_B_PERIPHERAL, CTIMER0_MOTOR_B_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);
///* Start the timer */
//CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);

//CTIMER


/********** TIMER 1 - MOTEUR A *************/
ctimer_config_t CTIMER1_MOTOR_A_config = {
		.mode = kCTIMER_TimerMode,
		.input = kCTIMER_Capture_0,
		.prescale = 0
};

ctimer_match_config_t CTIMER1_MOTOR_A_Match_0_config = {
		.matchValue = 2499, // Fréquence de 400 Hz
		.enableCounterReset = true,
		.enableCounterStop = false,
		.outControl = kCTIMER_Output_Toggle,
		.outPinInitState = false,
		.enableInterrupt = false
};

/********** TIMER 0 - MOTEUR B *************/
ctimer_config_t CTIMER0_MOTOR_B_config = {
		.mode = kCTIMER_TimerMode,
		.input = kCTIMER_Capture_0,
		.prescale = 0
};

ctimer_match_config_t CTIMER0_MOTOR_B_Match_0_config = {
		.matchValue = 2499, // Fréquence de 400 Hz
		.enableCounterReset = true,
		.enableCounterStop = false,
		.outControl = kCTIMER_Output_Toggle,
		.outPinInitState = false,
		.enableInterrupt = false
};

void CTIMER1_MOTOR_A_init(void) {
	/* CTIMER1 peripheral initialization */
	CTIMER_Init(CTIMER1_MOTOR_A_PERIPHERAL, &CTIMER1_MOTOR_A_config);
	/* Match channel 2 of CTIMER1 peripheral initialization */
	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER1_MOTOR_A_Match_0_config);
	/* Start the timer if necessary */
	//  CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
}

void CTIMER0_MOTOR_B_init(void) {
	/* CTIMER0 peripheral initialization */
	CTIMER_Init(CTIMER0_MOTOR_B_PERIPHERAL, &CTIMER0_MOTOR_B_config);
	/* Match channel 3 of CTIMER0 peripheral initialization */
	CTIMER_SetupMatch(CTIMER0_MOTOR_B_PERIPHERAL, CTIMER0_MOTOR_B_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);
	/* Start the timer if necessary */
	// CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}

void MOTEUR_TIMER_init(void){
	CTIMER0_MOTOR_B_init();
	CTIMER1_MOTOR_A_init();
}

void MOTOR_A_B_start(void){
	MOTOR_ENABLE_ON();
	CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
	CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}


void MOTOR_left (void){
	MOTOR_ENABLE_ON();

		MOTOR_A_DIRECTION_ARRIERE();
		MOTOR_B_DIRECTION_AVANT();
		CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
		CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
		MOTOR_A_run (MOTOR_CALCUL_match_value_motor(100));
		MOTOR_B_run (MOTOR_CALCUL_match_value_motor(100));


}

void MOTOR_right (void){
	MOTOR_ENABLE_ON();
	MOTOR_A_DIRECTION_AVANT();
	MOTOR_B_DIRECTION_ARRIERE();
	CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
	CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
	MOTOR_A_run (MOTOR_CALCUL_match_value_motor(100));
	MOTOR_B_run (MOTOR_CALCUL_match_value_motor(100));

}


void MOTOR_A_B_stop(void){
	MOTOR_ENABLE_OFF();
	CTIMER_StopTimer(CTIMER1_MOTOR_A_PERIPHERAL);
	CTIMER_StopTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}

void MOTOR_A_stop(void){
	MOTOR_ENABLE_OFF();
	CTIMER_StopTimer(CTIMER1_MOTOR_A_PERIPHERAL);
}

void MOTOR_B_stop(void){
	MOTOR_ENABLE_OFF();
	CTIMER_StopTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}

int MOTOR_CALCUL_match_value_motor (int Motor_Frequence){
	/**** Calcul Timer 1 ****/
	//	uint32_t Clock_Timer1;
	//	uint32_t Clk_enable_timer1;
	//	uint32_t Clk_match_0;
	//	Clock_Timer1 = 1000000;

	////	CTIMER_Init(CTIMER1_MOTOR_A_PERIPHERAL, &CTIMER1_MOTOR_A_config);
	//
	//	Clk_enable_timer1 = Clock_Timer1 / (CTIMER1_MOTOR_A_config.prescale + 1);
	//	Clk_match_0 = (step / Clk_enable_timer1 ) -1 ;
	//
	////	CTIMER1_MOTOR_A_Match_0_config.matchValue = Clk_match_0;

	Motor_Frequence = Motor_Frequence * 2;
	int match_value =0;
	match_value = (1000000 / Motor_Frequence )-1;
	return match_value;
}


int MOTOR_CALCUL_angle(int degree){
	uint32_t rayon_roue = 35;
	uint32_t distance_roue_A_B = 0;
	uint32_t nbr_pas;

	// 1 pas moteur = 1,8° = 0.0035/200 soit 0.175 mm
	// Fonction à continuer.

	return nbr_pas;
}

void MOTOR_A_run (uint32_t Motor_matchvalue){
	// Modification du matchValue timer1
	CTIMER1_MOTOR_A_Match_0_config.matchValue = Motor_matchvalue;
	// Setup du timer1
	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER1_MOTOR_A_Match_0_config);
	// Reset du timer1
	CTIMER_Reset(CTIMER1_MOTOR_A_PERIPHERAL);
	// Start du timer1
	CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
}

void MOTOR_B_run (uint32_t Motor_matchvalue){
	// Modification du matchValue timer0
	CTIMER0_MOTOR_B_Match_0_config.matchValue = Motor_matchvalue;
	// Setup du timer0
	CTIMER_SetupMatch(CTIMER0_MOTOR_B_PERIPHERAL, CTIMER0_MOTOR_B_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);
	// Reset du timer0
	CTIMER_Reset(CTIMER0_MOTOR_B_PERIPHERAL);
	// Start du timer0
	CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}

// Angle

// Rotation
