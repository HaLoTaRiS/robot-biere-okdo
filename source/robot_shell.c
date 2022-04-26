/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : appli_shell.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "robot_shell.h"
#include "board.h"
#include "peripherals.h"

#include "device_motor.h"

//#include "FreeRTOS.h"  // OS FreeRTOS
//#include "task.h"	   // Task OS

extern SDK_ALIGN(uint8_t s_shellHandleBuffer[SHELL_HANDLE_SIZE], 4);
extern shell_handle_t s_shellHandle;
extern TaskHandle_t xHandleHello;
TaskHandle_t xHandleMotorRun = NULL;
TaskHandle_t xHandleMotorLeft = NULL;
TaskHandle_t xHandleMotorRight = NULL;
TaskHandle_t xHandleMotorStop = NULL;

shell_status_t LedControl(shell_handle_t shellHandle, int32_t argc, char **argv)
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



shell_status_t MotorRun(shell_handle_t shellHandle, int32_t argc, char **argv) {


	int32_t sens = ((int32_t)atoi(argv[1]));
	int32_t vitesse = ((int32_t)atoi(argv[2]));
	SHELL_Printf("vitesse : %d \r\n",vitesse);
	run_motor_A(vitesse);

	if (sens == 1)
	{
		MOTOR_A_DIRECTION_AVANT();
		MOTOR_B_DIRECTION_AVANT();
		vTaskResume(xHandleMotorRun);
	}
	else if (sens == 2)
	{
		MOTOR_A_DIRECTION_ARRIERE();
		MOTOR_B_DIRECTION_ARRIERE();
		vTaskResume(xHandleMotorRun);
	}
	else {
		SHELL_Printf("ERROR >> Error Sens\r\n");
		LED_BLUE_ON();
	}

//	SHELL_Printf("memoire après %d\r\n",xPortGetFreeHeapSize());

	return kStatus_SHELL_Success;

}

shell_status_t MotorLeft(shell_handle_t shellHandle, int32_t argc, char **argv) {

	BaseType_t xReturned;
	// task MotorRun
	xReturned = xTaskCreate(
			vTaskMotorLeft,
			"Tache Motor Left",
			STACK_SIZE_MOTOR_RUN,
			(void *) NULL,
			task_MOTOR_LEFT_PRIORITY,
			&xHandleMotorLeft );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorLeft creation : Could not allocate required memory\r\n");
	}

	vTaskResume(xHandleMotorLeft);

	return kStatus_SHELL_Success;
}

shell_status_t MotorRight(shell_handle_t shellHandle, int32_t argc, char **argv) {
	BaseType_t xReturned;
	// task MotorRun
	xReturned = xTaskCreate(
			vTaskMotorRight,
			"Tache Motor Right",
			STACK_SIZE_MOTOR_RIGHT,
			(void *) NULL,
			task_MOTOR_RIGHT_PRIORITY,
			&xHandleMotorRight );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorRight creation : Could not allocate required memory\r\n");
	}
	return kStatus_SHELL_Success;

	vTaskResume(xHandleMotorRight);

}

shell_status_t MotorStop(shell_handle_t shellHandle, int32_t argc, char **argv) {

//	vTaskSuspend( xHandleMotorRun );

//	BaseType_t xReturned;
//	// task MotorRun
//	xReturned = xTaskCreate(
//			vTaskMotorStop,
//			"Tache Motor STOP",
//			STACK_SIZE_MOTOR_STOP,
//			(void *) NULL,
//			task_MOTOR_STOP_PRIORITY,
//			&xHandleMotorStop );
//
//	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
//		LED_RED_ON();
//		SHELL_Printf("ERROR >> Task MotorStop creation : Could not allocate required memory\r\n");
//	}
//
//	vTaskResume(xHandleMotorStop);
	SHELL_Printf("INFO >> Task Run doit s'arreter\r\n");
	vTaskSuspend(xHandleMotorRun);
	return kStatus_SHELL_Success;
}


/*******************************************************************************
 * Variables SHELL
 ******************************************************************************/
SHELL_COMMAND_DEFINE(led,
		"\r\n\"led arg1 arg2\":\r\n Usage:\r\n    arg1: 1|2|3|4...         "
		"   Led index\r\n    arg2: on|off                Led status\r\n",
		LedControl,
		2);

SHELL_COMMAND_DEFINE(run,
		" \"run\"   | arg1 : distance       | Robot Run\r\n",
		MotorRun,
		2);

SHELL_COMMAND_DEFINE(left,
		" \"left\"  | arg1 : degree         | Robot turn left\r\n",
		MotorLeft,
		1);

