/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_BLOWER_FAN_H
#define __NX7_BLOWER_FAN_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		NX7_Blower_Tolerance	0.10

#define		NX7_Blower_Volt_L1		4.50
#define		NX7_Blower_Volt_L2		5.50
#define		NX7_Blower_Volt_L3		6.50
#define		NX7_Blower_Volt_L4		7.50
#define		NX7_Blower_Volt_L5		8.50
#define		NX7_Blower_Volt_L6		9.50
#define		NX7_Blower_Volt_L7		10.5
#define		NX7_Blower_Volt_L8		16.0

#define		NX7_Blower_DAC_L1		1100
#define		NX7_Blower_DAC_L2		1350
#define		NX7_Blower_DAC_L3		1600
#define		NX7_Blower_DAC_L4		1850
#define		NX7_Blower_DAC_L5		2100
#define		NX7_Blower_DAC_L6		2350
#define		NX7_Blower_DAC_L7		2600
#define		NX7_Blower_DAC_L8		4000

/* Exported macro *************************************************************/
#define  Blower_Relay_ON   HAL_GPIO_WritePin(Blower_Relay_GPIO_Port, Blower_Relay_Pin, GPIO_PIN_SET)
#define  Blower_Relay_OFF  HAL_GPIO_WritePin(Blower_Relay_GPIO_Port, Blower_Relay_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void NX7_Blower_Init(void);
void NX7_Blower_OFF(void);
void NX7_Blower_Up(void);
void NX7_Blower_Down(void);
void NX7_Blower_Handler(Blower_State state);

#endif
