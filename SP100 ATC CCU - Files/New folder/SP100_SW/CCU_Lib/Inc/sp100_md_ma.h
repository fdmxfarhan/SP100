/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_MD_MA_H
#define __SP100_MD_MA_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_MD_Tolerance			0.05
#define		SP100_MD_Face_Pos			4.75
#define		SP100_MD_Face_Foot_Pos		3.63
#define		SP100_MD_Foot_Pos			2.50
#define		SP100_MD_Foot_Def_Pos		1.38
#define		SP100_MD_Def_Pos			0.25

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_MD_MA_STP(void);
void SP100_MD_MA_FWD(void);
void SP100_MD_MA_RVS(void);
void SP100_MD_MA_Handler(MD_State state);

#endif
