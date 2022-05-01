/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : appli_shell.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#ifndef INC_ROBOT_SHELL_H
#define INC_ROBOT_SHELL_H

#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"	   // Task OS

extern serial_handle_t g_serialHandle;

#define LED_NUMBERS  3U
#define SHELL_Printf PRINTF

/*******************************************************************************/
/* Task priorities. */
/*******************************************************************************/
#define task_HELLO_PRIORITY (configMAX_PRIORITIES - 1)
#define task_MOTOR_RUN_PRIORITY (configMAX_PRIORITIES - 11)
#define task_MOTOR_LEFT_PRIORITY (configMAX_PRIORITIES - 12)
#define task_MOTOR_RIGHT_PRIORITY (configMAX_PRIORITIES - 12)
#define task_VL53L0X_PRIORITY (configMAX_PRIORITIES - 10)

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/

#define STACK_SIZE_HELLO 200
#define STACK_SIZE_SHELL 500
#define STACK_SIZE_MOTOR_RUN 400
#define STACK_SIZE_MOTOR_LEFT 400
#define STACK_SIZE_MOTOR_RIGHT 400
#define STACK_SIZE_VL53L0X 400


/*******************************************************************************
 * Prototypes SHELL
 ******************************************************************************/
shell_status_t LedControl(shell_handle_t shellHandle, int32_t argc, char **argv);
shell_status_t MotorRun(shell_handle_t shellHandle, int32_t argc, char **argv);
shell_status_t MotorLeft(shell_handle_t shellHandle, int32_t argc, char **argv);
shell_status_t MotorRight(shell_handle_t shellHandle, int32_t argc, char **argv);
shell_status_t MotorStop(shell_handle_t shellHandle, int32_t argc, char **argv);
shell_status_t VL53L0X(shell_handle_t shellHandle, int32_t argc, char **argv);

/*******************************************************************************
 * Fonction  SHELL
 ******************************************************************************/
void init_shell(void);

/*******************************************************************************
 * Task  SHELL
 ******************************************************************************/

void vTaskShell(void * p);
void vTaskHello(void *pvParameters);

void vTaskMotorRun(void *pvParameters);
void vTaskMotorLeft(void *pvParameters);
void vTaskMotorRight(void *pvParameters);
void vTaskVL53L0X(void *pvParameters);


#endif
