/* Includes *******************************************************************/
#include "nx7_tim_isr.h"
#include "nx7_airmix_ma.h"
#include "nx7_mode_ma.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern  TIM_HandleTypeDef  htim1;	//--> R-DEF
extern  TIM_HandleTypeDef  htim3;	//--> ADC1_Trigger
extern  TIM_HandleTypeDef  htim4;	//--> LCD_Backlight
extern  TIM_HandleTypeDef  htim6;	//--> Airmix_Lock_State
extern  TIM_HandleTypeDef  htim7;	//--> Mode_Lock_State
extern  TIM_HandleTypeDef  htim15;	//--> CCU_SENSOR_Entry
extern  TIM_HandleTypeDef  htim16;	//--> Mode_SEG_State
extern  TIM_HandleTypeDef  htim17;	//--> CCU_DIAG_Entry
extern  CCU_State  NX7_CCU_State;
extern  R_DEF_State  NX7_R_DEF_State;
extern	Blower_State  NX7_Blower_State;
extern	MA_Lock_State  Airmix_MA_Lock_State;
extern	MA_Lock_State  Mode_MA_Lock_State;
extern  Mode_SEG_State  NX7_Mode_SEG_State;

/* Functions body *************************************************************/
/* TIM ISR Handler -----------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* TIM1 ISR Handler ------------------------------------------------------*/
	if(htim->Instance == TIM1)
	{
		NX7_R_DEF_State = R_DEF_OFF;
	}
	/* TIM6 ISR Handler ------------------------------------------------------*/
	if(htim->Instance == TIM6)
	{
		Airmix_MA_Lock_State = MA_Lock_Error;
		NX7_Airmix_MA_STP();
		HAL_TIM_Base_Stop_IT(&htim6);
		__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
	}
	/* TIM7 ISR Handler ------------------------------------------------------*/
	if(htim->Instance == TIM7)
	{
		Mode_MA_Lock_State = MA_Lock_Error;
		NX7_Mode_MA_STP();
		HAL_TIM_Base_Stop_IT(&htim7);
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	}
	/* TIM16 ISR Handler ------------------------------------------------------*/
	if(htim->Instance == TIM16)
	{
		NX7_Mode_SEG_State = Mode_SEG_OFF;
		HAL_TIM_Base_Stop_IT(&htim16);
		__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
	}
}
