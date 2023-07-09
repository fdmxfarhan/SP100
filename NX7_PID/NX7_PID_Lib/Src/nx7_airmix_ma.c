/* Includes *******************************************************************/
#include "nx7_airmix_ma.h"
#include "nx7_tle94106es.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
float	NX7_Airmix_FB;
extern	TIM_HandleTypeDef	htim6;
MA_Lock_State  Airmix_MA_Lock_State;

/* Functions body *************************************************************/
/* NX7_Airmix_MA_STP ---------------------------------------------------------*/
void NX7_Airmix_MA_STP(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0xF0;
	if(temp != 0x50)
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0x0F;
		temp |= 0x50;		//--> OUTH4:HZ & OUTL4:ON & OUTH3:HZ & OUTL3:ON
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Stop --> Airmix_Lock_State
		HAL_TIM_Base_Stop_IT(&htim6);
		__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
	}
}

/* NX7_Airmix_MA_FWD ---------------------------------------------------------*/
void NX7_Airmix_MA_FWD(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0xF0;
	if((temp != 0x60) && (Airmix_MA_Lock_State == MA_Lock_OK))
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0x0F;
		temp |= 0x60;		//--> OUTH4:HZ & OUTL4:ON & OUTH3:ON & OUTL3:HZ
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Start --> Airmix_Lock_State
		htim6.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim6);
	}
}

/* NX7_Airmix_MA_RVS -----------------------------------------------------------*/
void NX7_Airmix_MA_RVS(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0xF0;
	if((temp != 0x90) && (Airmix_MA_Lock_State == MA_Lock_OK))
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0x0F;
		temp |= 0x90;		//--> OUTH4:ON & OUTL4:HZ & OUTH3:HZ & OUTL3:ON
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM6 Start --> Airmix_Lock_State
		htim6.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim6);
	}
}

/* NX7_Airmix_MA_Handler -------------------------------------------------------*/
void NX7_Airmix_MA_Handler(Airmix_State state)
{
	switch (state)
	{
		case Airmix_Lo:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_Lo_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_Lo_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_05:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_05_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_05_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_10:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_10_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_10_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_15:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_15_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_15_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_20:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_20_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_20_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_25:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_25_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_25_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_30:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_30_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_30_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_35:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_35_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_35_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_40:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_40_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_40_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_45:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_45_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_45_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_50:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_50_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_50_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_55:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_55_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_55_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_60:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_60_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_60_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_65:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_65_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_65_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_70:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_70_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_70_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_75:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_75_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_75_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_80:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_80_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_80_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_85:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_85_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_85_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_90:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_90_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_90_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
		case Airmix_95:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_95_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_95_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;
		}
		case Airmix_Hi:
		{
			if(NX7_Airmix_FB <= (NX7_Airmix_Hi_Pos-NX7_Airmix_Tolerance))
				NX7_Airmix_MA_FWD();
			else if(NX7_Airmix_FB >= (NX7_Airmix_Hi_Pos+NX7_Airmix_Tolerance))
				NX7_Airmix_MA_RVS();
			else
				NX7_Airmix_MA_STP();
			break;			
		}
	}
}
