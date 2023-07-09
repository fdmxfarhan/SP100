/* Includes *******************************************************************/
#include "SP100_lcd.h"
#include "SP100_ext_isr.h"
#include "SP100_Intake.h"
#include <stdio.h>
#include <string.h>

/* Private typedef ************************************************************/

/* Private define *************************************************************/
//--> LCD RAM Mapping [Reg,Seg]
const   uint8_t   AUTO[]            = {0x07,0x10};
const   uint8_t   DEF[]             = {0x04,0x20};
const   uint8_t   R_DEF[]           = {0x04,0x80};
const   uint8_t   AC[]              = {0x05,0x10};

const   uint8_t   PAX[]             = {0x04,0x40};
const   uint8_t   Face[]            = {0x05,0x04};
const   uint8_t   Foot[]            = {0x05,0x01};
const   uint8_t   Def[]             = {0x05,0x02};

const   uint8_t   Fan[]             = {0x02,0x08};
const   uint8_t   Fan_BLI1[]        = {0x02,0x10};
const   uint8_t   Fan_BLI2[]        = {0x02,0x40};
const   uint8_t   Fan_BLI3[]        = {0x02,0x20};
const   uint8_t   Fan_BLI4[]        = {0x02,0x80};
const   uint8_t   Fan_BLI5[]        = {0x04,0x08};//{0x04,0x02};
const   uint8_t   Fan_BLI6[]        = {0x04,0x02};//{0x04,0x08};
const   uint8_t   Fan_BLI7[]        = {0x04,0x04};
const   uint8_t   Fan_BLI8[]        = {0x04,0x01};
const   uint8_t   Fan_BLO1[]        = {0x03,0x01};
const   uint8_t   Fan_BLO2[]        = {0x03,0x04};
const   uint8_t   Fan_BLO3[]        = {0x03,0x02};
const   uint8_t   Fan_BLO4[]        = {0x03,0x08};
const   uint8_t   Fan_BLO5[]        = {0x03,0x80};
const   uint8_t   Fan_BLO6[]        = {0x03,0x20};
const   uint8_t   Fan_BLO7[]        = {0x03,0x40};
const   uint8_t   Fan_BLO8[]        = {0x03,0x10};

const   uint8_t   SP_Degree[]       = {0x05,0x08};
const   uint8_t   SP_Point[]        = {0x06,0x10};
const   uint8_t   SP_Frst_Seg_A[]   = {0x08,0x08};
const   uint8_t   SP_Frst_Seg_B[]   = {0x07,0x80};
const   uint8_t   SP_Frst_Seg_C[]   = {0x07,0x40};
const   uint8_t   SP_Frst_Seg_D[]   = {0x08,0x01};
const   uint8_t   SP_Frst_Seg_E[]   = {0x08,0x04};
const   uint8_t   SP_Frst_Seg_F[]   = {0x08,0x02};
const   uint8_t   SP_Frst_Seg_G[]   = {0x07,0x20};
const   uint8_t   SP_Scnd_Seg_A[]   = {0x07,0x08};
const   uint8_t   SP_Scnd_Seg_B[]   = {0x06,0x80};
const   uint8_t   SP_Scnd_Seg_C[]   = {0x06,0x40};
const   uint8_t   SP_Scnd_Seg_D[]   = {0x07,0x01};
const   uint8_t   SP_Scnd_Seg_E[]   = {0x07,0x04};
const   uint8_t   SP_Scnd_Seg_F[]   = {0x07,0x02};
const   uint8_t   SP_Scnd_Seg_G[]   = {0x06,0x20};
const   uint8_t   SP_Thrd_Seg_A[]   = {0x06,0x08};
const   uint8_t   SP_Thrd_Seg_B[]   = {0x05,0x80};
const   uint8_t   SP_Thrd_Seg_C[]   = {0x05,0x40};
const   uint8_t   SP_Thrd_Seg_D[]   = {0x06,0x01};
const   uint8_t   SP_Thrd_Seg_E[]   = {0x06,0x04};
const   uint8_t   SP_Thrd_Seg_F[]   = {0x06,0x02};
const   uint8_t   SP_Thrd_Seg_G[]   = {0x05,0x20};

const   uint8_t   Out_Temp[]        = {0x04,0x10};
const   uint8_t   OT_Degree[]       = {0x01,0x08};
const   uint8_t   OT_Minus[]        = {0x00,0x01};
const   uint8_t   OT_Frst_Seg_A[]   = {0x00,0x80};
const   uint8_t   OT_Frst_Seg_B[]   = {0x01,0x02};
const   uint8_t   OT_Frst_Seg_C[]   = {0x01,0x01};
const   uint8_t   OT_Frst_Seg_D[]   = {0x00,0x10};
const   uint8_t   OT_Frst_Seg_E[]   = {0x00,0x40};
const   uint8_t   OT_Frst_Seg_F[]   = {0x00,0x20};
const   uint8_t   OT_Frst_Seg_G[]   = {0x01,0x04};
const   uint8_t   OT_Scnd_Seg_A[]   = {0x01,0x80};
const   uint8_t   OT_Scnd_Seg_B[]   = {0x02,0x02};
const   uint8_t   OT_Scnd_Seg_C[]   = {0x02,0x01};
const   uint8_t   OT_Scnd_Seg_D[]   = {0x01,0x10};
const   uint8_t   OT_Scnd_Seg_E[]   = {0x01,0x40};
const   uint8_t   OT_Scnd_Seg_F[]   = {0x01,0x20};
const   uint8_t   OT_Scnd_Seg_G[]   = {0x02,0x04};

