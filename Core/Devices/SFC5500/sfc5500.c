/*
 * sfc5500.c
 *
 *  Created on: May 13, 2025
 *      Author: HTSANG
 */

#include "sfc5500.h"
#include "SFC5500.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_gpio.h"
#include <string.h>
#include "board.h"



static uint8_t tx_buffer[SFC5500_TX_BUFFER_SIZE];
static uint8_t rx_buffer[SFC5500_RX_BUFFER_SIZE];
static volatile uint8_t rx_index = 0;
static volatile uint8_t rx_complete = 0;

static uint8_t shdlc_crc(uint8_t *Data, uint8_t len)
{
    uint16_t Temp = 0;

    for (uint8_t i = 0; i < len; i++)
    {
        Temp += Data[i];
    }
    return (uint8_t)(~(Temp & 0xFF));
}

/* Gửi lệnh SHDLC qua RS485 */
static SFC5500_Status_t shdlc_send_command(SFC5500_Handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t data_len) {
    if (data_len > SFC5500_TX_BUFFER_SIZE - 7) return SFC5500_ERROR_RESPONSE; // Kiểm tra độ dài

    tx_buffer[0] = SFC5500_START_BYTE;
    tx_buffer[1] = handle->slave_addr;
    tx_buffer[2] = cmd;
    tx_buffer[3] = data_len;
    for (uint8_t i = 0; i < data_len; i++) {
        tx_buffer[4 + i] = *(data + i);
    }

    uint8_t crc = shdlc_crc(&tx_buffer[1], 3 + data_len);
    tx_buffer[4 + data_len] = crc;
    tx_buffer[5 + data_len] = SFC5500_STOP_BYTE;

    LL_GPIO_SetOutputPin(handle->de_port, handle->de_pin);
    LL_GPIO_SetOutputPin(EXP_RS485_NRE_GPIO_Port, EXP_RS485_NRE_Pin);

    for (uint8_t i = 0; i < 6 + data_len; i++) {
        while (!LL_USART_IsActiveFlag_TXE(handle->uart)); // Sửa lỗi: dùng TXE
        LL_USART_TransmitData8(handle->uart, tx_buffer[i]);
    }

    while (!LL_USART_IsActiveFlag_TC(handle->uart)); // Chờ truyền hoàn tất
    LL_GPIO_ResetOutputPin(handle->de_port, handle->de_pin);
    LL_GPIO_ResetOutputPin(EXP_RS485_NRE_GPIO_Port, EXP_RS485_NRE_Pin);

    return SFC5500_OK;
}

/* Xử lý phản hồi SHDLC */
static SFC5500_Status_t shdlc_process_response(SFC5500_Handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t *data_len, uint8_t max_len) {
    if (rx_complete && rx_index >= 7 && rx_buffer[0] == SFC5500_START_BYTE && rx_buffer[rx_index - 1] == SFC5500_STOP_BYTE) {
        uint8_t crc_received = rx_buffer[rx_index - 2];
        uint8_t crc_calculated = shdlc_crc(&rx_buffer[1], rx_index - 3);
        if (crc_received != crc_calculated) {
            return SFC5500_ERROR_CRC;
        }

        if (rx_buffer[1] != handle->slave_addr || rx_buffer[2] != cmd || rx_buffer[3] != 0x00) {
            return SFC5500_ERROR_RESPONSE;
        }

        uint8_t len = rx_buffer[4]; // Data length
        if (len > max_len) len = max_len;
        *data_len = len;
        for (uint8_t i = 0; i < len; i++) {
            data[i] = rx_buffer[5 + i];
        }
        return SFC5500_OK;
    }
    return SFC5500_ERROR_TIMEOUT;
}

/* Khởi tạo driver */
SFC5500_Status_t SFC5500_Init(SFC5500_Handle_t *handle) {
    if (handle == NULL || handle->uart == NULL || handle->de_port == NULL) {
        return SFC5500_ERROR_RESPONSE;
    }

    handle->slave_addr = SFC5500_SLAVE_ADDRESS;

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(handle->de_port, handle->de_pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_ResetOutputPin(handle->de_port, handle->de_pin);

    LL_USART_EnableIT_RXNE(handle->uart);

    return SFC5500_OK;
}


/* Lấy thông tin thiết bị */
SFC5500_Status_t SFC5500_GetDeviceInfo(SFC5500_Handle_t *handle, char *product_name) {
    if (handle == NULL || handle->uart == NULL || handle->de_port == NULL) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[] = {0x01};
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_GET_DEVICE_INFOR_CMD, data, 1);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 100000; i++);
    rx_complete = 1;

    uint8_t max_len = 16;
    uint8_t response_data[max_len];
	uint8_t response_len;
	status = shdlc_process_response(handle, SFC5500_GET_DEVICE_INFOR_CMD, response_data, &response_len, max_len);


    if (status == SFC5500_OK) {
        uint8_t copy_len = (response_len < max_len - 1) ? response_len : max_len - 1;
        for (uint8_t i = 0; i < copy_len; i++) {
        	product_name[i] = (char)response_data[i];
        }
        product_name[copy_len] = '\0';
    }
    return status;
}

