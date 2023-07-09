/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_BLOWER_FAN_H
#define __SP100_BLOWER_FAN_H

/* Includes *******************************************************************/
#include "SP100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_Blower_Tolerance	0.10

#define		SP100_Blower_Volt_L1		4.50
#define		SP100_Blower_Volt_L2		5.50
#define		SP100_Blower_Volt_L3		6.50
#define		SP100_Blower_Volt_L4		7.50
#define		SP100_Blower_Volt_L5		8.50
#define		SP100_Blower_Volt_L6		9.50
#define		SP100_Blower_Volt_L7		10.5
#define		SP100_Blower_Volt_L8		16.0

#define		SP100_Blower_DAC_L1		1100
#define		SP100_Blower_DAC_L2		1350
#define		SP100_Blower_DAC_L3		1600
#define		SP100_Blower_DAC_L4		1850
#define		SP100_Blower_DAC_L5		2100
#define		SP100_Blower_DAC_L6		2350
#define		SP100_Blower_DAC_L7		2600
#define		SP100_Blower_DAC_L8		4000

/* Exported macro *************************************************************/
//#define  Blower_Relay_ON   HAL_GPIO_WritePin(Blower_Relay_GPIO_Port, Blower_Relay_Pin, GPIO_PIN_SET)
//#define  Blower_Relay_OFF  HAL_GPIO_WritePin(Blower_Relay_GPIO_Port, Blower_Relay_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void SP100_Blower_Init(void);
void SP100_Blower_OFF(void);
void SP100_Blower_Up(void);
void SP100_Blower_Down(void);
void SP100_Blower_Handler(Blower_State state);
void SP100_Blower_State_Down(void);
void SP100_Blower_State_Up(void);
int SP100_Blower_Get_State_Num(Blower_State state);
Blower_State volt2state(int v);
#endif