/* Private macro **************************************************************/

/* Private variables **********************************************************/
extern	I2C_HandleTypeDef  hi2c2;
extern  TIM_HandleTypeDef  htim3;
uint8_t All_Segments[100][2] = {
{0x07,0x10},//AUTO
{0x04,0x80},//DEF
{0x04,0x20},//R_DEF
{0x05,0x10},//AC
{0x04,0x40},//SANDALI
{0x05,0x04},//FACE
{0x05,0x01},//FOOT
{0x05,0x02},//WINDOW
{0x02,0x08},//FAN
{0x02,0x10},//FAN1
{0x02,0x40},//FAN2
{0x02,0x20},//FAN3
{0x02,0x80},//FAN4
{0x04,0x08},//FAN5
{0x04,0x02},//FAN6
{0x04,0x04},//FAN7
{0x04,0x01},//FAN8
{0x03,0x01},//FAN1_R
{0x03,0x04},//FAN2_R
{0x03,0x02},//FAN3_R
{0x03,0x08},//FAN4_R
{0x03,0x80},//FAN5_R
{0x03,0x20},//FAN6_R
{0x03,0x40},//FAN7_R
{0x03,0x10},//FAN8_R
{0x05,0x08},//DEGREE
{0x06,0x10},//DOT
{0x08,0x08},//SP_FRST_A
{0x07,0x80},//SP_FRST_B
{0x07,0x40},//SP_FRST_C
{0x08,0x01},//SP_FRST_D
{0x08,0x04},//SP_FRST_E
{0x08,0x02},//SP_FRST_F
{0x07,0x20},//SP_FRST_G
{0x07,0x08},//SP_SCND_A
{0x06,0x80},//SP_SCND_B
{0x06,0x40},//SP_SCND_C
{0x07,0x01},//SP_SCND_D
{0x07,0x04},//SP_SCND_E
{0x07,0x02},//SP_SCND_F
{0x06,0x20},//SP_SCND_G
{0x06,0x08},//SP_THRD_A
{0x05,0x80},//SP_THRD_B
{0x05,0x40},//SP_THRD_C
{0x06,0x01},//SP_THRD_D
{0x06,0x04},//SP_THRD_E
{0x06,0x02},//SP_THRD_F
{0x05,0x20},//SP_THRD_G
{0x04,0x10},//OUT_TEMP
{0x01,0x08},//DEGREE_OUT
{0x00,0x01},//MINUS_OUT
{0x00,0x80},//OT_FRST_A
{0x01,0x02},//OT_FRST_B
{0x01,0x01},//OT_FRST_C
{0x00,0x10},//OT_FRST_D
{0x00,0x40},//OT_FRST_E
{0x00,0x20},//OT_FRST_F
{0x01,0x04},//OT_FRST_G
{0x01,0x80},//OT_SCND_A
{0x02,0x02},//OT_SCND_B
{0x02,0x01},//OT_SCND_C
{0x01,0x10},//OT_SCND_D
{0x01,0x40},//OT_SCND_E
{0x01,0x04},//OT_SCND_F
{0x02,0x08} //OT_SCND_G
};
SEG_State Number_Segment[10][7] = {
//{A, B, C, D, E, F, G},
	{SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_OFF}, // 0
	{SEG_OFF, SEG_ON, SEG_ON, SEG_OFF, SEG_OFF, SEG_OFF, SEG_OFF},	// 1
	{SEG_ON, SEG_ON, SEG_OFF, SEG_ON, SEG_ON, SEG_OFF, SEG_ON}, // 2
	{SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_OFF, SEG_OFF, SEG_ON}, // 3
	{SEG_OFF, SEG_ON, SEG_ON, SEG_OFF, SEG_OFF, SEG_ON, SEG_ON}, // 4
	{SEG_ON, SEG_OFF, SEG_ON, SEG_ON, SEG_OFF, SEG_ON, SEG_ON}, // 5
	{SEG_ON, SEG_OFF, SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON}, // 6
	{SEG_ON, SEG_ON, SEG_ON, SEG_OFF, SEG_OFF, SEG_OFF, SEG_OFF}, // 7
	{SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_ON}, // 8
	{SEG_ON, SEG_ON, SEG_ON, SEG_ON, SEG_OFF, SEG_ON, SEG_ON}, // 9
};
int seg_cnt = 0;

