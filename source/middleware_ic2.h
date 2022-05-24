/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : middleware_i2c.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#ifndef _MIDDLEWARE_I2C_H
#define _MIDDLEWARE_I2C_H

#include "fsl_i2c.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Bus I2C */
#define I2C_CLK_SRC     I2C4_BASE
#define I2C_CLK_FREQ    12000000		// 12 Mhz
#define I2C_BAUDRATE    100000			// Vitesse

#define I2C_FC4_PERIPHERAL   I2C4		// Nom du périphérique I2C FLEXCOMM4

#define VL53L0X_DEFAULT_ADDRESS (0x29)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Bus I2C */
/**** fonction pour driver VL53LX0 ****/
void I2C_InitModule(void);
void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
		status_t status, void *userData);
bool i2c_read_addr8_data8(uint8_t reg_addr, uint8_t *data);
bool i2c_write_addr8_data8(uint8_t reg_addr, uint8_t data);
bool i2c_read_addr8_data16(uint8_t reg_addr, uint16_t *data);


/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Bus I2C */


#endif



