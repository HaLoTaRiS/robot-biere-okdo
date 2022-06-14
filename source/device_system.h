/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_system.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */

#include "fsl_debug_console.h"
#include "fsl_shell.h"
#include "FreeRTOS.h"  // OS FreeRTOS
#include "task.h"	   // Task OS

#ifndef INC_DEVICE_SYSTEM_H
#define INC_DEVICE_SYSTEM_H


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define task_SYSTEM_PRIORITY (configMAX_PRIORITIES - 1)

#define STACK_SIZE_SYSTEM 300
#define SHELL_Printf PRINTF

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/
void init_system(void);
void vTaskSystem(void *pvParameters);


#endif