/* SP100_LCD_Init ------------------------------------------------------------*/
void SP100_LCD_Init(void)
{
	SP100_LCD_Command(Mode_Setting|0x0C);
	SP100_LCD_Command(Internal_Voltage_Adjust_Control|0x30);
	SP100_LCD_Command(Blinking_Frequency|0x00);
	SP100_LCD_ALL_SEG(SEG_OFF);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	if(Illumination_State == GPIO_PIN_SET)
	{
		SP100_LCD_Backlight(SP100_LCD_NightLight_PWM);
	}
	else
	{
		SP100_LCD_Backlight(SP100_LCD_DayLight_PWM);
	}
}

/* SP100_LCD_DeInit ----------------------------------------------------------*/
void SP100_LCD_DeInit(void)
{
	SP100_LCD_Command(Mode_Setting|0x00);
	SP100_LCD_Command(Internal_Voltage_Adjust_Control|0x00);
	SP100_LCD_Command(Blinking_Frequency|0x00);
	SP100_LCD_ALL_SEG(SEG_OFF);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

/* SP100_LCD_Command ---------------------------------------------------------*/
void SP100_LCD_Command(uint8_t command)
{
	uint8_t		pCommand[1] = {command};
	HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, pCommand, 1, 10);
}

/* SP100_LCD_SEG_Read --------------------------------------------------------*/
uint8_t SP100_LCD_SEG_Read(uint8_t address)
{
	uint8_t		pAddress[1] = {address};
	uint8_t		rxData[1];
	HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, pAddress, 1, 10);
	HAL_I2C_Master_Receive(&hi2c2, HT16C22A_Device_Address, rxData, 1, 10);
	return rxData[0];
}

/* SP100_LCD_SEG_OFF ---------------------------------------------------------*/
void SP100_LCD_SEG_OFF(const uint8_t *ptr)
{
	uint8_t   address=*(ptr), data=*(ptr+1);
	data   =  ~data;
	data  &=  SP100_LCD_SEG_Read(address);
	uint8_t   txData[2] = {address,data};
	HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, txData, 2, 10);
}

/* SP100_LCD_SEG_ON ----------------------------------------------------------*/
void SP100_LCD_SEG_ON(const uint8_t *ptr)
{
	uint8_t    address=*(ptr), data=*(ptr+1);
	data   |=  SP100_LCD_SEG_Read(address);
	uint8_t    txData[2] = {address,data};
	HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, txData, 2, 10);
}

/* SP100_LCD_Backlight -------------------------------------------------------*/
void SP100_LCD_Backlight(uint16_t pwm)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwm);
}

/* SP100_LCD_ALL_SEG ---------------------------------------------------------*/
void SP100_LCD_ALL_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		for(register int i=0x00; i<=0x08; i++)
		{
			uint8_t		txData[2] = {i,0x00};
			HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, txData, 2, 10);
		}
		break;
	}
	case SEG_ON:
	{
		for(register int i=0x00; i<=0x08; i++)
		{
			uint8_t		txData[2] = {i,0xFF};
			HAL_I2C_Master_Transmit(&hi2c2, HT16C22A_Device_Address|0x01, txData, 2, 10);
		}
		break;
	}
	}
}

/* SP100_LCD_AUTO_SEG --------------------------------------------------------*/
void SP100_LCD_AUTO_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(AUTO);	//--> AUTO : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(AUTO);		//--> AUTO : ON
		break;
	}
	}
}

/* SP100_LCD_DEF_SEG ---------------------------------------------------------*/
void SP100_LCD_DEF_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(DEF);		//--> DEF : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(DEF);		//--> DEF : ON
		break;
	}
	}
}

/* SP100_LCD_Mode_SEG --------------------------------------------------------*/
void SP100_LCD_Mode_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(PAX);		//--> PAX  : OFF
		SP100_LCD_SEG_OFF(Face);	//--> Face : OFF
		SP100_LCD_SEG_OFF(Foot);	//--> Foot : OFF
		SP100_LCD_SEG_OFF(Def);		//--> Def  : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_ON(Face);		//--> Face : ON
		SP100_LCD_SEG_ON(Foot);		//--> Foot : ON
		SP100_LCD_SEG_ON(Def);		//--> Def  : ON
		break;
	}
	}
}

/* SP100_LCD_Blower_SEG ------------------------------------------------------*/
void SP100_LCD_Blower_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(Fan);			//--> Fan  : OFF
		SP100_LCD_SEG_OFF(Fan_BLI1);	//--> BLI1 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI2);	//--> BLI2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI3);	//--> BLI3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI4);	//--> BLI4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO1);	//--> BLO1 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO2);	//--> BLO2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO3);	//--> BLO3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO4);	//--> BLO4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_ON(Fan_BLI5);		//--> BLI5 : ON
		SP100_LCD_SEG_ON(Fan_BLI6);		//--> BLI6 : ON
		SP100_LCD_SEG_ON(Fan_BLI7);		//--> BLI7 : ON
		SP100_LCD_SEG_ON(Fan_BLI8);		//--> BLI8 : ON
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_ON(Fan_BLO5);		//--> BLO5 : ON
		SP100_LCD_SEG_ON(Fan_BLO6);		//--> BLO6 : ON
		SP100_LCD_SEG_ON(Fan_BLO7);		//--> BLO7 : ON
		SP100_LCD_SEG_ON(Fan_BLO8);		//--> BLO8 : ON
		break;
	}
	}
}

