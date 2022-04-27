/*
 *  TP FreeRTOS
 *  Jeremy VICENTE & Baptiste FRITOT
 *  tm_1637.h
 *  Drivers haut niveau d'un afficheur 7segments
 *
 *	Configuration :
 *	D15 : Horloge
 *	D14 : Data Out
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TM1637_H
#define TM1637_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "fsl_common.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"

#ifndef BOARD_AFF_SCL_GPIO
#define BOARD_AFF_SCL_GPIO GPIO
#endif
#define BOARD_AFF_SCL_GPIO_PORT 0U
#ifndef BOARD_AFF_SCL_GPIO_PIN
#define BOARD_AFF_SCL_GPIO_PIN 14U
#endif

#define AFF_SCL_ON()                                             \
		GPIO_PortSet(BOARD_AFF_SCL_GPIO, BOARD_AFF_SCL_GPIO_PORT, \
				1U << BOARD_AFF_SCL_GPIO_PIN)

#define AFF_SCL_OFF()                                          \
		GPIO_PortClear(BOARD_AFF_SCL_GPIO, BOARD_AFF_SCL_GPIO_PORT, \
				1U << BOARD_AFF_SCL_GPIO_PIN)

#ifndef BOARD_AFF_DIO_GPIO
#define BOARD_AFF_DIO_GPIO GPIO
#endif
#define BOARD_AFF_DIO_GPIO_PORT 0U
#ifndef BOARD_AFF_DIO_GPIO_PIN
#define BOARD_AFF_DIO_GPIO_PIN 13U
#endif

#define AFF_DIO_ON()                                             \
		GPIO_PortSet(BOARD_AFF_DIO_GPIO, BOARD_AFF_DIO_GPIO_PORT, \
				1U << BOARD_AFF_DIO_GPIO_PIN)

#define AFF_DIO_OFF()                                          \
		GPIO_PortClear(BOARD_AFF_DIO_GPIO, BOARD_AFF_DIO_GPIO_PORT, \
				1U << BOARD_AFF_DIO_GPIO_PIN)

#define TM1637_DELAY  	1000
#define ADDR_AUTO     	0x40
#define ADDR_FIXED    	0x44
#define STARTADDR     	0xc0

/**************definitions for brightness***********************/
#define BRIGHT_DARKEST 	0
#define BRIGHT_TYPICAL 	2
#define BRIGHTEST      	7

/************definitions for type of the 4-Digit Display*********************/
#define D4036B 			0
#define D4056A 			1

//Special characters index of tube table
#define INDEX_NEGATIVE_SIGN		16
#define INDEX_BLANK			    0 // 17 nothing ,0  zero beter for clock

/* Exported functions prototypes ---------------------------------------------*/
void TM1637_init(void);
void TM1637_display(uint8_t Seg_N,int8_t DispData);
void TM1637_display_all(uint16_t Decimal);
void TM1637_displayTime(uint8_t hours,uint8_t minutes);
void TM1637_brightness(uint8_t brightness);
void TM1637_clearDisplay(void);
void tik_delay(uint32_t i);

#endif
/*****************************END OF FILE****/
