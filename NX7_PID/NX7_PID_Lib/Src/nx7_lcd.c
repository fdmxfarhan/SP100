/* Includes *******************************************************************/
#include "nx7_lcd.h"
#include "nx7_ext_isr.h"
#include <stdio.h>
#include <string.h>

/* Private typedef ************************************************************/
/* Private define *************************************************************/
/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim4;
extern CCU_State NX7_CCU_State;
extern Sensor_State Ambient_Sensor_State;

/* Functions body *************************************************************/
/* NX7_LCD_Init --------------------------------------------------------------*/
void NX7_LCD_Init(void)
{
	NX7_LCD_Command(Mode_Set_Command|0x00);
	NX7_LCD_Command(System_Set_Command|0x03);
	NX7_LCD_ALL_SEG(SEG_OFF);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	if(Illumination_State == GPIO_PIN_SET)
	{
		NX7_LCD_Backlight(NX7_LCD_NightLight_PWM);
	}
	else
	{
		NX7_LCD_Backlight(NX7_LCD_DayLight_PWM);
	}
}

/* NX7_LCD_Init --------------------------------------------------------------*/
void NX7_LCD_DeInit(void)
{
	NX7_LCD_Command(Mode_Set_Command|0x00);
	NX7_LCD_Command(System_Set_Command&0x80);
	NX7_LCD_ALL_SEG(SEG_OFF);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
}

/* NX7_LCD_Command -----------------------------------------------------------*/
void NX7_LCD_Command(uint8_t command)
{
	uint8_t		pCommand[1] = {command};
	HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, pCommand, 1, 10);
}

/* NX7_LCD_SEG_Read ----------------------------------------------------------*/
uint8_t NX7_LCD_SEG_Read(uint8_t address)
{
	uint8_t		pAddress[1] = {address};
	uint8_t		rxData[1];
	HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, pAddress, 1, 10);
	HAL_I2C_Master_Receive(&hi2c2, HT16K23_Device_Address, rxData, 1, 10);
	return rxData[0];
}

/* NX7_LCD_SEG_OFF -----------------------------------------------------------*/
void NX7_LCD_SEG_OFF(uint8_t address, uint8_t data)
{
	data   =  ~data;
	data  &=  NX7_LCD_SEG_Read(address);
	uint8_t		txData[2] = {address,data};
	HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, txData, 2, 10);
}

/* NX7_LCD_SEG_ON ------------------------------------------------------------*/
void NX7_LCD_SEG_ON(uint8_t address, uint8_t data)
{
	data |= NX7_LCD_SEG_Read(address);
	uint8_t		txData[2] = {address,data};
	HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, txData, 2, 10);
}

/* NX7_LCD_Backlight ---------------------------------------------------------*/
void NX7_LCD_Backlight(uint16_t pwm)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pwm);
}

/* NX7_LCD_ALL_SEG -----------------------------------------------------------*/
void NX7_LCD_ALL_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		for(register int i=0x00; i<=0x09; i++)
		{
			uint8_t		txData[2] = {i,0x00};
			HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, txData, 2, 10);
		}
		break;
	}
	case SEG_ON:
	{
		for(register int i=0x00; i<=0x09; i++)
		{
			uint8_t		txData[2] = {i,0xFF};
			HAL_I2C_Master_Transmit(&hi2c2, HT16K23_Device_Address|0x01, txData, 2, 10);
		}
		break;
	}
	}
}

/* NX7_LCD_OFF_SEG -----------------------------------------------------------*/
void NX7_LCD_OFF_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x03, 0x80);		//--> OFF : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x03, 0x80);			//--> OFF : ON
		break;
	}
	}
}

/* NX7_LCD_AUTO_SEG ----------------------------------------------------------*/
void NX7_LCD_AUTO_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x03, 0x40);		//--> AUTO : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x03, 0x40);			//--> AUTO : ON
		break;
	}
	}
}

/* NX7_LCD_ECON_SEG ----------------------------------------------------------*/
void NX7_LCD_ECON_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x03, 0x20);		//--> ECON : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x03, 0x20);			//--> ECON : ON
		break;
	}
	}
}

