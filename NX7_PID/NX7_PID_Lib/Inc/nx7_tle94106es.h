/* Define to prevent recursive inclusion **************************************/
#ifndef __NX7_TLE94106ES_H
#define __NX7_TLE94106ES_H

/* Includes *******************************************************************/
#include "nx7_atc_ccu.h"

/* Exported types *************************************************************/

/* Exported constants *********************************************************/
//--> TLE94106ES Control Registers
#define		HB_ACT_1_CTRL		0x03	//--> read/write
#define		HB_ACT_2_CTRL		0x43	//--> read/write
#define		HB_MODE_1_CTRL		0x63	//--> read/write
#define		HB_MODE_2_CTRL		0x13	//--> read/write
#define		PWM_CH_FREQ_CTRL	0x33	//--> read/write
#define		PWM1_DC_CTRL		0x73	//--> read/write
#define		PWM2_DC_CTRL		0x0B	//--> read/write
#define		PWM3_DC_CTRL		0x4B	//--> read/write
#define		FW_OL_CTRL			0x2B	//--> read/write
#define		CONFIG_CTRL			0x67	//--> read
//--> TLE94106ES Status Registers
#define		SYS_DIAG_1			0x1B	//--> read/clear
#define		SYS_DIAG_2			0x5B	//--> read/clear
#define		SYS_DIAG_3			0x3B	//--> read/clear
#define		SYS_DIAG_5			0x07	//--> read/clear
#define		SYS_DIAG_6			0x47	//--> read/clear

/* Exported macro *************************************************************/
// TLE_EN
#define		TLE_EN_SET		HAL_GPIO_WritePin(TLE_EN_GPIO_Port, TLE_EN_Pin, GPIO_PIN_SET);
#define		TLE_EN_CLR		HAL_GPIO_WritePin(TLE_EN_GPIO_Port, TLE_EN_Pin, GPIO_PIN_RESET);
// TLE_CSN
#define		TLE_CSN_SET		HAL_GPIO_WritePin(TLE_CSN_GPIO_Port, TLE_CSN_Pin, GPIO_PIN_SET);
#define		TLE_CSN_CLR		HAL_GPIO_WritePin(TLE_CSN_GPIO_Port, TLE_CSN_Pin, GPIO_PIN_RESET);

/* Exported functions *********************************************************/
void NX7_TLE_Init(void);
void NX7_TLE_DeInit(void);
uint8_t NX7_TLE_Ctrl_Register_Read(uint8_t address);
uint8_t NX7_TLE_Ctrl_Register_Write(uint8_t address, uint8_t data);

#endif
