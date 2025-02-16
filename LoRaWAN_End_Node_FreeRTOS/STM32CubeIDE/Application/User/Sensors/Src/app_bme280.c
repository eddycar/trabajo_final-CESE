/*
 * I2C.c
 *
 *  Created on: Sep 30, 2024
 *      Author: eddyc
 */
#include <app_bme280.h>
#include "string.h"
#include "i2c.h"

#define MEASUREMENT_PERIOD_TIME 40

uint8_t rslt = BME280_OK;
bme280_dev_t s_dev;
uint8_t id = BME280_I2C_ADDR_PRIM;

UTIL_TIMER_Object_t measurementTimer;

static void onMeasurementTimer(void *param);

void initialize_bme280_sensor(void) {
	s_dev.intf = BME280_I2C_INTF;
	s_dev.read = i2c_read;
	s_dev.write = i2c_write;
	s_dev.delay_ms = user_delay_ms;
	s_dev.intf_ptr = &id;

	UTIL_TIMER_Create(&measurementTimer, MEASUREMENT_PERIOD_TIME, UTIL_TIMER_ONESHOT, onMeasurementTimer, NULL);
	/**
	 * @brief  It reads the chip-id and calibration data from the sensor.
	 *
	 */
	rslt = bme280_init(&s_dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to initialize the device (code %d)\r\n", rslt);
	}

	rslt = configure_forced_mode_data_acquisition(&s_dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to stream sensor data (code %d)\r\n", rslt);
	}
	APP_LOG(TS_OFF, VLEVEL_M, "BME280 initialized\r\n");
}

void user_delay_ms(uint32_t period, void *tmr_intf_ptr) {
	HAL_Delay(period/1000);
}

int8_t configure_forced_mode_data_acquisition(bme280_dev_t *dev) {
	int8_t rslt;
	struct bme280_settings settings = { 0 };

	/* Get the current sensor settings */
	rslt = bme280_get_sensor_settings(&settings, dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to get sensor settings (code %d)\r\n", rslt);
		return rslt;
	}

	/* Recommended mode of operation: Weather monitoring */
	settings.filter = BME280_FILTER_COEFF_OFF;
	settings.osr_h = BME280_OVERSAMPLING_1X;
	settings.osr_p = BME280_OVERSAMPLING_1X;
	settings.osr_t = BME280_OVERSAMPLING_1X;

	/* Set the sensor settings */
	rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to set sensor settings (code %d)\r\n", rslt);
		return rslt;
	}
	return rslt;
}

BME280_sensor_t print_sensor_data(bme280_data_t *comp_data) {

	BME280_sensor_t data;

	data.temperature = 0.01f * comp_data->temperature;
	data.pressure = 0.0001f * comp_data->pressure;
	data.humidity = 1.0f / 1024.0f * comp_data->humidity;

	return data;
}

BME280_sensor_t sensor_data_acquisition(void) {
	struct bme280_data comp_data;
	BME280_sensor_t BME280_data;

	/* Continuously stream sensor data */
	rslt = bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &s_dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to set sensor mode (code %d).\r\n", rslt);
	}

	/* Wait for the measurement to complete and print data @25Hz */
	//s_dev.delay_ms(40, s_dev.intf_ptr);
	UTIL_TIMER_Start(&measurementTimer);
	while (UTIL_TIMER_IsRunning(&measurementTimer));

	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &s_dev);
	if (rslt != BME280_OK) {
		APP_LOG(TS_OFF, VLEVEL_M, "Failed to get sensor data(code %d).\r\n", rslt);
	}

	BME280_data = print_sensor_data(&comp_data);

	return BME280_data;
}

static void onMeasurementTimer(void *param){
	APP_LOG(TS_OFF, VLEVEL_M, "Measurement timer expired.\r\n");
}
