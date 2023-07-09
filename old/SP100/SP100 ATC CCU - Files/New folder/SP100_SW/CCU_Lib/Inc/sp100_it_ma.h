/* Define to prevent recursive inclusion **************************************/
#ifndef __SP100_IT_MA_H
#define __SP100_IT_MA_H

/* Includes *******************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void SP100_IT_MA_STP(void);
void SP100_IT_MA_Fresh(void);
void SP100_IT_MA_Recycle(void);
void SP100_IT_MA_Handler(IT_State state);

#endif
