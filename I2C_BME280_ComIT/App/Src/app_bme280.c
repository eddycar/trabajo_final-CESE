/*
 * I2C.c
 *
 *  Created on: Sep 30, 2024
 *      Author: eddyc
 */
#include <app_bme280.h>
#include "string.h"
#include "i2c.h"

uint8_t rslt = BME280_OK;
bme280_dev_t s_dev;
uint8_t id = BME280_I2C_ADDR_PRIM;

void initialize_bme280_sensor(void) {
	s_dev.intf = BME280_I2C_INTF;
	s_dev.read = i2c_read;
	s_dev.write = i2c_write;
	s_dev.delay_us = user_delay_us;
	s_dev.intf_ptr = &id;

/**
 * @brief  It reads the chip-id and calibration data from the sensor.
 * 
 */
	rslt = bme280_init(&s_dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to initialize the device (code %d).\n", rslt);
	}

	rslt = configure_forced_mode_data_acquisition(&s_dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to stream sensor data (code %d).\n", rslt);
	}
}

void user_delay_us(uint32_t period, void *intf_ptr) {
	HAL_Delay(period / 1000);
}

int8_t configure_forced_mode_data_acquisition(bme280_dev_t *dev) {
	int8_t rslt;
	struct bme280_settings settings = { 0 };

	/* Get the current sensor settings */
	rslt = bme280_get_sensor_settings(&settings, dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to get sensor settings (code %d).\n", rslt);
		return rslt;
	}

	/* Recommended mode of operation: Weather monitoring */
	settings.filter = BME280_FILTER_COEFF_OFF;
	settings.osr_h 	= BME280_OVERSAMPLING_1X;
	settings.osr_p 	= BME280_OVERSAMPLING_1X;
	settings.osr_t 	= BME280_OVERSAMPLING_1X;

	/* Set the sensor settings */
	rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to set sensor settings (code %d).\n", rslt);
		return rslt;
	}

	LOGGER_LOG("Temperature, Pressure, Humidity\n");

	return rslt;
}

void print_sensor_data(bme280_data_t *comp_data) {
	float temp;
	float press;
	float hum;

	temp = 0.01f * comp_data->temperature;
	press = 0.0001f * comp_data->pressure;
	hum = 1.0f / 1024.0f * comp_data->humidity;

	LOGGER_INFO("Temperatura: %.2f°C", temp);
	LOGGER_INFO("Presion: %.2fhPa", press);
	LOGGER_INFO("Humedad: %.2f%%\n", hum);
}

void sensor_data_acquisition(void) {
	struct bme280_data comp_data;
	/* Continuously stream sensor data */
	rslt = bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &s_dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to set sensor mode (code %d).\n", rslt);
	}

	/* Wait for the measurement to complete and print data @25Hz */
	s_dev.delay_us(40000, s_dev.intf_ptr);

	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &s_dev);
	if (rslt != BME280_OK) {
		LOGGER_LOG("Failed to get sensor data(code %d).\n", rslt);
	}

	print_sensor_data(&comp_data);
	s_dev.delay_us(1000000, s_dev.intf_ptr);
}
