################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.c 

OBJS += \
./Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.o 

C_DEPS += \
./Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/Chip/%.o Core/App/Chip/%.su: ../Core/App/Chip/%.c Core/App/Chip/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jessica Doe/Documents/remoteNodeMonitor/Core/App" -I"C:/Users/Jessica Doe/Documents/remoteNodeMonitor/Core/App/Chip" -I"C:/Users/Jessica Doe/Documents/remoteNodeMonitor/Core/App/sCommon" -I"C:/Users/Jessica Doe/Documents/remoteNodeMonitor/Core/App/sCommon/Chips" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App-2f-Chip

clean-Core-2f-App-2f-Chip:
	-$(RM) ./Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.d ./Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.o ./Core/App/Chip/NODE_MONITOR_NUCLEOF446RE.su

.PHONY: clean-Core-2f-App-2f-Chip

