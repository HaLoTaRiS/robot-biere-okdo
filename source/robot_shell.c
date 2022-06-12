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

#include "driver_vl53l0x.h"
#include "device_xl320.h"
#include "middleware_ic2.h"
#include "middleware_uart.h"
#include "driver_ultrason.h"

// Switch détection biere
#include "device_switch.h"

#define VL53L0X_SINGLE

//#include "FreeRTOS.h"  // OS FreeRTOS
//#include "task.h"	   // Task OS

extern SDK_ALIGN(uint8_t s_shellHandleBuffer[SHELL_HANDLE_SIZE], 4);
extern shell_handle_t s_shellHandle;
TaskHandle_t xHandleSystem;
TaskHandle_t xHandleMotorRun = NULL;
TaskHandle_t xHandleMotorLeft = NULL;
TaskHandle_t xHandleMotorRight = NULL;
TaskHandle_t xHandleMotorStop = NULL;
TaskHandle_t xHandleVL53L0X = NULL;
TaskHandle_t xHandleXL320 = NULL;

int32_t angle;
int32_t vitesse;
uint8_t flag_run_stop = 0;

extern i2c_master_handle_t i2c_fc4_handle;



shell_status_t MotorRun(shell_handle_t shellHandle, int32_t argc, char **argv) {

	int32_t sens = ((int32_t)atoi(argv[1]));
	vitesse = ((int32_t)atoi(argv[2]));

	flag_run_stop=1;

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

	angle = ((int32_t)atoi(argv[1]));

	MOTOR_turn_left();
	vTaskResume(xHandleMotorLeft);

	return kStatus_SHELL_Success;
}

shell_status_t MotorRight(shell_handle_t shellHandle, int32_t argc, char **argv) {
	angle = ((int32_t)atoi(argv[1]));

	MOTOR_turn_right();

	vTaskResume(xHandleMotorRight);

	return kStatus_SHELL_Success;

}

shell_status_t MotorStop(shell_handle_t shellHandle, int32_t argc, char **argv) {
	if (flag_run_stop == 1) {
		flag_run_stop = 0;
	}
	return kStatus_SHELL_Success;
}

shell_status_t VL53L0X(shell_handle_t shellHandle, int32_t argc, char **argv){
	static int on=0;
	if (on) {
		vTaskSuspend (xHandleVL53L0X);
	}
	else {
		vTaskResume (xHandleVL53L0X);
	}
	on = !on;
	return kStatus_SHELL_Success;
}

shell_status_t XL320(shell_handle_t shellHandle, int32_t argc, char **argv){

	//	uart_write_xl320(XL320_ADDR_LED, 1);
	//	uart_write_xl320(XL320_DATA_LED_BLUE, 1);

	//	uint8_t tx_msg[14] = {0};
	//
	//	// Example code ascii : HELLO BAPTISTE
	//	tx_msg[0] = 0x48;	// H
	//	tx_msg[1] = 0x45;	// E
	//	tx_msg[2] = 0x4c;	// L
	//	tx_msg[3] = 0x4c;	// L
	//	tx_msg[4] = 0x4F;	// O
	//	tx_msg[5] = 0x20;	// Space
	//	tx_msg[6] = 0x42;	// B
	//	tx_msg[7] = 0x41;	// A
	//	tx_msg[8] = 0x50;	// P
	//	tx_msg[9] = 0x54;	// T
	//	tx_msg[10] = 0x49;	// I
	//	tx_msg[11] = 0x53;	// S
	//	tx_msg[12] = 0x54;	// T
	//	tx_msg[13] = 0x45;	// E
	//
	//	fc2_uart_transmit(&tx_msg, 14);

	angle = ((int32_t)atoi(argv[1]));

	SHELL_Printf("  Angle : %d \r\n", angle);

	uint8_t temp_valeur[2];

	// convert
	uint32_t temp;
	temp = (uint32_t)(angle) * 1023;
	temp /= 300;

	// Valeur sur deux bits
	temp_valeur[0] = temp & 0xFF;
	temp_valeur[1] = (temp >> 8) & 0xFF;

	// Transmission sur l'uart:
	XL320_TX_ENABLE();
	uart_write_xl320(0x01,0x1E,temp_valeur,2);
	XL320_TX_DISABLED();

	return kStatus_SHELL_Success;
}

