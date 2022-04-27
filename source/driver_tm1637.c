/*
 *  TP FreeRTOS
 *  Jeremy VICENTE & Baptiste FRITOT
 *  tm_1637.c
 *  Drivers haut niveau d'un afficheur 7segments
 *
 *	Configuration :
 *	D15 : Horloge
 *	D14 : Data Out
 */

/* Includes ------------------------------------------------------------------*/
#include <driver_tm1637.h>
/* ----------------------------------------------------- */

#define DATA_PIN		GPIO_PIN_9
#define CLK_PIN			GPIO_PIN_8
#define TM1637_PORT 	GPIOB
#define POINT_ON   		1

uint8_t Cmd_SetAddr 	= STARTADDR	;
uint8_t Cmd_DispCtrl				;
uint8_t PointFlag 		= POINT_ON	; 	//_PointFlag=1:the clock point on
uint8_t _DispType  		= D4056A	;
uint8_t DecPoint					;
uint8_t BlankingFlag				;

//=========================================================================//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//=========================================================================//
//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0x3f,    // 0 0b00111111
  0x06,    // 1 0b00000110
  0x5b,    // 2 0b01011011
  0x4f,    // 3 0b01001111
  0x66,    // 4 0b01100110
  0x6d,    // 5 0b01101101
  0x7d,    // 6 0b01111101
  0x07,    // 7 0b00000111
  0x7f,    // 8 0b01111111
  0x6f,    // 9 0b01101111
  0x77,    // A 0b01110111
  0x7c,    // b 0b01111100
  0x39,    // C 0b00111001
  0x5e,    // d 0b01011110
  0x79,    // E 0b01111001
  0x71,    // F 0b01110001
  0x40,    // - 0b01000000
  0x00     // nothing 0b00000000
  };

void CLK_PIN_SET(void) {
	AFF_SCL_ON(); // CLK SET
}

void CLK_PIN_RESET(void) {
	AFF_SCL_OFF(); // CLK RESET
}

void DATA_PIN_SET(void) {
	AFF_DIO_ON(); // DATA SET
}

void DATA_PIN_RESET(void) {
	AFF_DIO_OFF(); // DATA RESET
}

//void DATA_PIN_READ(void) {
//	HAL_GPIO_ReadPin(TM1637_PORT, DATA_PIN); // DATA READ
//}

/**
  * @brief  Delay function
  * @retval void
  */
void tik_delay(uint32_t i) {
	for (int j=0;j<i;j++){
		__NOP();
	}
}
/**
  * @brief  GPIO configuration for SDA and CLK pin
  * @retval void
  */
void TM1637_init(void){
	/*
	 * GPIO is configured using stm32cube (.ioc file) \
	 * */
}
/**
  * @brief  signal to start the communication protocol
  * @retval void
  */
void TM1637_Generate_START(void)
{
	AFF_SCL_ON();
	AFF_DIO_ON();
	tik_delay(TM1637_DELAY);
	AFF_DIO_OFF();
}
/**
  * @brief  signal to stop the communication protocol
  * @retval void
  */
void TM1637_Generate_STOP(void)
{
	AFF_SCL_OFF(); // CLK RESET
	tik_delay(TM1637_DELAY);
	AFF_DIO_OFF(); // DATA RESET
	tik_delay(TM1637_DELAY);
	AFF_SCL_ON(); // CLK SET
	tik_delay(TM1637_DELAY);
	AFF_DIO_ON(); // DATA SET
}
/**
  * @brief  sending data to tm1637 module
  * @retval void
  */
void TM1637_WriteData(uint8_t data){
	uint8_t i;
    for(i=0;i<8;i++) {
    	CLK_PIN_RESET();
    	if(data & 0x01){
    		DATA_PIN_SET();
    	}
    	else {
    		DATA_PIN_RESET();
    	}
    	tik_delay(TM1637_DELAY);
    	data = data>>1;
    	CLK_PIN_SET();
    	tik_delay(TM1637_DELAY);
    }
    CLK_PIN_RESET();
	tik_delay(TM1637_DELAY);
	DATA_PIN_RESET();
//	DATA_PIN_READ(); // Commenté
	DATA_PIN_SET();
	CLK_PIN_SET();
	tik_delay(TM1637_DELAY);
	CLK_PIN_RESET();
}

/**
  * @brief
  * @retval int8_t
  */
