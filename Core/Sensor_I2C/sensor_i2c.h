/*
 * sensor_i2c.h
 *
 *  Created on: Dec 23, 2024
 *      Author: SANG HUYNH
 */

#ifndef SENSOR_I2C_SENSOR_I2C_H_
#define SENSOR_I2C_SENSOR_I2C_H_

#include "i2c.h"
#include "lsm6dsox.h"
#include "bmp390.h"
#include "bme280.h"
#include "h3lis331dl.h"
#include "h250.h"
#include "k33.h"

extern LSM6DSOX_Data_t LSM6DSOX_Data;
extern BME280_Data_t BME280_Data;
extern H3LIS331DL_Data_t H3LIS331DL_Data;
extern H250_I2C_Data_t H250_I2C_Data;
//extern H250_UART_Data_t H250_UART_Data;
extern K33_Data_t K33_Data;

void Sensor_I2C_Init(void);

#endif /* SENSOR_I2C_SENSOR_I2C_H_ */
