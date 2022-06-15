/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_system.c
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include <middleware_usb_com.h>
#include "device_system.h"
#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"
#include "board.h"
#include "pin_mux.h"
#include "peripherals.h"

#include "device_switch.h"
#include "driver_ultrason.h"

// Pour XL320 :
#include "middleware_uart.h"
#include "device_xl320.h"

// USB config
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_device_class.h"
#include "usb_device_cdc_acm.h"
#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"

#include "device_jetson.h"

TaskHandle_t xHandleSystem = NULL ;

extern struct Ultrason ultrason1;
extern struct Ultrason ultrason2;

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t Switch_sw0_on = 0;
bool flag_main = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void init_system(void){
	/**************** Task System ****************/
	BaseType_t xReturned;	// Pour création des tasks

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
			if (service_beer == 0) {
				SHELL_Printf("Une bière est détectée !\r\nROBOT-BIERE>> ");
				// Transmettre l'information de présence beer
				service_beer = 1 ;
				USB_Transmit_Uart(JETSON_ADDR_TX_PRECENCE_BEER, JETSON_DATA_PRESENCE_BEER);
				// Ordre fermeture pince
				main_close();
				// Transmettre l'information à la Jetson Bras fermé
				USB_Transmit_Uart(JETSON_ADDR_TX_BRAS_ETAT, JETSON_DATA_BRAS_CLOSE);
				flag_main = true;
			}
		}
		else {
			if (service_beer == 1) {
				SHELL_Printf("Je n'ai plus de bière ! Commande en chez Amazon ! \r\nROBOT-BIERE>> ");
				service_beer = 0;
				USB_Transmit_Uart(JETSON_ADDR_TX_PRECENCE_BEER, JETSON_DATA_NO_BEER);
			}
		}

		if (Switch_sw0_on == 1){ // Si je recois un ordre sw0 j'ouvre la main du robot
			Switch_sw0_on = 0;
			SHELL_Printf("Ordre manuel ouverture de la main du robot !\r\nROBOT-BIERE>> ");
			USB_Transmit_Uart(JETSON_ADDR_TX_BRAS_ETAT, JETSON_DATA_BRAS_OPEN);
			main_open();
		}

		// Lecture des capteurs XL053L0X Transfert vers Jetson

		vTaskDelay(1000/portTICK_PERIOD_MS);

		USB_Transmit_Uart(JETSON_ADDR_TX_ULTRASON_1, ultrason1.countCycleFinal);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_ULTRASON_2, ultrason2.countCycleFinal);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_LASER_1, 0);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_LASER_2, 0);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_LASER_3, 0);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_LASER_4, 0);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_BRAS_ETAT, service_beer);
		vTaskDelay(10/portTICK_PERIOD_MS);
		USB_Transmit_Uart(JETSON_ADDR_TX_PRECENCE_BEER, 0);

	}
}
