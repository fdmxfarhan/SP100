/* Includes *******************************************************************/
#include "SP100_Blower.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
int		dacVal;
//float	SP100_Blower_VOLT;
extern	DAC_HandleTypeDef	hdac;

/* Functions body *************************************************************/
/* SP100_Blower_Init -----------------------------------------------------------*/
void SP100_Blower_Init(void)
{
	dacVal = 0;
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacVal);
}

/* SP100_Blower_OFF ------------------------------------------------------------*/
void SP100_Blower_OFF(void)
{
	if(dacVal > 0)			 dacVal -= 50;
	if(dacVal > 3000)		{dacVal = 3000;}
	if(dacVal < 0)			{dacVal = 0;}

	//Blower_Relay_OFF;

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacVal);
}

/* SP100_Blower_Up -------------------------------------------------------------*/
void SP100_Blower_Up(void)
{
	dacVal += 20;
	if(dacVal < 1000)		{dacVal = 1000;}
	if(dacVal > 4000)		{dacVal = 4000;}

	//if(dacVal == 4000)		{Blower_Relay_ON;}
	//else					{Blower_Relay_OFF;}

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacVal);
}

/* SP100_Blower_Down -----------------------------------------------------------*/
void SP100_Blower_Down(void)
{
	dacVal -= 50;
	if(dacVal < 1000)		{dacVal = 1000;}
	if(dacVal > 4000)		{dacVal = 4000;}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacVal);
}

