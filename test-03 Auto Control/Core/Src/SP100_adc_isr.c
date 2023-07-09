/* Includes *******************************************************************/
#include "SP100_adc_isr.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
uint16_t	adcVal[16];
int off_counter = 6001;
extern	ADC_HandleTypeDef hadc;
extern	TIM_HandleTypeDef htim1;
int last_check = 0;
/* Functions body *************************************************************/
/* SP100_ADC_Init ------------------------------------------------------------*/
void SP100_ADC_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc);
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)adcVal, 8);
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
	//AUTO_LED_ON;
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	secCounter++;
	if(off_counter < 11000) off_counter++;

	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	SP100_IGN_Volt = adcVal[7];
	if(secCounter > 6000) {
		SP100_Ambient_Sensor = (4095 - adcVal[2])/30 - 82;
		SP100_Cabin_Sensor = (4095 - adcVal[0])/30 - 45.16;
		if(SP100_R_DEF_State == R_DEF_ON){
			if(SP100_CCU_State != CCU_IGN_OFF && SP100_IGN_Volt < 3050 && off_counter > 10000){
				SP100_CCU_State = CCU_IGN_OFF;
				SP100_R_DEF_State = R_DEF_OFF;
				off_counter = 0;
			}
			if(SP100_CCU_State == CCU_IGN_OFF && SP100_IGN_Volt > 3050 && off_counter > 10000 ){
				if(last_check == 1){
					SP100_CCU_State = CCU_OFF;
					off_counter = 0;
					last_check = 0;
				}
				else last_check = 1;
			}
		}else{
			if(SP100_CCU_State != CCU_IGN_OFF && SP100_IGN_Volt < 3050 && off_counter > 10000){
				SP100_CCU_State = CCU_IGN_OFF;
				SP100_R_DEF_State = R_DEF_OFF;
				off_counter = 0;
			}
			if(SP100_CCU_State == CCU_IGN_OFF && SP100_IGN_Volt > 3050 && off_counter > 10000){
				if(last_check == 1){
					SP100_CCU_State = CCU_OFF;
					off_counter = 0;
					last_check = 0;
				}
				else last_check = 1;
			}
		}
		
		SP100_Water_Sensor = (adcVal[1])/20 + 45;
		//SP100_Cabin_Sensor = (4095 - adcVal[0])/30 - 45.16;
		SP100_Evap_Sensor = (4095 - adcVal[3])/46 - 44;
		if(SP100_Evap_Sensor < 1.2) SP100_AC_Temp_State = AC_Temp_OFF;
		if(SP100_Evap_Sensor > 3) SP100_AC_Temp_State = AC_Temp_ON;
		SP100_OUT_TEMP_READY = READY;
		secCounter = 0;
	}
	
	SP100_Mode_FB		  = ((adcVal[4]*5.7)/4095);
	SP100_Airmix_FB		= ((adcVal[5]*5.7)/4095);
	SP100_Blower_VOLT	= ((adcVal[6]*3.3)/4095)*5.0;
	
	if(SP100_CCU_State == CCU_DIAG){
		if(adcVal[3] < 10 || adcVal[3] > 4080) SP100_Diag_Evap_State = DIAG_ERROR;
		else																	 SP100_Diag_Evap_State = DIAG_OK;
		if(adcVal[1] < 10 || adcVal[1] > 4080) SP100_Diag_Water_State = DIAG_ERROR;
		else																	 SP100_Diag_Water_State = DIAG_OK;
		if(adcVal[0] < 10 || adcVal[0] > 4080) SP100_Diag_Cabin_State = DIAG_ERROR;
		else																	 SP100_Diag_Cabin_State = DIAG_OK;
		if(adcVal[2] < 10 || adcVal[2] > 4080) SP100_Diag_Ambient_State = DIAG_ERROR;
		else																	 SP100_Diag_Ambient_State = DIAG_OK;
		if(adcVal[5] < 30 || adcVal[5] > 4080) SP100_Diag_Airmix_Pot_State = DIAG_ERROR;
		else																	 SP100_Diag_Airmix_Pot_State = DIAG_OK;
		if(adcVal[4] < 30 || adcVal[4] > 4080) SP100_Diag_Mode_Pot_State = DIAG_ERROR;
		else																	 SP100_Diag_Mode_Pot_State = DIAG_OK;
	}
	
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
