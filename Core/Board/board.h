/*
 * board.h
 *
 *  Created on: Nov 21, 2024
 *      Author: SANG HUYNH
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_
#include <stm32f407xx.h>
#include "lt8722.h"
#include "adg1414.h"
#include "mb85rs2mt.h"
#include "sfc5500.h"

//*****************************************************************************
// UART_CONSOLE
//*****************************************************************************
#define EXP_UART_CONSOLE_HANDLE       USART6
#define EXP_UART_CONSOLE_IRQ          USART6_IRQn


//*****************************************************************************
// UART_FORWARD
//*****************************************************************************
#define EXP_UART_FORWARD_HANDLE       USART1
#define EXP_UART_FORWARD_IRQ          USART1_IRQn

//*****************************************************************************
// UART_FORWARD
//*****************************************************************************
#define EXP_UART_CO2_HANDLE       USART2
#define EXP_UART_CO2_IRQ          USART2_IRQn


//*****************************************************************************
// I2C_SENSOR
//*****************************************************************************
#define EXP_I2C_SENSOR_HANDLE		I2C1
#define EXP_I2C_SENSOR_IRQ			I2C1_EV_IRQn




//*****************************************************************************
// SPI_TEC
//*****************************************************************************
#define SPI_TEC				SPI3

extern struct lt8722_dev tec_0;
extern struct lt8722_dev tec_1;
extern struct lt8722_dev tec_2;
extern struct lt8722_dev tec_3;
extern struct lt8722_dev * tec_table[];
extern struct mb85rs2mt_dev fram;
extern struct adg1414_dev exp_adg1414;
extern SFC5500_Handle_t sfc_handle;

#endif /* BOARD_BOARD_H_ */
