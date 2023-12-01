################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/App/Chip/TOASTER_NUCLEOF446RE.cpp 

OBJS += \
./Core/App/Chip/TOASTER_NUCLEOF446RE.o 

CPP_DEPS += \
./Core/App/Chip/TOASTER_NUCLEOF446RE.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/Chip/%.o Core/App/Chip/%.su: ../Core/App/Chip/%.cpp Core/App/Chip/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/App" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/App/Chip" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/Src" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App-2f-Chip

clean-Core-2f-App-2f-Chip:
	-$(RM) ./Core/App/Chip/TOASTER_NUCLEOF446RE.d ./Core/App/Chip/TOASTER_NUCLEOF446RE.o ./Core/App/Chip/TOASTER_NUCLEOF446RE.su

.PHONY: clean-Core-2f-App-2f-Chip

