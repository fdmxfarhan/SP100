/* Includes *******************************************************************/
#include "mylib_adc_isr.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
uint16_t	adcVal[7];

extern	ADC_HandleTypeDef hadc;
extern	TIM_HandleTypeDef htim1;

/* Functions body *************************************************************/
/* SP100_ADC_Init ------------------------------------------------------------*/
void SP100_ADC_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc);
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)adcVal, 7);
	HAL_TIM_Base_Start(&htim1);
}

/* SP100_ADC_DeInit ----------------------------------------------------------*/
void SP100_ADC_DeInit(void)
{
	HAL_TIM_Base_Stop(&htim1);
	HAL_ADC_Stop_DMA(&hadc);
}

/* ADC ISR Handler -----------------------------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	AUTO_LED_OFF;
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	secCounter++;
	if(secCounter == 11)
	{
		secCounter = 1;
		minCounter++;
		if(minCounter == 61)
		{
			minCounter = 1;
		}
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	SP100_Mode_FB		  = ((adcVal[4]*5.7)/4095);
	SP100_Airmix_FB		= ((adcVal[5]*5.7)/4095);
	SP100_Blower_VOLT	= ((adcVal[6]*3.3)/4095)*5.0;
	

	//--> Actuator State Detection
	if((SP100_Airmix_FB>0.20)||(SP100_Airmix_FB<4.80))	{Airmix_MA_Pot_State = MA_Pot_Error;}
	else												{Airmix_MA_Pot_State = MA_Pot_OK;}
	if((SP100_Mode_FB>0.20)||(SP100_Mode_FB<4.80))		{Mode_MA_Pot_State = MA_Pot_Error;}
	else												{Mode_MA_Pot_State = MA_Pot_OK;}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(SP100_AUTO_Blink_State == AUTO_Blink_OFF)
	{
		SP100_AUTO_Blink_State = AUTO_Blink_ON;
	}
	else
	{
		SP100_AUTO_Blink_State = AUTO_Blink_OFF;
	}
}
