/* Define to prevent recursive inclusion ***************************************/
#ifndef __SP100_SNSRS_H
#define __SP100_SNSRS_H

/* Includes ********************************************************************/
#include "sp100_atc_ccu.h"

/* Exported types **************************************************************/

/* Exported constants **********************************************************/
/* Evap_Snsr Config. --------------------------------------------------------*/
#define		Evap_Default		10.0					// Evap_Default -> 10°C
#define		Evap_Beta			3900.0					// Beta Value
#define		Evap_R25			1500.0					// Resistance @25°C
#define		Evap_Bias			4700.0					// Bias Resistor
#define		Evap_shA			0.001478188324			// Steinhart-Hart Coefficient A
#define		Evap_shB			0.0002565692472			// Steinhart-Hart Coefficient B
#define		Evap_shC		   -0.000000001327775824	// Steinhart-Hart Coefficient C
/* Cabin_Snsr Config. -------------------------------------------------------*/
#define		Cabin_Default		25.0					// Cabin_Default -> 25°C
#define		Cabin_Beta			3975.0					// Beta Value
#define		Cabin_R25			10000.0					// Resistance @25°C
#define		Cabin_Bias			10000.0					// Bias Resistor
#define		Cabin_shA			0.001037295333			// Steinhart-Hart Coefficient A
#define		Cabin_shB			0.0002515076137			// Steinhart-Hart Coefficient B
#define		Cabin_shC			0.0000000003204511687	// Steinhart-Hart Coefficient C
/* Water_Snsr Config. -------------------------------------------------------*/
#define		Water_Default		75.0					// Water_Default -> 75°C
#define		Water_Beta			3588.0					// Beta Value
#define		Water_R25			2051.0					// Resistance @25°C
#define		Water_Bias			1000.0					// Bias Resistor
#define		Water_shA			0.001349204971			// Steinhart-Hart Coefficient A
#define		Water_shB			0.0002529488403			// Steinhart-Hart Coefficient B
#define		Water_shC			0.0000001709149225		// Steinhart-Hart Coefficient C
/* Ambient_Snsr Config. -----------------------------------------------------*/
#define		Ambient_Default		25.0					// Ambient_Default -> 25°C
#define		Ambient_Beta		3470.0					// Beta Value
#define		Ambient_R25			2190.0					// Resistance @25°C
#define		Ambient_Bias		4700.0					// Bias Resistor
#define		Ambient_shA			0.001136235823			// Steinhart-Hart Coefficient A
#define		Ambient_shB			0.0002884357606			// Steinhart-Hart Coefficient B
#define		Ambient_shC    	   -0.000000001688326633	// Steinhart-Hart Coefficient C

/* Exported macro **************************************************************/

/* Exported functions **********************************************************/
void SP100_Snsrs_Handler(uint16_t evap, uint16_t cabin, uint16_t water, uint16_t ambient);
void SP100_Snsrs_Init(void);

#endif
