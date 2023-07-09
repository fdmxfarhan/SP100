/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_SENSORS_H
#define __NX7_SENSORS_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/
typedef struct
{
	float Evap_Sensor;
	float Cabin_Sensor;
	float Water_Sensor;
	float Ambient_Sensor;
	float Solar_Sensor;
}	CCU_Sensor;

/* Exported constants *********************************************************/
/* Evap_Sensor Config. -------------------------------------------------------*/
#define		Evap_Default		10.0					// Evap_Default -> 10°C
#define		Evap_Beta			3914.0					// Beta Value
#define		Evap_R25			2000.0					// Resistance @25°C
#define		Evap_Bias			4700.0					// Bias Resistor
#define		Evap_shA			0.001415001305			// Steinhart-Hart Coefficient A
#define		Evap_shB			0.00025494447325		// Steinhart-Hart Coefficient B
#define		Evap_shC			0.000000002748728631	// Steinhart-Hart Coefficient C

/* Cabin_Sensor Config. ------------------------------------------------------*/
#define		Cabin_Default		25.0					// Cabin_Default -> 25°C
#define		Cabin_Beta			3975.0					// Beta Value
#define		Cabin_R25			10000.0					// Resistance @25°C
#define		Cabin_Bias			10000.0					// Bias Resistor
#define		Cabin_shA			0.001037295333			// Steinhart-Hart Coefficient A
#define		Cabin_shB			0.0002515076137			// Steinhart-Hart Coefficient B
#define		Cabin_shC			0.0000000003204511687	// Steinhart-Hart Coefficient C
/* Water_Sensor Config. ------------------------------------------------------*/
#define		Water_Default		75.0					// Water_Default -> 75°C
#define		Water_Beta			3588.0					// Beta Value
#define		Water_R25			2051.0					// Resistance @25°C
#define		Water_Bias			1000.0					// Bias Resistor
#define		Water_shA			0.001349204971			// Steinhart-Hart Coefficient A
#define		Water_shB			0.0002529488403			// Steinhart-Hart Coefficient B
#define		Water_shC			0.0000001709149225		// Steinhart-Hart Coefficient C
/* Ambient_Sensor Config. ----------------------------------------------------*/
#define		Ambient_Default		25.0					// Ambient_Default -> 25°C
#define		Ambient_Beta		3470.0					// Beta Value
#define		Ambient_R25			2190.0					// Resistance @25°C
#define		Ambient_Bias		4700.0					// Bias Resistor
#define		Ambient_shA			0.001136235823			// Steinhart-Hart Coefficient A
#define		Ambient_shB			0.0002884357606			// Steinhart-Hart Coefficient B
#define		Ambient_shC    	   -0.000000001688326633	// Steinhart-Hart Coefficient C
/* Solar_Sensor Config. ------------------------------------------------------*/
#define		Solar_Default		100.0					// Solar_Default -> 100°C
#define		Solar_Beta			3950.0					// Beta Value
#define		Solar_R25			10000.0					// Resistance @25°C
#define		Solar_Bias			4700.0					// Bias Resistor
#define		Solar_shA			0.001022744255			// Steinhart-Hart Coefficient A
#define		Solar_shB			0.0002530924225			// Steinhart-Hart Coefficient B
#define		Solar_shC			0.0000000002621516287	// Steinhart-Hart Coefficient C

/* Exported macro *************************************************************/

/* Exported functions *********************************************************/
void NX7_Sensors_Handler(uint16_t evap, uint16_t cabin, uint16_t water, uint16_t ambient, uint16_t solar);

#endif
