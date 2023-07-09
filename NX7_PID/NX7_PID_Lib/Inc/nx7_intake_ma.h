/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_INTAKE_MA_H
#define __NX7_INTAKE_MA_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_Intake_MA_STP(void);
void NX7_Intake_MA_Fresh(void);
void NX7_Intake_MA_Recycle(void);
void NX7_Intake_MA_Handler(Intake_State state);

#endif
