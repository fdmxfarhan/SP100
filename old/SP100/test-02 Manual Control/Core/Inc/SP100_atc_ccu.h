/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_ATC_CCU_H
#define __SP100_ATC_CCU_H

/* Includes *******************************************************************/
#include "main.h"
#include "SP100_enum_typedef.h"
#include "SP100_global_variables.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define  AUTO_LED_ON      HAL_GPIO_WritePin(AUTO_LED_GPIO_Port, AUTO_LED_Pin, GPIO_PIN_SET)
#define  AUTO_LED_OFF     HAL_GPIO_WritePin(AUTO_LED_GPIO_Port, AUTO_LED_Pin, GPIO_PIN_RESET)
#define  DEF_LED_ON       HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_SET)
#define  DEF_LED_OFF      HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_RESET)
#define  Intake_LED_ON    HAL_GPIO_WritePin(Intake_LED_GPIO_Port, Intake_LED_Pin, GPIO_PIN_SET)
#define  Intake_LED_OFF   HAL_GPIO_WritePin(Intake_LED_GPIO_Port, Intake_LED_Pin, GPIO_PIN_RESET)
#define  AC_LED_ON        HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_SET)
#define  AC_LED_OFF       HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_RESET)
#define  R_DEF_LED_ON     HAL_GPIO_WritePin(R_DEF_LED_GPIO_Port, R_DEF_LED_Pin, GPIO_PIN_SET)
#define  R_DEF_LED_OFF    HAL_GPIO_WritePin(R_DEF_LED_GPIO_Port, R_DEF_LED_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void SP100_Delay(int delay);
void SP100_CCU_Init(void);
void SP100_CCU_State_Updater(CCU_State newState);
void SP100_CCU_Switch_Handler(uint16_t SW_Pin);
void SP100_CCU_Infinite_Loop(void);
void SP100_CCU_Auto_Calculations(void);
void SP100_Airmix_Auto_Calculate(int TS, int TA, int TC);

#endif
