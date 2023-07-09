################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myLib/mylib_adc_isr.c \
../myLib/mylib_atc_ccu.c \
../myLib/mylib_ext_isr.c \
../myLib/mylib_global_variables.c \
../myLib/mylib_lcd.c 

OBJS += \
./myLib/mylib_adc_isr.o \
./myLib/mylib_atc_ccu.o \
./myLib/mylib_ext_isr.o \
./myLib/mylib_global_variables.o \
./myLib/mylib_lcd.o 

C_DEPS += \
./myLib/mylib_adc_isr.d \
./myLib/mylib_atc_ccu.d \
./myLib/mylib_ext_isr.d \
./myLib/mylib_global_variables.d \
./myLib/mylib_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
myLib/%.o myLib/%.su: ../myLib/%.c myLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/98919/Desktop/SP100 ATC CCU - Files/New folder/SP100 ATC CCU - Files (1401-02-27)/SP100_ATC_CCU/myLib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-myLib

clean-myLib:
	-$(RM) ./myLib/mylib_adc_isr.d ./myLib/mylib_adc_isr.o ./myLib/mylib_adc_isr.su ./myLib/mylib_atc_ccu.d ./myLib/mylib_atc_ccu.o ./myLib/mylib_atc_ccu.su ./myLib/mylib_ext_isr.d ./myLib/mylib_ext_isr.o ./myLib/mylib_ext_isr.su ./myLib/mylib_global_variables.d ./myLib/mylib_global_variables.o ./myLib/mylib_global_variables.su ./myLib/mylib_lcd.d ./myLib/mylib_lcd.o ./myLib/mylib_lcd.su

.PHONY: clean-myLib

