/* Includes *******************************************************************/
#include "nx7_intake_ma.h"
#include "nx7_tle94106es.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/
/* Private variables **********************************************************/

/* Functions body *************************************************************/
/* NX7_Intake_MA_STP ---------------------------------------------------------*/
void NX7_Intake_MA_STP(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if(temp != 0x00)
	{
		NX7_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, 0x00);		//--> OUTL5:HZ & OUTL6:HZ
	}
}

/* NX7_Intake_MA_Fresh -------------------------------------------------------*/
void NX7_Intake_MA_Fresh(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if(temp != 0x01)
	{
		NX7_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, 0x01);		//--> OUTL5:ON & OUTL6:HZ
	}
}

/* NX7_Intake_MA_Recycle -----------------------------------------------------*/
void NX7_Intake_MA_Recycle(void)
{
	uint8_t temp;
	temp = NX7_TLE_Ctrl_Register_Read(HB_ACT_2_CTRL);
	if(temp != 0x04)
	{
		NX7_TLE_Ctrl_Register_Write(HB_ACT_2_CTRL, 0x04);		//--> OUTL5:HZ & OUTL6:ON
	}
}

/* NX7_Intake_MA_Handler -----------------------------------------------------*/
void NX7_Intake_MA_Handler(Intake_State state)
{
	switch (state)
	{
		case Intake_Fresh:
		{
			NX7_Intake_MA_Fresh();
			break;
		}
		case Intake_Recycle:
		{
			NX7_Intake_MA_Recycle();
			break;
		}
	}
}
