/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_EXT_ISR_H
#define __SP100_EXT_ISR_H

/* Includes *******************************************************************/
#include "mylib_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/
#define		Ignition_State			HAL_GPIO_ReadPin(Ignition_GPIO_Port, Ignition_Pin)
#define		Illumination_State		HAL_GPIO_ReadPin(Illumination_GPIO_Port, Illumination_Pin)
#define		OFF_Switch				HAL_GPIO_ReadPin(OFF_SW_GPIO_Port, OFF_SW_Pin)
#define		AUTO_Switch				HAL_GPIO_ReadPin(AUTO_SW_GPIO_Port, AUTO_SW_Pin)
#define		DEF_Switch				HAL_GPIO_ReadPin(DEF_SW_GPIO_Port, DEF_SW_Pin)
#define		AC_Switch				HAL_GPIO_ReadPin(AC_SW_GPIO_Port, AC_SW_Pin)
#define		Intake_Switch			HAL_GPIO_ReadPin(Intake_SW_GPIO_Port, Intake_SW_Pin)
#define		Mode_Switch				HAL_GPIO_ReadPin(Mode_SW_GPIO_Port, Mode_SW_Pin)
#define		Airmix_Up_Switch		HAL_GPIO_ReadPin(Airmix_Up_SW_GPIO_Port, Airmix_Up_SW_Pin)
#define		Airmix_Down_Switch		HAL_GPIO_ReadPin(Airmix_Down_SW_GPIO_Port, Airmix_Down_SW_Pin)
#define		Blower_Up_Switch		HAL_GPIO_ReadPin(Blower_Up_SW_GPIO_Port, Blower_Up_SW_Pin)
#define		Blower_Down_Switch		HAL_GPIO_ReadPin(Blower_Down_SW_GPIO_Port, Blower_Down_SW_Pin)
#define		R_DEF_Switch			HAL_GPIO_ReadPin(R_DEF_SW_GPIO_Port, R_DEF_SW_Pin)

#define		Rotary_Debounce			5000
#define		Button_Debounce			2500

/* Exported functions *********************************************************/

#endif
