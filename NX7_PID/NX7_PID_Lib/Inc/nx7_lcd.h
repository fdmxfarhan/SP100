/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_LCD_H
#define __NX7_LCD_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
//--> HT16K23 Registers
#define		HT16K23_Device_Address			0xE6
#define		Display_Data_Address_Pointer	0x00
#define		Key_Data_Address_Pointer		0x20
#define		INT_Flag_Address_Pointer		0x30
#define		System_Set_Command				0x80
#define		Mode_Set_Command				0xA0
#define		Key_Scan_Period_Setting			0xF8

/* Exported macro *************************************************************/
#define		NX7_LCD_DayLight_PWM			100
#define		NX7_LCD_NightLight_PWM			60

/* Exported functions *********************************************************/
void NX7_LCD_Init(void);
void NX7_LCD_DeInit(void);
void NX7_LCD_Command(uint8_t command);
uint8_t NX7_LCD_SEG_Read(uint8_t address);
void NX7_LCD_SEG_OFF(uint8_t address, uint8_t data);
void NX7_LCD_SEG_ON(uint8_t address, uint8_t data);
void NX7_LCD_Backlight(uint16_t pwm);

void NX7_LCD_ALL_SEG(SEG_State state);
void NX7_LCD_OFF_SEG(SEG_State state);
void NX7_LCD_AUTO_SEG(SEG_State state);
void NX7_LCD_ECON_SEG(SEG_State state);
void NX7_LCD_DEF_SEG(SEG_State state);
void NX7_LCD_Intake_SEG(SEG_State state);
void NX7_LCD_Mode_SEG(SEG_State state);
void NX7_LCD_Blower_SEG(SEG_State state);
void NX7_LCD_Out_Temp_SEG(SEG_State state);
void NX7_LCD_Set_Point_SEG(SEG_State state);

void NX7_LCD_State_Init_SEG(CCU_State state);

void NX7_LCD_AC_Handler(AC_State state);
void NX7_LCD_R_DEF_Handler(R_DEF_State state);
void NX7_LCD_Intake_Handler(Intake_State state);
void NX7_LCD_Mode_Handler(Mode_State state);
void NX7_LCD_Airmix_Handler(Airmix_State state);
void NX7_LCD_Blower_Handler(Blower_State state);

void NX7_LCD_Set_Point_Segment(char ch, int counter);
void NX7_LCD_Set_Point_Handler(float set_point);
void NX7_LCD_Out_Temp_Segment(char ch, int counter);
void NX7_LCD_Out_Temp_Handler(int out_temp);

void NX7_LCD_Sensor_Index_Handler(int index);

#endif
