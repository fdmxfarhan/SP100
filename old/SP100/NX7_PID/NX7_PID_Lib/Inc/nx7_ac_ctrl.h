/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_AC_CTRL_H
#define __NX7_AC_CTRL_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define		AC_Relay_ON		HAL_GPIO_WritePin(AC_Relay_GPIO_Port, AC_Relay_Pin, GPIO_PIN_SET)
#define		AC_Relay_OFF	HAL_GPIO_WritePin(AC_Relay_GPIO_Port, AC_Relay_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void NX7_AC_OFF(void);
void NX7_AC_ON(void);
void NX7_AC_Handler(AC_State state);

#endif
