/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Blower_VOLT_Pin GPIO_PIN_0
#define Blower_VOLT_GPIO_Port GPIOC
#define Cabin_Sensor_Pin GPIO_PIN_1
#define Cabin_Sensor_GPIO_Port GPIOC
#define Evap_Sensor_Pin GPIO_PIN_2
#define Evap_Sensor_GPIO_Port GPIOC
#define Ambient_Sensor_Pin GPIO_PIN_3
#define Ambient_Sensor_GPIO_Port GPIOC
#define Solar_Sensor_Pin GPIO_PIN_0
#define Solar_Sensor_GPIO_Port GPIOA
#define Airmix_FB_Pin GPIO_PIN_1
#define Airmix_FB_GPIO_Port GPIOA
#define Mode_FB_Pin GPIO_PIN_2
#define Mode_FB_GPIO_Port GPIOA
#define Water_Sensor_Pin GPIO_PIN_3
#define Water_Sensor_GPIO_Port GPIOA
#define IGN_VOLT_Pin GPIO_PIN_4
#define IGN_VOLT_GPIO_Port GPIOA
#define Blower_Control_Pin GPIO_PIN_5
#define Blower_Control_GPIO_Port GPIOA
#define Airmix_Up_SW_Pin GPIO_PIN_6
#define Airmix_Up_SW_GPIO_Port GPIOA
#define Airmix_Up_SW_EXTI_IRQn EXTI9_5_IRQn
#define Airmix_Down_SW_Pin GPIO_PIN_7
#define Airmix_Down_SW_GPIO_Port GPIOA
#define Airmix_Down_SW_EXTI_IRQn EXTI9_5_IRQn
#define Blower_OFF_Pin GPIO_PIN_4
#define Blower_OFF_GPIO_Port GPIOC
#define AC_SW_Pin GPIO_PIN_5
#define AC_SW_GPIO_Port GPIOC
#define AC_SW_EXTI_IRQn EXTI9_5_IRQn
#define R_DEF_SW_Pin GPIO_PIN_0
#define R_DEF_SW_GPIO_Port GPIOB
#define R_DEF_SW_EXTI_IRQn EXTI0_IRQn
#define Intake_SW_Pin GPIO_PIN_1
#define Intake_SW_GPIO_Port GPIOB
#define Intake_SW_EXTI_IRQn EXTI1_IRQn
#define LCD_SCL_Pin GPIO_PIN_10
#define LCD_SCL_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_11
#define LCD_SDA_GPIO_Port GPIOB
#define Illumination_Pin GPIO_PIN_12
#define Illumination_GPIO_Port GPIOB
#define Illumination_EXTI_IRQn EXTI15_10_IRQn
#define AUTO_SW_Pin GPIO_PIN_13
#define AUTO_SW_GPIO_Port GPIOB
#define AUTO_SW_EXTI_IRQn EXTI15_10_IRQn
#define DEF_SW_Pin GPIO_PIN_14
#define DEF_SW_GPIO_Port GPIOB
#define DEF_SW_EXTI_IRQn EXTI15_10_IRQn
#define Mode_SW_Pin GPIO_PIN_15
#define Mode_SW_GPIO_Port GPIOB
#define Mode_SW_EXTI_IRQn EXTI15_10_IRQn
#define DEF_LED_Pin GPIO_PIN_6
#define DEF_LED_GPIO_Port GPIOC
#define R_DEF_LED_Pin GPIO_PIN_7
#define R_DEF_LED_GPIO_Port GPIOC
#define POWER_SW_Pin GPIO_PIN_8
#define POWER_SW_GPIO_Port GPIOC
#define POWER_SW_EXTI_IRQn EXTI9_5_IRQn
#define Blower_Down_SW_Pin GPIO_PIN_9
#define Blower_Down_SW_GPIO_Port GPIOC
#define Blower_Down_SW_EXTI_IRQn EXTI9_5_IRQn
#define Blower_Up_SW_Pin GPIO_PIN_11
#define Blower_Up_SW_GPIO_Port GPIOA
#define Blower_Up_SW_EXTI_IRQn EXTI15_10_IRQn
#define TLE_CSN_Pin GPIO_PIN_15
#define TLE_CSN_GPIO_Port GPIOA
#define R_DEF_Relay_Pin GPIO_PIN_10
#define R_DEF_Relay_GPIO_Port GPIOC
#define AC_Relay_Pin GPIO_PIN_2
#define AC_Relay_GPIO_Port GPIOD
#define TLE_SCLK_Pin GPIO_PIN_3
#define TLE_SCLK_GPIO_Port GPIOB
#define TLE_SDO_Pin GPIO_PIN_4
#define TLE_SDO_GPIO_Port GPIOB
#define TLE_SDI_Pin GPIO_PIN_5
#define TLE_SDI_GPIO_Port GPIOB
#define TLE_EN_Pin GPIO_PIN_6
#define TLE_EN_GPIO_Port GPIOB
#define Blower_Relay_Pin GPIO_PIN_7
#define Blower_Relay_GPIO_Port GPIOB
#define LCD_Backlight_Pin GPIO_PIN_9
#define LCD_Backlight_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