/* SP100_LCD_Out_Temp_SEG ----------------------------------------------------*/
void SP100_LCD_Out_Temp_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(Out_Temp);	//--> OUT TEMP : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(Out_Temp);		//--> OUT TEMP : ON
		break;
	}
	}
}

/* SP100_LCD_Set_Point_SEG ---------------------------------------------------*/
void SP100_LCD_Set_Point_SEG(SEG_State state)
{
	switch (state)
	{
	case SEG_OFF:
	{
		SP100_LCD_SEG_OFF(SP_Degree);			//--> SP_°C         : OFF
		SP100_LCD_SEG_OFF(SP_Point);			//--> SP_Point      : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_A);		//--> SP_Frst_Seg.A : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_B);		//--> SP_Frst_Seg.B : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_C);		//--> SP_Frst_Seg.C : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_D);		//--> SP_Frst_Seg.D : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_E);		//--> SP_Frst_Seg.E : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_F);		//--> SP_Frst_Seg.F : OFF
		SP100_LCD_SEG_OFF(SP_Frst_Seg_G);		//--> SP_Frst_Seg.G : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_A);		//--> SP_Scnd_Seg.A : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_B);		//--> SP_Scnd_Seg.B : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_C);		//--> SP_Scnd_Seg.C : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_D);		//--> SP_Scnd_Seg.D : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_E);		//--> SP_Scnd_Seg.E : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_F);		//--> SP_Scnd_Seg.F : OFF
		SP100_LCD_SEG_OFF(SP_Scnd_Seg_G);		//--> SP_Scnd_Seg.G : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_A);		//--> SP_Thrd_Seg.A : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_B);		//--> SP_Thrd_Seg.B : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_C);		//--> SP_Thrd_Seg.C : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_D);		//--> SP_Thrd_Seg.D : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_E);		//--> SP_Thrd_Seg.E : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_F);		//--> SP_Thrd_Seg.F : OFF
		SP100_LCD_SEG_OFF(SP_Thrd_Seg_G);		//--> SP_Thrd_Seg.G : OFF
		break;
	}
	case SEG_ON:
	{
		SP100_LCD_SEG_ON(SP_Degree);			//--> SP_°C         : ON
		SP100_LCD_SEG_ON(SP_Point);				//--> SP_Point      : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_A);		//--> SP_Frst_Seg.A : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_B);		//--> SP_Frst_Seg.B : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_C);		//--> SP_Frst_Seg.C : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_D);		//--> SP_Frst_Seg.D : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_E);		//--> SP_Frst_Seg.E : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_F);		//--> SP_Frst_Seg.F : ON
		SP100_LCD_SEG_ON(SP_Frst_Seg_G);		//--> SP_Frst_Seg.G : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_A);		//--> SP_Scnd_Seg.A : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_B);		//--> SP_Scnd_Seg.B : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_C);		//--> SP_Scnd_Seg.C : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_D);		//--> SP_Scnd_Seg.D : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_E);		//--> SP_Scnd_Seg.E : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_F);		//--> SP_Scnd_Seg.F : ON
		SP100_LCD_SEG_ON(SP_Scnd_Seg_G);		//--> SP_Scnd_Seg.G : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_A);		//--> SP_Thrd_Seg.A : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_B);		//--> SP_Thrd_Seg.B : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_C);		//--> SP_Thrd_Seg.C : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_D);		//--> SP_Thrd_Seg.D : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_E);		//--> SP_Thrd_Seg.E : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_F);		//--> SP_Thrd_Seg.F : ON
		SP100_LCD_SEG_ON(SP_Thrd_Seg_G);		//--> SP_Thrd_Seg.G : ON
		break;
	}
	}
}

/* SP100_LCD_State_Init_SEG --------------------------------------------------*/
void SP100_LCD_State_Init_SEG(CCU_State state)
{

	switch (state)
	{
	case CCU_OFF:
	{
		SP100_LCD_AUTO_SEG(SEG_OFF);
		SP100_LCD_DEF_SEG(SEG_OFF);
		//SP100_LCD_Mode_SEG();
		SP100_LCD_Blower_SEG(SEG_OFF);
		SP100_LCD_Out_Temp_SEG(SEG_ON);
		SP100_LCD_Set_Point_SEG(SEG_OFF);
		break;
	}
	case CCU_AUTO:
	{
		//SP100_LCD_AUTO_SEG();
		SP100_LCD_DEF_SEG(SEG_OFF);
		//SP100_LCD_Mode_SEG();
		//SP100_LCD_Blower_SEG();
		SP100_LCD_Out_Temp_SEG(SEG_ON);
		//SP100_LCD_Set_Point_SEG();
		break;
	}
	case CCU_DEF:
	{
		//SP100_LCD_AUTO_SEG();
		SP100_LCD_DEF_SEG(SEG_ON);
		SP100_LCD_Mode_SEG(SEG_OFF);
		//SP100_LCD_Blower_SEG();
		SP100_LCD_Out_Temp_SEG(SEG_ON);
		//SP100_LCD_Set_Point_SEG();
		break;
	}
	case CCU_SENSOR:
	{
		//SP100_LCD_AUTO_SEG();
		SP100_LCD_DEF_SEG(SEG_OFF);
		SP100_LCD_Mode_SEG(SEG_OFF);
		SP100_LCD_Blower_SEG(SEG_OFF);
		SP100_LCD_Out_Temp_SEG(SEG_OFF);
		//SP100_LCD_Set_Point_SEG();
		break;
	}
	case CCU_DIAG:
	{
		SP100_LCD_ALL_SEG(SEG_OFF);
		break;
	}
	case CCU_IGN_OFF:
	{
		SP100_LCD_ALL_SEG(SEG_OFF);
		break;
	}
	}
}

