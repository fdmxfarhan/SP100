/* Includes *******************************************************************/
#include "nx7_mode_ma.h"
#include "nx7_tle94106es.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
float	NX7_Mode_FB;
extern	TIM_HandleTypeDef	htim7;
MA_Lock_State  Mode_MA_Lock_State;

/* Functions body *************************************************************/
/* NX7_Mode_MA_STP -----------------------------------------------------------*/
void NX7_Mode_MA_STP(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if(temp != 0x05)
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x05;		//--> OUTH2:HZ & OUTL2:ON & OUTH1:HZ & OUTL1:ON
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Stop --> Mode_Lock_State
		HAL_TIM_Base_Stop_IT(&htim7);
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	}
}

/* NX7_Mode_MA_FWD -----------------------------------------------------------*/
void NX7_Mode_MA_FWD(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if((temp != 0x06) && (Mode_MA_Lock_State == MA_Lock_OK))
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x06;		//--> OUTH2:HZ & OUTL2:ON & OUTH1:ON & OUTL1:HZ
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Start --> Mode_Lock_State
		htim7.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim7);
	}
}

/* NX7_Mode_MA_RVS -----------------------------------------------------------*/
void NX7_Mode_MA_RVS(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if((temp != 0x09) && (Mode_MA_Lock_State == MA_Lock_OK))
	{
		temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x09;		//--> OUTH2:ON & OUTL2:HZ & OUTH1:HZ & OUTL1:ON
		NX7_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Start --> Mode_Lock_State
		htim7.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim7);
	}
}

/* NX7_Mode_MA_Handler -------------------------------------------------------*/
void NX7_Mode_MA_Handler(Mode_State state)
{
	switch (state)
	{
		case Mode_Face:
		{
			if(NX7_Mode_FB <= (NX7_Mode_Face_Pos-NX7_Mode_Tolerance))
				NX7_Mode_MA_FWD();
			else if(NX7_Mode_FB >= (NX7_Mode_Face_Pos+NX7_Mode_Tolerance))
				NX7_Mode_MA_RVS();
			else
				NX7_Mode_MA_STP();
			break;			
		}
		case Mode_Face_Foot:
		{
			if(NX7_Mode_FB <= (NX7_Mode_Face_Foot_Pos-NX7_Mode_Tolerance))
				NX7_Mode_MA_FWD();
			else if(NX7_Mode_FB >= (NX7_Mode_Face_Foot_Pos+NX7_Mode_Tolerance))
				NX7_Mode_MA_RVS();
			else
				NX7_Mode_MA_STP();
			break;			
		}
		case Mode_Foot:
		{
			if(NX7_Mode_FB <= (NX7_Mode_Foot_Pos-NX7_Mode_Tolerance))
				NX7_Mode_MA_FWD();
			else if(NX7_Mode_FB >= (NX7_Mode_Foot_Pos+NX7_Mode_Tolerance))
				NX7_Mode_MA_RVS();
			else
				NX7_Mode_MA_STP();
			break;			
		}
		case Mode_Foot_Def:
		{
			if(NX7_Mode_FB <= (NX7_Mode_Foot_Def_Pos-NX7_Mode_Tolerance))
				NX7_Mode_MA_FWD();
			else if(NX7_Mode_FB >= (NX7_Mode_Foot_Def_Pos+NX7_Mode_Tolerance))
				NX7_Mode_MA_RVS();
			else
				NX7_Mode_MA_STP();
			break;			
		}
		case Mode_Def:
		{
			if(NX7_Mode_FB <= (NX7_Mode_Def_Pos-NX7_Mode_Tolerance))
				NX7_Mode_MA_FWD();
			else if(NX7_Mode_FB >= (NX7_Mode_Def_Pos+NX7_Mode_Tolerance))
				NX7_Mode_MA_RVS();
			else
				NX7_Mode_MA_STP();
			break;			
		}
	}
}
