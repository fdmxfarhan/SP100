/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_RD_CTRL_H
#define __SP100_RD_CTRL_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_RD_OFF(void);
void SP100_RD_ON(void);
void SP100_RD_Handler(RD_State state);

#endif
