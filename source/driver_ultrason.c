/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_ultrason.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "driver_ultrason.h"
#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"
#include "board.h"
#include "pin_mux.h"
#include "peripherals.h"

TaskHandle_t xHandleUltrasonTrig = NULL ;
TaskHandle_t xHandleUltrasonEcho = NULL ;

struct Ultrason ultrason1;
struct Ultrason ultrason2;

#define SHELL_Printf PRINTF

ctimer_callback_t ctimer_callback_table[] = {
		NULL, callback_timer2_ultrason, NULL, NULL, NULL, NULL, NULL, NULL};

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint32_t count = 0;

ctimer_match_config_t CTIMER2_ULTRASON_matchConfig0 = {
		.matchValue = 58,							// Division pour calcul en cm
		.enableCounterReset = true,
		.enableCounterStop = false,
		.outControl = kCTIMER_Output_Toggle,
		.outPinInitState = false,
		.enableInterrupt = true
};


/*******************************************************************************
 * Code
 ******************************************************************************/

void init_ultrason(void){

	ultrason1.flag = false;
	ultrason1.countCycleFinal= 0;
	ultrason1.countCycleTemp= 0;

	ultrason2.flag = false;
	ultrason2.countCycleFinal= 0;
	ultrason2.countCycleTemp= 0;

	ctimer_config_t CTIMER2_ULTRASON_config;
	BaseType_t xReturned;

	/**************** Task Ultrason Trig ****************/
	xReturned = xTaskCreate(
			vTaskUltrasonTrig,
			"Task Ultrason Trig",
			STACK_SIZE_ULTRASON_TRIG,
			(void *) NULL,
			task_ULTRASON_TRIG_PRIORITY,
			&xHandleUltrasonTrig);

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task Ultrason Trig creation : Could not allocate required memory\r\n");
	}
	// active la task UltrasonTrig
	vTaskResume(xHandleUltrasonTrig);

	/**************** Task Ultrason Echo ****************/
	xReturned = xTaskCreate(
			vTaskUltrasonEcho,
			"Task Ultrason Echo",
			STACK_SIZE_ULTRASON_ECHO,
			(void *) NULL,
			task_ULTRASON_ECHO_PRIORITY,
			&xHandleUltrasonEcho);

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task Ultrason Echo creation : Could not allocate required memory\r\n");
	}
	// active la task Ultrason 1 Echo
	vTaskSuspend(xHandleUltrasonEcho);

	// Init Timer2
	CTIMER_GetDefaultConfig(&CTIMER2_ULTRASON_config);
	CTIMER_Init(CTIMER2_ULTRASON_PERIPHERAL, &CTIMER2_ULTRASON_config);
	CTIMER_RegisterCallBack(CTIMER2_ULTRASON_PERIPHERAL, &ctimer_callback_table[0], kCTIMER_MultipleCallback);
	CTIMER_SetupMatch(CTIMER2_ULTRASON_PERIPHERAL, CTIMER_MAT0_OUT, &CTIMER2_ULTRASON_matchConfig0);

}


/******************************************************************************/
/* Task Ultrason Trigger                                                      */
/******************************************************************************/
void vTaskUltrasonTrig(void *pvParameters)
{
	SHELL_Printf("INFO >> Starting task ULTRASON Trig\r\n");
	while (1) {

		// Valeur Ultrason N°1
		ULTRASON_1_TRIG_ENABLE();
		vTaskDelay(1/portTICK_PERIOD_MS);
		ULTRASON_1_TRIG_DISABLED();
		vTaskDelay(30/portTICK_PERIOD_MS);
		CTIMER_StopTimer(CTIMER2_ULTRASON_PERIPHERAL);
		ultrason1.countCycleFinal = ultrason1.countCycleTemp;

		// Valeur Ultrason N°2
		ULTRASON_2_TRIG_ENABLE();
		vTaskDelay(1/portTICK_PERIOD_MS);
		ULTRASON_2_TRIG_DISABLED();
		vTaskDelay(30/portTICK_PERIOD_MS);
		CTIMER_StopTimer(CTIMER2_ULTRASON_PERIPHERAL);
		ultrason2.countCycleFinal = ultrason2.countCycleTemp;

	}
}

/******************************************************************************/
/* Task Ultrason 1 - Echo                                                     */
/******************************************************************************/

//Task Echo distance en CM
void vTaskUltrasonEcho(void *pvParameters)
{
	while (1) {
		vTaskDelay(100/portTICK_PERIOD_MS);

	}
}

void callback_timer2_ultrason(uint32_t flags)
{
	if (GPIO_PinRead(BOARD_ULTRASON_1_ECHO_GPIO, BOARD_ULTRASON_1_ECHO_GPIO_PORT,BOARD_ULTRASON_1_ECHO_GPIO_PORT_PIN)){
		ultrason1.countCycleTemp=count;
	}
	if (GPIO_PinRead(BOARD_ULTRASON_2_ECHO_GPIO, BOARD_ULTRASON_2_ECHO_GPIO_PORT,BOARD_ULTRASON_2_ECHO_GPIO_PORT_PIN)){
		ultrason2.countCycleTemp=count;
	}
	count++;
}
