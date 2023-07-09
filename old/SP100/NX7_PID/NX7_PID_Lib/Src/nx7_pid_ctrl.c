/* Includes *******************************************************************/
#include "nx7_pid_ctrl.h"
#include "nx7_sensors.h"
#include <math.h>

/* Private typedef ************************************************************/
/* Private define *************************************************************/

/* Private macro **************************************************************/
#define  TS  NX7_Set_Point
#define  TE  NX7_CCU_Sensor.Evap_Sensor
#define  TC  NX7_CCU_Sensor.Cabin_Sensor
#define  TW  NX7_CCU_Sensor.Water_Sensor
#define  TA  NX7_CCU_Sensor.Ambient_Sensor
#define  TL  NX7_CCU_Sensor.Solar_Sensor

/* Private variables **********************************************************/
int		flag = 0;

float	PID_Error = 0;
float	Airmix_Int_Error = 0;

float	Airmix_KP = 0;
float	Airmix_KI = 0;

float	Ksat = 0;

float	Blower_K1 = 0;
float	Blower_K2 = 0;

float	Blower_X = 0;

Intake_State  PID_Intake_State;
Mode_State    PID_Mode_State;
Airmix_State  PID_Airmix_State;
Blower_State  PID_Blower_State;

extern  float            NX7_Set_Point;
extern  CCU_Sensor       NX7_CCU_Sensor;
extern  Intake_State     NX7_Intake_State;
extern  Mode_State       NX7_Mode_State;
extern  Airmix_State     NX7_Airmix_State;
extern  Blower_State     NX7_Blower_State;
extern  Auto_Ctrl_State  Intake_Auto_Ctrl_State;
extern  Auto_Ctrl_State  Mode_Auto_Ctrl_State;
extern  Auto_Ctrl_State  Blower_Auto_Ctrl_State;

