################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/DateTime/date_time.c 

OBJS += \
./Core/DateTime/date_time.o 

C_DEPS += \
./Core/DateTime/date_time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/DateTime/%.o Core/DateTime/%.su Core/DateTime/%.cyclo: ../Core/DateTime/%.c Core/DateTime/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/STworkspace/EXP_V110_STANDALONE/Scheduler" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP/SysTick" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Common" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/WDog" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/LED" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP/UART" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Board" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP/Delay" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Devices" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP/I2C" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Temperature" -I"D:/STworkspace/EXP_V110_STANDALONE/ThirdParty/libfsp" -I"D:/STworkspace/EXP_V110_STANDALONE/ThirdParty" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C" -I"D:/STworkspace/EXP_V110_STANDALONE/BSP/I2C_Slave" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Devices/ADG1414" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Devices/MB85RS2MT" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/CLI_Terminal" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/CLI_Terminal/CLI_Command" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/CLI_Terminal/CLI_Setup" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/CLI_Terminal/CLI_Src" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/LED/Status_LED" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Temperature/Heater" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Temperature/LT8722" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Temperature/NTC" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/DateTime" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Auto_run" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/BMP390" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/LED/IR_LED" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/LSM6DSOX" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/BME280" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/H3LIS331DL" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/H250" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Sensor_I2C/K33" -I"D:/STworkspace/EXP_V110_STANDALONE/Core/Devices/SFC5500" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-DateTime

clean-Core-2f-DateTime:
	-$(RM) ./Core/DateTime/date_time.cyclo ./Core/DateTime/date_time.d ./Core/DateTime/date_time.o ./Core/DateTime/date_time.su

.PHONY: clean-Core-2f-DateTime