shell_status_t ultrason(shell_handle_t shellHandle, int32_t argc, char **argv){
	SHELL_Printf("Ultrason 1 : Distance %d cm\r\n", ultrason1.countCycleFinal);
	SHELL_Printf("Ultrason 2 : Distance %d cm\r\n", ultrason2.countCycleFinal);
	return kStatus_SHELL_Success;
}


/*******************************************************************************
 * Variables SHELL
 ******************************************************************************/
SHELL_COMMAND_DEFINE(run,
		" \"run\"   | arg1 : sens  +  arg2 : distance     | Robot Run\r\n",
		MotorRun,
		2);

SHELL_COMMAND_DEFINE(left,
		" \"left\"  | arg1 : degree                       | Robot turn left\r\n",
		MotorLeft,
		1);

SHELL_COMMAND_DEFINE(right,
		" \"right\" | arg1 : degree                       | Robot turn right\r\n",
		MotorRight,
		1);

SHELL_COMMAND_DEFINE(stop,
		" \"stop\"  | nothing                             | Robot stop\r\n",
		MotorStop,
		0);

SHELL_COMMAND_DEFINE(sensor,
		" \"sensor\"| nothing                             | Read Value I2C VL53L0X\r\n",
		VL53L0X,
		0);

SHELL_COMMAND_DEFINE(bras,
		" \"bras\"  | arg1 : degree (value 15 to 270 )    | Communication Uart XL320\r\n",
		XL320,
		1);

SHELL_COMMAND_DEFINE(ultrason,
		" \"ultrason\"  | nothing                        | Lecture ultrason 1 & 2\r\n",
		ultrason,
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

	/**************** Task System ****************/

	int DELAY_TASK_SYSTEM = 500;

	xReturned = xTaskCreate(
			vTaskSystem,
			"Task System",
			STACK_SIZE_SYSTEM,
			(void *) DELAY_TASK_SYSTEM,
			task_SYSTEM_PRIORITY,
			&xHandleSystem );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task System creation : Could not allocate required memory\r\n");
	}
	// active la task System
	vTaskResume(xHandleSystem);

	/**************** Task Motor Run ****************/
	xReturned = xTaskCreate(
			vTaskMotorRun,
			"Task Motor Run",
			STACK_SIZE_MOTOR_RUN,
			(void *) NULL,
			task_MOTOR_RUN_PRIORITY,
			&xHandleMotorRun );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorRun creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleMotorRun);

	/**************** Task Motor Left ****************/
	xReturned = xTaskCreate(
			vTaskMotorLeft,
			"Task Motor Left",
			STACK_SIZE_MOTOR_RUN,
			(void *) NULL,
			task_MOTOR_LEFT_PRIORITY,
			&xHandleMotorLeft );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorLeft creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleMotorLeft);

	/**************** Task Motor Right ****************/
	xReturned = xTaskCreate(
			vTaskMotorRight,
			"Task Motor Right",
			STACK_SIZE_MOTOR_RIGHT,
			(void *) NULL,
			task_MOTOR_RIGHT_PRIORITY,
			&xHandleMotorRight );

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task MotorRight creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleMotorRight);

	/**************** Task VL53L0X ****************/
	xReturned = xTaskCreate(
			vTaskVL53L0X,
			"Task I2C VL53L0X",
			STACK_SIZE_VL53L0X,
			(void *) NULL,
			task_VL53L0X_PRIORITY,
			&xHandleVL53L0X);

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task VL53L0X creation : Could not allocate required memory\r\n");
	}
	vTaskSuspend(xHandleVL53L0X);

}


