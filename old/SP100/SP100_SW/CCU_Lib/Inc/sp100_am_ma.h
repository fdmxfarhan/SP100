/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_AM_MA_H
#define __SP100_AM_MA_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_AM_Tolerance		0.05
#define		SP100_AM_Lo_Pos			0.50
#define		SP100_AM_05_Pos			0.70
#define		SP100_AM_10_Pos			0.90
#define		SP100_AM_15_Pos			1.10
#define		SP100_AM_20_Pos			1.30
#define		SP100_AM_25_Pos			1.50
#define		SP100_AM_30_Pos			1.70
#define		SP100_AM_35_Pos			1.90
#define		SP100_AM_40_Pos			2.10
#define		SP100_AM_45_Pos			2.30
#define		SP100_AM_50_Pos			2.50
#define		SP100_AM_55_Pos			2.70
#define		SP100_AM_60_Pos			2.90
#define		SP100_AM_65_Pos			3.10
#define		SP100_AM_70_Pos			3.30
#define		SP100_AM_75_Pos			3.50
#define		SP100_AM_80_Pos			3.70
#define		SP100_AM_85_Pos			3.90
#define		SP100_AM_90_Pos			4.10
#define		SP100_AM_95_Pos			4.30
#define		SP100_AM_Hi_Pos			4.50

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_AM_MA_STP(void);
void SP100_AM_MA_FWD(void);
void SP100_AM_MA_RVS(void);
void SP100_AM_MA_Handler(AM_State state);

#endif
