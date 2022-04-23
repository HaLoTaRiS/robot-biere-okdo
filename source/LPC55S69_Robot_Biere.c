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

#include "appli_shell.h" // Shell

#include "fsl_utick.h" // Driver pour utick
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"	   // Task OS

#include "fsl_shell.h"

/* TODO: insert other definitions and declarations here. */

/*******************************************************************************/
/* Task priorities. */
/*******************************************************************************/
#define task_hello_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/
TaskHandle_t xHandleHello = NULL;

static void TaskHello(void *pvParameters);

#define STACK_SIZE_HELLO 500
#define STACK_SIZE_SHELL 500

#define LED_NUMBERS  3U
#define SHELL_Printf PRINTF
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void Led_Init(void);

static shell_status_t LedControl(shell_handle_t shellHandle, int32_t argc, char **argv);

/*******************************************************************************
 * Variables SHELL
 ******************************************************************************/
SHELL_COMMAND_DEFINE(led,
		"\r\n\"led arg1 arg2\":\r\n Usage:\r\n    arg1: 1|2|3|4...         "
		"   Led index\r\n    arg2: on|off                Led status\r\n",
		LedControl,
		2);

SDK_ALIGN(static uint8_t s_shellHandleBuffer[SHELL_HANDLE_SIZE], 4);
static shell_handle_t s_shellHandle;

extern serial_handle_t g_serialHandle;

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
		SHELL_Printf("ROBOT-BIERE>> Bonjour Maitre : Veux-tu une bière ? \r\n",count);
		LED_GREEN_ON();
		vTaskDelay(200/portTICK_PERIOD_MS);
		LED_BLUE_ON();
		vTaskDelay(200/portTICK_PERIOD_MS);
		LED_RED_ON();
		vTaskDelay(200/portTICK_PERIOD_MS);
		LED_GREEN_OFF();
		vTaskDelay(200/portTICK_PERIOD_MS);
		LED_BLUE_OFF();
		vTaskDelay(200/portTICK_PERIOD_MS);
		LED_RED_OFF();
		vTaskDelay(200/portTICK_PERIOD_MS);
		vTaskSuspend(xHandleHello);
	}
}

/*******************************************************************************/
/* Tache Shell */
/******************************************************************************/
void vTaskShell(void * p) {
	//	ShellInit();
	//	ShellAdd('f', fonction, "Une fonction inutile");
	//	ShellAdd('a', addition, "Ma super addition");
	//
	//	ShellProcess();
	/* Init SHELL */
	s_shellHandle = &s_shellHandleBuffer[0];

	SHELL_Init(s_shellHandle, g_serialHandle, "ROBOT-BIERE>> ");
	/* Add new command to commands list */
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(led));

	//Commande dans le shell : Moteur
//	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(run));
//	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(left));
//	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(right));
//	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(stop));

	//Commande dans le shell : bras

	//Commande dans le shell : I2C


#if !(defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
	SHELL_Task(s_shellHandle);
#endif

}

static shell_status_t LedControl(shell_handle_t shellHandle, int32_t argc, char **argv)
{
	int32_t kLedIndex = ((int32_t)atoi(argv[1]));
	char *kLedCommand = argv[2];

	/* Check second argument to control led */
	switch (kLedIndex)
	{
#if defined(LED_NUMBERS) && LED_NUMBERS > 0
	case 1:
		if (strcmp(kLedCommand, "on") == 0)
		{
			LED_RED_ON();
		}
		else if (strcmp(kLedCommand, "off") == 0)
		{
			LED_RED_OFF();
		}
		else
		{
			SHELL_Printf("Control conmmand is wrong!\r\n");
		}
		break;
#endif
#if defined(LED_NUMBERS) && LED_NUMBERS > 1
	case 2:
		if (strcmp(kLedCommand, "on") == 0)
		{
			LED_GREEN_ON();
		}
		else if (strcmp(kLedCommand, "off") == 0)
		{
			LED_GREEN_OFF();
		}
		else
		{
			SHELL_Printf("Control conmmand is wrong!\r\n");
		}
		break;
#endif
#if defined(LED_NUMBERS) && LED_NUMBERS > 2
	case 3:
		if (strcmp(kLedCommand, "on") == 0)
		{
			LED_BLUE_ON();
		}
		else if (strcmp(kLedCommand, "off") == 0)
		{
			LED_BLUE_OFF();
		}
		else
		{
			SHELL_Printf("Control conmmand is wrong!\r\n");
		}
		break;
#endif
#if defined(LED_NUMBERS) && LED_NUMBERS > 3
	case 4:
		if (strcmp(kLedCommand, "on") == 0)
		{
			LED_4_ON();
		}
		else if (strcmp(kLedCommand, "off") == 0)
		{
			LED_4_OFF();
		}
		else
		{
			SHELL_Printf("Control conmmand is wrong!\r\n");
		}
		break;
#endif
	default:
		SHELL_Printf("LED index is wrong\r\n");
		break;
	}
	return kStatus_SHELL_Success;
}


void shell_init(void){

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

	SHELL_Printf("\r\nINFO >> Initialisation ...\r\n");

	BaseType_t xReturned;	// Pour création des tasks

	/**************** Task Shell ****************/
	TaskHandle_t xHandleShell = NULL;

	xReturned = xTaskCreate(
			vTaskShell,
			"Shell",
			STACK_SIZE_SHELL,
			( void * ) NULL,
			1,
			&xHandleShell );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		SHELL_Printf("Task Shell creation error: Could not allocate required memory\r\n");
	}

	/**************** Task Hello ****************/

	int DELAY_TASK_HELLO = 500;

	xReturned = xTaskCreate(
			TaskHello,
			"Tache Hello",
			STACK_SIZE_HELLO,
			(void *) DELAY_TASK_HELLO,
			task_hello_PRIORITY,
			&xHandleHello );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task Hello creation : Could not allocate required memory\r\n");
	}

	SHELL_Printf("INFO >> OS FreeRTOS Starting ... V1.0\r\n");
	SHELL_Printf("SYSTEM >> Robot Biere\r\n");
	SHELL_Printf("SYSTEM >> Version BETA 1.1\r\n\r\n");

	// Task hello initialisation
	vTaskResume(xHandleHello); // active une task Hello
	//  Rappel des fonctions disponibles :
	//	vTaskResume
	//	vTaskSuspend
	//	vTaskDelete
	//	vTaskDelay

	vTaskStartScheduler(); 	// On lance l'OS

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
