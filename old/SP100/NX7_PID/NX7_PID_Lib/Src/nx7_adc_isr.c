/* Includes *******************************************************************/
#include "nx7_adc_isr.h"
#include "nx7_blower_fan.h"
#include "nx7_sensors.h"
#include "nx7_pid_ctrl.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
uint16_t	adc1Val[9];
uint16_t	adcCounter = 0;

extern	CCU_State			NX7_CCU_State;
extern	float				NX7_IGN_VOLT;
extern	float				NX7_Blower_VOLT;
extern	float				NX7_Airmix_FB;
extern	float				NX7_Mode_FB;
extern	MA_Pot_State		Airmix_MA_Pot_State;
extern	MA_Pot_State		Mode_MA_Pot_State;
extern	Blower_State		NX7_Blower_State;
extern	AUTO_Blink_State	NX7_AUTO_Blink_State;

extern	ADC_HandleTypeDef hadc1;	//--> IGN_VOLT, Blower_VOLT, Airmix_FB, Mode_FB, Evap_Sensor, Cabin_Sensor, Water_Sensor, Ambient_Sensor, Solar_Sensor
extern	TIM_HandleTypeDef htim3;	//--> TIM3 is used to trigger ADC1

/* Functions body *************************************************************/
/* NX7_ADC_Init --------------------------------------------------------------*/
void NX7_ADC_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc1Val, 9);
	HAL_TIM_Base_Start(&htim3);
}

/* NX7_ADC_DeInit ------------------------------------------------------------*/
void NX7_ADC_DeInit(void)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_ADC_Stop_DMA(&hadc1);
}

/* ADC ISR Handler -----------------------------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	adcCounter++;
	if(adcCounter == 11)
	{
		adcCounter = 1;
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	NX7_IGN_VOLT	= ((adc1Val[0]*3.3)/4095)*4.0;
	NX7_Blower_VOLT	= ((adc1Val[1]*3.3)/4095)*5.0;
	NX7_Airmix_FB	= ((adc1Val[2]*3.3)/4095)*5.0/3.0;
	NX7_Mode_FB		= ((adc1Val[3]*3.3)/4095)*5.0/3.0;

	//--> CCU_IGN_OFF State Detection
	if(NX7_IGN_VOLT < 5.5)
	{
		if(NX7_CCU_State==CCU_OFF)
		{NX7_CCU_State = CCU_IGN_OFF;}
		else if((NX7_CCU_State==CCU_AUTO)||(NX7_CCU_State==CCU_DEF))
		{NX7_CCU_State_Updater(CCU_IGN_OFF);}
	}
	//--> Actuator State Detection
	if((NX7_Airmix_FB<0.10)||(NX7_Airmix_FB>4.90))	{Airmix_MA_Pot_State = MA_Pot_Error;}
	else											{Airmix_MA_Pot_State = MA_Pot_OK;}
	if((NX7_Mode_FB<0.10)||(NX7_Mode_FB>4.90))		{Mode_MA_Pot_State = MA_Pot_Error;}
	else											{Mode_MA_Pot_State = MA_Pot_OK;}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if((NX7_CCU_State==CCU_IGN_OFF)||(NX7_CCU_State==CCU_OFF))
	{
		NX7_Blower_Handler(Blower_OFF);
	}
	else if(NX7_CCU_State==CCU_DEF)
	{
		NX7_Blower_Handler(Blower_L8);
	}
	else if(NX7_CCU_State==CCU_AUTO)
	{
		NX7_Blower_Handler(NX7_Blower_State);
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if((adcCounter == 1) || (adcCounter == 6))
	{
		if(NX7_AUTO_Blink_State == AUTO_Blink_OFF)
		{
			NX7_AUTO_Blink_State = AUTO_Blink_ON;
		}
		else
		{
			NX7_AUTO_Blink_State = AUTO_Blink_OFF;
		}
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if((adcCounter == 1) || (adcCounter == 6))
	{
		if((NX7_CCU_State==CCU_AUTO) || (NX7_CCU_State==CCU_DEF))
		{
			NX7_PID_Ctrl_Blower();
		}
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(adcCounter == 9)
	{
		NX7_Sensors_Handler(adc1Val[4], adc1Val[5], adc1Val[6], adc1Val[7], adc1Val[8]);
	}

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(adcCounter == 10)
	{
		if((NX7_CCU_State==CCU_AUTO) || (NX7_CCU_State==CCU_DEF))
		{
			NX7_PID_Ctrl();
		}
	}

}
