/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_R_DEF_CTRL_H
#define __NX7_R_DEF_CTRL_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define		R_DEF_Relay_ON		HAL_GPIO_WritePin(R_DEF_Relay_GPIO_Port, R_DEF_Relay_Pin, GPIO_PIN_SET)
#define		R_DEF_Relay_OFF		HAL_GPIO_WritePin(R_DEF_Relay_GPIO_Port, R_DEF_Relay_Pin, GPIO_PIN_RESET)
#define		R_DEF_LED_ON		HAL_GPIO_WritePin(R_DEF_LED_GPIO_Port, R_DEF_LED_Pin, GPIO_PIN_SET)
#define		R_DEF_LED_OFF		HAL_GPIO_WritePin(R_DEF_LED_GPIO_Port, R_DEF_LED_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void NX7_R_DEF_OFF(void);
void NX7_R_DEF_ON(void);
void NX7_R_DEF_Handler(R_DEF_State state);

#endif
