/* Includes *******************************************************************/
#include "nx7_ext_isr.h"
#include "nx7_lcd.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/

/* Functions body *************************************************************/
/* Ext. ISR Handler ----------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
/* Illumination Handler ------------------------------------------------------*/
	if((GPIO_Pin==Illumination_Pin)&&(Illumination_State==GPIO_PIN_RESET))
	{
		NX7_LCD_Backlight(NX7_LCD_DayLight_PWM);
	}
	else if((GPIO_Pin==Illumination_Pin)&&(Illumination_State==GPIO_PIN_SET))
	{
		NX7_LCD_Backlight(NX7_LCD_NightLight_PWM);
	}
/* Airmix_Up Switch Handler --------------------------------------------------*/
	if((GPIO_Pin==Airmix_Up_SW_Pin)&&(Airmix_Up_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Airmix_Up_SW_Pin);
		NX7_Delay(Rotary_Debounce);
	}
/* Airmix_Down Switch Handler ------------------------------------------------*/
	else if((GPIO_Pin==Airmix_Down_SW_Pin)&&(Airmix_Down_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Airmix_Down_SW_Pin);
		NX7_Delay(Rotary_Debounce);
	}
/* Blower_Up Switch Handler --------------------------------------------------*/
	if((GPIO_Pin==Blower_Up_SW_Pin)&&(Blower_Up_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Blower_Up_SW_Pin);
		NX7_Delay(Rotary_Debounce);
	}
/* Blower_Down Switch Handler ------------------------------------------------*/
	else if((GPIO_Pin==Blower_Down_SW_Pin)&&(Blower_Down_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Blower_Down_SW_Pin);
		NX7_Delay(Rotary_Debounce);
	}
/* POWER Switch Handler ------------------------------------------------------*/
	if((GPIO_Pin==POWER_SW_Pin)&&(POWER_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(POWER_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
/* AUTO Switch Handler -------------------------------------------------------*/
	if((GPIO_Pin==AUTO_SW_Pin)&&(AUTO_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(AUTO_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
	if((GPIO_Pin==AUTO_SW_Pin)&&(AUTO_Switch==GPIO_PIN_SET))
	{
		asm("NOP");
	}
/* DEF Switch Handler --------------------------------------------------------*/
	if((GPIO_Pin==DEF_SW_Pin)&&(DEF_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(DEF_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
/* Intake Switch Handler -----------------------------------------------------*/
	if((GPIO_Pin==Intake_SW_Pin)&&(Intake_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Intake_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
/* Mode Switch Handler -------------------------------------------------------*/
	if((GPIO_Pin==Mode_SW_Pin)&&(Mode_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(Mode_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
/* A/C Switch Handler --------------------------------------------------------*/
	if((GPIO_Pin==AC_SW_Pin)&&(AC_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(AC_SW_Pin);
		NX7_Delay(Button_Debounce);
	}	
/* R_DEF Switch Handler ------------------------------------------------------*/
	if((GPIO_Pin==R_DEF_SW_Pin)&&(R_DEF_Switch==GPIO_PIN_RESET))
	{
		NX7_CCU_Switch_Handler(R_DEF_SW_Pin);
		NX7_Delay(Button_Debounce);
	}
	
	//--> Clear the Ext. Pending Bit
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}