/* NX7_LCD_DEF_SEG -----------------------------------------------------------*/
void NX7_LCD_DEF_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x02, 0x08);		//--> DEF : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x02, 0x08);			//--> DEF : ON
		break;
	}
	}
}

/* NX7_LCD_Intake_SEG --------------------------------------------------------*/
void NX7_LCD_Intake_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x06, 0x10);		//--> Car     : OFF
		NX7_LCD_SEG_OFF(0x05, 0x01);		//--> Fresh   : OFF
		NX7_LCD_SEG_OFF(0x05, 0x10);		//--> Recycle : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x06, 0x10);			//--> Car     : ON
		NX7_LCD_SEG_ON(0x05, 0x01);			//--> Fresh   : ON
		NX7_LCD_SEG_ON(0x05, 0x10);			//--> Recycle : ON
		break;
	}
	}
}

/* NX7_LCD_Mode_SEG ----------------------------------------------------------*/
void NX7_LCD_Mode_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x03, 0x01);		//--> PAX  : OFF
		NX7_LCD_SEG_OFF(0x07, 0x10);		//--> Face : OFF
		NX7_LCD_SEG_OFF(0x03, 0x10);		//--> Foot : OFF
		NX7_LCD_SEG_OFF(0x07, 0x20);		//--> Def  : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_ON(0x07, 0x10);			//--> Face : ON
		NX7_LCD_SEG_ON(0x03, 0x10);			//--> Foot : ON
		NX7_LCD_SEG_ON(0x07, 0x20);			//--> Def  : ON
		break;
	}
	}
}

/* NX7_LCD_Blower_SEG --------------------------------------------------------*/
void NX7_LCD_Blower_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x05, 0x02);		//--> BL : OFF
		NX7_LCD_SEG_OFF(0x04, 0x10);		//--> L1 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x20);		//--> L2 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x40);		//--> L3 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x80);		//--> L4 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_ON(0x04, 0x08);			//--> L5 : ON
		NX7_LCD_SEG_ON(0x04, 0x04);			//--> L6 : ON
		NX7_LCD_SEG_ON(0x04, 0x02);			//--> L7 : ON
		NX7_LCD_SEG_ON(0x04, 0x01);			//--> L8 : ON
		break;
	}
	}
}


/* NX7_LCD_Out_Temp_SEG ------------------------------------------------------*/
void NX7_LCD_Out_Temp_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x05, 0x08);		//--> OUT TEMP : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x05, 0x08);			//--> OUT TEMP : ON
		break;
	}
	}
}

