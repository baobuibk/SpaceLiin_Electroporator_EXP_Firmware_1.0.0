################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ThirdParty/libfsp/subdir.mk
-include Scheduler/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/WDog/subdir.mk
-include Core/Temperature/NTC/subdir.mk
-include Core/Temperature/LT8722/subdir.mk
-include Core/Temperature/Heater/subdir.mk
-include Core/Temperature/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Sensor_I2C/LSM6DSOX/subdir.mk
-include Core/Sensor_I2C/K33/subdir.mk
-include Core/Sensor_I2C/H3LIS331DL/subdir.mk
-include Core/Sensor_I2C/H250/subdir.mk
-include Core/Sensor_I2C/BMP390/subdir.mk
-include Core/Sensor_I2C/BME280/subdir.mk
-include Core/Sensor_I2C/subdir.mk
-include Core/LED/Status_LED/subdir.mk
-include Core/LED/IR_LED/subdir.mk
-include Core/Devices/SFC5500/subdir.mk
-include Core/Devices/MB85RS2MT/subdir.mk
-include Core/Devices/ADG1414/subdir.mk
-include Core/DateTime/subdir.mk
-include Core/CLI_Terminal/CLI_Src/subdir.mk
-include Core/CLI_Terminal/CLI_Setup/subdir.mk
-include Core/CLI_Terminal/CLI_Command/subdir.mk
-include Core/Board/subdir.mk
-include Core/Auto_run/subdir.mk
-include BSP/UART/subdir.mk
-include BSP/SysTick/subdir.mk
-include BSP/I2C_Slave/subdir.mk
-include BSP/I2C/subdir.mk
-include BSP/Delay/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EXP_V110_STANDALONE
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EXP_V110_STANDALONE.elf \

MAP_FILES += \
EXP_V110_STANDALONE.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EXP_V110_STANDALONE.list \

OBJCOPY_HEX += \
EXP_V110_STANDALONE.hex \

OBJCOPY_BIN += \
EXP_V110_STANDALONE.bin \


# All Target
all: main-build

# Main-build Target
main-build: EXP_V110_STANDALONE.elf secondary-outputs

# Tool invocations
EXP_V110_STANDALONE.elf EXP_V110_STANDALONE.map: $(OBJS) $(USER_OBJS) D:\STworkspace\EXP_V110_STANDALONE\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "EXP_V110_STANDALONE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\STworkspace\EXP_V110_STANDALONE\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EXP_V110_STANDALONE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EXP_V110_STANDALONE.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EXP_V110_STANDALONE.list"
	@echo 'Finished building: $@'
	@echo ' '

EXP_V110_STANDALONE.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "EXP_V110_STANDALONE.hex"
	@echo 'Finished building: $@'
	@echo ' '

EXP_V110_STANDALONE.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "EXP_V110_STANDALONE.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) EXP_V110_STANDALONE.bin EXP_V110_STANDALONE.elf EXP_V110_STANDALONE.hex EXP_V110_STANDALONE.list EXP_V110_STANDALONE.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
