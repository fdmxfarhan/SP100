/* Define to prevent recursive inclusion *************************************/
#ifndef __SP100_TYPEDEF_H
#define __SP100_TYPEDEF_H

/* CCU_State ----------------------------------------------------------------*/
typedef enum
{
	CCU_OFF,
	CCU_AUTO,
	CCU_DEF,
	CCU_SNSR,
	CCU_DIAG,
	CCU_IGN_OFF,
}	CCU_State;

/* IT_State -----------------------------------------------------------------*/
typedef enum
{
	IT_Fresh,
	IT_Recycle,
}	IT_State;

/* MD_State -----------------------------------------------------------------*/
typedef enum
{
	MD_Face,
	MD_Face_Foot,
	MD_Foot,
	MD_Foot_Def,
	MD_Def,
}	MD_State;

/* AM_State -----------------------------------------------------------------*/
typedef enum
{
	AM_Lo,
	AM_05,
	AM_10,
	AM_15,
	AM_20,
	AM_25,
	AM_30,
	AM_35,
	AM_40,
	AM_45,
	AM_50,
	AM_55,
	AM_60,
	AM_65,
	AM_70,
	AM_75,
	AM_80,
	AM_85,
	AM_90,
	AM_95,
	AM_Hi,
}	AM_State;

/* BL_State -----------------------------------------------------------------*/
typedef enum
{
	BL_OFF,
	BL_L1,
	BL_L2,
	BL_L3,
	BL_L4,
	BL_L5,
	BL_L6,
	BL_L7,
	BL_L8,
}	BL_State;

/* AC_State -----------------------------------------------------------------*/
typedef enum
{
	AC_OFF,
	AC_ON,
}	AC_State;

/* AC_Temp_State ------------------------------------------------------------*/
typedef enum
{
	AC_Temp_OFF,
	AC_Temp_ON,
}	AC_Temp_State;

/* RD_State -----------------------------------------------------------------*/
typedef enum
{
	RD_OFF,
	RD_ON,
}	RD_State;

/* Auto_Ctrl_State ----------------------------------------------------------*/
typedef enum
{
	Auto_Ctrl_OFF,
	Auto_Ctrl_ON,
}	Auto_Ctrl_State;

/* Snsr_State ---------------------------------------------------------------*/
typedef enum
{
	Snsr_OK,
	Snsr_Error,
}	Snsr_State;

/* MA_Lock_State ------------------------------------------------------------*/
typedef enum
{
	MA_Lock_OK,
	MA_Lock_Error,
}	MA_Lock_State;

/* MA_Pot_State -------------------------------------------------------------*/
typedef enum
{
	MA_Pot_OK,
	MA_Pot_Error,
}	MA_Pot_State;

/* AUTO_Error_State ---------------------------------------------------------*/
typedef enum
{
	AUTO_Error_OFF,
	AUTO_Error_ON,
}	AUTO_Error_State;

/* AUTO_Blink_State ---------------------------------------------------------*/
typedef enum
{
	AUTO_Blink_OFF,
	AUTO_Blink_ON,
}	AUTO_Blink_State;

/* SEG_State ----------------------------------------------------------------*/
typedef enum
{
	SEG_OFF,
	SEG_ON,
}	SEG_State;

/* MD_SEG_State -------------------------------------------------------------*/
typedef enum
{
	MD_SEG_OFF,
	MD_SEG_ON,
}	MD_SEG_State;

/* DIAG_State ---------------------------------------------------------------*/
typedef enum
{
	DIAG_Snsr,
	DIAG_Actr,
}	DIAG_State;

/* DIAG_Snsr_Index ----------------------------------------------------------*/
typedef enum
{
	DIAG_Snsr_All,
	DIAG_Snsr_Evap,
	DIAG_Snsr_Cabin,
	DIAG_Snsr_Water,
	DIAG_Snsr_Ambient,
	DIAG_Snsr_OFF,
}	DIAG_Snsr_Index;

/* DIAG_Actr_Index ----------------------------------------------------------*/
typedef enum
{
	DIAG_Actr_All,
	DIAG_Actr_AM_Lock,
	DIAG_Actr_MD_Lock,
	DIAG_Actr_AM_Pot,
	DIAG_Actr_MD_Pot,
	DIAG_Actr_OFF,
}	DIAG_Actr_Index;

/* DIAG_Actr_Busy -----------------------------------------------------------*/
typedef enum
{
	DIAG_Actr_Busy_OFF,
	DIAG_Actr_Busy_ON,
}	DIAG_Actr_Busy;

#endif
