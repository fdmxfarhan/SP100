/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_ENUM_TYPEDEF_H
#define __SP100_ENUM_TYPEDEF_H

/* Exported types *************************************************************/
/* CCU_State -----------------------------------------------------------------*/
typedef enum
{
	CCU_OFF,						//--> CCU_OFF
	CCU_AUTO,						//--> CCU_AUTO
	CCU_DEF,						//--> CCU_DEF
	CCU_SENSOR,						//--> CCU_SENSOR
	CCU_DIAG,						//--> CCU_DIAG
	CCU_IGN_OFF,					//--> CCU_IGN_OFF
}	CCU_State;

/* Intake_State --------------------------------------------------------------*/
typedef enum
{
	Intake_Fresh,					//--> Intake_Fresh
	Intake_Recycle,					//--> Intake_Recycle
}	Intake_State;

/* Mode_State ----------------------------------------------------------------*/
typedef enum
{
	Mode_Face,						//--> Mode_Face
	Mode_Face_Foot,					//--> Mode_Face_Foot
	Mode_Foot,						//--> Mode_Foot
	Mode_Foot_Def,					//--> Mode_Foot_Def
	Mode_Def,						//--> Mode_Def
}	Mode_State;

/* Airmix_State --------------------------------------------------------------*/
typedef enum
{
	Airmix_Lo,						//--> Airmix_Lo
	Airmix_05,						//--> Airmix_05
	Airmix_10,						//--> Airmix_10
	Airmix_15,						//--> Airmix_15
	Airmix_20,						//--> Airmix_20
	Airmix_25,						//--> Airmix_25
	Airmix_30,						//--> Airmix_30
	Airmix_35,						//--> Airmix_35
	Airmix_40,						//--> Airmix_40
	Airmix_45,						//--> Airmix_45
	Airmix_50,						//--> Airmix_50
	Airmix_55,						//--> Airmix_55
	Airmix_60,						//--> Airmix_60
	Airmix_65,						//--> Airmix_65
	Airmix_70,						//--> Airmix_70
	Airmix_75,						//--> Airmix_75
	Airmix_80,						//--> Airmix_80
	Airmix_85,						//--> Airmix_85
	Airmix_90,						//--> Airmix_90
	Airmix_95,						//--> Airmix_95
	Airmix_Hi,						//--> Airmix_Hi
}	Airmix_State;

/* Blower_State --------------------------------------------------------------*/
typedef enum
{
	Blower_OFF,						//--> Blower_OFF
	Blower_L1,						//--> Blower_L1
	Blower_L2,						//--> Blower_L2
	Blower_L3,						//--> Blower_L3
	Blower_L4,						//--> Blower_L4
	Blower_L5,						//--> Blower_L5
	Blower_L6,						//--> Blower_L6
	Blower_L7,						//--> Blower_L7
	Blower_L8,						//--> Blower_L8
}	Blower_State;

/* AC_State ------------------------------------------------------------------*/
typedef enum
{
	AC_OFF,							//--> AC_OFF
	AC_ON,							//--> AC_ON
}	AC_State;

/* AC_Temp_State -------------------------------------------------------------*/
typedef enum
{
	AC_Temp_OFF,					//--> AC_Temp_OFF
	AC_Temp_ON,						//--> AC_Temp_ON
}	AC_Temp_State;

/* R_DEF_State ---------------------------------------------------------------*/
typedef enum
{
	R_DEF_OFF,						//--> R_DEF_OFF
	R_DEF_ON,						//--> R_DEF_ON
}	R_DEF_State;

/* Auto_Ctrl_State -----------------------------------------------------------*/
typedef enum
{
	Auto_Ctrl_OFF,					//--> Auto_Ctrl_OFF
	Auto_Ctrl_ON,					//--> Auto_Ctrl_ON
}	Auto_Ctrl_State;

/* Sensor_State --------------------------------------------------------------*/
typedef enum
{
	Sensor_OK,						//--> Sensor_OK
	Sensor_Error,					//--> Sensor_Error
}	Sensor_State;

/* MA_Lock_State -------------------------------------------------------------*/
typedef enum
{
	MA_Lock_OK,						//--> MA_Lock_OK
	MA_Lock_Error,					//--> MA_Lock_Error
}	MA_Lock_State;

/* MA_Pot_State --------------------------------------------------------------*/
typedef enum
{
	MA_Pot_OK,						//--> MA_Pot_OK
	MA_Pot_Error,					//--> MA_Pot_Error
}	MA_Pot_State;

/* AUTO_Error_State ----------------------------------------------------------*/
typedef enum
{
	AUTO_Error_OFF,					//--> AUTO_Error_OFF
	AUTO_Error_ON,					//--> AUTO_Error_ON
}	AUTO_Error_State;

/* AUTO_Blink_State ----------------------------------------------------------*/
typedef enum
{
	AUTO_Blink_OFF,					//--> AUTO_Blink_OFF
	AUTO_Blink_ON,					//--> AUTO_Blink_ON
}	AUTO_Blink_State;

/* SEG_State -----------------------------------------------------------------*/
typedef enum
{
	SEG_OFF,						//--> SEG_OFF
	SEG_ON,							//--> SEG_ON
}	SEG_State;

/* Mode_SEG_State ------------------------------------------------------------*/
typedef enum
{
	Mode_SEG_OFF,					//--> Mode_SEG_OFF
	Mode_SEG_ON,					//--> Mode_SEG_ON
}	Mode_SEG_State;

/* DIAG_State ----------------------------------------------------------------*/
typedef enum
{
	DIAG_Sensor,					//--> DIAG_Sensor
	DIAG_Actuator,					//--> DIAG_Actuator
}	DIAG_State;

/* DIAG_Sensor_Index ---------------------------------------------------------*/
typedef enum
{
	DIAG_Sensor_All,				//--> DIAG_Sensor_All
	DIAG_Sensor_Evap,				//--> DIAG_Sensor_Evap
	DIAG_Sensor_Cabin,				//--> DIAG_Sensor_Cabin
	DIAG_Sensor_Water,				//--> DIAG_Sensor_Water
	DIAG_Sensor_Ambient,			//--> DIAG_Sensor_Ambient
	DIAG_Sensor_OFF,				//--> DIAG_Sensor_OFF
}	DIAG_Sensor_Index;

/* DIAG_Actuator_Index -------------------------------------------------------*/
typedef enum
{
	DIAG_Actuator_All,				//--> DIAG_Actuator_All
	DIAG_Actuator_Airmix_Lock,		//--> DIAG_Actuator_Airmix_Lock
	DIAG_Actuator_Mode_Lock,		//--> DIAG_Actuator_Mode_Lock
	DIAG_Actuator_Airmix_Pot,		//--> DIAG_Actuator_Airmix_Pot
	DIAG_Actuator_Mode_Pot,			//--> DIAG_Actuator_Mode_Pot
	DIAG_Actuator_OFF,				//--> DIAG_Actuator_OFF
}	DIAG_Actuator_Index;

/* DIAG_Actuator_Busy --------------------------------------------------------*/
typedef enum
{
	DIAG_Actuator_Busy_OFF,			//--> DIAG_Actuator_Busy_OFF
	DIAG_Actuator_Busy_ON,			//--> DIAG_Actuator_Busy_ON
}	DIAG_Actuator_Busy;

#endif
