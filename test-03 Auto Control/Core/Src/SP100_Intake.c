/* Includes *******************************************************************/
#include "SP100_Intake.h"
#include "SP100_TLE94108ES.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/
/* Private variables **********************************************************/

/* Functions body *************************************************************/
/* SP100_Intake_STP ---------------------------------------------------------*/
void SP100_Intake_STP(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if((temp & 0x0F) != 0x00)
	{
		temp &= 0xF0;
		temp |= 0x00;	
		SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:HZ & OUTL6:HZ
	}
}

/* SP100_Intake_Fresh -------------------------------------------------------*/
void SP100_Intake_Fresh(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if((temp & 0x0F) != 0x09)
	{
		temp &= 0xF0;
		temp |= 0x09;	
		SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:ON & OUTL6:HZ
		
	}
}

/* SP100_Intake_Recycle -----------------------------------------------------*/
void SP100_Intake_Recycle(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if((temp & 0x0F) != 0x06)
	{
		temp &= 0xF0;
		temp |= 0x06;	
		SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:HZ & OUTL6:ON
	}
}

/* SP100_Intake_Handler -----------------------------------------------------*/
void SP100_Intake_Handler(Intake_State state)
{
	switch (state)
	{
		case Intake_Fresh:
		{
			SP100_Intake_Fresh();
			Intake_LED_OFF;
			break;
		}
		case Intake_Recycle:
		{
			SP100_Intake_Recycle();
			Intake_LED_ON;
			break;
		}
	}
}

void SP100_Compressor_ON(void)
{
	if(SP100_AC_Temp_State == AC_Temp_ON && SP100_CCU_State != CCU_OFF){
		uint8_t temp;
		temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
		temp |= 0x20;
		SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:ON & OUTL6:HZ
	} else SP100_Compressor_OFF(); 
}

void SP100_Compressor_OFF(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	temp &= 0xCF;
	SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:ON & OUTL6:HZ
}

void SP100_R_DEF_ON(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	temp |= 0x40;
	SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:ON & OUTL6:HZ
}

void SP100_R_DEF_OFF(void)
{
	uint8_t temp;
	temp = SP100_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	temp &= 0x3F;
	SP100_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, temp);		//--> OUTL5:ON & OUTL6:HZ
}

