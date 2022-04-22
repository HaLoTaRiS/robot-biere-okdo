/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : LPC55S69_Robot_Biere.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

/**
 * @file    LPC55S69_Robot_Biere.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

#include "fsl_utick.h" // Driver pour utick
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"	   // Task OS

/* TODO: insert other definitions and declarations here. */

/*******************************************************************************/
/* Task priorities. */
/*******************************************************************************/
#define task_hello_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/
static void TaskHello(void *pvParameters);

#define STACK_SIZE_HELLO 500

/*
 * @brief   Application entry point.
 */
/*******************************************************************************/
/* Tache Hello */
/******************************************************************************/
static void TaskHello(void *pvParameters)
{
	int count =0;
	while(1) {
		count++;
		PRINTF("Tache Hello appellée : %d\r\n",count);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	/* Paramètrage IO / Ctimer / Channel */
	BOARD_InitBootPins();

	/* Clock name : BOARD_Boot_Clock_ROBOT() :
	 * 	  PPL0 à 150 MHz : ON
	 * 	  Clock 12MHz    : ON
	 * 	  Clock HF 96MHz : ON
	 * 	  Clock 1 MHz 	 : ON
	 */
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	UTICK_Init(UTICK0); //Initialise Utick

	printf("INFO >> Initialisation ...\r\n");
	LED_GREEN_ON();
	LED_BLUE_ON();
	LED_RED_ON();

	LED_GREEN_OFF();
	LED_BLUE_OFF();
	LED_RED_OFF();


	TaskHandle_t xHandleHello = NULL;

	BaseType_t xReturned;

	int DELAY_TASK_HELLO = 500;

	/**************** Tache Hello ****************/
	xReturned = xTaskCreate(
			TaskHello,
			"Tache Hello",
			STACK_SIZE_HELLO,
			(void *) DELAY_TASK_HELLO,
			task_hello_PRIORITY,
			&xHandleHello );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		printf("ERROR >> Task Hello creation : Could not allocate required memory\r\n");
	}

	vTaskResume(xHandleHello); // active la tache Hello
	PRINTF("INFO >> OS FreeRTOS Starting ... V1.0\r\n");
	PRINTF("SYSTEM >> Robot Biere\r\n");
	PRINTF("SYSTEM >> Version BETA 1.0\r\n");
	vTaskStartScheduler();

	/* Force the counter to be placed into memory. */
	volatile static int i = 0 ;
	/* Enter an infinite loop, just incrementing a counter. */
	while(1) {

		i++ ;
		/* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
		__asm volatile ("nop");
	}
	return 0 ;
}
