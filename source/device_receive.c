/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_receive.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#include "device_receive.h"
#include "device_jetson.h"
#include "middleware_usb_com.h"
#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"
#include "board.h"
#include "pin_mux.h"
#include "peripherals.h"

#include "device_motor.h"
#include "device_xl320.h"

TaskHandle_t xHandleReceiveJetson = NULL ;

struct Jetson jetson;

extern bool flag_main;

#define SHELL_Printf PRINTF

/*******************************************************************************
 * Variables
 ******************************************************************************/

//#define JETSON_ADDR_RX_LEFT				0x4C	// Char : L
//#define JETSON_ADDR_RX_RIGHT			0x52	// Char : R
//#define JETSON_ADDR_RX_BRAS				0x53	// Char : S


/*******************************************************************************
 * Code
 ******************************************************************************/

void init_receive_data(void){
	BaseType_t xReturned;

	/**************** Task Ultrason Trig ****************/
	xReturned = xTaskCreate(
			vTaskReceiveData,
			"Task Ultrason Trig",
			STACK_SIZE_RECEIVE_DATA,
			(void *) NULL,
			task_RECEIVE_DATA_PRIORITY,
			&xHandleReceiveJetson);

	if( xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ) {
		LED_RED_ON();
		SHELL_Printf("ERROR >> Task Receive Data creation : Could not allocate required memory\r\n");
	}
	// active la task UltrasonTrig
	vTaskResume(xHandleReceiveJetson);

}


uint16_t function_convert(uint16_t data_jetson){
	uint16_t calcul = data_jetson/60;
	return calcul;

}

/******************************************************************************/
/* Task Receive DATA                                                          */
/******************************************************************************/
void vTaskReceiveData(void *pvParameters)
{
	SHELL_Printf("INFO >> Starting task Receive Data Jetson\r\n");
	while (1) {
		USB_Receive_UART(jetson.id,jetson.data);
		switch (jetson.id) {
		/*** Commande pour le bras ***/
		case JETSON_ADDR_RX_BRAS :
			// Commande pour ouvrir le bras
			if (jetson.data == JETSON_DATA_BRAS_CLOSE){
				USB_Transmit_Uart(JETSON_ADDR_TX_BRAS_ETAT, JETSON_DATA_BRAS_CLOSE);
				flag_main = true;
			}
			// Commande pour fermer le bras
			else if (jetson.data == JETSON_DATA_BRAS_OPEN){
				USB_Transmit_Uart(JETSON_ADDR_TX_BRAS_ETAT, JETSON_DATA_BRAS_OPEN);
				main_open();
			}

		/*** Commande moteur Gauche A ***/
		case JETSON_ADDR_RX_LEFT :
			if (jetson.data== 49) {
				MOTOR_A_B_stop();
			}
			else if (jetson.data < 49){
				jetson.memo_left = 49 - jetson.data;
				jetson.vitesse_left = function_convert(jetson.memo_left);
				MOTOR_A_run(jetson.vitesse_left);
				MOTOR_A_DIRECTION_ARRIERE();
			}
			else if ((jetson.data > 50) && (jetson.data <= 99)){
				jetson.memo_left = 49 - jetson.data;
				jetson.vitesse_left = function_convert(jetson.memo_left);
				MOTOR_A_run(jetson.vitesse_left);
				MOTOR_A_DIRECTION_AVANT();
			}

		/*** Commande moteur DROIT B ***/
		case JETSON_ADDR_RX_RIGHT :
			if (jetson.data== 49) {
				MOTOR_A_B_stop();
			}
			else if (jetson.data < 49){
				jetson.memo_right = 49 - jetson.data;
				jetson.vitesse_right = function_convert(jetson.memo_right);
				MOTOR_B_run(jetson.vitesse_right);
				MOTOR_B_DIRECTION_ARRIERE();
			}
			else if ((jetson.data > 50) && (jetson.data <= 99)){
				jetson.memo_right = 49 - jetson.data;
				jetson.vitesse_right = function_convert(jetson.memo_right);
				MOTOR_B_run(jetson.vitesse_right);
				MOTOR_B_DIRECTION_AVANT();
			}
		}
	}
	vTaskDelay(1/portTICK_PERIOD_MS);
}

//struct Jetson {
//	uint8_t id;
//	uint16_t data;
//	uint16_t memo_right;
//	uint16_t memo_left;
//	uint8_t sens_right;
//	uint8_t sens_left;
//	uint32_t vitesse_right;
//	uint32_t vitesse_left;
//};
