#ifndef VL53L0X_H
#define VL53L0X_H

#include <stdbool.h>
#include <stdint.h>

#define VL53L0X_OUT_OF_RANGE (8190)

bool vl53l0x_init(void);

/**
 * Does a single range measurement
 * @param range contains the measured range or VL53L0X_OUT_OF_RANGE
 *        if out of range.
 * @return True if success, False if error
 * @note   Polling-based
 */
bool vl53l0x_read_range_single(uint16_t *range);


#endif /* VL53L0X_H */

#ifndef INC_DEVICE_VL53L0X_H
#define INC_DEVICE_VL53L0X_H

/******** Input ********/
/* Declaration SENSOR_1_INT on GPIO1_0 */
#ifndef BOARD_SENSOR_1_INT_GPIO
#define BOARD_SENSOR_1_INT_GPIO GPIO
#endif
#define BOARD_SENSOR_1_INT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_1_INT_GPIO_PIN
#define BOARD_SENSOR_1_INT_GPIO_PIN 0U
#endif
#define BOARD_SENSOR_1_INT_NAME        "SENSOR 1 INT"
#define BOARD_SENSOR_1_INT_IRQ         PIN_INT1_IRQn
#define BOARD_SENSOR_1_INT_IRQ_HANDLER PIN_INT1_IRQHandler

/* Declaration SENSOR_2_INT on GPIO1_1 */
#ifndef BOARD_SENSOR_2_INT_GPIO
#define BOARD_SENSOR_2_INT_GPIO GPIO
#endif
#define BOARD_SENSOR_2_INT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_2_INT_GPIO_PIN
#define BOARD_SENSOR_2_INT_GPIO_PIN 1U
#endif
#define BOARD_SENSOR_2_INT_NAME        "SENSOR 2 INT"
#define BOARD_SENSOR_2_INT_IRQ         PIN_INT1_IRQn
#define BOARD_SENSOR_2_INT_IRQ_HANDLER PIN_INT1_IRQHandler
#define BOARD_SENSOR_2_INT_GPIO_PININT_INDEX 1

/* Declaration SENSOR_3_INT on GPIO1_3 */
#ifndef BOARD_SENSOR_3_INT_GPIO
#define BOARD_SENSOR_3_INT_GPIO GPIO
#endif
#define BOARD_SENSOR_3_INT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_3_INT_GPIO_PIN
#define BOARD_SENSOR_3_INT_GPIO_PIN 3U
#endif
#define BOARD_SENSOR_3_INT_NAME        "SENSOR 3 INT"
#define BOARD_SENSOR_3_INT_IRQ         PIN_INT1_IRQn
#define BOARD_SENSOR_3_INT_IRQ_HANDLER PIN_INT1_IRQHandler
#define BOARD_SENSOR_3_INT_GPIO_PININT_INDEX 1

/* Declaration SENSOR_4_INT on GPIO1_8 */
#ifndef BOARD_SENSOR_4_INT_GPIO
#define BOARD_SENSOR_4_INT_GPIO GPIO
#endif
#define BOARD_SENSOR_4_INT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_4_INT_GPIO_PIN
#define BOARD_SENSOR_4_INT_GPIO_PIN 8U
#endif
#define BOARD_SENSOR_4_INT_NAME        "SENSOR 4 INT"
#define BOARD_SENSOR_4_INT_IRQ         PIN_INT1_IRQn
#define BOARD_SENSOR_4_INT_IRQ_HANDLER PIN_INT1_IRQHandler
#define BOARD_SENSOR_4_INT_GPIO_PININT_INDEX 1

/******** OUTPUT CONFIGURATION ********/
/* Declaration SENSOR_1_XSHUT on GPIO0_7 */
#ifndef BOARD_SENSOR_1_XSHUT_GPIO
#define BOARD_SENSOR_1_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_1_XSHUT_GPIO_PORT 0U
#ifndef BOARD_SENSOR_1_XSHUT_GPIO_PIN
#define BOARD_SENSOR_1_XSHUT_GPIO_PIN 7U
#endif

/* Declaration SENSOR_2_XSHUT on GPIO1_1 */
#ifndef BOARD_SENSOR_2_XSHUT_GPIO
#define BOARD_SENSOR_2_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_2_XSHUT_GPIO_PORT 0U
#ifndef BOARD_SENSOR_2_XSHUT_GPIO_PIN
#define BOARD_SENSOR_2_XSHUT_GPIO_PIN 31U
#endif

/* Declaration SENSOR_3_XSHUT on GPIO1_2 */
#ifndef BOARD_SENSOR_3_XSHUT_GPIO
#define BOARD_SENSOR_3_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_3_XSHUT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_3_XSHUT_GPIO_PIN
#define BOARD_SENSOR_3_XSHUT_GPIO_PIN 2U
#endif

/* Declaration SENSOR_4_XSHUT on GPIO1_5 */
#ifndef BOARD_SENSOR_4_XSHUT_GPIO
#define BOARD_SENSOR_4_XSHUT_GPIO GPIO
#endif
#define BOARD_SENSOR_4_XSHUT_GPIO_PORT 1U
#ifndef BOARD_SENSOR_4_XSHUT_GPIO_PIN
#define BOARD_SENSOR_4_XSHUT_GPIO_PIN 8U
#endif


// Fonction

/********* SENSOR_2_XSHUT GPIO 0_7 *********/
#define SENSOR_1_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_1_XSHUT_GPIO, BOARD_SENSOR_1_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_1_XSHUT_GPIO_PIN)

#define SENSOR_1_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_1_XSHUT_GPIO, BOARD_SENSOR_1_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_1_XSHUT_GPIO_PIN)

/********* SENSOR_2_XSHUT GPIO 0_31 *********/
#define SENSOR_2_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_2_XSHUT_GPIO, BOARD_SENSOR_2_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_2_XSHUT_GPIO_PIN)

#define SENSOR_2_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_2_XSHUT_GPIO, BOARD_SENSOR_2_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_2_XSHUT_GPIO_PIN)

/********* SENSOR_3_XSHUT GPIO 1_2 *********/
#define SENSOR_3_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_3_XSHUT_GPIO, BOARD_SENSOR_3_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_3_XSHUT_GPIO_PIN)

#define SENSOR_3_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_3_XSHUT_GPIO, BOARD_SENSOR_3_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_3_XSHUT_GPIO_PIN)

/********* SENSOR_4_XSHUT GPIO 1_5 *********/
#define SENSOR_4_XSHUT_ON()                                             \
		GPIO_PortSet(BOARD_SENSOR_4_XSHUT_GPIO, BOARD_SENSOR_4_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_4_XSHUT_GPIO_PIN)

#define SENSOR_4_XSHUT_OFF()                                          \
		GPIO_PortClear(BOARD_SENSOR_4_XSHUT_GPIO, BOARD_SENSOR_4_XSHUT_GPIO_PORT, \
				1U << BOARD_SENSOR_4_XSHUT_GPIO_PIN)


void init_GINT_SENSOR(void);
void init_GINT_SENSOR(void);
bool vl53l0x_init(void);
#define VL53L0X_OUT_OF_RANGE (8190)
bool vl53l0x_read_range_single(uint16_t *range);

#endif