SHELL_COMMAND_DEFINE(right,
		" \"right\" | arg1 : degree         | Robot turn right\r\n",
		MotorRight,
		1);

SHELL_COMMAND_DEFINE(stop,
		" \"stop\"  | nothing               | Robot stop\r\n",
		MotorStop,
		0);


/*******************************************************************************
 * Variables SHELL
 ******************************************************************************/


void init_shell(void) {

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
			vTaskHello,
			"Tache Hello",
			STACK_SIZE_HELLO,
			(void *) DELAY_TASK_HELLO,
			task_HELLO_PRIORITY,
			&xHandleHello );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task Hello creation : Could not allocate required memory\r\n");
	}

	/**************** Task Motor Run ****************/
	xReturned = xTaskCreate(
			vTaskMotorRun,
			"Tache Motor Run",
			STACK_SIZE_MOTOR_RUN,
			(void *) NULL,
			task_MOTOR_RUN_PRIORITY,
			&xHandleMotorRun );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorRun creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleMotorRun);
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
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(run));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(left));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(right));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(stop));

	//Commande dans le shell : bras

	//Commande dans le shell : I2C

#if !(defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
	SHELL_Task(s_shellHandle);
#endif

}


/******************************************************************************/
/* Task Hello                                                                 */
/* @brief : just test FreeRTOS + uart communication + Gpio LED + task         */
/******************************************************************************/
void vTaskHello(void *pvParameters)
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

/******************************************************************************/
/* Task MotorRun                                                              */
/******************************************************************************/
void vTaskMotorRun(void *pvParameters)
{

	while(1){


		SHELL_Printf("INFO >> Motor Run\r\n");
//		SHELL_Printf("freq : %d \r\n ",CLOCK_GetCTimerClkFreq(1U));
		MOTOR_A_B_start();

		vTaskDelay(2000/portTICK_PERIOD_MS);
		SHELL_Printf("INFO >> Fin Motor Run\r\n");
		MOTOR_A_B_stop();

		vTaskSuspend(xHandleMotorRun);
	}
	// Ne fonctionne pas comme STM32
	//	SHELL_Printf("memoire après delete %d\r\n",xPortGetFreeHeapSize());
	//	char buf [1024];
	//	vTaskList(buf);
	//	SHELL_Printf("**************************************************\r\n");
	//	SHELL_Printf("TACHE           ETAT    PRIO    PILE    NUMERO\r\n");
	//	SHELL_Printf("**************************************************\r\n");
	//	SHELL_Printf("%s",buf);
	//	SHELL_Printf("**************************************************\r\n\r\n");
	//	SHELL_Printf("B : Blocked | R : Ready | D : Deleted | S : Suspended\r\n\r\n");

}

/******************************************************************************/
/* Task MotorLeft	                                                          */
/******************************************************************************/
void vTaskMotorLeft(void *pvParameters)
{
	SHELL_Printf("INFO >> Je suis dans Task Motor Left\r\n");
	vTaskDelay(4000/portTICK_PERIOD_MS);
	SHELL_Printf("INFO >> Fin Task Motor Left\r\n");

	vTaskDelete(xHandleMotorLeft);
}

/******************************************************************************/
/* Task MotorRight	                                                          */
/******************************************************************************/
void vTaskMotorRight(void *pvParameters)
{
	SHELL_Printf("INFO >> Je suis dans Task Motor Right\r\n");
	vTaskDelay(4000/portTICK_PERIOD_MS);
	SHELL_Printf("INFO >> Fin Task Motor Right\r\n");

	vTaskSuspend(xHandleMotorRight);
}

/******************************************************************************/
/* Task MotorStop	                                                          */
/******************************************************************************/
void vTaskMotorStop(void *pvParameters)
{

	SHELL_Printf("INFO >> Je suis dans Task Motor STOP\r\n");
	vTaskDelay(4000/portTICK_PERIOD_MS);
	SHELL_Printf("INFO >> Fin Task Motor Right\r\n");
//	vTaskDelete(xHandleMotorStop);


	vTaskSuspend( xHandleMotorRun );


//	if(xHandleMotorLeft != NULL ) {
//		vTaskDelete( xHandleMotorLeft );
//	}
//
//	if(xHandleMotorRight != NULL ) {
//		vTaskDelete( xHandleMotorRight );
//	}
	vTaskDelay(10/portTICK_PERIOD_MS);
}


/*
 *
 * Problème de mémoire HEAP a analyser
 * Memory :
 * vPortFree()
 * The vPortGetHeapStats() API function provides additional information on the heap status.
 *
 */
