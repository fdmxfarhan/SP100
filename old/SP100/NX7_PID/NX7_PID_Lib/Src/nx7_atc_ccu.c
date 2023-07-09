/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"
#include "nx7_typedef.h"
#include "nx7_ext_isr.h"
#include "nx7_tim_isr.h"
#include "nx7_adc_isr.h"
#include "nx7_sensors.h"
#include "nx7_tle94106es.h"
#include "nx7_intake_ma.h"
#include "nx7_mode_ma.h"
#include "nx7_airmix_ma.h"
#include "nx7_blower_fan.h"
#include "nx7_ac_ctrl.h"
#include "nx7_r_def_ctrl.h"
#include "nx7_pid_ctrl.h"
#include "nx7_lcd.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/

/* Private macro **************************************************************/
#define  DEF_LED_ON   HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_SET)
#define  DEF_LED_OFF  HAL_GPIO_WritePin(DEF_LED_GPIO_Port, DEF_LED_Pin, GPIO_PIN_RESET)

/* Private variables **********************************************************/
CCU_State			NX7_CCU_preState			=	CCU_AUTO;
CCU_State			NX7_CCU_State				=	CCU_OFF;

Intake_State		NX7_Intake_State			=	Intake_Fresh;
Mode_State			NX7_Mode_State				=	Mode_Face;
Airmix_State		NX7_Airmix_State			=	Airmix_Lo;
Blower_State		NX7_Blower_State			=	Blower_OFF;
AC_State			NX7_AC_State				=	AC_OFF;
AC_Temp_State		NX7_AC_Temp_State			=	AC_Temp_OFF;
R_DEF_State			NX7_R_DEF_State				=	R_DEF_OFF;

Auto_Ctrl_State		Intake_Auto_Ctrl_State		=	Auto_Ctrl_ON;
Auto_Ctrl_State		Mode_Auto_Ctrl_State		=	Auto_Ctrl_ON;
Auto_Ctrl_State		Blower_Auto_Ctrl_State		=	Auto_Ctrl_ON;

Sensor_State		Evap_Sensor_State			=	Sensor_OK;
Sensor_State		Cabin_Sensor_State			=	Sensor_OK;
Sensor_State		Water_Sensor_State			=	Sensor_OK;
Sensor_State		Ambient_Sensor_State		=	Sensor_Error;
Sensor_State		Solar_Sensor_State			=	Sensor_OK;

MA_Lock_State		Airmix_MA_Lock_State		=	MA_Lock_OK;
MA_Lock_State		Mode_MA_Lock_State			=	MA_Lock_OK;
MA_Pot_State		Airmix_MA_Pot_State			=	MA_Pot_OK;
MA_Pot_State		Mode_MA_Pot_State			=	MA_Pot_OK;

AUTO_Error_State	NX7_AUTO_Error_State		=	AUTO_Error_OFF;
AUTO_Blink_State	NX7_AUTO_Blink_State		=	AUTO_Blink_OFF;

Mode_SEG_State		NX7_Mode_SEG_State			=	Mode_SEG_OFF;

float	NX7_IGN_VOLT;							// IGN Voltage Value
float	NX7_Set_Point = 25.0;					// Set_Point
int		NX7_CCU_SENSOR_Index = 1;				// CCU_SENSOR_Index

extern	TIM_HandleTypeDef	htim16;				// Mode_SEG_State
extern	CCU_Sensor	NX7_CCU_Sensor;				// Evap., Cabin, Ambient, Water, Solar
extern	float		NX7_Airmix_FB;				// Airmix Feedback
extern	float		NX7_Mode_FB;				// Mode Feedback
extern	int			flag;						// Hysteresis flag
extern	int			dacVal;						// dacVal

/* Functions body *************************************************************/
/* NX7_Delay -----------------------------------------------------------------*/
void NX7_Delay(int delay)
{
	for(register int i=0; i<delay; i++);
}

/* NX7_CCU_Init --------------------------------------------------------------*/
void NX7_CCU_Init(void)
{
	NX7_ADC_Init();
	NX7_Blower_Init();
	NX7_TLE_Init();
	NX7_LCD_Init();
}

/* NX7_CCU_State_Updater -----------------------------------------------------*/
void NX7_CCU_State_Updater(CCU_State newState)
{
	NX7_CCU_preState	=	NX7_CCU_State;
	NX7_CCU_State		=	newState;
	//--> NX7_CCU_preState exceptions
	if(NX7_CCU_preState == CCU_OFF)			{NX7_CCU_preState = CCU_AUTO;}
	if(NX7_CCU_preState == CCU_IGN_OFF)		{NX7_CCU_preState = CCU_AUTO;}
}