/* NX7_LCD_Set_Point_SEG -----------------------------------------------------*/
void NX7_LCD_Set_Point_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_OFF(0x02, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_OFF(0x02, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
		NX7_LCD_SEG_OFF(0x01, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_OFF(0x01, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_OFF(0x01, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
		NX7_LCD_SEG_OFF(0x00, 0x02);		//--> °C    : OFF
		NX7_LCD_SEG_OFF(0x00, 0x01);		//--> °F    : OFF
		NX7_LCD_SEG_OFF(0x01, 0x01);		//--> Point : OFF
		NX7_LCD_SEG_OFF(0x00, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_OFF(0x00, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_OFF(0x00, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
		break;
	}
	case SEG_ON:
	{
		NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
		NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
		NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
		NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
		NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
		NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
		NX7_LCD_SEG_ON(0x00, 0x02);			//--> °C    : ON
		NX7_LCD_SEG_ON(0x00, 0x01);			//--> °F    : ON
		NX7_LCD_SEG_ON(0x01, 0x01);			//--> Point : ON
		NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_ON(0x01, 0x02);			//--> Seg.E : ON
		NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
		NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
		break;
	}
	}

}

/* NX7_LCD_State_Init_SEG ----------------------------------------------------*/
void NX7_LCD_State_Init_SEG(CCU_State state)
{

	switch (state)
	{
	case CCU_OFF:
	{
		NX7_LCD_OFF_SEG(SEG_ON);
		NX7_LCD_AUTO_SEG(SEG_OFF);
		NX7_LCD_ECON_SEG(SEG_OFF);
		NX7_LCD_DEF_SEG(SEG_OFF);
		//NX7_LCD_Intake_SEG();
		//NX7_LCD_Mode_SEG();
		NX7_LCD_Blower_SEG(SEG_OFF);
		NX7_LCD_Out_Temp_SEG(SEG_ON);
		NX7_LCD_Set_Point_SEG(SEG_OFF);
		break;
	}
	case CCU_AUTO:
	{
		NX7_LCD_OFF_SEG(SEG_OFF);
		//NX7_LCD_AUTO_SEG();
		NX7_LCD_ECON_SEG(SEG_OFF);
		NX7_LCD_DEF_SEG(SEG_OFF);
		//NX7_LCD_Intake_SEG();
		//NX7_LCD_Mode_SEG();
		//NX7_LCD_Blower_SEG();
		NX7_LCD_Out_Temp_SEG(SEG_ON);
		//NX7_LCD_Set_Point_SEG();
		break;
	}
	case CCU_DEF:
	{
		NX7_LCD_OFF_SEG(SEG_OFF);
		//NX7_LCD_AUTO_SEG();
		NX7_LCD_ECON_SEG(SEG_OFF);
		NX7_LCD_DEF_SEG(SEG_ON);
		//NX7_LCD_Intake_SEG();
		NX7_LCD_Mode_SEG(SEG_OFF);
		//NX7_LCD_Blower_SEG();
		NX7_LCD_Out_Temp_SEG(SEG_ON);
		//NX7_LCD_Set_Point_SEG();
		break;
	}
	case CCU_IGN_OFF:
	{
		NX7_LCD_ALL_SEG(SEG_OFF);
		break;
	}
	}
}

/* NX7_LCD_AC_Handler --------------------------------------------------------*/
void NX7_LCD_AC_Handler(AC_State state)
{
	switch (state)
	{
	case AC_OFF:
	{
		NX7_LCD_SEG_OFF(0x00, 0x08);		//--> AC : OFF
		break;
	}
	case AC_ON:
	{
		NX7_LCD_SEG_ON(0x00, 0x08);			//--> AC : ON
		break;
	}
	}
}

/* NX7_LCD_R_DEF_Handler -----------------------------------------------------*/
void NX7_LCD_R_DEF_Handler(R_DEF_State state)
{
	switch (state)
	{
	case R_DEF_OFF:
	{
		NX7_LCD_SEG_OFF(0x00, 0x04);		//--> R-DEF : OFF
		break;
	}
	case R_DEF_ON:
	{
		NX7_LCD_SEG_ON(0x00, 0x04);			//--> R-DEF : ON
		break;
	}
	}
}

/* NX7_LCD_Intake_Handler ----------------------------------------------------*/
void NX7_LCD_Intake_Handler(Intake_State state)
{
	switch (state)
	{
	case Intake_Fresh:
	{
		NX7_LCD_SEG_ON(0x06, 0x10);			//--> Car     : ON
		NX7_LCD_SEG_ON(0x05, 0x01);			//--> Fresh   : ON
		NX7_LCD_SEG_OFF(0x05, 0x10);		//--> Recycle : OFF
		break;
	}
	case Intake_Recycle:
	{
		NX7_LCD_SEG_ON(0x06, 0x10);			//--> Car     : ON
		NX7_LCD_SEG_OFF(0x05, 0x01);		//--> Fresh   : OFF
		NX7_LCD_SEG_ON(0x05, 0x10);			//--> Recycle : ON
		break;
	}
	}
}

/* NX7_LCD_Mode_Handler ------------------------------------------------------*/
void NX7_LCD_Mode_Handler(Mode_State state)
{
	switch (state)
	{
	case Mode_Face:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_ON(0x07, 0x10);			//--> Face : ON
		NX7_LCD_SEG_OFF(0x03, 0x10);		//--> Foot : OFF
		NX7_LCD_SEG_OFF(0x07, 0x20);		//--> Def  : OFF
		break;
	}
	case Mode_Face_Foot:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_ON(0x07, 0x10);			//--> Face : ON
		NX7_LCD_SEG_ON(0x03, 0x10);			//--> Foot : ON
		NX7_LCD_SEG_OFF(0x07, 0x20);		//--> Def  : OFF
		break;
	}
	case Mode_Foot:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_OFF(0x07, 0x10);		//--> Face : OFF
		NX7_LCD_SEG_ON(0x03, 0x10);			//--> Foot : ON
		NX7_LCD_SEG_OFF(0x07, 0x20);		//--> Def  : OFF
		break;
	}
	case Mode_Foot_Def:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_OFF(0x07, 0x10);		//--> Face : OFF
		NX7_LCD_SEG_ON(0x03, 0x10);			//--> Foot : ON
		NX7_LCD_SEG_ON(0x07, 0x20);			//--> Def  : ON
		break;
	}
	case Mode_Def:
	{
		NX7_LCD_SEG_ON(0x03, 0x01);			//--> PAX  : ON
		NX7_LCD_SEG_OFF(0x07, 0x10);		//--> Face : OFF
		NX7_LCD_SEG_OFF(0x03, 0x10);		//--> Foot : OFF
		NX7_LCD_SEG_ON(0x07, 0x20);			//--> Def  : ON
		break;
	}
	}
}

/* NX7_LCD_Airmix_Handler ----------------------------------------------------*/
void NX7_LCD_Airmix_Handler(Airmix_State state)
{

}

/* NX7_LCD_Blower_Handler ----------------------------------------------------*/
void NX7_LCD_Blower_Handler(Blower_State state)
{
	switch (state)
	{
	case Blower_OFF:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_OFF(0x04, 0x10);		//--> L1 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x20);		//--> L2 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x40);		//--> L3 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x80);		//--> L4 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L1:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_OFF(0x04, 0x20);		//--> L2 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x40);		//--> L3 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x80);		//--> L4 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L2:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_OFF(0x04, 0x40);		//--> L3 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x80);		//--> L4 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L3:
	{
	NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
	NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
	NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
	NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
	NX7_LCD_SEG_OFF(0x04, 0x80);		//--> L4 : OFF
	NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
	NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
	NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
	NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
	break;
	}
	case Blower_L4:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_OFF(0x04, 0x08);		//--> L5 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L5:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_ON(0x04, 0x08);			//--> L5 : ON
		NX7_LCD_SEG_OFF(0x04, 0x04);		//--> L6 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L6:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_ON(0x04, 0x08);			//--> L5 : ON
		NX7_LCD_SEG_ON(0x04, 0x04);			//--> L6 : ON
		NX7_LCD_SEG_OFF(0x04, 0x02);		//--> L7 : OFF
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L7:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_ON(0x04, 0x08);			//--> L5 : ON
		NX7_LCD_SEG_ON(0x04, 0x04);			//--> L6 : ON
		NX7_LCD_SEG_ON(0x04, 0x02);			//--> L7 : ON
		NX7_LCD_SEG_OFF(0x04, 0x01);		//--> L8 : OFF
		break;
	}
	case Blower_L8:
	{
		NX7_LCD_SEG_ON(0x05, 0x02);			//--> BL : ON
		NX7_LCD_SEG_ON(0x04, 0x10);			//--> L1 : ON
		NX7_LCD_SEG_ON(0x04, 0x20);			//--> L2 : ON
		NX7_LCD_SEG_ON(0x04, 0x40);			//--> L3 : ON
		NX7_LCD_SEG_ON(0x04, 0x80);			//--> L4 : ON
		NX7_LCD_SEG_ON(0x04, 0x08);			//--> L5 : ON
		NX7_LCD_SEG_ON(0x04, 0x04);			//--> L6 : ON
		NX7_LCD_SEG_ON(0x04, 0x02);			//--> L7 : ON
		NX7_LCD_SEG_ON(0x04, 0x01);			//--> L8 : ON
		break;
	}
	}
}

