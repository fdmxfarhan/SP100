/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_ATC_CCU_H
#define __NX7_ATC_CCU_H

/* Includes *******************************************************************/
#include "main.h"
#include "nx7_typedef.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_Delay(int delay);
void NX7_CCU_Init(void);
void NX7_CCU_State_Updater(CCU_State newState);
void NX7_CCU_Switch_Handler(uint16_t SW_Pin);
void NX7_AUTO_Error_State_Handler(void);
void NX7_CCU_Infinite_Loop(void);

#endif
