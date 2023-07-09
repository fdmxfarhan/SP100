################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CCU_Lib/sp100_a2d_isr.c \
../CCU_Lib/sp100_ac_ctrl.c \
../CCU_Lib/sp100_am_ma.c \
../CCU_Lib/sp100_atc_ccu.c \
../CCU_Lib/sp100_bl.c \
../CCU_Lib/sp100_diag.c \
../CCU_Lib/sp100_ext_isr.c \
../CCU_Lib/sp100_glbl_vars.c \
../CCU_Lib/sp100_isi_ctrl.c \
../CCU_Lib/sp100_it_ma.c \
../CCU_Lib/sp100_lcd.c \
../CCU_Lib/sp100_md_ma.c \
../CCU_Lib/sp100_rd_ctrl.c \
../CCU_Lib/sp100_snsrs.c \
../CCU_Lib/sp100_tim_isr.c \
../CCU_Lib/sp100_tle94108es.c 

OBJS += \
./CCU_Lib/sp100_a2d_isr.o \
./CCU_Lib/sp100_ac_ctrl.o \
./CCU_Lib/sp100_am_ma.o \
./CCU_Lib/sp100_atc_ccu.o \
./CCU_Lib/sp100_bl.o \
./CCU_Lib/sp100_diag.o \
./CCU_Lib/sp100_ext_isr.o \
./CCU_Lib/sp100_glbl_vars.o \
./CCU_Lib/sp100_isi_ctrl.o \
./CCU_Lib/sp100_it_ma.o \
./CCU_Lib/sp100_lcd.o \
./CCU_Lib/sp100_md_ma.o \
./CCU_Lib/sp100_rd_ctrl.o \
./CCU_Lib/sp100_snsrs.o \
./CCU_Lib/sp100_tim_isr.o \
./CCU_Lib/sp100_tle94108es.o 

C_DEPS += \
./CCU_Lib/sp100_a2d_isr.d \
./CCU_Lib/sp100_ac_ctrl.d \
./CCU_Lib/sp100_am_ma.d \
./CCU_Lib/sp100_atc_ccu.d \
./CCU_Lib/sp100_bl.d \
./CCU_Lib/sp100_diag.d \
./CCU_Lib/sp100_ext_isr.d \
./CCU_Lib/sp100_glbl_vars.d \
./CCU_Lib/sp100_isi_ctrl.d \
./CCU_Lib/sp100_it_ma.d \
./CCU_Lib/sp100_lcd.d \
./CCU_Lib/sp100_md_ma.d \
./CCU_Lib/sp100_rd_ctrl.d \
./CCU_Lib/sp100_snsrs.d \
./CCU_Lib/sp100_tim_isr.d \
./CCU_Lib/sp100_tle94108es.d 


# Each subdirectory must supply rules for building sources it contributes
CCU_Lib/%.o CCU_Lib/%.su: ../CCU_Lib/%.c CCU_Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Mehrzad/Desktop/SP100 ATC CCU/ITD - Files/SP100_SW/CCU_Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CCU_Lib

clean-CCU_Lib:
	-$(RM) ./CCU_Lib/sp100_a2d_isr.d ./CCU_Lib/sp100_a2d_isr.o ./CCU_Lib/sp100_a2d_isr.su ./CCU_Lib/sp100_ac_ctrl.d ./CCU_Lib/sp100_ac_ctrl.o ./CCU_Lib/sp100_ac_ctrl.su ./CCU_Lib/sp100_am_ma.d ./CCU_Lib/sp100_am_ma.o ./CCU_Lib/sp100_am_ma.su ./CCU_Lib/sp100_atc_ccu.d ./CCU_Lib/sp100_atc_ccu.o ./CCU_Lib/sp100_atc_ccu.su ./CCU_Lib/sp100_bl.d ./CCU_Lib/sp100_bl.o ./CCU_Lib/sp100_bl.su ./CCU_Lib/sp100_diag.d ./CCU_Lib/sp100_diag.o ./CCU_Lib/sp100_diag.su ./CCU_Lib/sp100_ext_isr.d ./CCU_Lib/sp100_ext_isr.o ./CCU_Lib/sp100_ext_isr.su ./CCU_Lib/sp100_glbl_vars.d ./CCU_Lib/sp100_glbl_vars.o ./CCU_Lib/sp100_glbl_vars.su ./CCU_Lib/sp100_isi_ctrl.d ./CCU_Lib/sp100_isi_ctrl.o ./CCU_Lib/sp100_isi_ctrl.su ./CCU_Lib/sp100_it_ma.d ./CCU_Lib/sp100_it_ma.o ./CCU_Lib/sp100_it_ma.su ./CCU_Lib/sp100_lcd.d ./CCU_Lib/sp100_lcd.o ./CCU_Lib/sp100_lcd.su ./CCU_Lib/sp100_md_ma.d ./CCU_Lib/sp100_md_ma.o ./CCU_Lib/sp100_md_ma.su ./CCU_Lib/sp100_rd_ctrl.d ./CCU_Lib/sp100_rd_ctrl.o ./CCU_Lib/sp100_rd_ctrl.su ./CCU_Lib/sp100_snsrs.d ./CCU_Lib/sp100_snsrs.o ./CCU_Lib/sp100_snsrs.su ./CCU_Lib/sp100_tim_isr.d ./CCU_Lib/sp100_tim_isr.o ./CCU_Lib/sp100_tim_isr.su ./CCU_Lib/sp100_tle94108es.d ./CCU_Lib/sp100_tle94108es.o ./CCU_Lib/sp100_tle94108es.su

.PHONY: clean-CCU_Lib

