/* Includes *******************************************************************/
#include <math.h>
#include <stdlib.h>
#include "SP100_atc_ccu.h"
#include "SP100_ext_isr.h"
#include "SP100_adc_isr.h"
#include "SP100_TLE94108ES.h"
#include "SP100_Intake.h"
#include "SP100_lcd.h"
#include "SP100_Mode.h"
#include "SP100_Airmix.h"
#include "SP100_Blower.h"


/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/
/* Private variables **********************************************************/
int lcd_cnt = 0;
int auto_cnt = 0;
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
	if(HAL_GPIO_ReadPin(IGN_GPIO_Port, IGN_Pin))
		SP100_CCU_State = CCU_OFF;
	else
		SP100_CCU_State = CCU_IGN_OFF;
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
		//SP100_Mode_FWD();
		//SP100_Airmix_FWD();
		//lcd_cnt++;
		if(SP100_CCU_State != CCU_OFF)
			SP100_CCU_State_Updater(CCU_OFF);
		SP100_Mode_SEG_State = Mode_SEG_OFF;
	}
	/* -------------------------------------------------------- <AUTO_SW_Pin> */
	if(SW_Pin == AUTO_SW_Pin)
	{
		//SP100_Mode_RVS();
		//SP100_Airmix_RVS();
		//lcd_cnt--;
		Intake_Auto_Ctrl_State = Auto_Ctrl_ON;
		Mode_Auto_Ctrl_State = Auto_Ctrl_ON;
		Blower_Auto_Ctrl_State = Auto_Ctrl_ON;
		AC_Auto_Ctrl_State = Auto_Ctrl_ON;
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
				SP100_CCU_State_Updater(CCU_AUTO);
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
				SP100_CCU_State =  CCU_DEF;
				SP100_AC_State = AC_ON;
				SP100_Blower_State = Blower_L8;
				SP100_Intake_State = Intake_Fresh;
				SP100_Mode_State = Mode_Def;
				break;
			}
			case CCU_AUTO:
			{
				SP100_CCU_State_Updater(CCU_DEF);
				SP100_AC_State = AC_ON;
				SP100_Blower_State = Blower_L8;
				SP100_Intake_State = Intake_Fresh;
				SP100_Mode_State = Mode_Def;
				break;
			}
			case CCU_DEF:
			{
				SP100_CCU_State_Updater(SP100_CCU_preState);
				break;
			}
			case CCU_SENSOR:
			{
				SP100_CCU_State_Updater(CCU_DEF);
				SP100_AC_State = AC_ON;
				SP100_Blower_State = Blower_L8;
				SP100_Intake_State = Intake_Fresh;
				SP100_Mode_State = Mode_Def;
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
		//SP100_Mode_STP();
		//SP100_Airmix_STP();
		//if(SP100_AC_State == AC_ON) SP100_AC_State = AC_OFF;
		//else									 		  SP100_AC_State = AC_ON;
		AC_Auto_Ctrl_State = Auto_Ctrl_OFF;
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			SP100_CCU_State_Updater(SP100_CCU_preState);
			SP100_AC_State = AC_ON;
			break;
		}
		case CCU_AUTO:
		{
			if(SP100_AC_State == AC_ON) SP100_AC_State = AC_OFF;
			else									 		  SP100_AC_State = AC_ON;
			SP100_CCU_State_Updater(CCU_SENSOR);
			break;
		}
		case CCU_DEF:
		{
			if(SP100_AC_State == AC_ON) SP100_AC_State = AC_OFF;
			else									 		  SP100_AC_State = AC_ON;
			break;
		}
		case CCU_SENSOR:
		{
			if(SP100_AC_State == AC_ON) SP100_AC_State = AC_OFF;
			else									 		  SP100_AC_State = AC_ON;
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
		//if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
		//else 																	 SP100_Intake_State = Intake_Fresh;
		Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
		switch (SP100_CCU_State)
		{
			case CCU_OFF:
			{
				if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
				else 																	 SP100_Intake_State = Intake_Fresh;
				break;
			}
			case CCU_AUTO:
			{
				if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
				else 																	 SP100_Intake_State = Intake_Fresh;
				SP100_CCU_State_Updater(CCU_SENSOR);
				break;
			}
			case CCU_DEF:
			{
				if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
				else 																	 SP100_Intake_State = Intake_Fresh;
				break;
			}
			case CCU_SENSOR:
			{
				if(SP100_Intake_State == Intake_Fresh) SP100_Intake_State = Intake_Recycle;
				else 																	 SP100_Intake_State = Intake_Fresh;
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
		/*
		if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
		else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
		else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
		else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
		else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
		*/
		Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
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
			SP100_Mode_SEG_State = Mode_SEG_ON;
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
			SP100_CCU_State_Updater(CCU_SENSOR);
			break;
		}
		case CCU_DEF:
		{
			if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
			else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
			else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
			else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
			else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
			SP100_CCU_State_Updater(CCU_SENSOR);
			break;
		}
		case CCU_SENSOR:
		{
			if(SP100_Mode_State == Mode_Face)				{SP100_Mode_State = Mode_Face_Foot;}
			else if(SP100_Mode_State == Mode_Face_Foot)		{SP100_Mode_State = Mode_Foot;}
			else if(SP100_Mode_State == Mode_Foot)			{SP100_Mode_State = Mode_Foot_Def;}
			else if(SP100_Mode_State == Mode_Foot_Def)		{SP100_Mode_State = Mode_Def;}
			else if(SP100_Mode_State == Mode_Def)			{SP100_Mode_State = Mode_Face;}
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
	/* --------------------------------------------------- <Blower_Up_SW_Pin> */
	if(SW_Pin == Blower_Up_SW_Pin)
	{
		//if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
		switch (SP100_CCU_State)
		{
			case CCU_OFF:
			{
				SP100_Blower_State = Blower_L1;
				SP100_CCU_State_Updater(SP100_CCU_preState);
				break;
			}
			case CCU_AUTO:
			{
				if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
				SP100_CCU_State_Updater(CCU_SENSOR);
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
				break;
			}
			case CCU_DEF:
			{
				if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
				break;
			}
			case CCU_SENSOR:
			{
				if(SP100_Blower_State < Blower_L8)	{SP100_Blower_State++;}
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
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
	/* ------------------------------------------------- <Blower_Down_SW_Pin> */
	if(SW_Pin == Blower_Down_SW_Pin)
	{
		//if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
		switch (SP100_CCU_State)
		{
			case CCU_OFF:
			{
				SP100_Blower_State = Blower_L1;
				SP100_CCU_State_Updater(SP100_CCU_preState);
				break;
			}
			case CCU_AUTO:
			{
				if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
				SP100_CCU_State_Updater(CCU_SENSOR);
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
				break;
			}
			case CCU_DEF:
			{
				if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
				break;
			}
			case CCU_SENSOR:
			{
				if(SP100_Blower_State > Blower_L1)	{SP100_Blower_State--;}
				Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
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
	/* --------------------------------------------------- <Airmix_Up_SW_Pin> */
	if(SW_Pin == Airmix_Up_SW_Pin)
	{
		//if(SP100_Set_Point < 32.5) SP100_Set_Point += 0.5;
		switch (SP100_CCU_State)
		{
			case CCU_OFF:
			{
				break;
			}
			case CCU_AUTO:
			{
				if(SP100_Set_Point < 32.5) SP100_Set_Point += 0.5;
				break;
			}
			case CCU_DEF:
			{
				if(SP100_Set_Point < 32.5) SP100_Set_Point += 0.5;
				break;
			}
			case CCU_SENSOR:
			{
				if(SP100_Set_Point < 32.5) SP100_Set_Point += 0.5;
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
		//if(SP100_Set_Point > 13.5) SP100_Set_Point -= 0.5;
		switch (SP100_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			if(SP100_Set_Point > 13.5) SP100_Set_Point -= 0.5;
			break;
		}
		case CCU_DEF:
		{
			if(SP100_Set_Point > 13.5) SP100_Set_Point -= 0.5;
			break;
		}
		case CCU_SENSOR:
		{
			if(SP100_Set_Point > 13.5) SP100_Set_Point -= 0.5;
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
		/*
		if(SP100_R_DEF_State == R_DEF_OFF)		{SP100_R_DEF_State = R_DEF_ON;}
		else if(SP100_R_DEF_State == R_DEF_ON)	{SP100_R_DEF_State = R_DEF_OFF;}
		*/
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
				break;
			}
			case CCU_IGN_OFF:
			{
				break;
			}
		}
	}
}
void SP100_Airmix_Auto_Calculate(int TS, int TA, int TC)
{
	if(TS - TA > 1){
		if(TS < 14)								SP100_Airmix_State = Airmix_Lo;
		else if(TS > 32)					SP100_Airmix_State = Airmix_Hi;
		else if(TS - TC <= -5)    SP100_Airmix_State = Airmix_50;
		else if(TS - TC <= -4.5)  SP100_Airmix_State = Airmix_55;
		else if(TS - TC <= -4  )  SP100_Airmix_State = Airmix_55;
		else if(TS - TC <= -3.5)  SP100_Airmix_State = Airmix_60;
		else if(TS - TC <= -3  )  SP100_Airmix_State = Airmix_60;
		else if(TS - TC <= -2.5)  SP100_Airmix_State = Airmix_65;
		else if(TS - TC <= -2  )  SP100_Airmix_State = Airmix_70;
		else if(TS - TC <= -1.5)  SP100_Airmix_State = Airmix_70;
		else if(TS - TC <= -1  )  SP100_Airmix_State = Airmix_75;
		else if(TS - TC <= -0.5)  SP100_Airmix_State = Airmix_75;
		else if(TS - TC <=  0  )  SP100_Airmix_State = Airmix_80;
		else if(TS - TC <=  0.5)  SP100_Airmix_State = Airmix_80;
		else if(TS - TC <=  1  )  SP100_Airmix_State = Airmix_85;
		else if(TS - TC <=  1.5)  SP100_Airmix_State = Airmix_85;
		else if(TS - TC <=  2  )  SP100_Airmix_State = Airmix_90;
		else if(TS - TC <=  2.5)  SP100_Airmix_State = Airmix_90;
		else if(TS - TC <=  3  )  SP100_Airmix_State = Airmix_95;
		else if(TS - TC <=  3.5)  SP100_Airmix_State = Airmix_95;
		else if(TS - TC <=  4  )  SP100_Airmix_State = Airmix_Hi;
		else if(TS - TC <=  4.5)  SP100_Airmix_State = Airmix_Hi;
		else if(TS - TC <=  5  )  SP100_Airmix_State = Airmix_Hi;
		else 				     		    	SP100_Airmix_State = Airmix_Hi;
	}
	if(TS - TC < -1){
		if(TS < 14)								SP100_Airmix_State = Airmix_Lo;
		else if(TS > 32)					SP100_Airmix_State = Airmix_Hi;
		else if(TS - TC <= -5)    SP100_Airmix_State = Airmix_Lo;
		else if(TS - TC <= -4.5)  SP100_Airmix_State = Airmix_Lo;
		else if(TS - TC <= -4  )  SP100_Airmix_State = Airmix_Lo;
		else if(TS - TC <= -3.5)  SP100_Airmix_State = Airmix_Lo;
		else if(TS - TC <= -3  )  SP100_Airmix_State = Airmix_05;
		else if(TS - TC <= -2.5)  SP100_Airmix_State = Airmix_05;
		else if(TS - TC <= -2  )  SP100_Airmix_State = Airmix_10;
		else if(TS - TC <= -1.5)  SP100_Airmix_State = Airmix_10;
		else if(TS - TC <= -1  )  SP100_Airmix_State = Airmix_15;
		else if(TS - TC <= -0.5)  SP100_Airmix_State = Airmix_15;
		else if(TS - TC <=  0  )  SP100_Airmix_State = Airmix_20;
		else if(TS - TC <=  0.5)  SP100_Airmix_State = Airmix_20;
		else if(TS - TC <=  1  )  SP100_Airmix_State = Airmix_25;
		else if(TS - TC <=  1.5)  SP100_Airmix_State = Airmix_30;
		else if(TS - TC <=  2  )  SP100_Airmix_State = Airmix_35;
		else if(TS - TC <=  2.5)  SP100_Airmix_State = Airmix_40;
		else if(TS - TC <=  3  )  SP100_Airmix_State = Airmix_45;
		else if(TS - TC <=  3.5)  SP100_Airmix_State = Airmix_50;
		else if(TS - TC <=  4  )  SP100_Airmix_State = Airmix_55;
		else if(TS - TC <=  4.5)  SP100_Airmix_State = Airmix_60;
		else if(TS - TC <=  5  )  SP100_Airmix_State = Airmix_65;
		else 				     		    	SP100_Airmix_State = Airmix_70;
	}
}

void SP100_CCU_Auto_Calculations(void)
{
	float TS = SP100_Set_Point;
	float TA = SP100_Ambient_Sensor;
	float TC = SP100_Cabin_Sensor;
	float TW = SP100_Water_Sensor;
	//float TE = SP100_Evap_Sensor;
	
	// ------------ Intake
	if(Intake_Auto_Ctrl_State == Auto_Ctrl_ON){
		if(TS < 14)								SP100_Intake_State = Intake_Recycle;
		else if(TS > 32)					SP100_Intake_State = Intake_Fresh;
		else if(TS - TA > 1){
			if(TS - TC >= 1) SP100_Intake_State = Intake_Recycle;
			else 				     SP100_Intake_State = Intake_Fresh;
		}
		else if(TS - TC < -1){
			if(TS - TC < 1)  SP100_Intake_State = Intake_Recycle;
			else 				     SP100_Intake_State = Intake_Fresh;
		}
	}
	// ------------ Mode
	if(Mode_Auto_Ctrl_State == Auto_Ctrl_ON){
		if(TS < 14)								SP100_Mode_State = Mode_Face;
		else if(TS > 32)					SP100_Mode_State = Mode_Foot;
		else if(TS - TA > 1){
			if(TS - TC <= -4.5)     SP100_Mode_State = Mode_Foot_Def;
			else if(TS - TC < -1.5) SP100_Mode_State = Mode_Face_Foot;
			else if(TS - TC < 2.5)  SP100_Mode_State = Mode_Foot;
			else 				     		    SP100_Mode_State = Mode_Face_Foot;
		}
		else if(TS - TC < -1){
			if(TS - TC <= -1.5) 		SP100_Mode_State = Mode_Face;
			else if(TS - TC < 3.5)  SP100_Mode_State = Mode_Face_Foot;
			else 				     		    SP100_Mode_State = Mode_Foot_Def;
		}
	}
	// ------------ Airmix
	SP100_Airmix_Auto_Calculate(TS, TA, TC);
	// ------------ Blower
	if(Blower_Auto_Ctrl_State == Auto_Ctrl_ON){
		int s = 0;
		if(TS < 14)			  s = 8;
		else if(TS > 32)	s = 8;
		else if(TS - TA > 1){
			if(TW > 65){
				if(TS-TA >= 1) 				s = ceil(abs((int) (TS-TC)) + 0.5);
				else if(TS-TA <= -1)  s = 1;
				else 								  s = ceil(abs((int) ((TS-TC)*0.4)) + 1);
			}
			else if(TW > 35){
				if(abs((int) (TS-TA)) > 1) s = floor(0.2*TW - 5);
				else											 s = 1;
			}
			else s = 1;
		}
		else if(TS - TC < -1){
			if(TS-TA >= -5 && TS-TA < 0) 				 s = ceil(abs((int) (TS-TC)) + 0.5);
			else if(TS-TA >= -10 && TS-TA < -5)  s = ceil(abs((int) (TS-TC)) + 1.5);
			else if(TS-TA >= -20 && TS-TA < -10) s = ceil(abs((int) (TS-TC)) + 2.5);
			else if(TS-TA < -20) 								 s = ceil(abs((int) (TS-TC)) + 1.5);
		}
		if(s < SP100_Blower_Get_State_Num(SP100_Blower_State)) SP100_Blower_State_Down();
		if(s > SP100_Blower_Get_State_Num(SP100_Blower_State)) SP100_Blower_State_Up();
//		if(s <= 1) 			SP100_Blower_State = Blower_L1;
//		else if(s <= 2) SP100_Blower_State = Blower_L2;
//		else if(s <= 3) SP100_Blower_State = Blower_L3;
//		else if(s <= 4) SP100_Blower_State = Blower_L4;
//		else if(s <= 5) SP100_Blower_State = Blower_L5;
//		else if(s <= 6) SP100_Blower_State = Blower_L6;
//		else if(s <= 7) SP100_Blower_State = Blower_L7;
//		else 					  SP100_Blower_State = Blower_L8;
		// ------------ AC
		if(TS < 14)						SP100_AC_State = AC_ON;
		else if(TS > 32)			SP100_AC_State = AC_OFF;
		else if(TS - TC > 1) 	SP100_AC_State = AC_OFF;
		else if(TS - TC < -1)	SP100_AC_State = AC_ON;
	}
}
	
/* SP100_CCU_Infinite_Loop ---------------------------------------------------*/
void SP100_CCU_Infinite_Loop(void)
{
	while(1)
	{
		if(SP100_CCU_State == CCU_IGN_OFF)
		{
			SP100_LCD_ALL_SEG(SEG_OFF);
			SP100_Blower_Handler(Blower_OFF);
			SP100_Intake_Handler(SP100_Intake_State);
			AUTO_LED_OFF;
			AC_LED_OFF;
			DEF_LED_OFF;
			Intake_LED_OFF;
			R_DEF_LED_OFF;
			SP100_Mode_Handler(SP100_Mode_State);
		}
		if(SP100_CCU_State == CCU_OFF)
		{
			AUTO_LED_OFF;
			AC_LED_OFF;
			DEF_LED_OFF;
			SP100_LCD_OFF_State();
			SP100_Blower_Handler(Blower_OFF);
			SP100_Intake_Handler(SP100_Intake_State);
			SP100_Mode_Handler(SP100_Mode_State);
			SP100_Airmix_Handler(SP100_Airmix_State);
		}
		if(SP100_CCU_State == CCU_AUTO)
		{
			if(auto_cnt == 20){
				SP100_CCU_Auto_Calculations();
				auto_cnt = 0;
			}else auto_cnt++;
			SP100_Airmix_Handler(SP100_Airmix_State);
			SP100_Intake_Handler(SP100_Intake_State);
			SP100_Mode_Handler(SP100_Mode_State);
			SP100_Blower_Handler(SP100_Blower_State);
			SP100_LCD_Update();
		}
		if(SP100_CCU_State == CCU_SENSOR)
		{
			if(auto_cnt == 20){
				SP100_CCU_Auto_Calculations();
				auto_cnt = 0;
			}else auto_cnt++;
			SP100_Airmix_Handler(SP100_Airmix_State);
			SP100_Intake_Handler(SP100_Intake_State);
			SP100_Mode_Handler(SP100_Mode_State);
			SP100_Blower_Handler(SP100_Blower_State);
			SP100_LCD_Update();
		}
		if(SP100_CCU_State == CCU_DEF)
		{
			SP100_Airmix_Handler(SP100_Airmix_State);
			SP100_Intake_Handler(SP100_Intake_State);
			SP100_Mode_Handler(SP100_Mode_State);
			SP100_Blower_Handler(SP100_Blower_State);
			SP100_Airmix_Auto_Calculate(SP100_Set_Point, SP100_Ambient_Sensor, SP100_Cabin_Sensor);
			SP100_LCD_Update();
		}
	}
}




