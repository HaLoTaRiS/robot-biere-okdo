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

void init_motor(void){
	;
}

void start_motor(void){
	MOTOR_ENABLE_ON();
}

void stop_motor(void){
	MOTOR_ENABLE_OFF();
}

void run_motor_A(void){

}

void run_motor_B(void){

}
