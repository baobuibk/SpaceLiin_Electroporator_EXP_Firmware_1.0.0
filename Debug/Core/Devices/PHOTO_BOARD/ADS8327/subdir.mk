################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Devices/PHOTO_BOARD/ADS8327/ads8327.c 

OBJS += \
./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.o 

C_DEPS += \
./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Devices/PHOTO_BOARD/ADS8327/%.o Core/Devices/PHOTO_BOARD/ADS8327/%.su Core/Devices/PHOTO_BOARD/ADS8327/%.cyclo: ../Core/Devices/PHOTO_BOARD/ADS8327/%.c Core/Devices/PHOTO_BOARD/ADS8327/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I"D:/STworkspace/EXP_V110/Core/Devices/DateTime" -I"D:/STworkspace/EXP_V110/Core/Devices/Auto_run" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/STworkspace/EXP_V110/Scheduler" -I"D:/STworkspace/EXP_V110/BSP" -I"D:/STworkspace/EXP_V110/BSP/SysTick" -I"D:/STworkspace/EXP_V110/Core/Common" -I"D:/STworkspace/EXP_V110/Core/WDog" -I"D:/STworkspace/EXP_V110/Core/LED" -I"D:/STworkspace/EXP_V110/BSP/UART" -I"D:/STworkspace/EXP_V110/Core/CMDLine" -I"D:/STworkspace/EXP_V110/Core/Board" -I"D:/STworkspace/EXP_V110/BSP/Delay" -I"D:/STworkspace/EXP_V110/Core/Devices" -I"D:/STworkspace/EXP_V110/Core/Devices/LT8722" -I"D:/STworkspace/EXP_V110/BSP/I2C" -I"D:/STworkspace/EXP_V110/Core/Devices/NTC" -I"D:/STworkspace/EXP_V110/Core/Temperature" -I"D:/STworkspace/EXP_V110/Core/Devices/BMP390" -I"D:/STworkspace/EXP_V110/Core/Devices/Heater" -I"D:/STworkspace/EXP_V110/Core/COPC" -I"D:/STworkspace/EXP_V110/ThirdParty/libfsp" -I"D:/STworkspace/EXP_V110/ThirdParty" -I"D:/STworkspace/EXP_V110/Core/Sensor_I2C" -I"D:/STworkspace/EXP_V110/Core/Devices/IR_LED" -I"D:/STworkspace/EXP_V110/BSP/I2C_Slave" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/STworkspace/EXP_V110/Core/Devices/LASER_BOARD" -I"D:/STworkspace/EXP_V110/Core/Devices/LASER_BOARD/MCP4902" -I"D:/STworkspace/EXP_V110/Core/Devices/ADG1414" -I"D:/STworkspace/EXP_V110/Core/Devices/PHOTO_BOARD/ADS8327" -I"D:/STworkspace/EXP_V110/Core/Devices/PHOTO_BOARD" -I"D:/STworkspace/EXP_V110/Core/Devices/MB85RS2MT" -I"D:/STworkspace/EXP_V110/Core/CLI_Terminal" -I"D:/STworkspace/EXP_V110/Core/CLI_Terminal/CLI_Command" -I"D:/STworkspace/EXP_V110/Core/CLI_Terminal/CLI_Setup" -I"D:/STworkspace/EXP_V110/Core/CLI_Terminal/CLI_Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Devices-2f-PHOTO_BOARD-2f-ADS8327

clean-Core-2f-Devices-2f-PHOTO_BOARD-2f-ADS8327:
	-$(RM) ./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.cyclo ./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.d ./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.o ./Core/Devices/PHOTO_BOARD/ADS8327/ads8327.su

.PHONY: clean-Core-2f-Devices-2f-PHOTO_BOARD-2f-ADS8327

