################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f429xx/Legacy/stm32f4xx_hal_can.c 

OBJS += \
./system/src/stm32f429xx/Legacy/stm32f4xx_hal_can.o 

C_DEPS += \
./system/src/stm32f429xx/Legacy/stm32f4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f429xx/Legacy/%.o: ../system/src/stm32f429xx/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f429xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


