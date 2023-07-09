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
	dacVal -= 25;
	if(dacVal < 1000)		{dacVal = 1000;}
	if(dacVal > 4000)		{dacVal = 4000;}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacVal);
}

/* SP100_Blower_Handler --------------------------------------------------------*/
void SP100_Blower_Handler(Blower_State state)
{
	
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
