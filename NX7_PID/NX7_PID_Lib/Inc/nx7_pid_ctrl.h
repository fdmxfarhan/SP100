/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_PID_CTRL_H
#define __NX7_PID_CTRL_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_PID_Ctrl_No_Hysteresis(void);
void NX7_PID_Ctrl(void);
void NX7_PID_Ctrl_Blower(void);

#endif