/*******************************************************************************/
/* Tache Shell */
/******************************************************************************/
void vTaskShell(void * p) {
	s_shellHandle = &s_shellHandleBuffer[0];

	SHELL_Init(s_shellHandle, g_serialHandle, "ROBOT-BIERE>> ");
	//Commande dans le shell : Moteur
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(run));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(left));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(right));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(stop));

	//Commande dans le shell : bras
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(bras));

	//Commande dans le shell : I2C
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(sensor));
	SHELL_RegisterCommand(s_shellHandle, SHELL_COMMAND(ultrason));

#if !(defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
	SHELL_Task(s_shellHandle);
#endif

}


/******************************************************************************/
/* Task System                                                                 */
/* @brief : just test FreeRTOS + uart communication + Gpio LED + task         */
/******************************************************************************/
void vTaskSystem(void *pvParameters)
{
	int count =0;
	// Phase initialisation System
	uint8_t temp = 0;
	SHELL_Printf("ROBOT-BIERE>> Bonjour Maitre : Veux-tu une bière ? \r\n",count);
	LED_GREEN_ON();
	XL320_TX_ENABLE();
	temp = XL320_DATA_LED_GREEN;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp, 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	LED_BLUE_ON();
	temp = XL320_DATA_LED_BLUE;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp , 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	LED_RED_ON();
	temp = XL320_DATA_LED_RED;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp , 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	LED_GREEN_OFF();
	temp = XL320_DATA_LED_YELLOW;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp , 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	LED_BLUE_OFF();
	temp = XL320_DATA_LED_CYAN;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp , 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	LED_RED_OFF();
	temp = XL320_DATA_LED_PURPLE;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp , 1);
	vTaskDelay(200/portTICK_PERIOD_MS);
	temp = XL320_DATA_LED_OFF;
	uart_write_xl320(0x01, XL320_ADDR_LED, &temp, 1);
	XL320_TX_DISABLED();
	while(1) {

		// Détection présence bière
		if (GPIO_PinRead(BOARD_SWITCH_BIERE_GPIO, BOARD_SWITCH_BIERE_GPIO_PORT,BOARD_SWITCH_BIERE_GPIO_PORT_PIN ) == 0x0){
			if (service_beer == false) {
				SHELL_Printf("ROBOT-BIERE>> Une bière est détectée !\r\n");
				service_beer = true;
				// Nota : Commande UART pour fermer la pince ?!
				//
				// Transmettre l'information à la Jetson
			}
		}
		else {
			if (service_beer == true) {
				SHELL_Printf("ROBOT-BIERE>> Je n'ai plus de bière ! Commande en chez Amazon ! \r\n");
				service_beer = false;
				//
				// Transmettre l'information à la Jetson
			}
		}

		// Lecture des capteurs XL053L0X Transfert vers Jetson

		vTaskDelay(500/portTICK_PERIOD_MS);


	}
}




/******************************************************************************/
/* Task MotorRun                                                              */
/******************************************************************************/
void vTaskMotorRun(void *pvParameters)
{
	const uint32_t min_speed = 200;
	const uint32_t max_speed = 1500;
	uint32_t var_speed= 200 ;

	if (vitesse < 200){
		vitesse = 200;
	}
	else if (vitesse > 1500 ){
		vitesse = 1500;
	}

	while(1){

		SHELL_Printf("ROBOT-BIERE >> Motor A/B : START\r\n");
		MOTOR_A_B_start();
		while (var_speed<=vitesse){

			MOTOR_A_run(MOTOR_CALCUL_match_value_motor (var_speed));
			MOTOR_B_run(MOTOR_CALCUL_match_value_motor (var_speed));

			SHELL_Printf("ROBOT-BIERE >> MOTOR A/B : %d Hz\r\n", var_speed);
			vTaskDelay(20/portTICK_PERIOD_MS);
			var_speed = var_speed + 20;
		}
		while (flag_run_stop){
			vTaskDelay(10/portTICK_PERIOD_MS);
		}

		while (var_speed>=min_speed){

			MOTOR_A_run(MOTOR_CALCUL_match_value_motor (var_speed));
			MOTOR_B_run(MOTOR_CALCUL_match_value_motor (var_speed));

			SHELL_Printf("ROBOT-BIERE >> MOTOR A/B : %d Hz\r\n", var_speed);
			vTaskDelay(20/portTICK_PERIOD_MS);
			var_speed = var_speed - 20;
		}
		SHELL_Printf("ROBOT-BIERE >> Motor A/B : STOP\r\n");
		MOTOR_A_B_stop();

		vTaskSuspend(xHandleMotorRun);
	}
}

