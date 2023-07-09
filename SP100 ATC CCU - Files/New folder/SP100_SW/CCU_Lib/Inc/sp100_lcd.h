/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_LCD_H
#define __SP100_LCD_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

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
#define		SP100_LCD_NightLight_PWM			70

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
void SP100_LCD_MD_SEG(SEG_State state);
void SP100_LCD_BL_SEG(SEG_State state);
void SP100_LCD_OT_SEG(SEG_State state);
void SP100_LCD_SP_SEG(SEG_State state);

void SP100_LCD_State_Init_SEG(CCU_State state);

void SP100_LCD_AC_Handler(AC_State state);
void SP100_LCD_RD_Handler(RD_State state);
void SP100_LCD_MD_Handler(MD_State state);
void SP100_LCD_AM_Handler(AM_State state);
void SP100_LCD_BL_Handler(BL_State state);

void SP100_LCD_SP_Segment(char ch, int counter);
void SP100_LCD_SP_Handler(float sp);
void SP100_LCD_OT_Segment(char ch, int counter);
void SP100_LCD_OT_Handler(int ot);

void SP100_LCD_Snsr_Index_Handler(int index);

void SP100_LCD_DIAG_Snsr_Handler(DIAG_Snsr_Index snsr_index);
void SP100_LCD_DIAG_Actr_Handler(DIAG_Actr_Index actr_index);
void SP100_LCD_DIAG_Actr_Busy(void);

#endif
