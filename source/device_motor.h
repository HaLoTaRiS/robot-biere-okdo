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

#include "fsl_common.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"


/*******************************************************************************/
/* definitions & declarations */
/*******************************************************************************/

/******************************* INPUT / OUTPUT *******************************/

#ifndef INC_DEVICE_MOTOR_H
#define INC_DEVICE_MOTOR_H

// MOTOR_ENABLE : >> GPIO0_16

#ifndef BOARD_MOTOR_ENABLE_GPIO
#define BOARD_MOTOR_ENABLE_GPIO GPIO
#endif
#define BOARD_MOTOR_ENABLE_GPIO_PORT 0U
#ifndef BOARD_MOTOR_ENABLE_GPIO_PIN
#define BOARD_MOTOR_ENABLE_GPIO_PIN 16U
#endif

// MOTOR_A_DIRECTION_A : >> GPIO0_15

#ifndef BOARD_MOTOR_A_DIRECTION_GPIO
#define BOARD_MOTOR_A_DIRECTION_GPIO GPIO
#endif
#define BOARD_MOTOR_A_DIRECTION_GPIO_PORT 0U
#ifndef BOARD_MOTOR_A_DIRECTION_GPIO_PIN
#define BOARD_MOTOR_A_DIRECTION_GPIO_PIN 15U
#endif

// MOTOR_A_DIRECTION_B : >> GPIO1_26
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

// Nota : Il faut inverser le sens entre moteur A et B (SET/CLEAR)
#define MOTOR_A_DIRECTION_AVANT()                                             \
		GPIO_PortSet(BOARD_MOTOR_A_DIRECTION_GPIO, BOARD_MOTOR_A_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_A_DIRECTION_GPIO_PIN)

#define MOTOR_A_DIRECTION_ARRIERE()                                          \
		GPIO_PortClear(BOARD_MOTOR_A_DIRECTION_GPIO, BOARD_MOTOR_A_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_A_DIRECTION_GPIO_PIN)

#define MOTOR_B_DIRECTION_AVANT()                                             \
		GPIO_PortClear(BOARD_MOTOR_B_DIRECTION_GPIO, BOARD_MOTOR_B_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_B_DIRECTION_GPIO_PIN)

#define MOTOR_B_DIRECTION_ARRIERE()                                          \
		GPIO_PortSet(BOARD_MOTOR_B_DIRECTION_GPIO, BOARD_MOTOR_B_DIRECTION_GPIO_PORT, \
				1U << BOARD_MOTOR_B_DIRECTION_GPIO_PIN)

/******************************* TIMER *******************************/
#define CTIMER1_MOTOR_A_PERIPHERAL CTIMER1
/* Timer tick frequency in Hz (input frequency of the timer) */
#define CTIMER1_MOTOR_A_TICK_FREQ 1000000UL
/* Timer tick period in ns (input period of the timer) */
#define CTIMER1_MOTOR_A_TICK_PERIOD 1000UL
/* Definition of PWM period channel. */
#define CTIMER1_MOTOR_A_PWM_PERIOD_CH kCTIMER_Match_0
/* Definition of channel 2 ID */
#define CTIMER1_MOTOR_A_MATCH_0_CHANNEL kCTIMER_Match_2
/* Definition of peripheral ID */
#define CTIMER0_MOTOR_B_PERIPHERAL CTIMER0
/* Timer tick frequency in Hz (input frequency of the timer) */
#define CTIMER0_MOTOR_B_TICK_FREQ 1000000UL
/* Timer tick period in ns (input period of the timer) */
#define CTIMER0_MOTOR_B_TICK_PERIOD 1000UL
/* Definition of PWM period channel. */
#define CTIMER0_MOTOR_B_PWM_PERIOD_CH kCTIMER_Match_0
/* Definition of channel 3 ID */
#define CTIMER0_MOTOR_B_MATCH_0_CHANNEL kCTIMER_Match_3
/* Definition of peripheral ID */

#define CLK_TIMER0 CLOCK_GetCTimerClkFreq(0U)
#define CLK_TIMER1 CLOCK_GetCTimerClkFreq(1U)

extern ctimer_config_t CTIMER1_MOTOR_A_config;
extern ctimer_match_config_t CTIMER1_MOTOR_A_Match_0_config;
extern ctimer_config_t CTIMER0_MOTOR_B_config;
extern ctimer_match_config_t CTIMER0_MOTOR_B_Match_0_config;

/*******************************************************************************/
/* Fonctions */
/*******************************************************************************/

void MOTEUR_TIMER_init(void);

void CTIMER1_MOTOR_A_init(void);
void CTIMER0_MOTOR_B_init(void);

void MOTOR_A_B_start(void);
void MOTOR_A_B_stop(void);

int MOTOR_CALCUL_match_value_motor (int Motor_Frequence);
int MOTOR_CALCUL_angle(int degree);

void MOTOR_A_run (uint32_t Motor_matchvalue);
void MOTOR_B_run (uint32_t Motor_matchvalue);

void MOTOR_turn_left (void);
void MOTOR_turn_right (void);

void stop_motor (void);

#endif