/******************************************************************************/
/* Task MotorLeft	                                                          */
/******************************************************************************/
void vTaskMotorLeft(void *pvParameters)
{
	float var_angle;

	while(1){
		// Code a continuer pour rotation de X degre
		var_angle = 0;
		SHELL_Printf("ROBOT-BIERE >> Début Rotation Gauche\r\n");
		while (var_angle < angle){
			//			TM1637_display_all(var_angle);
			vTaskDelay(10/portTICK_PERIOD_MS);
			SHELL_Printf("ROBOT-BIERE >> Rotation Gauche %2.5f \r\n",var_angle);
			var_angle = var_angle + 0.315; //changer la valeur selon distance des roues
		}
		SHELL_Printf("ROBOT-BIERE >> Fin Rotation Gauche\r\n");
		MOTOR_A_B_stop();
		vTaskSuspend(xHandleMotorLeft);
	}
}

/******************************************************************************/
/* Task MotorRight	                                                          */
/******************************************************************************/
void vTaskMotorRight(void *pvParameters)
{
	float var_angle;
	while(1){
		// Code a continuer pour rotation de X degre
		var_angle = 0;
		SHELL_Printf("ROBOT-BIERE >> Début Rotation Droit \r\n");
		while (var_angle < angle){
			//			TM1637_display_all(var_angle);
			vTaskDelay(10/portTICK_PERIOD_MS);
			SHELL_Printf("ROBOT-BIERE >> Rotation Droit %2.5f \r\n",var_angle);
			var_angle = var_angle + 0.315; //changer la valeur selon distance des roues
		}
		SHELL_Printf("ROBOT-BIERE >> Fin Rotation Droit \r\n");
		MOTOR_A_B_stop();
		vTaskSuspend(xHandleMotorRight);
	}
}


/******************************************************************************/
/* Task VL53L0X	                                                          */
/******************************************************************************/
void vTaskVL53L0X(void *pvParameters)
{

	I2C_MasterTransferCreateHandle(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
			i2c_master_callback, NULL);

	SENSOR_1_XSHUT_ON();
	vTaskDelay(10/portTICK_PERIOD_MS);
	// Initialisation du bus I2C
	bool success = vl53l0x_init();

	uint16_t range = 0;
	while (success) {
		success = vl53l0x_read_range_single(&range);
		SHELL_Printf("range : %d\r",range);
	}




}

//static void FLEXCOMM2_init(void) {
//USART_Init(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_config, FLEXCOMM2_CLOCK_SOURCE);
//USART_TransferCreateHandle(FLEXCOMM2_PERIPHERAL, &FLEXCOMM2_handle, NULL, NULL);
//}
/*
 *
 * Problème de mémoire HEAP a analyser
 * Memory :
 * vPortFree()
 * The vPortGetHeapStats() API function provides additional information on the heap status.
 *
 * Exemple Bouton GPIO :
 *		if (GPIO_PinRead(GPIO, BOARD_SW1_PORT,BOARD_SW1_PIN ) == 0x0){
 *		Fontion();
 *		}
 *
 */