/* Đặt baudrate */
SFC5500_Status_t SFC5500_SetBaudrate(SFC5500_Handle_t *handle, uint32_t baudrate) {
    if (handle == NULL || (baudrate != 9600 && baudrate != 19200 && baudrate != 38400 &&
         baudrate != 115200 && baudrate != 230400 && baudrate != 460800)) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[4] = {
        (baudrate >> 24) & 0xFF,
        (baudrate >> 16) & 0xFF,
        (baudrate >> 8) & 0xFF,
        baudrate & 0xFF
    };
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_GET_SET_BAUDRATE_CMD, data, 4);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 100000; i++); // Chờ 10ms, nên dùng timer
    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_GET_SET_BAUDRATE_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len == 0) {
        // Cấu hình lại USART với baudrate mới
        LL_USART_Disable(handle->uart);
        LL_USART_SetBaudRate(handle->uart, SystemCoreClock, LL_USART_OVERSAMPLING_16, baudrate);
        LL_USART_Enable(handle->uart);
        return SFC5500_OK;
    }
    return status;
}

/* Lấy baudrate */
SFC5500_Status_t SFC5500_GetBaudrate(SFC5500_Handle_t *handle, uint32_t *baudrate) {
    if (handle == NULL || baudrate == NULL) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[] = {0x00};
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_GET_SET_SETPOINT_CMD, data, 0);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 100000; i++); // Chờ 10ms, nên dùng timer
    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_GET_SET_BAUDRATE_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len >= 4) {
        *baudrate = ((uint32_t)response_data[0] << 24) |
                    ((uint32_t)response_data[1] << 16) |
                    ((uint32_t)response_data[2] << 8) |
                    response_data[3];
    }
    return status;
}

/* Reset thiết bị */
SFC5500_Status_t SFC5500_ResetDevice(SFC5500_Handle_t *handle) {
    if (handle == NULL) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[] = {0x00};
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_DEVICE_RESET_CMD, data, 0);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 100000; i++); // Chờ 10ms, nên dùng timer

    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_DEVICE_RESET_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len == 0) {
        for (uint32_t i = 0; i < 5000000; i++);
        return SFC5500_OK;
    }
    return status;
}

/* Đặt setpoint lưu lượng */
SFC5500_Status_t SFC5500_SetSetpoint(SFC5500_Handle_t *handle, uint8_t scaling, float setpoint) {
    if (handle == NULL ||
        (scaling != SFC5500_SCALE_NORMALIZED &&
         scaling != SFC5500_SCALE_PHYSICAL &&
         scaling != SFC5500_SCALE_USER_UNIT)) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint32_t setpoint_raw = *(uint32_t*)&setpoint;
    uint8_t data[5] = {
        scaling,
        (setpoint_raw >> 24) & 0xFF,
        (setpoint_raw >> 16) & 0xFF,
        (setpoint_raw >> 8) & 0xFF,
        setpoint_raw & 0xFF
    };
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_GET_SET_SETPOINT_CMD, data, 5);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 50000; i++); // Chờ 5ms, nên dùng timer

    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_GET_SET_SETPOINT_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len == 0) {
        return SFC5500_OK;
    }
    return status;
}

/* Lấy setpoint lưu lượng */
SFC5500_Status_t SFC5500_GetSetpoint(SFC5500_Handle_t *handle, uint8_t scaling, float *setpoint) {
    if (handle == NULL || setpoint == NULL ||
        (scaling != SFC5500_SCALE_NORMALIZED &&
         scaling != SFC5500_SCALE_PHYSICAL &&
         scaling != SFC5500_SCALE_USER_UNIT)) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[] = {scaling};
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_GET_SET_SETPOINT_CMD, data, 1);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 50000; i++); // Chờ 5ms, nên dùng timer

    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_GET_SET_SETPOINT_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len >= 4) {
        uint32_t raw_value = ((uint32_t)response_data[0] << 24) |
                             ((uint32_t)response_data[1] << 16) |
                             ((uint32_t)response_data[2] << 8) |
                             response_data[3];
        *setpoint = *(float*)&raw_value;
    }
    return status;
}

/* Đọc giá trị lưu lượng đo được */
SFC5500_Status_t SFC5500_ReadMeasuredFlow(SFC5500_Handle_t *handle, uint8_t scaling, float *flow) {
    if (handle == NULL || flow == NULL ||
        (scaling != SFC5500_SCALE_NORMALIZED &&
         scaling != SFC5500_SCALE_PHYSICAL &&
         scaling != SFC5500_SCALE_USER_UNIT)) {
        return SFC5500_ERROR_RESPONSE;
    }

    rx_index = 0;
    rx_complete = 0;

    uint8_t data[] = {scaling};
    SFC5500_Status_t status = shdlc_send_command(handle, SFC5500_READ_MEASURE_FLOW_CMD, data, 1);
    if (status != SFC5500_OK) {
        return status;
    }

    for (uint32_t i = 0; i < 50000; i++); // Chờ 5ms, nên dùng timer

    rx_complete = 1;

    uint8_t response_data[16];
    uint8_t response_len;
    status = shdlc_process_response(handle, SFC5500_READ_MEASURE_FLOW_CMD, response_data, &response_len, 16);
    if (status == SFC5500_OK && response_len >= 4) {
        uint32_t raw_value = ((uint32_t)response_data[0] << 24) |
                             ((uint32_t)response_data[1] << 16) |
                             ((uint32_t)response_data[2] << 8) |
                             response_data[3];
        *flow = *(float*)&raw_value;
    }
    return status;
}

/* Xử lý ngắt UART */
void SFC5500_UART_IRQHandler(SFC5500_Handle_t *handle) {
    if (LL_USART_IsActiveFlag_RXNE(handle->uart)) {
        rx_buffer[rx_index] = LL_USART_ReceiveData8(handle->uart);
        rx_index++;
        if (rx_index >= SFC5500_RX_BUFFER_SIZE) {
            rx_index = 0;
        }
    }
}
