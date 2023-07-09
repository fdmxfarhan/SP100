################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NX7_PID_Lib/Src/nx7_ac_ctrl.c \
../NX7_PID_Lib/Src/nx7_adc_isr.c \
../NX7_PID_Lib/Src/nx7_airmix_ma.c \
../NX7_PID_Lib/Src/nx7_atc_ccu.c \
../NX7_PID_Lib/Src/nx7_blower_fan.c \
../NX7_PID_Lib/Src/nx7_ext_isr.c \
../NX7_PID_Lib/Src/nx7_intake_ma.c \
../NX7_PID_Lib/Src/nx7_lcd.c \
../NX7_PID_Lib/Src/nx7_mode_ma.c \
../NX7_PID_Lib/Src/nx7_pid_ctrl.c \
../NX7_PID_Lib/Src/nx7_r_def_ctrl.c \
../NX7_PID_Lib/Src/nx7_sensors.c \
../NX7_PID_Lib/Src/nx7_tim_isr.c \
../NX7_PID_Lib/Src/nx7_tle94106es.c 

OBJS += \
./NX7_PID_Lib/Src/nx7_ac_ctrl.o \
./NX7_PID_Lib/Src/nx7_adc_isr.o \
./NX7_PID_Lib/Src/nx7_airmix_ma.o \
./NX7_PID_Lib/Src/nx7_atc_ccu.o \
./NX7_PID_Lib/Src/nx7_blower_fan.o \
./NX7_PID_Lib/Src/nx7_ext_isr.o \
./NX7_PID_Lib/Src/nx7_intake_ma.o \
./NX7_PID_Lib/Src/nx7_lcd.o \
./NX7_PID_Lib/Src/nx7_mode_ma.o \
./NX7_PID_Lib/Src/nx7_pid_ctrl.o \
./NX7_PID_Lib/Src/nx7_r_def_ctrl.o \
./NX7_PID_Lib/Src/nx7_sensors.o \
./NX7_PID_Lib/Src/nx7_tim_isr.o \
./NX7_PID_Lib/Src/nx7_tle94106es.o 

C_DEPS += \
./NX7_PID_Lib/Src/nx7_ac_ctrl.d \
./NX7_PID_Lib/Src/nx7_adc_isr.d \
./NX7_PID_Lib/Src/nx7_airmix_ma.d \
./NX7_PID_Lib/Src/nx7_atc_ccu.d \
./NX7_PID_Lib/Src/nx7_blower_fan.d \
./NX7_PID_Lib/Src/nx7_ext_isr.d \
./NX7_PID_Lib/Src/nx7_intake_ma.d \
./NX7_PID_Lib/Src/nx7_lcd.d \
./NX7_PID_Lib/Src/nx7_mode_ma.d \
./NX7_PID_Lib/Src/nx7_pid_ctrl.d \
./NX7_PID_Lib/Src/nx7_r_def_ctrl.d \
./NX7_PID_Lib/Src/nx7_sensors.d \
./NX7_PID_Lib/Src/nx7_tim_isr.d \
./NX7_PID_Lib/Src/nx7_tle94106es.d 


# Each subdirectory must supply rules for building sources it contributes
NX7_PID_Lib/Src/%.o: ../NX7_PID_Lib/Src/%.c NX7_PID_Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F100xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Mehrzad/Desktop/NX7_PID/NX7_PID_Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-NX7_PID_Lib-2f-Src

clean-NX7_PID_Lib-2f-Src:
	-$(RM) ./NX7_PID_Lib/Src/nx7_ac_ctrl.d ./NX7_PID_Lib/Src/nx7_ac_ctrl.o ./NX7_PID_Lib/Src/nx7_adc_isr.d ./NX7_PID_Lib/Src/nx7_adc_isr.o ./NX7_PID_Lib/Src/nx7_airmix_ma.d ./NX7_PID_Lib/Src/nx7_airmix_ma.o ./NX7_PID_Lib/Src/nx7_atc_ccu.d ./NX7_PID_Lib/Src/nx7_atc_ccu.o ./NX7_PID_Lib/Src/nx7_blower_fan.d ./NX7_PID_Lib/Src/nx7_blower_fan.o ./NX7_PID_Lib/Src/nx7_ext_isr.d ./NX7_PID_Lib/Src/nx7_ext_isr.o ./NX7_PID_Lib/Src/nx7_intake_ma.d ./NX7_PID_Lib/Src/nx7_intake_ma.o ./NX7_PID_Lib/Src/nx7_lcd.d ./NX7_PID_Lib/Src/nx7_lcd.o ./NX7_PID_Lib/Src/nx7_mode_ma.d ./NX7_PID_Lib/Src/nx7_mode_ma.o ./NX7_PID_Lib/Src/nx7_pid_ctrl.d ./NX7_PID_Lib/Src/nx7_pid_ctrl.o ./NX7_PID_Lib/Src/nx7_r_def_ctrl.d ./NX7_PID_Lib/Src/nx7_r_def_ctrl.o ./NX7_PID_Lib/Src/nx7_sensors.d ./NX7_PID_Lib/Src/nx7_sensors.o ./NX7_PID_Lib/Src/nx7_tim_isr.d ./NX7_PID_Lib/Src/nx7_tim_isr.o ./NX7_PID_Lib/Src/nx7_tle94106es.d ./NX7_PID_Lib/Src/nx7_tle94106es.o

.PHONY: clean-NX7_PID_Lib-2f-Src