int8_t TM1637_coding(uint8_t DispData)
{
	uint8_t PointData;
	if(PointFlag == POINT_ON)PointData = 0x80;
	else PointData = 0;
	if(DispData == 0x7f) DispData = 0x00 + PointData;
	else DispData = digitToSegment[DispData] + PointData;
	return DispData;
}
/**
  * @brief
  * @retval void
  */
void TM1637_coding_all(uint8_t DispData[])
{
	uint8_t PointData;
	uint8_t i;
	PointData =  PointFlag ? 0x80:0;
	for(i = 0;i < 4;i ++)
	{
		if(DispData[i] == 0x7f)DispData[i] = 0x00;
		else DispData[i] = digitToSegment[DispData[i]] + PointData;
	DispData[i] += 0x80;
	}
	if((_DispType == D4056A)&&(DecPoint != 3))
	{
	DispData[DecPoint] += 0x80;
	DecPoint = 3;
	}
}
/**
  * @brief
  * @retval void
  */
void separate_Digit_to_digits(int16_t Digit,uint8_t SegArray[])
{
	if((Digit > 9999)||(Digit < -999))return;
	if(Digit < 0)
	{
		SegArray[0] = INDEX_NEGATIVE_SIGN;
		Digit = (Digit & 0x7fff);
		SegArray[1] = Digit/100;
		Digit %= 100;
		SegArray[2] = Digit / 10;
		SegArray[3] = Digit % 10;
		if(BlankingFlag)
		{
			if(SegArray[1] == 0)
			{
				SegArray[1] = INDEX_BLANK;
				if(SegArray[2] == 0) SegArray[2] = INDEX_BLANK;
			}
		}
	}
	else
	{
		SegArray[0] = Digit/1000;
		Digit %= 1000;
		SegArray[1] = Digit/100;
		Digit %= 100;
		SegArray[2] = Digit / 10;
		SegArray[3] = Digit % 10;
		if(BlankingFlag)
		{
			if(SegArray[0] == 0)
			{
				SegArray[0] = INDEX_BLANK;
				if(SegArray[1] == 0)
				{
					SegArray[1] = INDEX_BLANK;
					if(SegArray[2] == 0) SegArray[2] = INDEX_BLANK;
				}
			}
		}
	}
	BlankingFlag = 1;
}
/**
  * @brief
  * @retval void
  */
void TM1637_display(uint8_t Seg_N,int8_t DispData)
{
	int8_t SegData;
	SegData = TM1637_coding(DispData);
	TM1637_Generate_START();
	TM1637_WriteData(ADDR_FIXED);
	TM1637_Generate_STOP();
	TM1637_Generate_START();
	TM1637_WriteData(Seg_N|0xc0);
	TM1637_WriteData(SegData);
	TM1637_Generate_STOP();
	TM1637_Generate_START();
	TM1637_WriteData(Cmd_DispCtrl);
	TM1637_Generate_STOP();
}
/**
  * @brief
  * @retval void
  */
void TM1637_display_all(uint16_t Digit)
{
	uint8_t SegData[4];
	uint8_t i;
	separate_Digit_to_digits(Digit,SegData);
	TM1637_coding_all(SegData);
	TM1637_Generate_START();
	TM1637_WriteData(ADDR_AUTO);
	TM1637_Generate_STOP();
	TM1637_Generate_START();
	TM1637_WriteData(Cmd_SetAddr);
	for(i=0;i < 4;i ++) {
	  TM1637_WriteData(SegData[i]);
	}
	TM1637_Generate_STOP();
	TM1637_Generate_START();
	TM1637_WriteData(Cmd_DispCtrl);
	TM1637_Generate_STOP();
}
/**
  * @brief
  * @retval void
  */
void TM1637_brightness(uint8_t brightness)
{
	Cmd_DispCtrl = 0x88 + brightness;
}
/**
  * @brief
  * @retval void
  */
void TM1637_clearDisplay(void)
{
	uint8_t i;
	for(i=0;i<4;i++)TM1637_display(i,0x7f);
}
/**
  * @brief
  * @retval void
  */
void TM1637_displayTime(uint8_t hours,uint8_t minutes)
{
	uint16_t time = (hours*100)+minutes;
	PointFlag =  PointFlag ? 0:1;
	TM1637_display_all(time);
}
/*****************************END OF FILE****/
