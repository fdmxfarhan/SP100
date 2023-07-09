/* Includes *******************************************************************/
#include "nx7_sensors.h"
#include <math.h>

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
float	tempCabin, tempAmbient;

CCU_Sensor	NX7_CCU_Sensor;

extern	Sensor_State	Evap_Sensor_State;
extern	Sensor_State	Cabin_Sensor_State;
extern	Sensor_State	Water_Sensor_State;
extern	Sensor_State	Ambient_Sensor_State;
extern	Sensor_State	Solar_Sensor_State;
extern	AC_Temp_State	NX7_AC_Temp_State;

/* Functions body *************************************************************/
/* NX7_Sensors_Handler -------------------------------------------------------*/
void NX7_Sensors_Handler(uint16_t evap, uint16_t cabin, uint16_t water, uint16_t ambient, uint16_t solar)
{
	//--> Digital to Analog Conversion
	float adc1AnlgVal[5];
	adc1AnlgVal[0]	= (evap*3.3)/4095;
	adc1AnlgVal[1]	= (cabin*3.3)/4095;
	adc1AnlgVal[2]	= (water*3.3)/4095;
	adc1AnlgVal[3]	= (ambient*3.3)/4095;
	adc1AnlgVal[4]	= (solar*3.3)/4095;
	//--> Voltage to Resistance Conversion
	float evapRes		=	(Evap_Bias*adc1AnlgVal[0])/(3.3-adc1AnlgVal[0]);
	float cabinRes		=	(Cabin_Bias*adc1AnlgVal[1])/(3.3-adc1AnlgVal[1]);
	float waterRes		=	(Water_Bias*adc1AnlgVal[2])/(3.3-adc1AnlgVal[2]);
	float ambientRes	=	(Ambient_Bias*adc1AnlgVal[3])/(3.3-adc1AnlgVal[3]);
	float solarRes		=	(Solar_Bias*adc1AnlgVal[4])/(3.3-adc1AnlgVal[4]);
	//--> Resistance Logarithm
	float logVal[5];
	logVal[0]	= logf(evapRes);
	logVal[1]	= logf(cabinRes);
	logVal[2]	= logf(waterRes);
	logVal[3]	= logf(ambientRes);
	logVal[4]	= logf(solarRes);
	//--> Steinhart-Hart Equation
	NX7_CCU_Sensor.Evap_Sensor		=	1 / ((Evap_shA)+(Evap_shB*logVal[0])+(Evap_shC*powf(logVal[0],3)));
	tempCabin						=	1 / ((Cabin_shA)+(Cabin_shB*logVal[1])+(Cabin_shC*powf(logVal[1],3)));
	NX7_CCU_Sensor.Water_Sensor		=	1 / ((Water_shA)+(Water_shB*logVal[2])+(Water_shC*powf(logVal[2],3)));
	tempAmbient						=	1 / ((Ambient_shA)+(Ambient_shB*logVal[3])+(Ambient_shC*powf(logVal[3],3)));
	NX7_CCU_Sensor.Solar_Sensor		=	1 / ((Solar_shA)+(Solar_shB*logVal[4])+(Solar_shC*powf(logVal[4],3)));
	//--> Kelvin to Celsius Conversion
	NX7_CCU_Sensor.Evap_Sensor		-=	273.15;
	tempCabin						-=	273.15;
	NX7_CCU_Sensor.Water_Sensor		-=	273.15;
	tempAmbient						-=	273.15;
	NX7_CCU_Sensor.Solar_Sensor		-=	273.15;
	//--> tempCabin & tempAmbient
	if(fabsf(tempCabin-NX7_CCU_Sensor.Cabin_Sensor) > 0.20)
	{
		NX7_CCU_Sensor.Cabin_Sensor = tempCabin;
	}
	if(fabsf(tempAmbient-NX7_CCU_Sensor.Ambient_Sensor) > 0.50)
	{
		NX7_CCU_Sensor.Ambient_Sensor = tempAmbient;
	}
	//--> Sensor State Detection
	if((adc1AnlgVal[0]<0.10)||(adc1AnlgVal[0]>3.20))	{Evap_Sensor_State = Sensor_Error;}
	else												{Evap_Sensor_State = Sensor_OK;}
	if((adc1AnlgVal[1]<0.10)||(adc1AnlgVal[1]>3.20))	{Cabin_Sensor_State = Sensor_Error;}
	else												{Cabin_Sensor_State = Sensor_OK;}
	if((adc1AnlgVal[2]<0.10)||(adc1AnlgVal[2]>3.20))	{Water_Sensor_State = Sensor_Error;}
	else												{Water_Sensor_State = Sensor_OK;}
	if((adc1AnlgVal[3]<0.10)||(adc1AnlgVal[3]>3.20))	{Ambient_Sensor_State = Sensor_Error;}
	else												{Ambient_Sensor_State = Sensor_OK;}
	if((adc1AnlgVal[4]<0.10)||(adc1AnlgVal[4]>3.20))	{Solar_Sensor_State = Sensor_Error;}
	else												{Solar_Sensor_State = Sensor_OK;}
	//--> Sensor Default Value
	if(Evap_Sensor_State == Sensor_Error)				{NX7_CCU_Sensor.Evap_Sensor = Evap_Default;}
	if(Cabin_Sensor_State == Sensor_Error)				{NX7_CCU_Sensor.Cabin_Sensor = Cabin_Default;}
	if(Water_Sensor_State == Sensor_Error)				{NX7_CCU_Sensor.Water_Sensor = Water_Default;}
	if(Ambient_Sensor_State == Sensor_Error)			{NX7_CCU_Sensor.Ambient_Sensor = Ambient_Default;}
	if(Solar_Sensor_State == Sensor_Error)				{NX7_CCU_Sensor.Solar_Sensor = Solar_Default;}
	//--> AC_Temp_State Detection
	if(NX7_CCU_Sensor.Evap_Sensor < 0.5)				{NX7_AC_Temp_State = AC_Temp_OFF;}
	if(NX7_CCU_Sensor.Evap_Sensor > 3.0)				{NX7_AC_Temp_State = AC_Temp_ON;}
}
