/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_INTAKE_H
#define __SP100_INTAKE_H

/* Includes *******************************************************************/
#include "mylib_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_Intake_STP(void);
void SP100_Intake_Fresh(void);
void SP100_Intake_Recycle(void);
void SP100_Intake_Handler(Intake_State state);

#endif
