/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_BL_H
#define __SP100_BL_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_BL_Tolerance		0.10

#define		SP100_BL_Volt_L1		4.50
#define		SP100_BL_Volt_L2		5.50
#define		SP100_BL_Volt_L3		6.50
#define		SP100_BL_Volt_L4		7.50
#define		SP100_BL_Volt_L5		8.50
#define		SP100_BL_Volt_L6		9.50
#define		SP100_BL_Volt_L7		10.5
#define		SP100_BL_Volt_L8		16.0

#define		SP100_BL_PWM_L1			1100
#define		SP100_BL_PWM_L2			1350
#define		SP100_BL_PWM_L3			1600
#define		SP100_BL_PWM_L4			1850
#define		SP100_BL_PWM_L5			2100
#define		SP100_BL_PWM_L6			2350
#define		SP100_BL_PWM_L7			2600
#define		SP100_BL_PWM_L8			4000

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_BL_Init(void);
void SP100_BL_DeInit(void);
void SP100_BL_OFF(void);
void SP100_BL_Up(void);
void SP100_BL_Down(void);
void SP100_BL_Handler(BL_State state);

#endif
