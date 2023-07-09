/* Includes *******************************************************************/
#include "nx7_tle94106es.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern	SPI_HandleTypeDef	hspi1;

/* Functions body *************************************************************/
/* NX7_TLE_Init --------------------------------------------------------------*/
void NX7_TLE_Init(void)
{
	TLE_EN_SET;		NX7_Delay(100000);
	//NX7_TLE_Ctrl_Register_Write(FW_OL_CTRL, 0xFC);	// Free-wheeling diodes
}

/* NX7_TLE_DeInit ------------------------------------------------------------*/
void NX7_TLE_DeInit(void)
{
	TLE_EN_CLR;
}

/* NX7_TLE_Ctrl_Register_Read ------------------------------------------------*/
uint8_t NX7_TLE_Ctrl_Register_Read(uint8_t address)
{
	uint8_t		rxData[2];
	uint8_t		txData[2] = {address,0xFF};
	TLE_CSN_CLR;	NX7_Delay(500);
	HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 10);
	NX7_Delay(500);	TLE_CSN_SET;	NX7_Delay(500);
	return rxData[1];
}

/* NX7_TLE_Ctrl_Register_Write -----------------------------------------------*/
uint8_t NX7_TLE_Ctrl_Register_Write(uint8_t address, uint8_t data)
{
	uint8_t		rxData[2];
	uint8_t		txData[2] = {address|0x80,data};
	TLE_CSN_CLR;	NX7_Delay(500);
	HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 10);
	NX7_Delay(500);	TLE_CSN_SET;	NX7_Delay(500);
	return rxData[1];
}
