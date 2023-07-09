/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_LCD_H
#define __SP100_LCD_H

/* Includes *******************************************************************/
#include "SP100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
//--> HT16C22A Registers
#define		HT16C22A_Device_Address				0x7E
#define		Mode_Setting						0x80
#define		Address_Pointer						0x00
#define		Blinking_Frequency					0xC0
#define		Internal_Voltage_Adjust_Control		0x40

/* Exported macro *************************************************************/
#define		SP100_LCD_DayLight_PWM				100
#define		SP100_LCD_NightLight_PWM			60

/* Exported functions *********************************************************/
void SP100_LCD_Init(void);
void SP100_LCD_DeInit(void);
void SP100_LCD_Command(uint8_t command);
uint8_t SP100_LCD_SEG_Read(uint8_t address);
void SP100_LCD_SEG_OFF(const uint8_t *ptr);
void SP100_LCD_SEG_ON(const uint8_t *ptr);
void SP100_LCD_Backlight(uint16_t pwm);

void SP100_LCD_ALL_SEG(SEG_State state);
void SP100_LCD_AUTO_SEG(SEG_State state);
void SP100_LCD_DEF_SEG(SEG_State state);
void SP100_LCD_Mode_SEG(SEG_State state);
void SP100_LCD_Blower_SEG(SEG_State state);
void SP100_LCD_Out_Temp_SEG(SEG_State state);
void SP100_LCD_Set_Point_SEG(SEG_State state);

void SP100_LCD_State_Init_SEG(CCU_State state);

void SP100_LCD_AC_Handler(AC_State state);
void SP100_LCD_R_DEF_Handler(R_DEF_State state);
void SP100_LCD_Mode_Handler(Mode_State state);
void SP100_LCD_Airmix_Handler(Airmix_State state);
void SP100_LCD_Blower_Handler(Blower_State state);

void SP100_LCD_Set_Point_Segment(char ch, int counter);
void SP100_LCD_Set_Point_Handler(float set_point);
void SP100_LCD_Out_Temp_Segment(char ch, int counter);
void SP100_LCD_Out_Temp_Handler(int out_temp);

void SP100_LCD_Test(int index);
void SP100_LCD_Temp_Count_Test(void);
void SP100_LCD_Print_Temp(int num);
void SP100_LCD_Update(void);
void SP100_LCD_Show_Set_Point(void);
void SP100_LCD_SetPoint_Low(void);
void SP100_LCD_SetPoint_High(void);
void SP100_LCD_Print_Out_Temp(int num);
void SP100_LCD_Show_Out_Temp(void);
void SP100_LCD_OUT_Temp_Count_Test(void);
void SP100_LCD_Auto_Handler(void);
void SP100_LCD_OFF_State(void);
void SP100_LCD_Diag_State(void);
#endif
