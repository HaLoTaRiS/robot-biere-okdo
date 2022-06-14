/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_ultrason.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#ifndef INC_DRIVER_ULTRASON_H
#define INC_DRIVER_ULTRASON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "fsl_ctimer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define task_ULTRASON_TRIG_PRIORITY (configMAX_PRIORITIES - 10)
#define task_ULTRASON_ECHO_PRIORITY (configMAX_PRIORITIES - 10)

#define STACK_SIZE_ULTRASON_TRIG 120		// 100 insuffisant
#define STACK_SIZE_ULTRASON_ECHO 200



/*** ultason 1 ***/
// Output TRIG
#ifndef BOARD_ULTRASON_1_TRIG_GPIO
#define BOARD_ULTRASON_1_TRIG_GPIO GPIO
#endif
#ifndef BOARD_ULTRASON_1_TRIG_GPIO_PORT
#define BOARD_ULTRASON_1_TRIG_GPIO_PORT 1U
#endif
#ifndef BOARD_ULTRASON_1_TRIG_GPIO_PORT_PIN
#define BOARD_ULTRASON_1_TRIG_GPIO_PORT_PIN 9U
#endif

// Input ECHO
#ifndef BOARD_ULTRASON_1_ECHO_GPIO
#define BOARD_ULTRASON_1_ECHO_GPIO GPIO
#endif
#ifndef BOARD_ULTRASON_1_ECHO_GPIO_PORT
#define BOARD_ULTRASON_1_ECHO_GPIO_PORT 1U
#endif
#ifndef BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN
#define BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN 10U
#endif

/*** ultason 2 ***/
// output TRIG
#ifndef BOARD_ULTRASON_2_TRIG_GPIO
#define BOARD_ULTRASON_2_TRIG_GPIO GPIO
#endif
#ifndef BOARD_ULTRASON_2_TRIG_GPIO_PORT
#define BOARD_ULTRASON_2_TRIG_GPIO_PORT 0U
#endif
#ifndef BOARD_ULTRASON_2_TRIG_GPIO_PORT_PIN
#define BOARD_ULTRASON_2_TRIG_GPIO_PORT_PIN 14U
#endif

// input ECHO
#ifndef BOARD_ULTRASON_2_ECHO_GPIO
#define BOARD_ULTRASON_2_ECHO_GPIO GPIO
#endif
#ifndef BOARD_ULTRASON_2_ECHO_GPIO_PORT
#define BOARD_ULTRASON_2_ECHO_GPIO_PORT 0U
#endif
#ifndef BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN
#define BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN 13U
#endif


#define ULTRASON_1_TRIG_ENABLE()                                             \
		GPIO_PortSet(BOARD_ULTRASON_1_TRIG_GPIO, BOARD_ULTRASON_1_ECHO_GPIO_PORT, \
				1U << BOARD_ULTRASON_1_TRIG_GPIO_PORT_PIN)

#define ULTRASON_1_TRIG_DISABLED()                                          \
		GPIO_PortClear(BOARD_ULTRASON_1_TRIG_GPIO, BOARD_ULTRASON_1_ECHO_GPIO_PORT, \
				1U << BOARD_ULTRASON_1_TRIG_GPIO_PORT_PIN)

#define ULTRASON_2_TRIG_ENABLE()                                             \
		GPIO_PortSet(BOARD_ULTRASON_2_TRIG_GPIO, BOARD_ULTRASON_2_TRIG_GPIO_PORT, \
				1U << BOARD_ULTRASON_2_TRIG_GPIO_PORT_PIN)

#define ULTRASON_2_TRIG_DISABLED()                                          \
		GPIO_PortClear(BOARD_ULTRASON_2_TRIG_GPIO, BOARD_ULTRASON_2_TRIG_GPIO_PORT, \
				1U << BOARD_ULTRASON_2_TRIG_GPIO_PORT_PIN)

// For interrupt ultrason 1 echo
#define ULTRASON_1_ECHO_POL_MASK (1U << BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN)
#define ULTRASON_1_ECHO_ENA_MASK (1U << BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN)


// For interrupt ultrason 1 echo
#define ULTRASON_2_ECHO_POL_MASK (1U << BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN)
#define ULTRASON_2_ECHO_ENA_MASK (1U << BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN)

struct Ultrason {
	bool flag;
	uint32_t countCycleFinal;
	uint32_t countCycleTemp;
};

extern struct Ultrason ultrason1;
extern struct Ultrason ultrason2;

// For timer

#define CTIMER2_ULTRASON_PERIPHERAL          CTIMER2
#define CTIMER_MAT0_OUT kCTIMER_Match_1

extern ctimer_config_t CTIMER2_ULTRASON_config;
extern ctimer_match_config_t CTIMER2_ULTRASON_Match_0_config;

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/
void init_ultrason(void);
void vTaskUltrasonTrig(void *pvParameters);
void vTaskUltrasonEcho(void *pvParameters);
void callback_timer2_ultrason(uint32_t flags);

#endif