/* NX7_CCU_Switch_Handler ----------------------------------------------------*/
void NX7_CCU_Switch_Handler(uint16_t SW_Pin)
{
	/* ------------------------------------------------------- <POWER_SW_Pin> */
	if(SW_Pin == POWER_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			NX7_CCU_State_Updater(NX7_CCU_preState);
			break;
		}
		case CCU_AUTO:
		{
			NX7_CCU_State_Updater(CCU_OFF);
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_OFF);
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* -------------------------------------------------------- <AUTO_SW_Pin> */
	if(SW_Pin == AUTO_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			Intake_Auto_Ctrl_State = Auto_Ctrl_ON;
			Mode_Auto_Ctrl_State = Auto_Ctrl_ON;
			Blower_Auto_Ctrl_State = Auto_Ctrl_ON;
			break;
		}
		case CCU_AUTO:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			Intake_Auto_Ctrl_State = Auto_Ctrl_ON;
			Mode_Auto_Ctrl_State = Auto_Ctrl_ON;
			Blower_Auto_Ctrl_State = Auto_Ctrl_ON;
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			Intake_Auto_Ctrl_State = Auto_Ctrl_ON;
			Mode_Auto_Ctrl_State = Auto_Ctrl_ON;
			Blower_Auto_Ctrl_State = Auto_Ctrl_ON;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* --------------------------------------------------------- <DEF_SW_Pin> */
	if(SW_Pin == DEF_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			NX7_CCU_State_Updater(CCU_DEF);
			break;
		}
		case CCU_AUTO:
		{
			NX7_CCU_State_Updater(CCU_DEF);
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(NX7_CCU_preState);
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ---------------------------------------------------------- <AC_SW_Pin> */
	if(SW_Pin == AC_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			if(NX7_CCU_preState == CCU_AUTO)		{NX7_CCU_State_Updater(CCU_AUTO);}
			else if(NX7_CCU_preState == CCU_DEF)	{NX7_CCU_State_Updater(CCU_DEF);}
			break;
		}
		case CCU_AUTO:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			NX7_Intake_State = Intake_Fresh;
			NX7_Mode_State = Mode_Def;
			NX7_Blower_State = Blower_L8;
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------------ <Intake_SW_Pin> */
	if(SW_Pin == Intake_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			if(NX7_Intake_State == Intake_Fresh)		{NX7_Intake_State = Intake_Recycle;}
			else if(NX7_Intake_State == Intake_Recycle)	{NX7_Intake_State = Intake_Fresh;}
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Intake_State == Intake_Fresh)		{NX7_Intake_State = Intake_Recycle;}
			else if(NX7_Intake_State == Intake_Recycle)	{NX7_Intake_State = Intake_Fresh;}
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			NX7_Intake_State = Intake_Recycle;
			NX7_Mode_State = Mode_Def;
			NX7_Blower_State = Blower_L8;
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* -------------------------------------------------------- <Mode_SW_Pin> */
	if(SW_Pin == Mode_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			if(NX7_Mode_State == Mode_Face)				{NX7_Mode_State = Mode_Face_Foot;}
			else if(NX7_Mode_State == Mode_Face_Foot)	{NX7_Mode_State = Mode_Foot;}
			else if(NX7_Mode_State == Mode_Foot)		{NX7_Mode_State = Mode_Foot_Def;}
			else if(NX7_Mode_State == Mode_Foot_Def)	{NX7_Mode_State = Mode_Def;}
			else if(NX7_Mode_State == Mode_Def)			{NX7_Mode_State = Mode_Face;}
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			// TIM16 Start --> Mode_SEG_State
			NX7_Mode_SEG_State = Mode_SEG_ON;
			htim16.Instance->CNT = 0x00;
			__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
			HAL_TIM_Base_Start_IT(&htim16);
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Mode_State == Mode_Face)				{NX7_Mode_State = Mode_Face_Foot;}
			else if(NX7_Mode_State == Mode_Face_Foot)	{NX7_Mode_State = Mode_Foot;}
			else if(NX7_Mode_State == Mode_Foot)		{NX7_Mode_State = Mode_Foot_Def;}
			else if(NX7_Mode_State == Mode_Foot_Def)	{NX7_Mode_State = Mode_Def;}
			else if(NX7_Mode_State == Mode_Def)			{NX7_Mode_State = Mode_Face;}
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			NX7_Intake_State = Intake_Fresh;
			NX7_Mode_State = Mode_Face;
			NX7_Blower_State = Blower_L8;
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* --------------------------------------------------- <Blower_Up_SW_Pin> */
	if(SW_Pin == Blower_Up_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			NX7_CCU_State_Updater(NX7_CCU_preState);
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Blower_State < Blower_L8)	{NX7_Blower_State++;}
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			NX7_Intake_State = Intake_Fresh;
			NX7_Mode_State = Mode_Def;
			NX7_Blower_State = Blower_L8;
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------- <Blower_Down_SW_Pin> */
	if(SW_Pin == Blower_Down_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			NX7_CCU_State_Updater(NX7_CCU_preState);
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Blower_State > Blower_L1)	{NX7_Blower_State--;}
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_DEF:
		{
			NX7_CCU_State_Updater(CCU_AUTO);
			NX7_Intake_State = Intake_Fresh;
			NX7_Mode_State = Mode_Def;
			NX7_Blower_State = Blower_L7;
			Intake_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Mode_Auto_Ctrl_State = Auto_Ctrl_OFF;
			Blower_Auto_Ctrl_State = Auto_Ctrl_OFF;
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* --------------------------------------------------- <Airmix_Up_SW_Pin> */
	if(SW_Pin == Airmix_Up_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Set_Point == -1000)									{NX7_Set_Point = 14.0;}
			else if((NX7_Set_Point >= 14.0) && (NX7_Set_Point < 20.0))	{NX7_Set_Point += 1.0;}
			else if((NX7_Set_Point >= 20.0) && (NX7_Set_Point < 26.0))	{NX7_Set_Point += 0.5;}
			else if((NX7_Set_Point >= 26.0) && (NX7_Set_Point < 32.0))	{NX7_Set_Point += 1.0;}
			else if(NX7_Set_Point == 32.0)								{NX7_Set_Point = +1000;}
			break;
		}
		case CCU_DEF:
		{
			if(NX7_Set_Point == -1000)									{NX7_Set_Point = 14.0;}
			else if((NX7_Set_Point >= 14.0) && (NX7_Set_Point < 20.0))	{NX7_Set_Point += 1.0;}
			else if((NX7_Set_Point >= 20.0) && (NX7_Set_Point < 26.0))	{NX7_Set_Point += 0.5;}
			else if((NX7_Set_Point >= 26.0) && (NX7_Set_Point < 32.0))	{NX7_Set_Point += 1.0;}
			else if(NX7_Set_Point == 32.0)								{NX7_Set_Point = +1000;}
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------- <Airmix_Down_SW_Pin> */
	if(SW_Pin == Airmix_Down_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_Set_Point == +1000)									{NX7_Set_Point = 32.0;}
			else if((NX7_Set_Point <= 32.0) && (NX7_Set_Point > 26.0))	{NX7_Set_Point -= 1.0;}
			else if((NX7_Set_Point <= 26.0) && (NX7_Set_Point > 20.0))	{NX7_Set_Point -= 0.5;}
			else if((NX7_Set_Point <= 20.0) && (NX7_Set_Point > 14.0))	{NX7_Set_Point -= 1.0;}
			else if(NX7_Set_Point == 14.0)								{NX7_Set_Point = -1000;}
			break;
		}
		case CCU_DEF:
		{
			if(NX7_Set_Point == +1000)									{NX7_Set_Point = 32.0;}
			else if((NX7_Set_Point <= 32.0) && (NX7_Set_Point > 26.0))	{NX7_Set_Point -= 1.0;}
			else if((NX7_Set_Point <= 26.0) && (NX7_Set_Point > 20.0))	{NX7_Set_Point -= 0.5;}
			else if((NX7_Set_Point <= 20.0) && (NX7_Set_Point > 14.0))	{NX7_Set_Point -= 1.0;}
			else if(NX7_Set_Point == 14.0)								{NX7_Set_Point = -1000;}
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
	/* ------------------------------------------------------- <R_DEF_SW_Pin> */
	if(SW_Pin == R_DEF_SW_Pin)
	{
		switch (NX7_CCU_State)
		{
		case CCU_OFF:
		{
			if(NX7_R_DEF_State == R_DEF_OFF)		{NX7_R_DEF_State = R_DEF_ON;}
			else if(NX7_R_DEF_State == R_DEF_ON)	{NX7_R_DEF_State = R_DEF_OFF;}
			break;
		}
		case CCU_AUTO:
		{
			if(NX7_R_DEF_State == R_DEF_OFF)		{NX7_R_DEF_State = R_DEF_ON;}
			else if(NX7_R_DEF_State == R_DEF_ON)	{NX7_R_DEF_State = R_DEF_OFF;}
			break;
		}
		case CCU_DEF:
		{
			if(NX7_R_DEF_State == R_DEF_OFF)		{NX7_R_DEF_State = R_DEF_ON;}
			else if(NX7_R_DEF_State == R_DEF_ON)	{NX7_R_DEF_State = R_DEF_OFF;}
			break;
		}
		case CCU_IGN_OFF:
		{
			break;
		}
		}
	}
}

/* NX7_AUTO_Error_State_Handler ----------------------------------------------*/
void NX7_AUTO_Error_State_Handler(void)
{
	NX7_AUTO_Error_State  = Evap_Sensor_State | Cabin_Sensor_State | Water_Sensor_State | Ambient_Sensor_State | Solar_Sensor_State;
	NX7_AUTO_Error_State |= Airmix_MA_Lock_State | Mode_MA_Lock_State | Airmix_MA_Pot_State | Mode_MA_Pot_State;
}

/* NX7_CCU_Infinite_Loop -----------------------------------------------------*/
void NX7_CCU_Infinite_Loop(void)
{
	while(1)
	{

/* ------------------------------------------------------ <CCU_IGN_OFF_State> */
		if(NX7_CCU_State == CCU_IGN_OFF)
		{

		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
		while(NX7_CCU_State == CCU_IGN_OFF)
		{
			// Timer Start
			//NX7_Intake_MA_Handler(Intake_Fresh);
			NX7_Mode_MA_STP();
			NX7_Airmix_MA_STP();
			//NX7_Mode_MA_Handler(Mode_Face);
			//NX7_Airmix_MA_Handler(Airmix_Lo);
			//NX7_Blower_Handler(Blower_OFF);	//delete
			NX7_AC_Handler(AC_OFF);
			NX7_R_DEF_State = R_DEF_OFF;
			NX7_R_DEF_Handler(NX7_R_DEF_State);
			// Timer Stop

			Evap_Sensor_State    = Sensor_OK;
			Cabin_Sensor_State   = Sensor_OK;
			Water_Sensor_State   = Sensor_OK;
			Ambient_Sensor_State = Sensor_Error;
			Solar_Sensor_State   = Sensor_OK;
			Airmix_MA_Lock_State = MA_Lock_OK;
			Mode_MA_Lock_State   = MA_Lock_OK;
			Airmix_MA_Pot_State  = MA_Pot_OK;
			Mode_MA_Pot_State    = MA_Pot_OK;
			NX7_AUTO_Error_State = AUTO_Error_OFF;

			NX7_TLE_DeInit();
			NX7_LCD_DeInit();

			while(NX7_IGN_VOLT < 8.0);

			NX7_TLE_Init();
			NX7_LCD_Init();

			NX7_CCU_State = CCU_OFF;
		}
		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

		}


/* ---------------------------------------------------------- <CCU_OFF_State> */
		if(NX7_CCU_State == CCU_OFF)
		{
		//--> Mode_SEG_State_OFF & TIM16 Stop
		NX7_Mode_SEG_State = Mode_SEG_OFF;
		HAL_TIM_Base_Stop_IT(&htim16);
		__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
		//--> Hysteresis flag reset
		flag = 0;

		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
		while(NX7_CCU_State == CCU_OFF)
		{
			NX7_LCD_State_Init_SEG(CCU_OFF);

			NX7_Intake_MA_Handler(NX7_Intake_State);
			NX7_Mode_MA_Handler(NX7_Mode_State);
			NX7_Airmix_MA_Handler(NX7_Airmix_State);
			//NX7_Blower_Handler(Blower_OFF);	//delete
			NX7_AC_Handler(AC_OFF);
			NX7_R_DEF_Handler(NX7_R_DEF_State);

			NX7_LCD_Intake_Handler(NX7_Intake_State);

			if(NX7_Mode_SEG_State == Mode_SEG_ON)
			{NX7_LCD_Mode_Handler(NX7_Mode_State);}
			else
			{NX7_LCD_Mode_SEG(SEG_OFF);}

			NX7_LCD_AC_Handler(AC_OFF);
			NX7_LCD_R_DEF_Handler(NX7_R_DEF_State);
			NX7_LCD_Out_Temp_Handler(NX7_CCU_Sensor.Ambient_Sensor);
		}
		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

		//--> Mode_SEG_State_OFF & TIM16 Stop
		NX7_Mode_SEG_State = Mode_SEG_OFF;
		HAL_TIM_Base_Stop_IT(&htim16);
		__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
		//--> No_Hysteresis Function
		NX7_PID_Ctrl_No_Hysteresis();
		}


/* --------------------------------------------------------- <CCU_AUTO_State> */
		if(NX7_CCU_State == CCU_AUTO)
		{
		//NX7_PID_Ctrl();
		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
		while(NX7_CCU_State == CCU_AUTO)
		{
			NX7_LCD_State_Init_SEG(CCU_AUTO);

			NX7_Intake_MA_Handler(NX7_Intake_State);
			NX7_Mode_MA_Handler(NX7_Mode_State);
			NX7_Airmix_MA_Handler(NX7_Airmix_State);
			//NX7_Blower_Handler(NX7_Blower_State);	//delete
			NX7_AC_Handler(AC_ON);
			NX7_R_DEF_Handler(NX7_R_DEF_State);

			NX7_AUTO_Error_State_Handler();

			switch (NX7_AUTO_Error_State)
			{
			case AUTO_Error_OFF:
			{
				if(Intake_Auto_Ctrl_State & Mode_Auto_Ctrl_State & Blower_Auto_Ctrl_State)
				{
					NX7_LCD_AUTO_SEG(SEG_ON);
				}
				else
				{
					NX7_LCD_AUTO_SEG(SEG_OFF);
				}
				break;
			}
			case AUTO_Error_ON:
			{
				if(NX7_AUTO_Blink_State == AUTO_Blink_ON)
				{
					NX7_LCD_AUTO_SEG(SEG_ON);
				}
				else
				{
					NX7_LCD_AUTO_SEG(SEG_OFF);
				}
				break;
			}
			}

			NX7_LCD_Intake_Handler(NX7_Intake_State);
			NX7_LCD_Mode_Handler(NX7_Mode_State);
			NX7_LCD_Blower_Handler(NX7_Blower_State);
			NX7_LCD_AC_Handler(AC_ON);
			NX7_LCD_R_DEF_Handler(NX7_R_DEF_State);
			NX7_LCD_Out_Temp_Handler(NX7_CCU_Sensor.Ambient_Sensor);
			NX7_LCD_Set_Point_Handler(NX7_Set_Point);
		}
		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

		}


/* ---------------------------------------------------------- <CCU_DEF_State> */
		if(NX7_CCU_State == CCU_DEF)
		{
		DEF_LED_ON;

		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
		while(NX7_CCU_State == CCU_DEF)
		{
			NX7_LCD_State_Init_SEG(CCU_DEF);

			NX7_Intake_MA_Handler(Intake_Fresh);
			NX7_Mode_MA_Handler(Mode_Def);
			NX7_Airmix_MA_Handler(NX7_Airmix_State);
			//NX7_Blower_Handler(NX7_Blower_State);	//delete
			NX7_AC_Handler(AC_ON);
			NX7_R_DEF_Handler(NX7_R_DEF_State);

			NX7_AUTO_Error_State_Handler();

			switch (NX7_AUTO_Error_State)
			{
			case AUTO_Error_OFF:
			{
				NX7_LCD_AUTO_SEG(SEG_OFF);
				break;
			}
			case AUTO_Error_ON:
			{
				if(NX7_AUTO_Blink_State == AUTO_Blink_ON)
				{
					NX7_LCD_AUTO_SEG(SEG_ON);
				}
				else
				{
					NX7_LCD_AUTO_SEG(SEG_OFF);
				}
				break;
			}
			}

			NX7_LCD_Intake_Handler(Intake_Fresh);
			NX7_LCD_Blower_Handler(Blower_L8);
			NX7_LCD_AC_Handler(AC_ON);
			NX7_LCD_R_DEF_Handler(NX7_R_DEF_State);
			NX7_LCD_Out_Temp_Handler(NX7_CCU_Sensor.Ambient_Sensor);
			NX7_LCD_Set_Point_Handler(NX7_Set_Point);
		}
		/* <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

		DEF_LED_OFF;
		}

	} //--> End of while(1)
}
