################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/GPIO.c 

OBJS += \
./STM32F103C6_Drivers/GPIO.o 

C_DEPS += \
./STM32F103C6_Drivers/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/GPIO.o: ../STM32F103C6_Drivers/GPIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/mahmo/STM32CubeIDE/workspace_1.4.0/DRIVERS/STM32F103C6_Drivers/Seven_segment_driver" -I"C:/Users/mahmo/STM32CubeIDE/workspace_1.4.0/DRIVERS/STM32F103C6_Drivers/LCD_driver" -I"C:/Users/mahmo/STM32CubeIDE/workspace_1.4.0/DRIVERS/STM32F103C6_Drivers/Keypad_driver" -I"C:/Users/mahmo/STM32CubeIDE/workspace_1.4.0/DRIVERS/STM32F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