/* SP100_LCD_AC_Handler ------------------------------------------------------*/
void SP100_LCD_AC_Handler(AC_State state)
{
	switch (state)
	{
	case AC_OFF:
	{
		SP100_LCD_SEG_OFF(AC);		//--> A/C : OFF
		SP100_Compressor_OFF();
		AC_LED_OFF;
		break;
	}
	case AC_ON:
	{
		SP100_Compressor_ON();
		SP100_LCD_SEG_ON(AC);		//--> A/C : ON
		AC_LED_ON;
		break;
	}
	}
}

/* SP100_LCD_R_DEF_Handler ---------------------------------------------------*/
void SP100_LCD_R_DEF_Handler(R_DEF_State state)
{
	switch (state)
	{
		case R_DEF_OFF:
		{
			SP100_LCD_SEG_OFF(R_DEF);		//--> R-DEF : OFF
			SP100_R_DEF_OFF();
			R_DEF_LED_OFF;
			break;
		}
		case R_DEF_ON:
		{
			SP100_LCD_SEG_ON(R_DEF);		//--> R-DEF : ON
			SP100_R_DEF_ON();
			R_DEF_LED_ON;
			break;
		}
	}
}

/* SP100_LCD_Mode_Handler ----------------------------------------------------*/
void SP100_LCD_Mode_Handler(Mode_State state)
{
	switch (state)
	{
	case Mode_Face:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_ON(Face);		//--> Face : ON
		SP100_LCD_SEG_OFF(Foot);	//--> Foot : OFF
		SP100_LCD_SEG_OFF(Def);		//--> Def  : OFF
		break;
	}
	case Mode_Face_Foot:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_ON(Face);		//--> Face : ON
		SP100_LCD_SEG_ON(Foot);		//--> Foot : ON
		SP100_LCD_SEG_OFF(Def);		//--> Def  : OFF
		break;
	}
	case Mode_Foot:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_OFF(Face);	//--> Face : OFF
		SP100_LCD_SEG_ON(Foot);		//--> Foot : ON
		SP100_LCD_SEG_OFF(Def);		//--> Def  : OFF
		break;
	}
	case Mode_Foot_Def:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_OFF(Face);	//--> Face : OFF
		SP100_LCD_SEG_ON(Foot);		//--> Foot : ON
		SP100_LCD_SEG_ON(Def);		//--> Def  : ON
		break;
	}
	case Mode_Def:
	{
		SP100_LCD_SEG_ON(PAX);		//--> PAX  : ON
		SP100_LCD_SEG_OFF(Face);	//--> Face : OFF
		SP100_LCD_SEG_OFF(Foot);	//--> Foot : OFF
		SP100_LCD_SEG_ON(Def);		//--> Def  : ON
		break;
	}
	}
}

/* SP100_LCD_Airmix_Handler --------------------------------------------------*/
void SP100_LCD_Airmix_Handler(Airmix_State state)
{

}

