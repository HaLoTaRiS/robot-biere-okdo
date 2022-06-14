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

#ifndef INC_DEVICE_SYSTEM_H
#define INC_DEVICE_SYSTEM_H


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define task_SYSTEM_PRIORITY (configMAX_PRIORITIES - 15)

#define STACK_SIZE_SYSTEM 	200		// 100 insuffisant

/*******************************************************************************/
/* Prototypes */
/******************************************************************************/
void init_system(void);


#endif
