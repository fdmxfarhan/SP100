/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_AIRMIX_MA_H
#define __NX7_AIRMIX_MA_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
#define		NX7_Airmix_Tolerance		0.100
#define		NX7_Airmix_Lo_Pos			0.500
#define		NX7_Airmix_05_Pos			0.695
#define		NX7_Airmix_10_Pos			0.890
#define		NX7_Airmix_15_Pos			1.085
#define		NX7_Airmix_20_Pos			1.280
#define		NX7_Airmix_25_Pos			1.475
#define		NX7_Airmix_30_Pos			1.670
#define		NX7_Airmix_35_Pos			1.865
#define		NX7_Airmix_40_Pos			2.060
#define		NX7_Airmix_45_Pos			2.255
#define		NX7_Airmix_50_Pos			2.450
#define		NX7_Airmix_55_Pos			2.645
#define		NX7_Airmix_60_Pos			2.840
#define		NX7_Airmix_65_Pos			3.035
#define		NX7_Airmix_70_Pos			3.230
#define		NX7_Airmix_75_Pos			3.425
#define		NX7_Airmix_80_Pos			3.620
#define		NX7_Airmix_85_Pos			3.815
#define		NX7_Airmix_90_Pos			4.010
#define		NX7_Airmix_95_Pos			4.205
#define		NX7_Airmix_Hi_Pos			4.400

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_Airmix_MA_STP(void);
void NX7_Airmix_MA_FWD(void);
void NX7_Airmix_MA_RVS(void);
void NX7_Airmix_MA_Handler(Airmix_State state);

#endif