/* SP100_LCD_Blower_Handler --------------------------------------------------*/
void SP100_LCD_Blower_Handler(Blower_State state)
{
	switch (state)
	{
	case Blower_OFF:
	{
		SP100_LCD_SEG_OFF(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_OFF(Fan_BLI1);	//--> BLI1 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI2);	//--> BLI2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI3);	//--> BLI3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI4);	//--> BLI4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO1);	//--> BLO1 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO2);	//--> BLO2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO3);	//--> BLO3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO4);	//--> BLO4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L1:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_OFF(Fan_BLI2);	//--> BLI2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI3);	//--> BLI3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI4);	//--> BLI4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_OFF(Fan_BLO2);	//--> BLO2 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO3);	//--> BLO3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO4);	//--> BLO4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L2:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_OFF(Fan_BLI3);	//--> BLI3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI4);	//--> BLI4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_OFF(Fan_BLO3);	//--> BLO3 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO4);	//--> BLO4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L3:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_OFF(Fan_BLI4);	//--> BLI4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_OFF(Fan_BLO4);	//--> BLO4 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L4:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_OFF(Fan_BLI5);	//--> BLI5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_OFF(Fan_BLO5);	//--> BLO5 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L5:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_ON(Fan_BLI5);		//--> BLI5 : ON
		SP100_LCD_SEG_OFF(Fan_BLI6);	//--> BLI6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_ON(Fan_BLO5);		//--> BLO5 : ON
		SP100_LCD_SEG_OFF(Fan_BLO6);	//--> BLO6 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L6:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_ON(Fan_BLI5);		//--> BLI5 : ON
		SP100_LCD_SEG_ON(Fan_BLI6);		//--> BLI6 : ON
		SP100_LCD_SEG_OFF(Fan_BLI7);	//--> BLI7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_ON(Fan_BLO5);		//--> BLO5 : ON
		SP100_LCD_SEG_ON(Fan_BLO6);		//--> BLO6 : ON
		SP100_LCD_SEG_OFF(Fan_BLO7);	//--> BLO7 : OFF
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L7:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_ON(Fan_BLI5);		//--> BLI5 : ON
		SP100_LCD_SEG_ON(Fan_BLI6);		//--> BLI6 : ON
		SP100_LCD_SEG_ON(Fan_BLI7);		//--> BLI7 : ON
		SP100_LCD_SEG_OFF(Fan_BLI8);	//--> BLI8 : OFF
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_ON(Fan_BLO5);		//--> BLO5 : ON
		SP100_LCD_SEG_ON(Fan_BLO6);		//--> BLO6 : ON
		SP100_LCD_SEG_ON(Fan_BLO7);		//--> BLO7 : ON
		SP100_LCD_SEG_OFF(Fan_BLO8);	//--> BLO8 : OFF
		break;
	}
	case Blower_L8:
	{
		SP100_LCD_SEG_ON(Fan);			//--> Fan  : ON
		SP100_LCD_SEG_ON(Fan_BLI1);		//--> BLI1 : ON
		SP100_LCD_SEG_ON(Fan_BLI2);		//--> BLI2 : ON
		SP100_LCD_SEG_ON(Fan_BLI3);		//--> BLI3 : ON
		SP100_LCD_SEG_ON(Fan_BLI4);		//--> BLI4 : ON
		SP100_LCD_SEG_ON(Fan_BLI5);		//--> BLI5 : ON
		SP100_LCD_SEG_ON(Fan_BLI6);		//--> BLI6 : ON
		SP100_LCD_SEG_ON(Fan_BLI7);		//--> BLI7 : ON
		SP100_LCD_SEG_ON(Fan_BLI8);		//--> BLO8 : ON
		SP100_LCD_SEG_ON(Fan_BLO1);		//--> BLO1 : ON
		SP100_LCD_SEG_ON(Fan_BLO2);		//--> BLO2 : ON
		SP100_LCD_SEG_ON(Fan_BLO3);		//--> BLO3 : ON
		SP100_LCD_SEG_ON(Fan_BLO4);		//--> BLO4 : ON
		SP100_LCD_SEG_ON(Fan_BLO5);		//--> BLO5 : ON
		SP100_LCD_SEG_ON(Fan_BLO6);		//--> BLO6 : ON
		SP100_LCD_SEG_ON(Fan_BLO7);		//--> BLO7 : ON
		SP100_LCD_SEG_ON(Fan_BLO8);		//--> BLO8 : ON
		break;
	}
	}
}

/* SP100_LCD_Set_Point_Segment -----------------------------------------------*/
void SP100_LCD_Set_Point_Segment(char ch, int counter)
{
	//--> Error
}

/* SP100_LCD_Set_Point_Handler -----------------------------------------------*/
void SP100_LCD_Set_Point_Handler(float set_point)
{
	//--> Error
}

/* SP100_LCD_Out_Temp_Segment ------------------------------------------------*/
void SP100_LCD_Out_Temp_Segment(char ch, int counter)
{
	//--> Error
}

/* SP100_LCD_Out_Temp_Handler ------------------------------------------------*/
void SP100_LCD_Out_Temp_Handler(int out_temp)
{
	//--> Error
}
/* SP100_LCD_Print_Temp ------------------------------------------------*/
void SP100_LCD_Print_Temp(int num)
{
	SP100_LCD_SEG_ON(SP_Degree);
	SP100_LCD_SEG_ON(SP_Point);
	if(Number_Segment[num%10][0] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_A);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_A);
	if(Number_Segment[num%10][1] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_B);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_B);
	if(Number_Segment[num%10][2] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_C);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_C);
	if(Number_Segment[num%10][3] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_D);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_D);
	if(Number_Segment[num%10][4] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_E);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_E);
	if(Number_Segment[num%10][5] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_F);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_F);
	if(Number_Segment[num%10][6] == SEG_ON) SP100_LCD_SEG_ON( SP_Thrd_Seg_G);
	else																		SP100_LCD_SEG_OFF(SP_Thrd_Seg_G);
	
	if(Number_Segment[(num/10)%10][0] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_A);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_A);
	if(Number_Segment[(num/10)%10][1] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_B);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_B);
	if(Number_Segment[(num/10)%10][2] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_C);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_C);
	if(Number_Segment[(num/10)%10][3] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_D);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_D);
	if(Number_Segment[(num/10)%10][4] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_E);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_E);
	if(Number_Segment[(num/10)%10][5] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_F);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_F);
	if(Number_Segment[(num/10)%10][6] == SEG_ON) 	SP100_LCD_SEG_ON( SP_Scnd_Seg_G);
	else																					SP100_LCD_SEG_OFF(SP_Scnd_Seg_G);
	
	if(Number_Segment[(num/100)%10][0] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_A);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_A);
	if(Number_Segment[(num/100)%10][1] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_B);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_B);
	if(Number_Segment[(num/100)%10][2] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_C);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_C);
	if(Number_Segment[(num/100)%10][3] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_D);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_D);
	if(Number_Segment[(num/100)%10][4] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_E);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_E);
	if(Number_Segment[(num/100)%10][5] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_F);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_F);
	if(Number_Segment[(num/100)%10][6] == SEG_ON) SP100_LCD_SEG_ON( SP_Frst_Seg_G);
	else																					SP100_LCD_SEG_OFF(SP_Frst_Seg_G);
}
void SP100_LCD_Print_Out_Temp(int num)
{
	SP100_LCD_SEG_ON(OT_Degree);
	SP100_LCD_SEG_ON(Out_Temp);
	
	if(Number_Segment[(num/1)%10][0] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_A);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_A);
	if(Number_Segment[(num/1)%10][1] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_B);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_B);
	if(Number_Segment[(num/1)%10][2] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_C);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_C);
	if(Number_Segment[(num/1)%10][3] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_D);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_D);
	if(Number_Segment[(num/1)%10][4] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_E);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_E);
	if(Number_Segment[(num/1)%10][5] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_F);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_F);
	if(Number_Segment[(num/1)%10][6] == SEG_ON) 	SP100_LCD_SEG_ON( OT_Scnd_Seg_G);
	else																					SP100_LCD_SEG_OFF(OT_Scnd_Seg_G);
	
	if(Number_Segment[(num/10)%10][0] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_A);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_A);
	if(Number_Segment[(num/10)%10][1] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_B);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_B);
	if(Number_Segment[(num/10)%10][2] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_C);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_C);
	if(Number_Segment[(num/10)%10][3] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_D);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_D);
	if(Number_Segment[(num/10)%10][4] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_E);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_E);
	if(Number_Segment[(num/10)%10][5] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_F);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_F);
	if(Number_Segment[(num/10)%10][6] == SEG_ON)  SP100_LCD_SEG_ON( OT_Frst_Seg_G);
	else																					SP100_LCD_SEG_OFF(OT_Frst_Seg_G);
}
void SP100_LCD_SetPoint_Low(void)
{
	SP100_LCD_SEG_OFF(SP_Degree);
	SP100_LCD_SEG_OFF(SP_Point);

	SP100_LCD_SEG_OFF(SP_Frst_Seg_A);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_B);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_C);
	SP100_LCD_SEG_ON( SP_Frst_Seg_D);
	SP100_LCD_SEG_ON( SP_Frst_Seg_E);
	SP100_LCD_SEG_ON( SP_Frst_Seg_F);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_G);
	
	SP100_LCD_SEG_ON( SP_Scnd_Seg_A);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_B);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_C);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_D);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_E);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_G);
	
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_A);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_B);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_C);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_D);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_E);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_G);
	
}
void SP100_LCD_SetPoint_High(void)
{
	SP100_LCD_SEG_OFF(SP_Degree);
	SP100_LCD_SEG_OFF(SP_Point);
	
	SP100_LCD_SEG_OFF(SP_Frst_Seg_A);
	SP100_LCD_SEG_ON( SP_Frst_Seg_B);
	SP100_LCD_SEG_ON( SP_Frst_Seg_C);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_D);
	SP100_LCD_SEG_ON( SP_Frst_Seg_E);
	SP100_LCD_SEG_ON( SP_Frst_Seg_F);
	SP100_LCD_SEG_ON( SP_Frst_Seg_G);
	
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_A);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_B);
	SP100_LCD_SEG_ON( SP_Scnd_Seg_C);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_D);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_E);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_G);
	
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_A);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_B);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_C);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_D);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_E);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_G);
	
}
void SP100_LCD_Temp_Count_Test(void)
{
	SP100_LCD_Print_Temp(seg_cnt);
	seg_cnt++;
	seg_cnt%=1000;
	SP100_Delay(1000);
}
void SP100_LCD_OUT_Temp_Count_Test(void)
{
	SP100_LCD_Print_Out_Temp(seg_cnt);
	seg_cnt++;
	seg_cnt%=1000;
	SP100_Delay(100000);
}
void SP100_LCD_Test(int index)
{
	//if(index > 0) SP100_LCD_SEG_OFF(All_Segments[index-1]);
	SP100_LCD_SEG_ON(All_Segments[index]);
}
void SP100_LCD_Show_Set_Point(void)
{
	if(SP100_Set_Point < 14) SP100_LCD_SetPoint_Low();
	else if(SP100_Set_Point > 32)SP100_LCD_SetPoint_High();
	else SP100_LCD_Print_Temp(SP100_Set_Point * 10);
}
void SP100_LCD_Show_Out_Temp(void)
{
	if(SP100_Ambient_Sensor > 0){
		SP100_LCD_Print_Out_Temp(SP100_Ambient_Sensor);
		SP100_LCD_SEG_OFF(OT_Minus);
	}
	else{
		SP100_LCD_Print_Out_Temp(-SP100_Ambient_Sensor);
		SP100_LCD_SEG_ON(OT_Minus);
	}
}
void SP100_LCD_Show_Cabin_Sensor(void)
{
	
	SP100_LCD_Print_Out_Temp(SP100_Cabin_Sensor);
}
void SP100_LCD_Auto_Handler(void)
{
	if(SP100_CCU_State == CCU_AUTO) {
		SP100_LCD_SEG_ON(AUTO);
		AUTO_LED_ON;
	}
	else {
		SP100_LCD_SEG_OFF(AUTO);
		AUTO_LED_OFF;
	}
}
/* SP100_LCD_Update ------------------------------------------------*/
void SP100_LCD_Update(void)
{
	SP100_LCD_AC_Handler(SP100_AC_State);
	SP100_LCD_R_DEF_Handler(SP100_R_DEF_State);
	SP100_LCD_Show_Set_Point();
	//SP100_LCD_Show_Out_Temp();
	SP100_LCD_Print_Out_Temp(SP100_Cabin_Sensor);
	//SP100_LCD_Print_Out_Temp(SP100_Water_Sensor);
	SP100_LCD_Blower_Handler(SP100_Blower_State);
	SP100_LCD_Auto_Handler();
	if(SP100_CCU_State == CCU_DEF) {
		SP100_LCD_SEG_OFF(PAX);
		SP100_LCD_SEG_OFF(Face);
		SP100_LCD_SEG_OFF(Foot);		
		SP100_LCD_SEG_OFF(Def);
		SP100_LCD_SEG_ON(DEF);
		DEF_LED_ON;
	}
	else {
		SP100_LCD_Mode_Handler(SP100_Mode_State);
		SP100_LCD_SEG_OFF(DEF);
		DEF_LED_OFF;
	}
	// ---- Test Functions:
	//SP100_LCD_Print_Temp(SP100_Mode_FB * 100);
	//SP100_LCD_Temp_Count_Test();
	//SP100_LCD_OUT_Temp_Count_Test();
	//SP100_LCD_Show_Cabin_Sensor();
}

