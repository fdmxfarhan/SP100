/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_MODE_MA_H
#define __NX7_MODE_MA_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		NX7_Mode_Tolerance			0.10
#define		NX7_Mode_Face_Pos			4.50
#define		NX7_Mode_Face_Foot_Pos		3.30
#define		NX7_Mode_Foot_Pos			2.40
#define		NX7_Mode_Foot_Def_Pos		1.40
#define		NX7_Mode_Def_Pos			0.50

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_Mode_MA_STP(void);
void NX7_Mode_MA_FWD(void);
void NX7_Mode_MA_RVS(void);
void NX7_Mode_MA_Handler(Mode_State state);

#endif