/* NX7_LCD_Set_Point_Segment -------------------------------------------------*/
void NX7_LCD_Set_Point_Segment(char ch, int counter)
{
	switch (counter)
	{
		case 0:
		{
			switch (ch)
			{
				case '0':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '1':
				{
					NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '2':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_OFF(0x02, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '3':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '4':
				{
					NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '5':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x02, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '6':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x02, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '7':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '8':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case '9':
				{
					NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
				case 'L':
				{
					NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_OFF(0x02, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_OFF(0x02, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
					break;
				}
				case 'H':
				{
					NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
					break;
				}
			}
			break;			
		}
		case 1:
		{
			switch (ch)
			{
				case '0':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
					break;
				}
				case '1':
				{
					NX7_LCD_SEG_OFF(0x01, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
					break;
				}
				case '2':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_OFF(0x01, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '3':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '4':
				{
					NX7_LCD_SEG_OFF(0x01, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '5':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x01, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '6':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x01, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '7':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
					break;
				}
				case '8':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case '9':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x02, 0x02);			//--> Seg.G : ON
					break;
				}
				case 'O':
				{
					NX7_LCD_SEG_ON(0x01, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x01, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x01, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x01, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
					break;
				}
				case 'I':
				{
					NX7_LCD_SEG_OFF(0x01, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_OFF(0x01, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_OFF(0x01, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_ON(0x02, 0x01);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x02, 0x04);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
					break;
				}
			}
			break;
		}
		case 2:
		{
			switch (ch)
			{
				case '.':
				{
					NX7_LCD_SEG_ON(0x00, 0x02);			//--> °C       : ON
					NX7_LCD_SEG_OFF(0x00, 0x01);		//--> °F       : OFF
					NX7_LCD_SEG_ON(0x01, 0x01);			//--> Point    : ON
					break;
				}
				case ' ':
				{
					NX7_LCD_SEG_OFF(0x00, 0x02);		//--> °C       : OFF
					NX7_LCD_SEG_OFF(0x00, 0x01);		//--> °F       : OFF
					NX7_LCD_SEG_OFF(0x01, 0x01);		//--> Point    : OFF
					break;
				}
			}
			break;
		}
		case 3:
		{
			switch (ch)
			{
				case '0':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x01, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '1':
				{
					NX7_LCD_SEG_OFF(0x00, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '2':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_OFF(0x00, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x01, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '3':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '4':
				{
					NX7_LCD_SEG_OFF(0x00, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '5':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x00, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '6':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x00, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x01, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '7':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
					break;
				}
				case '8':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x01, 0x02);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case '9':
				{
					NX7_LCD_SEG_ON(0x00, 0x80);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x00, 0x40);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x00, 0x20);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x00, 0x10);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x01, 0x08);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x01, 0x04);			//--> Seg.G : ON
					break;
				}
				case ' ':
				{
					NX7_LCD_SEG_OFF(0x00, 0x80);		//--> Seg.A : OFF
					NX7_LCD_SEG_OFF(0x00, 0x40);		//--> Seg.B : OFF
					NX7_LCD_SEG_OFF(0x00, 0x20);		//--> Seg.C : OFF
					NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
					break;
				}
			}
			break;
		}
	}
}

/* NX7_LCD_Set_Point_Handler -------------------------------------------------*/
void NX7_LCD_Set_Point_Handler(float set_point)
{
	if(set_point == -1000)
	{
		char str[8]={0}; int counter=0;
		sprintf(str, "LO  ");
		do
		{
			NX7_LCD_Set_Point_Segment(str[counter], counter);
			counter++;
		}	while(str[counter]!=0);
	}
	else if(set_point == +1000)
	{
		char str[8]={0}; int counter=0;
		sprintf(str, "HI  ");
		do
		{
			NX7_LCD_Set_Point_Segment(str[counter], counter);
			counter++;
		}	while(str[counter]!=0);
	}
	else
	{
		char str[8]={0}; int counter=0;
		sprintf(str, "%04.1f", set_point);
		do
		{
			NX7_LCD_Set_Point_Segment(str[counter], counter);
			counter++;
		}	while(str[counter]!=0);
	}
}

/* NX7_LCD_Out_Temp_Segment --------------------------------------------------*/
void NX7_LCD_Out_Temp_Segment(char ch, int counter)
{
	switch (counter)
	{
		case 0:
		{
			switch (ch)
			{
				case '+':
				{
					NX7_LCD_SEG_ON(0x07, 0x80);			//--> °C       : ON
					NX7_LCD_SEG_OFF(0x07, 0x40);		//--> °F       : OFF
					NX7_LCD_SEG_OFF(0x05, 0x04);		//--> Minus    : OFF
					break;
				}
				case '-':
				{
					NX7_LCD_SEG_ON(0x07, 0x80);			//--> °C       : ON
					NX7_LCD_SEG_OFF(0x07, 0x40);		//--> °F       : OFF
					NX7_LCD_SEG_ON(0x05, 0x04);			//--> Minus    : ON
					break;
				}
				case ' ':
				{
					NX7_LCD_SEG_ON(0x07, 0x80);			//--> °C       : ON
					NX7_LCD_SEG_OFF(0x07, 0x40);		//--> °F       : OFF
					NX7_LCD_SEG_OFF(0x05, 0x04);		//--> Minus    : OFF
					break;
				}
			}
			break;
		}
		case 1:
		{
			switch (ch)
			{
				case '0':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x05, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x05, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '1':
				{
					NX7_LCD_SEG_OFF(0x06, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x06, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x05, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x05, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '2':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_OFF(0x06, 0x02);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x05, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_OFF(0x05, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '3':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x05, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '4':
				{
					NX7_LCD_SEG_OFF(0x06, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x06, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '5':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x06, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '6':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x06, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x05, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '7':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x06, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x05, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x05, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '8':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x05, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '9':
				{
					NX7_LCD_SEG_ON(0x06, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x06, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x06, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x06, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x05, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
				case '-':
				{
					NX7_LCD_SEG_OFF(0x06, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_OFF(0x06, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_OFF(0x06, 0x02);		//--> Seg.C : OFF
					NX7_LCD_SEG_OFF(0x06, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x05, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x05, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x05, 0x40);			//--> Seg.G : ON
					break;
				}
			}
			break;
		}
		case 2:
		{
			switch (ch)
			{
				case '0':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x06, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_OFF(0x06, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '1':
				{
					NX7_LCD_SEG_OFF(0x07, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x07, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x06, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x06, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '2':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_OFF(0x07, 0x02);		//--> Seg.C : OFF
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x06, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_OFF(0x06, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '3':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x06, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '4':
				{
					NX7_LCD_SEG_OFF(0x07, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x07, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '5':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x07, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '6':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_OFF(0x07, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x06, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '7':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_OFF(0x07, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x06, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_OFF(0x06, 0x40);		//--> Seg.G : OFF
					break;
				}
				case '8':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_ON(0x06, 0x20);			//--> Seg.E : ON
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '9':
				{
					NX7_LCD_SEG_ON(0x07, 0x08);			//--> Seg.A : ON
					NX7_LCD_SEG_ON(0x07, 0x04);			//--> Seg.B : ON
					NX7_LCD_SEG_ON(0x07, 0x02);			//--> Seg.C : ON
					NX7_LCD_SEG_ON(0x07, 0x01);			//--> Seg.D : ON
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_ON(0x06, 0x80);			//--> Seg.F : ON
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
				case '-':
				{
					NX7_LCD_SEG_OFF(0x07, 0x08);		//--> Seg.A : OFF
					NX7_LCD_SEG_OFF(0x07, 0x04);		//--> Seg.B : OFF
					NX7_LCD_SEG_OFF(0x07, 0x02);		//--> Seg.C : OFF
					NX7_LCD_SEG_OFF(0x07, 0x01);		//--> Seg.D : OFF
					NX7_LCD_SEG_OFF(0x06, 0x20);		//--> Seg.E : OFF
					NX7_LCD_SEG_OFF(0x06, 0x80);		//--> Seg.F : OFF
					NX7_LCD_SEG_ON(0x06, 0x40);			//--> Seg.G : ON
					break;
				}
			}
			break;
		}
	}
}

/* NX7_LCD_Out_Temp_Handler --------------------------------------------------*/
void NX7_LCD_Out_Temp_Handler(int out_temp)
{
	switch (Ambient_Sensor_State)
	{
	case Sensor_OK:
	{
		if(out_temp >= 0)
		{
			char str1[8]={'+'}, str2[8]={0}; int counter=0;
			sprintf(str2, "%02i", out_temp);
			strcat(str1, str2);
			do
			{
				NX7_LCD_Out_Temp_Segment(str1[counter], counter);
				counter++;
			} while(str1[counter]!=0);
		}
		else
		{
			char str[8]={0}; int counter=0;
			sprintf(str, "%03i", out_temp);
			do
			{
				NX7_LCD_Out_Temp_Segment(str[counter], counter);
				counter++;
			} while(str[counter]!=0);
		}
		break;
	}
	case Sensor_Error:
	{
		char str[8]={0}; int counter=0;
		sprintf(str, " --");
		do
		{
			NX7_LCD_Out_Temp_Segment(str[counter], counter);
			counter++;
		} while(str[counter]!=0);
		break;
	}
	}
}

/* NX7_LCD_Sensor_Index_Handler ----------------------------------------------*/
void NX7_LCD_Sensor_Index_Handler(int index)
{
	switch (index)
	{
	case 1:
	{
		NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x03, 0x04);		//--> Seg.G : OFF
		break;
	}
	case 2:
	{
		NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_OFF(0x02, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_ON(0x03, 0x02);			//--> Seg.E : ON
		NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
		break;
	}
	case 3:
	{
		NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x03, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
		break;
	}
	case 4:
	{
		NX7_LCD_SEG_OFF(0x02, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_ON(0x02, 0x40);			//--> Seg.B : ON
		NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_OFF(0x02, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
		NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
		break;
	}
	case 5:
	{
		NX7_LCD_SEG_ON(0x02, 0x80);			//--> Seg.A : ON
		NX7_LCD_SEG_OFF(0x02, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_ON(0x02, 0x20);			//--> Seg.C : ON
		NX7_LCD_SEG_ON(0x02, 0x10);			//--> Seg.D : ON
		NX7_LCD_SEG_OFF(0x03, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_ON(0x03, 0x08);			//--> Seg.F : ON
		NX7_LCD_SEG_ON(0x03, 0x04);			//--> Seg.G : ON
		break;
	}
	}
		NX7_LCD_SEG_OFF(0x01, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_OFF(0x01, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_OFF(0x01, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_OFF(0x01, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x02, 0x01);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x02, 0x04);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x02, 0x02);		//--> Seg.G : OFF
		NX7_LCD_SEG_OFF(0x00, 0x02);		//--> °C    : OFF
		NX7_LCD_SEG_OFF(0x00, 0x01);		//--> °F    : OFF
		NX7_LCD_SEG_OFF(0x01, 0x01);		//--> Point : OFF
		NX7_LCD_SEG_OFF(0x00, 0x80);		//--> Seg.A : OFF
		NX7_LCD_SEG_OFF(0x00, 0x40);		//--> Seg.B : OFF
		NX7_LCD_SEG_OFF(0x00, 0x20);		//--> Seg.C : OFF
		NX7_LCD_SEG_OFF(0x00, 0x10);		//--> Seg.D : OFF
		NX7_LCD_SEG_OFF(0x01, 0x02);		//--> Seg.E : OFF
		NX7_LCD_SEG_OFF(0x01, 0x08);		//--> Seg.F : OFF
		NX7_LCD_SEG_OFF(0x01, 0x04);		//--> Seg.G : OFF
}

