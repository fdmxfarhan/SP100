/* Includes *******************************************************************/
#include "nx7_r_def_ctrl.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern	TIM_HandleTypeDef	htim1;

/* Functions body *************************************************************/
/* NX7_R_DEF_OFF -------------------------------------------------------------*/
void NX7_R_DEF_OFF(void)
{
	if(HAL_GPIO_ReadPin(R_DEF_Relay_GPIO_Port, R_DEF_Relay_Pin) == GPIO_PIN_SET)
	{
		R_DEF_Relay_OFF;
		R_DEF_LED_OFF;
		// TIM1 Stop --> R_DEF
		HAL_TIM_Base_Stop_IT(&htim1);
		__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
	}
}

/* NX7_R_DEF_ON --------------------------------------------------------------*/
void NX7_R_DEF_ON(void)
{
	if(HAL_GPIO_ReadPin(R_DEF_Relay_GPIO_Port, R_DEF_Relay_Pin) == GPIO_PIN_RESET)
	{
		R_DEF_Relay_ON;
		R_DEF_LED_ON;
		// TIM1 Start --> R_DEF
		htim1.Instance->CNT = 0x00;
		htim1.Instance->RCR = 0x02;
		htim1.Instance->EGR = 0x01;
		__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim1);
	}
}

/* NX7_R_DEF_Handler ---------------------------------------------------------*/
void NX7_R_DEF_Handler(R_DEF_State state)
{
	switch (state)
	{
		case R_DEF_OFF:
		{
			NX7_R_DEF_OFF();
			break;
		}
		case R_DEF_ON:
		{
			NX7_R_DEF_ON();
			break;
		}
	}
}