/* Functions body *************************************************************/
/* NX7_PID_Ctrl_No_Hysteresis ------------------------------------------------*/
void NX7_PID_Ctrl_No_Hysteresis(void)
{
/* ------------------------------------------------------- <PID_Calculations> */
	PID_Error = TS-TC;

	if(fabsf(TS-TA) < 10)
	{
		Ksat = 40;
	}
	else if((fabsf(TS-TA) >= 10) && (fabsf(TS-TA) < 15))
	{
		Ksat = 45;
	}
	else if(fabsf(TS-TA) >= 15)
	{
		Ksat = 50;
	}

	Airmix_Int_Error += PID_Error;
	if(fabsf(Airmix_Int_Error) > Ksat)
	{
		Airmix_Int_Error = Ksat * (Airmix_Int_Error/fabsf(Airmix_Int_Error));
	}
	//if(Airmix_Int_Error > +50)			{Airmix_Int_Error = +50;}
	//else if(Airmix_Int_Error < -50)		{Airmix_Int_Error = -50;}

/* --------------------------------------------------------------- <Blower_X> */
	if(fabsf(TA-TS) < fabsf(TA-25))		{Blower_X = fabsf(TA-TS);}
	else								{Blower_X = fabsf(TA-25);}

/* ------------------------------------------------------------- <Flag_State> */
	if(TS-TA >= 0)			{flag = +1;}
	else if(TS-TA < 0)		{flag = -1;}

/* ------------------------------------------------------ <Intake_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA >= 0)
	{
		if(TS-TC < +1)
		{
			PID_Intake_State = Intake_Fresh;
		}
		else if((TS-TC >= +1) && (TS-TC < +22.5))
		{
			PID_Intake_State = Intake_Recycle;
		}
		else if(TS-TC >= +22.5)
		{
			PID_Intake_State = Intake_Fresh;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < 0)
	{
		if(TS-TC < +1)
		{
			PID_Intake_State = Intake_Recycle;
		}
		else if(TS-TC >= +1)
		{
			PID_Intake_State = Intake_Fresh;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(Intake_Auto_Ctrl_State == Auto_Ctrl_ON)
	{
		NX7_Intake_State = PID_Intake_State;
	}

/* -------------------------------------------------------- <Mode_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA >= 0)
	{
		if(TS-TC < -4.5)
		{
			PID_Mode_State = Mode_Foot_Def;
		}
		else if((TS-TC >= -4.5) && (TS-TC < -1.5))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if((TS-TC >= -1.5) && (TS-TC < +2.5))
		{
			PID_Mode_State = Mode_Foot;
		}
		else if((TS-TC >= +2.5) && (TS-TC < +22.5))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if(TS-TC >= +22.5)
		{
			PID_Mode_State = Mode_Foot;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < 0)
	{
		if(TS-TC < -1.5)
		{
			PID_Mode_State = Mode_Face;
		}
		else if((TS-TC >= -1.5) && (TS-TC < +3.5))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if(TS-TC >= +3.5)
		{
			PID_Mode_State = Mode_Foot_Def;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(Mode_Auto_Ctrl_State == Auto_Ctrl_ON)
	{
		NX7_Mode_State = PID_Mode_State;
	}

/* ------------------------------------------------------ <Airmix_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA >= 0)
	{
		Airmix_KP = 1.0/30 * fabsf(PID_Error);
		Airmix_KI = 1.0/50;
		float airmix = 1 - 1.1 * (Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error);
		if(airmix < 0.0)	{airmix = 0.0;}
		if(airmix > 0.8)	{airmix = 0.8;}
		PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < 0)
	{
		Airmix_KP = -1.0/15 * fabsf(PID_Error);
		Airmix_KI = -1.0/50;
		float airmix = Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error;
		if(airmix < 0.2)	{airmix = 0.2;}
		if(airmix > 1.0)	{airmix = 1.0;}
		PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	NX7_Airmix_State = PID_Airmix_State;

/* ------------------------------------------------------ <Blower_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA >= 0)
	{
		if(TW >= +65)
		{
			Blower_K1 = 1.0/25;
			Blower_K2 = 1.0/40;
			float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
			if(blower > 1.0)	{blower = 1.0;}
			PID_Blower_State = roundf(8*blower);
			if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
			if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
		}
		else if((TW > +35) && (TW < +65))
		{
			if(TS-TC < -1)
			{
				PID_Blower_State = floorf((0.2*TW)-5);
			}
			else if((TS-TC >= -1) && (TS-TC <= +1))
			{
				PID_Blower_State = Blower_L1;
			}
			else if(TS-TC > +1)
			{
				PID_Blower_State = floorf((0.2*TW)-5);
			}
		}
		else if(TW <= +35)
		{
			PID_Blower_State = Blower_L1;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < 0)
	{
		Blower_K1 = 2.0/25;
		Blower_K2 = 1.6/40;
		float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
		if(blower > 1.0)	{blower = 1.0;}
		PID_Blower_State = roundf(8*blower);
		if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
		if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	// void NX7_PID_Ctrl_Blower(void) is executed every 0.5 second
}

/* NX7_PID_Ctrl --------------------------------------------------------------*/
void NX7_PID_Ctrl(void)
{
/* ------------------------------------------------------- <PID_Calculations> */
	PID_Error = TS-TC;

	if(fabsf(TS-TA) < 10)
	{
		Ksat = 40;
	}
	else if((fabsf(TS-TA) >= 10) && (fabsf(TS-TA) < 15))
	{
		Ksat = 45;
	}
	else if(fabsf(TS-TA) >= 15)
	{
		Ksat = 50;
	}

	Airmix_Int_Error += PID_Error;
	if(fabsf(Airmix_Int_Error) > Ksat)
	{
		Airmix_Int_Error = Ksat * (Airmix_Int_Error/fabsf(Airmix_Int_Error));
	}
	//if(Airmix_Int_Error > +50)			{Airmix_Int_Error = +50;}
	//else if(Airmix_Int_Error < -50)		{Airmix_Int_Error = -50;}

/* --------------------------------------------------------------- <Blower_X> */
	if(fabsf(TA-TS) < fabsf(TA-25))		{Blower_X = fabsf(TA-TS);}
	else								{Blower_X = fabsf(TA-25);}

/* ------------------------------------------------------------- <Flag_State> */
	if(TS-TA > +2.5)		{flag = +1;}
	else if(TS-TA < -2.5)	{flag = -1;}

/* ------------------------------------------------------ <Intake_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA > +2.5)
	{
		if(TS-TC <= 0)
		{
			PID_Intake_State = Intake_Fresh;
		}
		else if((TS-TC >= +2) && (TS-TC <= +20))
		{
			PID_Intake_State = Intake_Recycle;
		}
		else if(TS-TC >= +25)
		{
			PID_Intake_State = Intake_Fresh;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < -2.5)
	{
		if(TS-TC <= 0)
		{
			PID_Intake_State = Intake_Recycle;
		}
		else if(TS-TC >= +2)
		{
			PID_Intake_State = Intake_Fresh;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if((TS-TA >= -2.5) && (TS-TA <= +2.5))
	{
		if(flag == +1)
		{
			if(TS-TC <= 0)
			{
				PID_Intake_State = Intake_Fresh;
			}
			else if((TS-TC >= +2) && (TS-TC <= +20))
			{
				PID_Intake_State = Intake_Recycle;
			}
			else if(TS-TC >= +25)
			{
				PID_Intake_State = Intake_Fresh;
			}
		}
		else if(flag == -1)
		{
			if(TS-TC <= 0)
			{
				PID_Intake_State = Intake_Recycle;
			}
			else if(TS-TC >= +2)
			{
				PID_Intake_State = Intake_Fresh;
			}
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(Intake_Auto_Ctrl_State == Auto_Ctrl_ON)
	{
		NX7_Intake_State = PID_Intake_State;
	}

/* -------------------------------------------------------- <Mode_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA > +2.5)
	{
		if(TS-TC <= -5)
		{
			PID_Mode_State = Mode_Foot_Def;
		}
		else if((TS-TC >= -4) && (TS-TC <= -2))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if((TS-TC >= -1) && (TS-TC <= +2))
		{
			PID_Mode_State = Mode_Foot;
		}
		else if((TS-TC >= +3) && (TS-TC <= +20))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if(TS-TC >= +25)
		{
			PID_Mode_State = Mode_Foot;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < -2.5)
	{
		if(TS-TC <= -2)
		{
			PID_Mode_State = Mode_Face;
		}
		else if((TS-TC >= -1) && (TS-TC <= +3))
		{
			PID_Mode_State = Mode_Face_Foot;
		}
		else if(TS-TC >= +4)
		{
			PID_Mode_State = Mode_Foot_Def;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if((TS-TA >= -2.5) && (TS-TA <= +2.5))
	{
		if(flag == +1)
		{
			if(TS-TC <= -5)
			{
				PID_Mode_State = Mode_Foot_Def;
			}
			else if((TS-TC >= -4) && (TS-TC <= -2))
			{
				PID_Mode_State = Mode_Face_Foot;
			}
			else if((TS-TC >= -1) && (TS-TC <= +2))
			{
				PID_Mode_State = Mode_Foot;
			}
			else if((TS-TC >= +3) && (TS-TC <= +20))
			{
				PID_Mode_State = Mode_Face_Foot;
			}
			else if(TS-TC >= +25)
			{
				PID_Mode_State = Mode_Foot;
			}
		}
		else if(flag == -1)
		{
			if(TS-TC <= -2)
			{
				PID_Mode_State = Mode_Face;
			}
			else if((TS-TC >= -1) && (TS-TC <= +3))
			{
				PID_Mode_State = Mode_Face_Foot;
			}
			else if(TS-TC >= +4)
			{
				PID_Mode_State = Mode_Foot_Def;
			}
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(Mode_Auto_Ctrl_State == Auto_Ctrl_ON)
	{
		NX7_Mode_State = PID_Mode_State;
	}

/* ------------------------------------------------------ <Airmix_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA > +2.5)
	{
		Airmix_KP = 1.0/30 * fabsf(PID_Error);
		Airmix_KI = 1.0/50;
		float airmix = 1 - 1.1 * (Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error);
		if(airmix < 0.0)	{airmix = 0.0;}
		if(airmix > 0.8)	{airmix = 0.8;}
		PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < -2.5)
	{
		Airmix_KP = -1.0/15 * fabsf(PID_Error);
		Airmix_KI = -1.0/50;
		float airmix = Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error;
		if(airmix < 0.2)	{airmix = 0.2;}
		if(airmix > 1.0)	{airmix = 1.0;}
		PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if((TS-TA >= -2.5) && (TS-TA <= +2.5))
	{
		if(flag == +1)
		{
			Airmix_KP = 1.0/30 * fabsf(PID_Error);
			Airmix_KI = 1.0/50;
			float airmix = 1 - 1.1 * (Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error);
			if(airmix < 0.0)	{airmix = 0.0;}
			if(airmix > 0.8)	{airmix = 0.8;}
			PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
		}
		else if(flag == -1)
		{
			Airmix_KP = -1.0/15 * fabsf(PID_Error);
			Airmix_KI = -1.0/50;
			float airmix = Airmix_KP*PID_Error+Airmix_KI*Airmix_Int_Error;
			if(airmix < 0.2)	{airmix = 0.2;}
			if(airmix > 1.0)	{airmix = 1.0;}
			PID_Airmix_State = 20 - roundf(20*airmix);		// Airmix: 5%
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	NX7_Airmix_State = PID_Airmix_State;

/* ------------------------------------------------------ <Blower_State_Ctrl> */
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	if(TS-TA > +2.5)
	{
		if(TW >= +65)
		{
			Blower_K1 = 1.0/25;
			Blower_K2 = 1.0/40;
			float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
			if(blower > 1.0)	{blower = 1.0;}
			PID_Blower_State = roundf(8*blower);
			if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
			if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
		}
		else if((TW > +35) && (TW < +65))
		{
			if(TS-TC < -1)
			{
				PID_Blower_State = floorf((0.2*TW)-5);
			}
			else if((TS-TC >= -1) && (TS-TC <= +1))
			{
				PID_Blower_State = Blower_L1;
			}
			else if(TS-TC > +1)
			{
				PID_Blower_State = floorf((0.2*TW)-5);
			}
		}
		else if(TW <= +35)
		{
			PID_Blower_State = Blower_L1;
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if(TS-TA < -2.5)
	{
		Blower_K1 = 2.0/25;
		Blower_K2 = 1.6/40;
		float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
		if(blower > 1.0)	{blower = 1.0;}
		PID_Blower_State = roundf(8*blower);
		if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
		if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	else if((TS-TA >= -2.5) && (TS-TA <= +2.5))
	{
		if(flag == +1)
		{
			if(TW >= +65)
			{
				Blower_K1 = 1.0/25;
				Blower_K2 = 1.0/40;
				float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
				if(blower > 1.0)	{blower = 1.0;}
				PID_Blower_State = roundf(8*blower);
				if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
				if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
			}
			else if((TW > +35) && (TW < +65))
			{
				if(TS-TC < -1)
				{
					PID_Blower_State = floorf((0.2*TW)-5);
				}
				else if((TS-TC >= -1) && (TS-TC <= +1))
				{
					PID_Blower_State = Blower_L1;
				}
				else if(TS-TC > +1)
				{
					PID_Blower_State = floorf((0.2*TW)-5);
				}
			}
			else if(TW <= +35)
			{
				PID_Blower_State = Blower_L1;
			}
		}
		else if(flag == -1)
		{
			Blower_K1 = 2.0/25;
			Blower_K2 = 1.6/40;
			float blower = Blower_K1*fabsf(PID_Error) + Blower_K2*Blower_X;
			if(blower > 1.0)	{blower = 1.0;}
			PID_Blower_State = roundf(8*blower);
			if(PID_Blower_State < Blower_L1)	{PID_Blower_State = Blower_L1;}
			if(PID_Blower_State > Blower_L8)	{PID_Blower_State = Blower_L8;}
		}
	}
	/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
	// void NX7_PID_Ctrl_Blower(void) is executed every 0.5 second
}

/* NX7_PID_Ctrl_Blower -------------------------------------------------------*/
void NX7_PID_Ctrl_Blower(void)
{
	if(Blower_Auto_Ctrl_State == Auto_Ctrl_ON)
	{
		if(NX7_Blower_State < PID_Blower_State)
		{
			NX7_Blower_State++;
		}
		else if(NX7_Blower_State > PID_Blower_State)
		{
			NX7_Blower_State--;
		}
	}
}
