/* Includes *******************************************************************/
#include "SP100_Mode.h"
#include "SP100_TLE94108ES.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
//float	SP100_Mode_FB;
extern	TIM_HandleTypeDef	htim7;
//MA_Lock_State  Mode_Lock_State;

/* Functions body *************************************************************/
/* SP100_Mode_STP -----------------------------------------------------------*/
void SP100_Mode_STP(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if(temp != 0x05)
	{
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x05;		//--> OUTH2:HZ & OUTL2:ON & OUTH1:HZ & OUTL1:ON
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Stop --> Mode_Lock_State
		HAL_TIM_Base_Stop_IT(&htim7);
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	}
}

/* SP100_Mode_FWD -----------------------------------------------------------*/
void SP100_Mode_FWD(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if((temp != 0x09) && (Mode_MA_Lock_State == MA_Lock_OK))
	{
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x09;		//--> OUTH2:HZ & OUTL2:ON & OUTH1:ON & OUTL1:HZ
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Start --> Mode_Lock_State
		htim7.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim7);
	}
}

/* SP100_Mode_RVS -----------------------------------------------------------*/
void SP100_Mode_RVS(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
	temp &= 0x0F;
	if((temp != 0x06) && (Mode_MA_Lock_State == MA_Lock_OK))
	{
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_1_CTRL);
		temp &= 0xF0;
		temp |= 0x06;		//--> OUTH2:ON & OUTL2:HZ & OUTH1:HZ & OUTL1:ON
		SP100_TLE_Ctrl_Register_Write(HB_ACT_1_CTRL, temp);
		// TIM7 Start --> Mode_Lock_State
		htim7.Instance->CNT = 0x00;
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim7);
	}
}

/* SP100_Mode_Handler -------------------------------------------------------*/
void SP100_Mode_Handler(Mode_State state)
{
	switch (state)
	{
		case Mode_Face:
		{
			if(SP100_Mode_FB <= (SP100_Mode_Face_Pos-SP100_Mode_Tolerance))
				SP100_Mode_FWD();
			else if(SP100_Mode_FB >= (SP100_Mode_Face_Pos+SP100_Mode_Tolerance))
				SP100_Mode_RVS();
			else
				SP100_Mode_STP();
			break;			
		}
		case Mode_Face_Foot:
		{
			if(SP100_Mode_FB <= (SP100_Mode_Face_Foot_Pos-SP100_Mode_Tolerance))
				SP100_Mode_FWD();
			else if(SP100_Mode_FB >= (SP100_Mode_Face_Foot_Pos+SP100_Mode_Tolerance))
				SP100_Mode_RVS();
			else
				SP100_Mode_STP();
			break;			
		}
		case Mode_Foot:
		{
			if(SP100_Mode_FB <= (SP100_Mode_Foot_Pos-SP100_Mode_Tolerance))
				SP100_Mode_FWD();
			else if(SP100_Mode_FB >= (SP100_Mode_Foot_Pos+SP100_Mode_Tolerance))
				SP100_Mode_RVS();
			else
				SP100_Mode_STP();
			break;			
		}
		case Mode_Foot_Def:
		{
			if(SP100_Mode_FB <= (SP100_Mode_Foot_Def_Pos-SP100_Mode_Tolerance))
				SP100_Mode_FWD();
			else if(SP100_Mode_FB >= (SP100_Mode_Foot_Def_Pos+SP100_Mode_Tolerance))
				SP100_Mode_RVS();
			else
				SP100_Mode_STP();
			break;			
		}
		case Mode_Def:
		{
			if(SP100_Mode_FB <= (SP100_Mode_Def_Pos-SP100_Mode_Tolerance))
				SP100_Mode_FWD();
			else if(SP100_Mode_FB >= (SP100_Mode_Def_Pos+SP100_Mode_Tolerance))
				SP100_Mode_RVS();
			else
				SP100_Mode_STP();
			break;			
		}
	}
}
