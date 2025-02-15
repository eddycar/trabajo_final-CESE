/*
 * I2C.h
 *
 *  Created on: Sep 30, 2024
 *      Author: eddyc
 */

#ifndef INC_APP_BME280_H_
#define INC_APP_BME280_H_

#include <logger.h>
#include "bme280.h"

typedef struct bme280_dev  bme280_dev_t;
typedef struct bme280_data bme280_data_t;

/**
 * @brief Delays execution for a specified number of microseconds.
 * 
 * @param period Number of microseconds to delay.
 * @param intf_ptr Interface pointer containing device-specific information.
 */
void user_delay_us(uint32_t period, void *intf_ptr);

/**
 * @brief Configures the BME280 sensor for data acquisition in forced mode.
 * 
 * @param dev Pointer to the BME280 device structure.
 * @return int8_t Returns 0 on success, or a negative error code.
 */
int8_t configure_forced_mode_data_acquisition(bme280_dev_t *dev);

/**
 * @brief Prints the compensated sensor data (temperature, pressure, humidity).
 * 
 * @param comp_data Pointer to the structure containing the compensated data.
 */
void print_sensor_data(bme280_data_t *comp_data);

/**
 * @brief Initializes the BME280 sensor with the I2C interface and prepares it for data acquisition.
 * 
 * This function sets up the BME280 sensor by configuring the I2C interface, 
 * setting the appropriate function pointers for reading, writing, and delaying, 
 * and initializing the sensor. It also configures the sensor for data acquisition 
 * in forced mode.
 */
void initialize_bme280_sensor(void);

/**
 * @brief Acquires sensor data from the BME280 and prints it.
 * 
 * This function performs a forced mode measurement, waits for the measurement 
 * to complete, and then retrieves the temperature, pressure, and humidity data 
 * from the sensor. The acquired data is then printed for monitoring purposes. 
 * It also introduces a delay before the next acquisition cycle.
 */
void sensor_data_acquisition(void);

#endif /* INC_APP_BME280_H_ */
