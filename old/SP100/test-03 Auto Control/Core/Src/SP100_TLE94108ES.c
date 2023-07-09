/* Includes *******************************************************************/
#include "SP100_TLE94108ES.h"

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern	SPI_HandleTypeDef	hspi1;

/* Functions body *************************************************************/
/* SP100_TLE_Init --------------------------------------------------------------*/
void SP100_TLE_Init(void)
{
	TLE_EN_SET;		
	SP100_Delay(100000);
	SP100_TLE_Ctrl_Register_Write(FW_OL_CTRL, 0xFC);	// Free-wheeling diodes
}

/* SP100_TLE_DeInit ------------------------------------------------------------*/
void SP100_TLE_DeInit(void)
{
	TLE_EN_CLR;
}

/* SP100_TLE_Ctrl_Register_Read ------------------------------------------------*/
uint8_t SP100_TLE_Ctrl_Register_Read(uint8_t address)
{
	uint8_t		rxData[2];
	uint8_t		txData[2] = {address,0xFF};
	TLE_CSN_CLR;	
	SP100_Delay(500);
	HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 10);
	SP100_Delay(500);	
	TLE_CSN_SET;	
	SP100_Delay(500);
	return rxData[1];
}

/* SP100_TLE_Ctrl_Register_Write -----------------------------------------------*/
uint8_t SP100_TLE_Ctrl_Register_Write(uint8_t address, uint8_t data)
{
	uint8_t		rxData[2];
	uint8_t		txData[2] = {address|0x80,data};
	TLE_CSN_CLR;	
	SP100_Delay(500);
	HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 10);
	SP100_Delay(500);	
	TLE_CSN_SET;	
	SP100_Delay(500);
	return rxData[1];
}
