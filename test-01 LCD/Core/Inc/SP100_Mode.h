/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_MODE_H
#define __SP100_MODE_H

/* Includes *******************************************************************/
#include "mylib_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_Mode_Tolerance			0.05
#define		SP100_Mode_Face_Pos				4.75 //4.75
#define		SP100_Mode_Face_Foot_Pos	3.63 //3.63
#define		SP100_Mode_Foot_Pos				2.50 //2.50
#define		SP100_Mode_Foot_Def_Pos		1.38 //1.38
#define		SP100_Mode_Def_Pos				0.25 //0.25

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_Mode_STP(void);
void SP100_Mode_FWD(void);
void SP100_Mode_RVS(void);
void SP100_Mode_Handler(Mode_State state);

#endif
