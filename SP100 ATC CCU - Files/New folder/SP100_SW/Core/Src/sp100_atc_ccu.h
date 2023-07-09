/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_ATC_CCU_H
#define __SP100_ATC_CCU_H

/* Includes *******************************************************************/
#include "main.h"
#include "sp100_typedef.h"
#include "sp100_glbl_vars.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define  AUTO_LED_ON      HAL_GPIO_WritePin(AUTO_LED_GPIO_Port, AUTO_LED_Pin, GPIO_PIN_SET)
#define  AUTO_LED_OFF     HAL_GPIO_WritePin(AUTO_LED_GPIO_Port, AUTO_LED_Pin, GPIO_PIN_RESET)
#define  DEF_LED_ON       HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_SET)
#define  DEF_LED_OFF      HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_RESET)
#define  IT_LED_ON        HAL_GPIO_WritePin(IT_LED_GPIO_Port, IT_LED_Pin, GPIO_PIN_SET)
#define  IT_LED_OFF       HAL_GPIO_WritePin(IT_LED_GPIO_Port, IT_LED_Pin, GPIO_PIN_RESET)
#define  AC_LED_ON        HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_SET)
#define  AC_LED_OFF       HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_RESET)
#define  RD_LED_ON        HAL_GPIO_WritePin(RD_LED_GPIO_Port, RD_LED_Pin, GPIO_PIN_SET)
#define  RD_LED_OFF       HAL_GPIO_WritePin(RD_LED_GPIO_Port, RD_LED_Pin, GPIO_PIN_RESET)

/* Exported functions *********************************************************/
void SP100_Delay(int delay);
void SP100_CCU_Init(void);
void SP100_CCU_DeInit(void);
void SP100_Variables_Init(void);
void SP100_CCU_State_Updater(CCU_State newState);
void SP100_CCU_Switch_Handler(uint16_t SW_Pin);
void SP100_AUTO_Error_State_Handler(void);
void SP100_CCU_Infinite_Loop(void);

#endif
