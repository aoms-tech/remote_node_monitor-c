################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f446retx.s 

OBJS += \
./Core/Startup/startup_stm32f446retx.o 

S_DEPS += \
./Core/Startup/startup_stm32f446retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-g++ -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/App" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/App/Chip" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/Inc" -I"C:/Users/CO-OP/Documents/remote_node_monitor-c/remoteNodeMonitor/Core/Src" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f446retx.d ./Core/Startup/startup_stm32f446retx.o

.PHONY: clean-Core-2f-Startup

