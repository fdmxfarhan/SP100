/* Includes *******************************************************************/
#include "SP100_Airmix.h"
#include "SP100_TLE94108ES.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
//float	SP100_Airmix_FB;
extern	TIM_HandleTypeDef	htim6;
//MA_Lock_State  Airmix_Lock_State;

/* Functions body *************************************************************/
/* SP100_Airmix_STP ---------------------------------------------------------*/
void SP100_Airmix_STP(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	if((temp & 0xF0) != 0x50)
	{
		temp &= 0x0F;
		temp |= 0x50;		//--> OUTH4:HZ & OUTL4:ON & OUTH3:HZ & OUTL3:ON
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Stop --> Airmix_Lock_State
		//HAL_TIM_Base_Stop_IT(&htim6);
		//__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
	}
}

/* SP100_Airmix_FWD ---------------------------------------------------------*/
void SP100_Airmix_FWD(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	if((temp & 0xF0) != 0x90) //&& (Airmix_MA_Lock_State == MA_Lock_OK))
	{
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0x0F;
		temp |= 0x90;		//--> OUTH4:HZ & OUTL4:ON & OUTH3:ON & OUTL3:HZ
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Start --> Airmix_Lock_State
		//htim6.Instance->CNT = 0x00;
		//__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		//HAL_TIM_Base_Start_IT(&htim6);
	}
}

/* SP100_Airmix_RVS -----------------------------------------------------------*/
void SP100_Airmix_RVS(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	if((temp & 0xF0) != 0x60) //&& (Airmix_MA_Lock_State == MA_Lock_OK))
	{
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0x0F;
		temp |= 0x60;		//--> OUTH4:ON & OUTL4:HZ & OUTH3:HZ & OUTL3:ON
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Start --> Airmix_Lock_State
		//htim6.Instance->CNT = 0x00;
		//__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		//HAL_TIM_Base_Start_IT(&htim6);
	}
}

/* SP100_Airmix_Handler -------------------------------------------------------*/
void SP100_Airmix_Handler(Airmix_State state)
{
	switch (state)
	{
		case Airmix_Lo:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_Lo_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_Lo_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_05:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_05_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_05_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_10:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_10_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_10_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_15:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_15_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_15_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_20:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_20_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_20_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_25:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_25_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_25_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_30:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_30_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_30_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_35:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_35_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_35_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_40:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_40_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_40_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_45:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_45_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_45_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_50:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_50_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_50_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_55:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_55_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_55_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_60:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_60_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_60_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_65:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_65_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_65_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_70:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_70_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_70_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_75:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_75_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_75_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_80:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_80_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_80_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_85:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_85_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_85_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_90:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_90_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_90_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
		case Airmix_95:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_95_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_95_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;
		}
		case Airmix_Hi:
		{
			if(SP100_Airmix_FB <= (SP100_Airmix_Hi_Pos-SP100_Airmix_Tolerance))
				SP100_Airmix_FWD();
			else if(SP100_Airmix_FB >= (SP100_Airmix_Hi_Pos+SP100_Airmix_Tolerance))
				SP100_Airmix_RVS();
			else
				SP100_Airmix_STP();
			break;			
		}
	}
}


Airmix_State SP100_Airmix_int2state(int val)
{
	if(val == 0)   return(Airmix_Lo);
	if(val == 5)   return(Airmix_05);
	if(val == 10)  return(Airmix_10);
	if(val == 15)  return(Airmix_15);
	if(val == 20)  return(Airmix_20);
	if(val == 25)  return(Airmix_25);
	if(val == 30)  return(Airmix_30);
	if(val == 35)  return(Airmix_35);
	if(val == 40)  return(Airmix_40);
	if(val == 45)  return(Airmix_45);
	if(val == 50)  return(Airmix_50);
	if(val == 55)  return(Airmix_55);
	if(val == 60)  return(Airmix_60);
	if(val == 65)  return(Airmix_65);
	if(val == 70)  return(Airmix_70);
	if(val == 75)  return(Airmix_75);
	if(val == 80)  return(Airmix_80);
	if(val == 85)  return(Airmix_85);
	if(val == 90)  return(Airmix_90);
	if(val == 95)  return(Airmix_95);
	if(val == 100) return(Airmix_Hi);
	
}

