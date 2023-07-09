/* Includes *******************************************************************/
#include "mylib_enum_typedef.h"

/* Global variables ***********************************************************/
/* CCU_State -----------------------------------------------------------------*/
CCU_State			SP100_CCU_preState			=	CCU_AUTO;
CCU_State			SP100_CCU_State				=	CCU_OFF;
/* Module_State --------------------------------------------------------------*/
Intake_State		SP100_Intake_State			=	Intake_Fresh;
Mode_State			SP100_Mode_State			=	Mode_Face;
Airmix_State		SP100_Airmix_State			=	Airmix_Lo;
Blower_State		SP100_Blower_State			=	Blower_OFF;
AC_State			SP100_AC_State				=	AC_OFF;
AC_Temp_State		SP100_AC_Temp_State			=	AC_Temp_OFF;
R_DEF_State			SP100_R_DEF_State			=	R_DEF_OFF;
/* Module_preState -----------------------------------------------------------*/
Intake_State		SP100_Intake_preState		=	Intake_Fresh;
Mode_State			SP100_Mode_preState			=	Mode_Face;
Blower_State		SP100_Blower_preState		=	Blower_OFF;
AC_State			SP100_AC_preState			=	AC_OFF;
/* Auto_Ctrl_State -----------------------------------------------------------*/
Auto_Ctrl_State		Intake_Auto_Ctrl_State		=	Auto_Ctrl_ON;
Auto_Ctrl_State		Mode_Auto_Ctrl_State		=	Auto_Ctrl_ON;
Auto_Ctrl_State		Blower_Auto_Ctrl_State		=	Auto_Ctrl_ON;
Auto_Ctrl_State		AC_Auto_Ctrl_State			=	Auto_Ctrl_ON;
/* Sensor_State --------------------------------------------------------------*/
Sensor_State		Evap_Sensor_State			=	Sensor_Error;
Sensor_State		Cabin_Sensor_State			=	Sensor_Error;
Sensor_State		Water_Sensor_State			=	Sensor_Error;
Sensor_State		Ambient_Sensor_State		=	Sensor_Error;
/* Actuator_State ------------------------------------------------------------*/
MA_Lock_State		Airmix_MA_Lock_State		=	MA_Lock_OK;
MA_Lock_State		Mode_MA_Lock_State			=	MA_Lock_OK;
MA_Pot_State		Airmix_MA_Pot_State			=	MA_Pot_OK;
MA_Pot_State		Mode_MA_Pot_State			=	MA_Pot_OK;
/* AUTO_Error_State ----------------------------------------------------------*/
AUTO_Error_State	SP100_AUTO_Error_State		=	AUTO_Error_OFF;
AUTO_Blink_State	SP100_AUTO_Blink_State		=	AUTO_Blink_OFF;
/* Mode_SEG_State ------------------------------------------------------------*/
Mode_SEG_State		SP100_Mode_SEG_State		=	Mode_SEG_OFF;
/* DIAG_State ----------------------------------------------------------------*/
DIAG_State			SP100_DIAG_State			=	DIAG_Sensor;
DIAG_Sensor_Index	SP100_DIAG_Sensor_Index		=	DIAG_Sensor_All;
DIAG_Actuator_Index	SP100_DIAG_Actuator_Index	=	DIAG_Actuator_All;
DIAG_Actuator_Busy	SP100_DIAG_Actuator_Busy	=	DIAG_Actuator_Busy_OFF;

float	SP100_Set_Point = 25.0;					// Set_Point

float	SP100_Evap_Sensor;						// Evap_Sensor
float	SP100_Cabin_Sensor;						// Cabin_Sensor
float	SP100_Water_Sensor;						// Water_Sensor
float	SP100_Ambient_Sensor;					// Ambient_Sensor

float	SP100_Airmix_FB;						// Airmix Feedback
float	SP100_Mode_FB;							// Mode Feedback
float	SP100_Blower_VOLT;						// Blower Voltage

int		secCounter = 0;							// Counter_Step = 100ms
int		minCounter = 0;							// Counter_Step = 1s