/* SP100_Blower_Handler --------------------------------------------------------*/
void SP100_Blower_Handler(Blower_State state)
{
	if(Blower_Auto_Ctrl_State == Auto_Ctrl_OFF || BLOWER_MODE == 0 || SP100_CCU_State == CCU_DEF){
		SP100_Blower_Dest_Volt1 = state2volt(state);
		switch (state)
		{
			case Blower_OFF:
			{
				SP100_Blower_OFF();
				break;
			}
			case Blower_L1:
			{
				if(dacVal < SP100_Blower_DAC_L1)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L1)
					SP100_Blower_Down();
				break;
			}
			case Blower_L2:
			{
				if(dacVal < SP100_Blower_DAC_L2)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L2)
					SP100_Blower_Down();
				break;
			}
			case Blower_L3:
			{
				if(dacVal < SP100_Blower_DAC_L3)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L3)
					SP100_Blower_Down();
				break;
			}
			case Blower_L4:
			{
				if(dacVal < SP100_Blower_DAC_L4)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L4)
					SP100_Blower_Down();
				break;
			}
			case Blower_L5:
			{
				if(dacVal < SP100_Blower_DAC_L5)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L5)
					SP100_Blower_Down();
				break;
			}
			case Blower_L6:
			{
				if(dacVal < SP100_Blower_DAC_L6)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L6)
					SP100_Blower_Down();
				break;
			}
			case Blower_L7:
			{
				if(dacVal < SP100_Blower_DAC_L7)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L7)
					SP100_Blower_Down();
				break;
			}
			case Blower_L8:
			{
				if(dacVal < SP100_Blower_DAC_L8)
					SP100_Blower_Up();
				else if(dacVal > SP100_Blower_DAC_L8)
					SP100_Blower_Down();
				break;
			}		
		}
	}
	else{
		if(SP100_CCU_State == CCU_OFF || SP100_CCU_State == CCU_IGN_OFF){
			SP100_Blower_OFF();
			SP100_Blower_Dest_Volt1 = 0;
		}
		else{
			float v = (SP100_Blower_Dest_Volt1 - 4) * 252.17 + 1100;
			if(dacVal < v)
				SP100_Blower_Up();
			else if(dacVal > v)
				SP100_Blower_Down();
		}
	}
}
void SP100_Blower_State_Down(void)
{
	switch (SP100_Blower_State)
	{
		case Blower_OFF:
		{
			SP100_Blower_State = Blower_OFF;
			break;
		}
		case Blower_L1:
		{
			SP100_Blower_State = Blower_L1;
			break;
		}
		case Blower_L2:
		{
			SP100_Blower_State = Blower_L1;
			break;
		}
		case Blower_L3:
		{
			SP100_Blower_State = Blower_L2;
			break;
		}
		case Blower_L4:
		{
			SP100_Blower_State = Blower_L3;
			break;
		}
		case Blower_L5:
		{
			SP100_Blower_State = Blower_L4;
			break;
		}
		case Blower_L6:
		{
			SP100_Blower_State = Blower_L5;
			break;
		}
		case Blower_L7:
		{
			SP100_Blower_State = Blower_L6;
			break;
		}
		case Blower_L8:
		{
			SP100_Blower_State = Blower_L7;
			break;
		}		
	}
}
void SP100_Blower_State_Up(void)
{
	switch (SP100_Blower_State)
	{
		case Blower_OFF:
		{
			SP100_Blower_State = Blower_OFF;
			break;
		}
		case Blower_L1:
		{
			SP100_Blower_State = Blower_L2;
			break;
		}
		case Blower_L2:
		{
			SP100_Blower_State = Blower_L3;
			break;
		}
		case Blower_L3:
		{
			SP100_Blower_State = Blower_L4;
			break;
		}
		case Blower_L4:
		{
			SP100_Blower_State = Blower_L5;
			break;
		}
		case Blower_L5:
		{
			SP100_Blower_State = Blower_L6;
			break;
		}
		case Blower_L6:
		{
			SP100_Blower_State = Blower_L7;
			break;
		}
		case Blower_L7:
		{
			SP100_Blower_State = Blower_L8;
			break;
		}
		case Blower_L8:
		{
			SP100_Blower_State = Blower_L8;
			break;
		}		
	}
}
int SP100_Blower_Get_State_Num(Blower_State state){
	switch (state)
	{
		case Blower_OFF:
		{
			return 0;
		}
		case Blower_L1:
		{
			return 1;
		}
		case Blower_L2:
		{
			return 2;
		}
		case Blower_L3:
		{
			return 3;
		}
		case Blower_L4:
		{
			return 4;
		}
		case Blower_L5:
		{
			return 5;
		}
		case Blower_L6:
		{
			return 6;
		}
		case Blower_L7:
		{
			return 7;
		}
		case Blower_L8:
		{
			return 8;
		}		
	}
	return -1;
}
Blower_State volt2state(float v){
	
	if(v < SP100_Blower_Volt_L1) return Blower_L1;
	else if(v < SP100_Blower_Volt_L2) return Blower_L2;
	else if(v < SP100_Blower_Volt_L3) return Blower_L3;
	else if(v < SP100_Blower_Volt_L4) return Blower_L4;
	else if(v < SP100_Blower_Volt_L5) return Blower_L5;
	else if(v < SP100_Blower_Volt_L6) return Blower_L6;
	else if(v < SP100_Blower_Volt_L7) return Blower_L7;
	else  return Blower_L8;
	/*
	if(v < 4.2) return Blower_L1;
	if(v < 5.2 && v > 4.6)   return Blower_L2;
	if(v < 6.4 && v > 5.6)   return Blower_L3;
	if(v < 7.6 && v > 6.8)   return Blower_L4;
	if(v < 8.8 && v > 8.0)   return Blower_L5;
	if(v < 10.0 && v > 9.2)  return Blower_L6;
	if(v < 11.2 && v > 10.4) return Blower_L7;
	if(v > 11.6) 						 return Blower_L8;
	return SP100_Blower_State;
	*/
}
float state2volt(Blower_State state){
	switch (state)
	{
		case Blower_OFF:
		{
			return 0;
		}
		case Blower_L1:
		{
			return SP100_Blower_Volt_L1;
		}
		case Blower_L2:
		{
			return SP100_Blower_Volt_L2;
		}
		case Blower_L3:
		{
			return SP100_Blower_Volt_L3;
		}
		case Blower_L4:
		{
			return SP100_Blower_Volt_L4;
		}
		case Blower_L5:
		{
			return SP100_Blower_Volt_L5;
		}
		case Blower_L6:
		{
			return SP100_Blower_Volt_L6;
		}
		case Blower_L7:
		{
			return SP100_Blower_Volt_L7;
		}
		case Blower_L8:
		{
			return SP100_Blower_Volt_L8;
		}		
	}
	return -1;
}
