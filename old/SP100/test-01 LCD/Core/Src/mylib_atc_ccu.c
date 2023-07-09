/* Includes *******************************************************************/
#include "mylib_atc_ccu.h"
#include "mylib_ext_isr.h"
#include "mylib_adc_isr.h"
#include "SP100_TLE94108ES.h"
#include "SP100_Intake.h"
#include "mylib_lcd.h"
#include "SP100_Mode.h"
#include "SP100_Airmix.h"
#include "SP100_Blower.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/
/* Private variables **********************************************************/
int lcd_cnt = 0;
/* Functions body *************************************************************/
/* SP100_Delay ---------------------------------------------------------------*/
void SP100_Delay(int delay)
{
	for(register int i=0; i<delay; i++);
}

/* SP100_CCU_Init ------------------------------------------------------------*/
void SP100_CCU_Init(void)
{
	SP100_ADC_Init();
	SP100_LCD_Init();
	SP100_TLE_Init();
	SP100_Blower_Init();
}

/* SP100_CCU_State_Updater ---------------------------------------------------*/
void SP100_CCU_State_Updater(CCU_State newState)
{
	SP100_CCU_preState	=	SP100_CCU_State;
	SP100_CCU_State		=	newState;
}

/* SP100_CCU_Switch_Handler --------------------------------------------------*/
void SP100_CCU_Switch_Handler(uint16_t SW_Pin)
{
	/* --------------------------------------------------------- <OFF_SW_Pin> */
	if(SW_Pin == OFF_SW_Pin)
	{
		SP100_Airmix_FWD();
		lcd_cnt++;
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			SP100_CCU_State_Updater(CCU_OFF);
			break;
		}
		case CCU_DEF:
		{
			SP100_CCU_State_Updater(CCU_OFF);
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* -------------------------------------------------------- <AUTO_SW_Pin> */
	if(SW_Pin == AUTO_SW_Pin)
	{
		SP100_Airmix_RVS();
		lcd_cnt--;
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			SP100_CCU_State_Updater(CCU_AUTO);
			break;
		}
		case CCU_AUTO:
		{
			SP100_CCU_State_Updater(CCU_AUTO);
			break;
		}
		case CCU_DEF:
		{
			SP100_CCU_State_Updater(CCU_AUTO);
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* --------------------------------------------------------- <DEF_SW_Pin> */
	if(SW_Pin == DEF_SW_Pin)
	{
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			SP100_CCU_State_Updater(CCU_DEF);
			break;
		}
		case CCU_AUTO:
		{
			SP100_CCU_State_Updater(CCU_DEF);
			break;
		}
		case CCU_DEF:
		{
			SP100_CCU_State_Updater(SP100_CCU_preState);
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ---------------------------------------------------------- <AC_SW_Pin> */
	if(SW_Pin == AC_SW_Pin)
	{
		SP100_Airmix_STP();
		if(SP100_AC_State == AC_ON) SP100_AC_State = AC_OFF;
		else									 		  SP100_AC_State = AC_ON;
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			SP100_CCU_State_Updater(SP100_CCU_preState);
			break;
		}
		case CCU_AUTO:
		{
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------------ <Intake_SW_Pin> */
	if(SW_Pin == Intake_SW_Pin)
	{
		if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
		else 																	 SP100_Intake_State = Intake_Fresh;
			
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* -------------------------------------------------------- <Mode_SW_Pin> */
	if(SW_Pin == Mode_SW_Pin)
	{
		if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
		else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
		else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
		else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
		else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
		/*
		switch (SP100_CCU_State)
		{
			
		case CCU_OFF:
		{
			if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
			else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
			else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
			else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
			else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_AUTO:
		{
			if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
			else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
			else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
			else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
			else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}*/
	}
	/* --------------------------------------------------- <Blower_Up_SW_Pin> */
	if(SW_Pin == Blower_Up_SW_Pin)
	{
		if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
		/*switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}*/
	}
	/* ------------------------------------------------- <Blower_Down_SW_Pin> */
	if(SW_Pin == Blower_Down_SW_Pin)
	{
		if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
		/*
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}*/
	}
	/* --------------------------------------------------- <Airmix_Up_SW_Pin> */
	if(SW_Pin == Airmix_Up_SW_Pin)
	{
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------- <Airmix_Down_SW_Pin> */
	if(SW_Pin == Airmix_Down_SW_Pin)
	{
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			break;
		}
		case CCU_DEF:
		{
			break;
		}
		case CCU_SENSOR:
		{
			break;
		}
		case CCU_DIAG:
		{
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------------- <R_DEF_SW_Pin> */
	if(SW_Pin == R_DEF_SW_Pin)
	{
		if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
		else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
		
		switch (SP100_CCU_State)
		{
			case CCU_OFF:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
			case CCU_AUTO:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
			case CCU_DEF:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
			case CCU_SENSOR:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
			case CCU_DIAG:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
			case CCU_IGN_OFF:
			{
				if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
				else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
				break;
			}
		}
	}
}

/* SP100_CCU_Infinite_Loop ---------------------------------------------------*/
void SP100_CCU_Infinite_Loop(void)
{
	while(1)
	{
		if(SP100_Intake_State == Intake_Fresh){
			SP100_Intake_Fresh();
			Intake_LED_OFF;			
		}else{
			SP100_Intake_Recycle();
			Intake_LED_ON;
		}
		SP100_Mode_Handler(SP100_Mode_State);
		SP100_Blower_Handler(SP100_Blower_State);
		SP100_LCD_Update();
		//SP100_LCD_Test(lcd_cnt);
		//SP100_LCD_ALL_SEG(SEG_ON);
		
		
		
		
		
		/*
		if(SP100_CCU_State == CCU_IGN_OFF)
		{
			SP100_LCD_ALL_SEG(SEG_OFF);
			//--> Warning -> CCU_IGN_OFF_State
		}
		if(SP100_CCU_State == CCU_OFF)
		{
			SP100_LCD_ALL_SEG(SEG_OFF);
			//--> Warning -> CCU_OFF_State
		}
		if(SP100_CCU_State == CCU_AUTO)
		{
			//SP100_LCD_ALL_SEG(SEG_ON);
			//--> Warning -> CCU_AUTO_State
		}
		if(SP100_CCU_State == CCU_DEF)
		{
			//SP100_LCD_ALL_SEG(SEG_ON);
			//--> Warning -> CCU_DEF_State
		}
		*/
	} //--> End of while(1)
}
