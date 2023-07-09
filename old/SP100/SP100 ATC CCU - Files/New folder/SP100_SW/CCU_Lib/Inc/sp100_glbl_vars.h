/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_GLBL_VARS_H
#define __SP100_GLBL_VARS_H

/* CCU_State -----------------------------------------------------------------*/
extern		CCU_State			SP100_CCU_preState;
extern		CCU_State			SP100_CCU_State;
/* Module_State --------------------------------------------------------------*/
extern		IT_State			SP100_IT_State;
extern		MD_State			SP100_MD_State;
extern		AM_State			SP100_AM_State;
extern		BL_State			SP100_BL_State;
extern		AC_State			SP100_AC_State;
extern		AC_Temp_State		SP100_AC_Temp_State;
extern		RD_State			SP100_RD_State;
/* Module_preState -----------------------------------------------------------*/
extern		IT_State			SP100_IT_preState;
extern		MD_State			SP100_MD_preState;
extern		BL_State			SP100_BL_preState;
extern		AC_State			SP100_AC_preState;
/* Auto_Ctrl_State -----------------------------------------------------------*/
extern		Auto_Ctrl_State		IT_Auto_Ctrl_State;
extern		Auto_Ctrl_State		MD_Auto_Ctrl_State;
extern		Auto_Ctrl_State		BL_Auto_Ctrl_State;
extern		Auto_Ctrl_State		AC_Auto_Ctrl_State;
/* Snsr_State ----------------------------------------------------------------*/
extern		Snsr_State			Evap_Snsr_State;
extern		Snsr_State			Cabin_Snsr_State;
extern		Snsr_State			Water_Snsr_State;
extern		Snsr_State			Ambient_Snsr_State;
/* Actr_State ----------------------------------------------------------------*/
extern		MA_Lock_State		AM_MA_Lock_State;
extern		MA_Lock_State		MD_MA_Lock_State;
extern		MA_Pot_State		AM_MA_Pot_State;
extern		MA_Pot_State		MD_MA_Pot_State;
/* AUTO_Error_State ----------------------------------------------------------*/
extern		AUTO_Error_State	SP100_AUTO_Error_State;
extern		AUTO_Blink_State	SP100_AUTO_Blink_State;
/* MD_SEG_State --------------------------------------------------------------*/
extern		MD_SEG_State		SP100_MD_SEG_State;
/* DIAG_State ----------------------------------------------------------------*/
extern		DIAG_State			SP100_DIAG_State;
extern		DIAG_Snsr_Index		SP100_DIAG_Snsr_Index;
extern		DIAG_Actr_Index		SP100_DIAG_Actr_Index;
extern		DIAG_Actr_Busy		SP100_DIAG_Actr_Busy;

extern		float				SP100_SP;

extern		float				SP100_Evap_Snsr;
extern		float				SP100_Cabin_Snsr;
extern		float				SP100_Water_Snsr;
extern		float				SP100_Ambient_Snsr;

extern		float				SP100_AM_FB;
extern		float				SP100_MD_FB;
extern		float				SP100_BL_VOLT;

extern		int					Counter;

extern		int					flag;
extern		int					pwmVal;

extern		int					SP100_CCU_Snsr_Index;

#endif
