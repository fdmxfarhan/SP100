/* Includes *******************************************************************/
#include "nx7_ac_ctrl.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern  AC_State       NX7_AC_State;
extern  AC_Temp_State  NX7_AC_Temp_State;

/* Functions body *************************************************************/
/* NX7_AC_OFF ----------------------------------------------------------------*/
void NX7_AC_OFF(void)
{
	NX7_AC_State = AC_OFF;
	AC_Relay_OFF;
}

/* NX7_AC_ON -----------------------------------------------------------------*/
void NX7_AC_ON(void)
{
	if(NX7_AC_Temp_State == AC_Temp_ON)
	{
		NX7_AC_State = AC_ON;
		AC_Relay_ON;
	}
	else
	{
		NX7_AC_State = AC_OFF;
		AC_Relay_OFF;
	}
}

/* NX7_AC_Handler ------------------------------------------------------------*/
void NX7_AC_Handler(AC_State state)
{
	switch (state)
	{
		case AC_OFF:
		{
			NX7_AC_OFF();
			break;
		}
		case AC_ON:
		{
			NX7_AC_ON();
			break;
		}
	}
}
