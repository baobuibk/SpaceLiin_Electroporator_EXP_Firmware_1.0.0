/*
 * sfc5500.h
 *
 *  Created on: May 13, 2025
 *      Author: HTSANG
 */

#ifndef DEVICES_SFC5500_SFC5500_H_
#define DEVICES_SFC5500_SFC5500_H_

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_gpio.h"
#include <stdint.h>

/* Cấu hình SHDLC */
#define SFC5500_SLAVE_ADDRESS       0x00
#define SFC5500_BAUDRATE            115200
#define SFC5500_START_BYTE          0x7E
#define SFC5500_STOP_BYTE           0x7E

/* SFC5500 COMMAND DEFINE */
#define SFC5500_GET_DEVICE_INFOR_CMD                  0xD0
#define SFC5500_GET_SET_SETPOINT_CMD                  0x00
#define SFC5500_GET_SET_SETPOINT_PERSIST_CMD          0x02
#define SFC5500_SET_SETPOINT_AND_READ_MEASURE_CMD     0x03

#define SFC5500_READ_MEASURE_FLOW_CMD                 0x08
#define SFC5500_READ_MEASURE_FLOW_BUFFER_CMD          0x09

#define SFC5500_GET_SET_VALVE_INPUT_SOURCE_CONFIG_CMD  0x20
#define SFC5500_GET_SET_MEDIUM_UNIT_CONFIG_CMD         0x21
#define SFC5500_GET_SET_CONTROLER_CONFIG_CMD           0x22

#define SFC5500_ADVANCE_MEASUREMENT_CMD               0x30
#define SFC5500_GET_CALIB_INFORMATION_CMD             0x40
#define SFC5500_GET_CURRENT_CALIB_INFORMATION_CMD     0x44
#define SFC5500_LOAD_CALIB_AND_RUN_CMD                0x45
#define SFC5500_USER_MEMORY_ACCESS_CMD                0x6E

#define SFC5500_GET_SET_BAUDRATE_CMD                   0x91
#define SFC5500_FACTORY_RESET_CMD                     0x92
#define SFC5500_GET_DEVICE_ERROR_CMD                  0xD2
#define SFC5500_DEVICE_RESET_CMD                      0xD3


/* Định nghĩa Scaling of Setpoint và Measured Flow */
#define SFC5500_SCALE_NORMALIZED        0x00
#define SFC5500_SCALE_PHYSICAL          0x01
#define SFC5500_SCALE_USER_UNIT         0x02

/* Cấu hình phần cứng */
#define SFC5500_UART                USART1
#define SFC5500_RS485_DE_PORT       GPIOA
#define SFC5500_RS485_DE_PIN        LL_GPIO_PIN_4

/* Kích thước buffer */
#define SFC5500_TX_BUFFER_SIZE      12 // Start + Address + Command + Length + Data (n bytes) + CRC16 + Stop
#define SFC5500_RX_BUFFER_SIZE      20

/* Kiểu dữ liệu */
typedef enum {
    SFC5500_OK = 0,
    SFC5500_ERROR_CRC,
    SFC5500_ERROR_RESPONSE,
    SFC5500_ERROR_TIMEOUT
} SFC5500_Status_t;

/* Cấu trúc driver */
typedef struct {
    USART_TypeDef *uart;            // UART instance (USART1)
    GPIO_TypeDef *de_port;          // RS485 DE/RE port
    uint32_t de_pin;                // RS485 DE/RE pin
    uint8_t slave_addr;             // SHDLC address
} SFC5500_Handle_t;

/* Nguyên mẫu hàm */
SFC5500_Status_t SFC5500_Init(SFC5500_Handle_t *handle);
SFC5500_Status_t SFC5500_GetDeviceInfo(SFC5500_Handle_t *handle, char *product_name);

SFC5500_Status_t SFC5500_SetBaudrate(SFC5500_Handle_t *handle, uint32_t baudrate);
SFC5500_Status_t SFC5500_GetBaudrate(SFC5500_Handle_t *handle, uint32_t *baudrate);

SFC5500_Status_t SFC5500_ResetDevice(SFC5500_Handle_t *handle);

SFC5500_Status_t SFC5500_SetSetpoint(SFC5500_Handle_t *handle, uint8_t scaling, float setpoint);
SFC5500_Status_t SFC5500_GetSetpoint(SFC5500_Handle_t *handle, uint8_t scaling, float *setpoint);

SFC5500_Status_t SFC5500_ReadMeasuredFlow(SFC5500_Handle_t *handle, uint8_t scaling, float *flow);

void SFC5500_UART_IRQHandler(SFC5500_Handle_t *handle);

#endif /* DEVICES_SFC5500_SFC5500_H_ */
