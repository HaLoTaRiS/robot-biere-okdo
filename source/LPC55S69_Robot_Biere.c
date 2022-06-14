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

// Pour corriger le code dans Board.h : Inversion led Blue et RED
//#define BOARD_LED_RED_GPIO GPIO
//#define BOARD_LED_RED_GPIO_PORT 1U
//#define BOARD_LED_RED_GPIO_PIN 4U // 4 à la place de 6
//
//#define BOARD_LED_BLUE_GPIO GPIO
//#define BOARD_LED_BLUE_GPIO_PORT 1U
//#define BOARD_LED_BLUE_GPIO_PIN 6U // 6 à la place de 4
//
//#define BOARD_LED_GREEN_GPIO GPIO
//#define BOARD_LED_GREEN_GPIO_PORT 1U
//#define BOARD_LED_GREEN_GPIO_PIN 7U


#include <robot_shell.h> // Shell
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

#include "middleware_uart.h"

#include "fsl_shell.h"
#include "device_motor.h"
#include "driver_ultrason.h"
#include "device_interrupt.h"

// Config USB
#include "fsl_device_registers.h"
#include "fsl_power.h"
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_cdc_acm.h"
#include "usb_device_ch9.h"

#include "usb_device_descriptor.h"
#include "virtual_com.h"
#include "usb_phy.h"


/* TODO: insert other definitions and declarations here. */




/*******************************************************************************
 * Prototypes
 ******************************************************************************/
SDK_ALIGN(uint8_t s_shellHandleBuffer[SHELL_HANDLE_SIZE], 4);
shell_handle_t s_shellHandle;

//SDK_ALIGN(static uint8_t s_shellHandleBuffer[SHELL_HANDLE_SIZE], 4);
//static shell_handle_t s_shellHandle;
//
//extern serial_handle_t g_serialHandle;

/*
 * @brief   Application entry point.
 */


/*
 * @brief   Application entry point.
 */



int main(void) {

	/* Init board hardware. */
	/* Paramètrage IO / Ctimer / Channel */

	RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);

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

	/***** Start config usb0 *****/
	NVIC_ClearPendingIRQ(USB0_IRQn);
	NVIC_ClearPendingIRQ(USB0_NEEDCLK_IRQn);
	NVIC_ClearPendingIRQ(USB1_IRQn);
	NVIC_ClearPendingIRQ(USB1_NEEDCLK_IRQn);

	POWER_DisablePD(kPDRUNCFG_PD_USB0_PHY); /*< Turn on USB0 Phy */

	/* reset the IP to make sure it's in reset state. */
	RESET_PeripheralReset(kUSB0D_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB0HSL_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB0HMR_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB1H_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB1D_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB1_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kUSB1RAM_RST_SHIFT_RSTn);

	POWER_DisablePD(kPDRUNCFG_PD_USB0_PHY); /*< Turn on USB Phy */
	CLOCK_SetClkDiv(kCLOCK_DivUsb0Clk, 1, false);
	CLOCK_AttachClk(kFRO_HF_to_USB0_CLK);
	/* enable usb0 host clock */
	CLOCK_EnableClock(kCLOCK_Usbhsl0);
	/*According to reference mannual, device mode setting has to be set by access usb host register */
	*((uint32_t *)(USBFSH_BASE + 0x5C)) |= USBFSH_PORTMODE_DEV_ENABLE_MASK;
	/* disable usb0 host clock */
	CLOCK_DisableClock(kCLOCK_Usbhsl0);
	/***** End config usb0 *****/

	MOTEUR_TIMER_init();


	UTICK_Init(UTICK0); //Initialise Utick

	SHELL_Printf("\r\nINFO >> Initialisation ...\r\n");

	init_shell(); 		// Initialise les tasks et fonction du shell
	init_ultrason(); 	// initialise la tache qui gère les ultrasons
	fc2_uart_init(); 	// Initialise l'Uart
	init_interrupt(); 	// Initialise toutes les interruptions PIO
	init_USB_UART(); 		// Initialise le port USB

	SHELL_Printf("INFO >> OS FreeRTOS Starting ... V1.0\r\n");
	SHELL_Printf("SYSTEM >> Robot Biere\r\n");
	SHELL_Printf("SYSTEM >> Version BETA 1.2\r\n\r\n");

	// Initialisation I2C

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
