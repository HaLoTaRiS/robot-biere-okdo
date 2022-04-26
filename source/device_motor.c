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
  .matchValue = 2499,
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
  .matchValue = 2499, // Fréquence de 4000 Hz
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
  /* Start the timer */
//  CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);
}


void CTIMER0_MOTOR_B_init(void) {
  /* CTIMER0 peripheral initialization */
  CTIMER_Init(CTIMER0_MOTOR_B_PERIPHERAL, &CTIMER0_MOTOR_B_config);
  /* Match channel 3 of CTIMER0 peripheral initialization */
  CTIMER_SetupMatch(CTIMER0_MOTOR_B_PERIPHERAL, CTIMER0_MOTOR_B_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);
  /* Start the timer */
//  CTIMER_StartTimer(CTIMER0_MOTOR_B_PERIPHERAL);
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


void left_motor ( uint16_t type, uint32_t angle){
	MOTOR_ENABLE_ON();
	MOTOR_A_DIRECTION_ARRIERE();
	MOTOR_B_DIRECTION_AVANT();
//	run_motor_A();
//	run_motor_B();
}

void right_motor ( uint16_t type, uint32_t angle){
	MOTOR_ENABLE_ON();
	MOTOR_A_DIRECTION_AVANT();
	MOTOR_B_DIRECTION_ARRIERE();
//	run_motor_A();
//	run_motor_B();
}


void MOTOR_A_B_stop(void){
	MOTOR_ENABLE_OFF();
	CTIMER_StopTimer(CTIMER1_MOTOR_A_PERIPHERAL);
	CTIMER_StopTimer(CTIMER0_MOTOR_B_PERIPHERAL);
}

void run_motor_A(uint32_t step){

	/**** Calcul Timer 1 ****/
	uint32_t Clock_Timer1;
	uint32_t Clk_enable_timer1;
	uint32_t Clk_match_0;
	Clock_Timer1 = 1000000;


//	CTIMER_Init(CTIMER1_MOTOR_A_PERIPHERAL, &CTIMER1_MOTOR_A_config);

	Clk_enable_timer1 = Clock_Timer1 / (CTIMER1_MOTOR_A_config.prescale + 1);
	Clk_match_0 = (step / Clk_enable_timer1 ) -1 ;

//	CTIMER1_MOTOR_A_Match_0_config.matchValue = Clk_match_0;



	CTIMER1_MOTOR_A_Match_0_config.matchValue = step;

	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER1_MOTOR_A_Match_0_config);
	CTIMER_StartTimer(CTIMER1_MOTOR_A_PERIPHERAL);


	/**** Calcul Match1  ****/

	//	CLOCK_GetCTimerClkFreq(1U);
	//
	//	CTIMER1_MOTOR_A_config.prescale + 1;

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

//timerClock =
//
//void run_motor_B(uint32_t step){
//
//
//
//	g_pwmPeriod = (timerClock / pwmFreqHz) - 1U;

//	static uint32_t motor_B_vitesse_ =  100*step;
//	CTIMER0_MOTOR_B_Match_0_config.matchValue = (motor_B_vitesse_*2)/1;
//	CTIMER_SetupMatch(CTIMER1_MOTOR_A_PERIPHERAL, CTIMER1_MOTOR_A_MATCH_0_CHANNEL, &CTIMER0_MOTOR_B_Match_0_config);

//}


// Notion de vitesse à prendre en compte


// Angle

// Rotation
