/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_Airmix_H
#define __SP100_Airmix_H

/* Includes *******************************************************************/
#include "SP100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		SP100_Airmix_Tolerance		0.1
#define		SP100_Airmix_Lo_Pos			0.50
#define		SP100_Airmix_05_Pos			0.70
#define		SP100_Airmix_10_Pos			0.90
#define		SP100_Airmix_15_Pos			1.10
#define		SP100_Airmix_20_Pos			1.30
#define		SP100_Airmix_25_Pos			1.50
#define		SP100_Airmix_30_Pos			1.70
#define		SP100_Airmix_35_Pos			1.90
#define		SP100_Airmix_40_Pos			2.10
#define		SP100_Airmix_45_Pos			2.30
#define		SP100_Airmix_50_Pos			2.50
#define		SP100_Airmix_55_Pos			2.70
#define		SP100_Airmix_60_Pos			2.90
#define		SP100_Airmix_65_Pos			3.10
#define		SP100_Airmix_70_Pos			3.30
#define		SP100_Airmix_75_Pos			3.50
#define		SP100_Airmix_80_Pos			3.70
#define		SP100_Airmix_85_Pos			3.90
#define		SP100_Airmix_90_Pos			4.10
#define		SP100_Airmix_95_Pos			4.30
#define		SP100_Airmix_Hi_Pos			4.50
/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_Airmix_STP(void);
void SP100_Airmix_FWD(void);
void SP100_Airmix_RVS(void);
void SP100_Airmix_Handler(Airmix_State state);

#endif
