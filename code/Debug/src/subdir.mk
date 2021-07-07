################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ir_sensor.c \
../src/main.c \
../src/pov_display.c \
../src/shift_register.c \
../src/stm23f103c8t6_dma.c \
../src/stm23f103c8t6_systick.c \
../src/stm32f103c8t6_afio.c \
../src/stm32f103c8t6_exti.c \
../src/stm32f103c8t6_gpio.c \
../src/stm32f103c8t6_nvic.c \
../src/stm32f103c8t6_rcc.c \
../src/stm32f103c8t6_spi.c \
../src/stm32f103c8t6_timer.c \
../src/stm32f103c8t6_usart.c 

OBJS += \
./src/ir_sensor.o \
./src/main.o \
./src/pov_display.o \
./src/shift_register.o \
./src/stm23f103c8t6_dma.o \
./src/stm23f103c8t6_systick.o \
./src/stm32f103c8t6_afio.o \
./src/stm32f103c8t6_exti.o \
./src/stm32f103c8t6_gpio.o \
./src/stm32f103c8t6_nvic.o \
./src/stm32f103c8t6_rcc.o \
./src/stm32f103c8t6_spi.o \
./src/stm32f103c8t6_timer.o \
./src/stm32f103c8t6_usart.o 

C_DEPS += \
./src/ir_sensor.d \
./src/main.d \
./src/pov_display.d \
./src/shift_register.d \
./src/stm23f103c8t6_dma.d \
./src/stm23f103c8t6_systick.d \
./src/stm32f103c8t6_afio.d \
./src/stm32f103c8t6_exti.d \
./src/stm32f103c8t6_gpio.d \
./src/stm32f103c8t6_nvic.d \
./src/stm32f103c8t6_rcc.d \
./src/stm32f103c8t6_spi.d \
./src/stm32f103c8t6_timer.d \
./src/stm32f103c8t6_usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


