/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_GLOBAL_VARIABLES_H
#define __SP100_GLOBAL_VARIABLES_H

/* Global variables ***********************************************************/
/* CCU_State -----------------------------------------------------------------*/
extern		CCU_State			SP100_CCU_preState;
extern		CCU_State			SP100_CCU_State;
/* Module_State --------------------------------------------------------------*/
extern		Intake_State		SP100_Intake_State;
extern		Mode_State			SP100_Mode_State;
extern		Airmix_State		SP100_Airmix_State;
extern		Blower_State		SP100_Blower_State;
extern		AC_State			SP100_AC_State;
extern		AC_Temp_State		SP100_AC_Temp_State;
extern		R_DEF_State			SP100_R_DEF_State;
/* Module_preState -----------------------------------------------------------*/
extern		Intake_State		SP100_Intake_preState;
extern		Mode_State			SP100_Mode_preState;
extern		Blower_State		SP100_Blower_preState;
extern		AC_State			SP100_AC_preState;
/* Auto_Ctrl_State -----------------------------------------------------------*/
extern		Auto_Ctrl_State		Intake_Auto_Ctrl_State;
extern		Auto_Ctrl_State		Mode_Auto_Ctrl_State;
extern		Auto_Ctrl_State		Blower_Auto_Ctrl_State;
extern		Auto_Ctrl_State		AC_Auto_Ctrl_State;
/* Sensor_State --------------------------------------------------------------*/
extern		Sensor_State		Evap_Sensor_State;
extern		Sensor_State		Cabin_Sensor_State;
extern		Sensor_State		Water_Sensor_State;
extern		Sensor_State		Ambient_Sensor_State;
/* Actuator_State ------------------------------------------------------------*/
extern		MA_Lock_State		Airmix_MA_Lock_State;
extern		MA_Lock_State		Mode_MA_Lock_State;
extern		MA_Pot_State		Airmix_MA_Pot_State;
extern		MA_Pot_State		Mode_MA_Pot_State;
/* AUTO_Error_State ----------------------------------------------------------*/
extern		AUTO_Error_State	SP100_AUTO_Error_State;
extern		AUTO_Blink_State	SP100_AUTO_Blink_State;
/* Mode_SEG_State ------------------------------------------------------------*/
extern		Mode_SEG_State		SP100_Mode_SEG_State;
/* DIAG_State ----------------------------------------------------------------*/
extern		DIAG_State			SP100_DIAG_State;
extern		DIAG_Sensor_Index	SP100_DIAG_Sensor_Index;
extern		DIAG_Actuator_Index	SP100_DIAG_Actuator_Index;
extern		DIAG_Actuator_Busy	SP100_DIAG_Actuator_Busy;

extern		float				SP100_Set_Point;			// Set_Point

extern		float				SP100_Evap_Sensor;			// Evap_Sensor
extern		float				SP100_Cabin_Sensor;			// Cabin_Sensor
extern		float				SP100_Water_Sensor;			// Water_Sensor
extern		float				SP100_Ambient_Sensor;		// Ambient_Sensor

extern		float				SP100_Airmix_FB;			// Airmix Feedback
extern		float				SP100_Mode_FB;				// Mode Feedback
extern		float				SP100_Blower_VOLT;			// Blower Voltage

extern		int					secCounter;					// Counter_Step = 100ms
extern		int					minCounter;					// Counter_Step = 1s

#endif
