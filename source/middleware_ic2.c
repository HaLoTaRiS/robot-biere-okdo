
#include "middleware_ic2.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Bus I2C */
i2c_master_handle_t i2c_fc4_handle;

volatile bool completionFlag = false;
volatile bool nakFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/


void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
		status_t status, void *userData) {
	/* Signal transfer success when received success status. */
	if (status == kStatus_Success) {
		completionFlag = true;
	}
	/* Signal transfer success when received success status. */
	if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak)) {
		nakFlag = true;
	}
}

void I2C_InitModule(void) {

	i2c_master_config_t i2c_FC4;
	uint32_t sourceClock = 0;

	/*
	 * i2c_FC4.baudRate_Bps = 100000U;
	 * i2c_FC4.enableStopHold = false;
	 * i2c_FC4.glitchFilterWidth = 0U;
	 * i2c_FC4.enableMaster = true;
	 */
	I2C_MasterGetDefaultConfig(&i2c_FC4);
	i2c_FC4.baudRate_Bps = I2C_BAUDRATE;
	sourceClock = I2C_CLK_FREQ;
	I2C_MasterInit(I2C_FC4_PERIPHERAL, &i2c_FC4, sourceClock);
}

bool i2c_read_addr8_data8(uint8_t reg_addr, uint8_t *read) {
	I2C_InitModule();
	i2c_master_transfer_t masterXfer;
	memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress = VL53L0X_DEFAULT_ADDRESS;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = 0;
	masterXfer.subaddressSize = 0;
	masterXfer.data = &reg_addr;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferNoStopFlag;

	I2C_MasterTransferNonBlocking(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
			&masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag)) {
	}
	nakFlag = false;

	if (completionFlag == true) {
		completionFlag = false;
		masterXfer.direction = kI2C_Read;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = read;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferRepeatedStartFlag;

		I2C_MasterTransferNonBlocking(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
				&masterXfer);

		/*  wait for transfer completed. */
		while ((!nakFlag) && (!completionFlag)) {
		}
		nakFlag = false;

		if (completionFlag == true) {
			completionFlag = false;
			//			PRINTF("Found a device\r\n");
			return true;
		} else {
			//			PRINTF("Not a successful i2c communication \r\n");
			return false;
		}
	} else {
		//		PRINTF("\r\n Don't find the device ! \r\n");
		return false;
	}
}


bool i2c_read_addr8_data16(uint8_t reg_addr, uint16_t *read){
	I2C_InitModule();
	i2c_master_transfer_t masterXfer;
	memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress = VL53L0X_DEFAULT_ADDRESS;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = 0;
	masterXfer.subaddressSize = 0;
	masterXfer.data = &reg_addr;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferNoStopFlag;

	I2C_MasterTransferNonBlocking(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
			&masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag)) {
	}
	nakFlag = false;

	if (completionFlag == true) {
		completionFlag = false;
		masterXfer.slaveAddress = VL53L0X_DEFAULT_ADDRESS;
		masterXfer.direction = kI2C_Read;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = read;
		masterXfer.dataSize = 2;
		masterXfer.flags = kI2C_TransferRepeatedStartFlag;

		I2C_MasterTransferNonBlocking(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
				&masterXfer);

		/*  wait for transfer completed. */
		while ((!nakFlag) && (!completionFlag)) {
		}
		nakFlag = false;

		if (completionFlag == true) {
			completionFlag = false;
			//			PRINTF("Found a device\r\n");
			return true;
		} else {
			//			PRINTF("Not a successful i2c communication \r\n");
			return false;
		}
	} else {
		//		PRINTF("\r\n Don't find the device ! \r\n");
		return false;
	}


}


bool i2c_write_addr8_data8(uint8_t reg_addr, uint8_t data) {

	I2C_InitModule();

	i2c_master_transfer_t masterXfer;
	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress = VL53L0X_DEFAULT_ADDRESS;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = reg_addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data = &data;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferRepeatedStartFlag;

	I2C_MasterTransferNonBlocking(I2C_FC4_PERIPHERAL, &i2c_fc4_handle,
			&masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag)) {
	}
	nakFlag = false;

	if (completionFlag == true) {
		completionFlag = false;
		//		PRINTF("Found a device\r\n");
		return true;
	}
	else {
		//		PRINTF("Not a successful i2c communication \r\n");
		return false;
	}
}
