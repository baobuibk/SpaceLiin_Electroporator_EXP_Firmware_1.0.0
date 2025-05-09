/*
 * sensor_i2c.c
 *
 *  Created on: Dec 23, 2024
 *      Author: SANG HUYNH
 */

#include "sensor_i2c.h"
#include "uart.h"
#include "board.h"

LSM6DSOX_Data_t LSM6DSOX_Data = {
    .Accel = {0, 0, 0},
    .Gyro =  {0, 0, 0}
};

BME280_Data_t BME280_Data = {
		.pressure = 0,
		.humidity = 0,
		.temperature = 0
};

H3LIS331DL_Data_t H3LIS331DL_Data = {
		.x = 0,
		.y = 0,
		.z = 0
};

H250_I2C_Data_t H250_I2C_Data = 0;
//H250_UART_Data_t H250_UART_Data;

K33_Data_t K33_Data = {
		.CO2 = 0,
		.Temp = 0,
		.RH = 0
};

void  Sensor_I2C_Init(void) {
	LL_GPIO_SetOutputPin(SENSOR1_EN_GPIO_Port, SENSOR1_EN_Pin);
	LL_GPIO_SetOutputPin(SENSOR2_EN_GPIO_Port, SENSOR2_EN_Pin);
	I2C_Status_t I2C_status = I2C_Success;
	I2C_status = LSM6DSOX_Init();
	if (I2C_status == I2C_Error) UART_SendStringRing(EXP_UART_CONSOLE_HANDLE, "LSM6DSOX is error \r\n");
	I2C_status = BME280_Init();
	if (I2C_status == I2C_Error) UART_SendStringRing(EXP_UART_CONSOLE_HANDLE, "BME280 is error \r\n");
	I2C_status = H3LIS331DL_Init();
	if (I2C_status == I2C_Error) UART_SendStringRing(EXP_UART_CONSOLE_HANDLE, "H3LIS331DL is error \r\n");

#ifdef H250_UART
	H250_UART_Init(EXP_UART_CO2_HANDLE);
#endif

}