void SP100_LCD_OFF_State(void)
{
	SP100_LCD_SEG_OFF(AUTO);
	SP100_LCD_SEG_OFF(DEF);
	SP100_LCD_SEG_OFF(AC);
	SP100_LCD_SEG_OFF(Fan);
	SP100_LCD_SEG_OFF(Fan_BLI1);
	SP100_LCD_SEG_OFF(Fan_BLI2);
	SP100_LCD_SEG_OFF(Fan_BLI3);
	SP100_LCD_SEG_OFF(Fan_BLI4);
	SP100_LCD_SEG_OFF(Fan_BLI5);
	SP100_LCD_SEG_OFF(Fan_BLI6);
	SP100_LCD_SEG_OFF(Fan_BLI7);
	SP100_LCD_SEG_OFF(Fan_BLI8);
	SP100_LCD_SEG_OFF(Fan_BLO1);
	SP100_LCD_SEG_OFF(Fan_BLO2);
	SP100_LCD_SEG_OFF(Fan_BLO3);
	SP100_LCD_SEG_OFF(Fan_BLO4);
	SP100_LCD_SEG_OFF(Fan_BLO5);
	SP100_LCD_SEG_OFF(Fan_BLO6);
	SP100_LCD_SEG_OFF(Fan_BLO7);
	SP100_LCD_SEG_OFF(Fan_BLO8);
	SP100_LCD_SEG_OFF(SP_Degree);
	SP100_LCD_SEG_OFF(SP_Point);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_A);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_B);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_C);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_D);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_E);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_F);
	SP100_LCD_SEG_OFF(SP_Frst_Seg_G);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_A);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_B);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_C);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_D);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_E);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Scnd_Seg_G);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_A);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_B);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_C);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_D);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_E);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_F);
	SP100_LCD_SEG_OFF(SP_Thrd_Seg_G);
	
	SP100_LCD_Show_Out_Temp();
	if(SP100_R_DEF_SEG_State == Mode_SEG_ON)
		SP100_LCD_R_DEF_Handler(SP100_R_DEF_State);
	else 
		SP100_LCD_SEG_OFF(R_DEF);
	if(SP100_Mode_SEG_State == Mode_SEG_ON){
		SP100_LCD_Mode_Handler(SP100_Mode_State);
	}else{
		SP100_LCD_SEG_OFF(PAX);
		SP100_LCD_SEG_OFF(Face);
		SP100_LCD_SEG_OFF(Foot);
		SP100_LCD_SEG_OFF(Def);		
	}
}

