/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_EXT_ISR_H
#define __SP100_EXT_ISR_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define		IGN_State				HAL_GPIO_ReadPin(IGN_GPIO_Port, IGN_Pin)
#define		Illumination_State		HAL_GPIO_ReadPin(Illumination_GPIO_Port, Illumination_Pin)
#define		OFF_Switch				HAL_GPIO_ReadPin(OFF_SW_GPIO_Port, OFF_SW_Pin)
#define		AUTO_Switch				HAL_GPIO_ReadPin(AUTO_SW_GPIO_Port, AUTO_SW_Pin)
#define		DEF_Switch				HAL_GPIO_ReadPin(DEF_SW_GPIO_Port, DEF_SW_Pin)
#define		AC_Switch				HAL_GPIO_ReadPin(AC_SW_GPIO_Port, AC_SW_Pin)
#define		IT_Switch				HAL_GPIO_ReadPin(IT_SW_GPIO_Port, IT_SW_Pin)
#define		MD_Switch				HAL_GPIO_ReadPin(MD_SW_GPIO_Port, MD_SW_Pin)
#define		AM_Up_Switch			HAL_GPIO_ReadPin(AM_Up_SW_GPIO_Port, AM_Up_SW_Pin)
#define		AM_Down_Switch			HAL_GPIO_ReadPin(AM_Down_SW_GPIO_Port, AM_Down_SW_Pin)
#define		BL_Up_Switch			HAL_GPIO_ReadPin(BL_Up_SW_GPIO_Port, BL_Up_SW_Pin)
#define		BL_Down_Switch			HAL_GPIO_ReadPin(BL_Down_SW_GPIO_Port, BL_Down_SW_Pin)
#define		RD_Switch				HAL_GPIO_ReadPin(RD_SW_GPIO_Port, RD_SW_Pin)

#define		Rotary_Debounce			50000
#define		Button_Debounce			250000

/* Exported functions *********************************************************/

#endif
