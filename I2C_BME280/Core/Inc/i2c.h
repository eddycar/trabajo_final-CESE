/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
/**
 * @brief Reads data from the I2C device at the specified register address.
 *
 * @param reg_addr The register address from which to read.
 * @param reg_data Pointer to the buffer where the read data will be stored.
 * @param len Number of bytes to read.
 * @param intf_ptr Interface pointer containing device-specific information.
 * @return int8_t Returns 0 on success, or >0 error code.
 */
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len,
		void *intf_ptr);

/**
 * @brief Writes data to the I2C device at the specified register address.
 *
 * @param reg_addr The register address to which data will be written.
 * @param reg_data Pointer to the data buffer to be written.
 * @param len Number of bytes to write.
 * @param intf_ptr Interface pointer containing device-specific information.
 * @return int8_t Returns 0 on success, or >0 error code.
 */
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
		void *intf_ptr);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

