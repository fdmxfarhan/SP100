/* Includes *******************************************************************/
#include "SP100_ext_isr.h"
#include "SP100_lcd.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/
/* Private variables **********************************************************/

/* Functions body *************************************************************/
/* Ext. ISR Handler ----------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
/* Ignition Handler ----------------------------------------------------------*/
	if((GPIO_Pin==Ignition_Pin)&&(Ignition_State==GPIO_PIN_RESET))
	{
		SP100_CCU_State = CCU_IGN_OFF;
	}
	else if((GPIO_Pin==Ignition_Pin)&&(Ignition_State==GPIO_PIN_SET))
	{
		SP100_CCU_State = CCU_OFF;
	}
/* Illumination Handler ------------------------------------------------------*/
	if((GPIO_Pin==Illumination_Pin)&&(Illumination_State==GPIO_PIN_RESET))
	{
		SP100_LCD_Backlight(SP100_LCD_DayLight_PWM);
	}
	else if((GPIO_Pin==Illumination_Pin)&&(Illumination_State==GPIO_PIN_SET))
	{
		SP100_LCD_Backlight(SP100_LCD_NightLight_PWM);
	}
/* Airmix_Up Switch Handler --------------------------------------------------*/
	if((GPIO_Pin==Airmix_Up_SW_Pin)&&(Airmix_Up_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Airmix_Up_SW_Pin);
		SP100_Delay(Rotary_Debounce);
	}
/* Airmix_Down Switch Handler ------------------------------------------------*/
	else if((GPIO_Pin==Airmix_Down_SW_Pin)&&(Airmix_Down_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Airmix_Down_SW_Pin);
		SP100_Delay(Rotary_Debounce);
	}
/* Blower_Up Switch Handler --------------------------------------------------*/
	if((GPIO_Pin==Blower_Up_SW_Pin)&&(Blower_Up_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Blower_Up_SW_Pin);
		SP100_Delay(Rotary_Debounce);
	}
/* Blower_Down Switch Handler ------------------------------------------------*/
	else if((GPIO_Pin==Blower_Down_SW_Pin)&&(Blower_Down_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Blower_Down_SW_Pin);
		SP100_Delay(Rotary_Debounce);
	}
/* OFF Switch Handler --------------------------------------------------------*/
	if((GPIO_Pin==OFF_SW_Pin) && (OFF_Switch==GPIO_PIN_RESET))
	{
		//HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, 1);
		SP100_CCU_Switch_Handler(OFF_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* AUTO Switch Handler -------------------------------------------------------*/
	if((GPIO_Pin==AUTO_SW_Pin)&&(AUTO_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(AUTO_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* DEF Switch Handler --------------------------------------------------------*/
	if((GPIO_Pin==DEF_SW_Pin)&&(DEF_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(DEF_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* Intake Switch Handler -----------------------------------------------------*/
	if((GPIO_Pin==Intake_SW_Pin)&&(Intake_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Intake_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* Mode Switch Handler -------------------------------------------------------*/
	if((GPIO_Pin==Mode_SW_Pin)&&(Mode_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(Mode_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* A/C Switch Handler --------------------------------------------------------*/
	if((GPIO_Pin==AC_SW_Pin)&&(AC_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(AC_SW_Pin);
		SP100_Delay(Button_Debounce);
	}
/* R_DEF Switch Handler ------------------------------------------------------*/
	if((GPIO_Pin==R_DEF_SW_Pin)&&(R_DEF_Switch==GPIO_PIN_RESET))
	{
		SP100_CCU_Switch_Handler(R_DEF_SW_Pin);
		SP100_Delay(Button_Debounce);
	}

	//--> Clear the Ext. Pending Bit
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}
