################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103C6_Drivers/USART_driver/subdir.mk
-include STM32F103C6_Drivers/Seven_segment_driver/subdir.mk
-include STM32F103C6_Drivers/SPI_driver/subdir.mk
-include STM32F103C6_Drivers/LCD_driver/subdir.mk
-include STM32F103C6_Drivers/Keypad_driver/subdir.mk
-include STM32F103C6_Drivers/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DRIVERS.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DRIVERS.list \

OBJCOPY_BIN += \
DRIVERS.bin \


# All Target
all: DRIVERS.elf secondary-outputs

# Tool invocations
DRIVERS.elf: $(OBJS) $(USER_OBJS) C:\Users\mahmo\STM32CubeIDE\workspace_1.4.0\DRIVERS\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "DRIVERS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\mahmo\STM32CubeIDE\workspace_1.4.0\DRIVERS\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DRIVERS.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DRIVERS.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DRIVERS.list"
	@echo 'Finished building: $@'
	@echo ' '

DRIVERS.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "DRIVERS.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
