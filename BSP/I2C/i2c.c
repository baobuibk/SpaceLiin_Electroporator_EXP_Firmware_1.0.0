/*
 * i2c.c
 *
 *  Created on: Nov 29, 2024
 *      Author: SANG HUYNH
 */

#include "i2c.h"


I2C_Status_t I2C_Write(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t reg, uint8_t data)
{
	uint32_t timeout = I2C_TIMEOUT;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStartCondition(I2Cx);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_SB(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, addr << 1);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_ADDR(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_ClearFlag_ADDR(I2Cx);
	LL_I2C_TransmitData8(I2Cx, reg);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_TXE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, data);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_TXE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStopCondition(I2Cx);
	return I2C_Success;
}

I2C_Status_t I2C_Read(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t reg, uint8_t* pData)
{
	uint8_t data = 0;
	uint32_t timeout = I2C_TIMEOUT;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStartCondition(I2Cx);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_SB(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, addr << 1);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_ADDR(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_ClearFlag_ADDR(I2Cx);
	LL_I2C_TransmitData8(I2Cx, reg);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_TXE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStartCondition(I2Cx);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_SB(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, (addr << 1) | 1);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_ADDR(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;
	LL_I2C_ClearFlag_ADDR(I2Cx);

	LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
	timeout = I2C_TIMEOUT;
	while(!LL_I2C_IsActiveFlag_RXNE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	data = LL_I2C_ReceiveData8(I2Cx);
	LL_I2C_GenerateStopCondition(I2Cx);
	*pData = data;
	return I2C_Success;
}

I2C_Status_t I2C_ReadMulti(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t reg, uint8_t* pData, uint16_t size)
{
	uint32_t timeout = I2C_TIMEOUT;

	while (LL_I2C_IsActiveFlag_BUSY(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStartCondition(I2Cx);
	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_SB(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, addr << 1);
	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_ADDR(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;
	LL_I2C_ClearFlag_ADDR(I2Cx);

	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_TXE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;
	LL_I2C_TransmitData8(I2Cx, reg);

	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_TXE(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_GenerateStartCondition(I2Cx);
	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_SB(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	LL_I2C_TransmitData8(I2Cx, (addr << 1) | 1);
	timeout = I2C_TIMEOUT;
	while (!LL_I2C_IsActiveFlag_ADDR(I2Cx) && timeout--);
	if (timeout == 0) return I2C_Error;

	if (size == 1) {
		LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
	} else {
		LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
	}
	LL_I2C_ClearFlag_ADDR(I2Cx);

	for (uint16_t i = 0; i < size; i++) {
		timeout = I2C_TIMEOUT;
		while (!LL_I2C_IsActiveFlag_RXNE(I2Cx) && timeout--);
		if (timeout == 0) return I2C_Error;

		if (i == (size - 2)) {
			LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
		}
		if (i == (size - 1)) {
			LL_I2C_GenerateStopCondition(I2Cx);
		}

		pData[i] = LL_I2C_ReceiveData8(I2Cx);
	}

	return I2C_Success;
}
