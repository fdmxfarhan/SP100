/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f0xx_hal.h"

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
#define Cabin_Sensor_Pin GPIO_PIN_0
#define Cabin_Sensor_GPIO_Port GPIOA
#define Water_Sensor_Pin GPIO_PIN_1
#define Water_Sensor_GPIO_Port GPIOA
#define Ambient_Sensor_Pin GPIO_PIN_2
#define Ambient_Sensor_GPIO_Port GPIOA
#define Evap_Sensor_Pin GPIO_PIN_3
#define Evap_Sensor_GPIO_Port GPIOA
#define Mode_FB_Pin GPIO_PIN_5
#define Mode_FB_GPIO_Port GPIOA
#define Airmix_FB_Pin GPIO_PIN_6
#define Airmix_FB_GPIO_Port GPIOA
#define Blower_VOLT_Pin GPIO_PIN_7
#define Blower_VOLT_GPIO_Port GPIOA
#define Illumination_Pin GPIO_PIN_4
#define Illumination_GPIO_Port GPIOC
#define Illumination_EXTI_IRQn EXTI4_15_IRQn
#define Ignition_Pin GPIO_PIN_5
#define Ignition_GPIO_Port GPIOC
#define Ignition_EXTI_IRQn EXTI4_15_IRQn
#define LCD_Backlight_Pin GPIO_PIN_0
#define LCD_Backlight_GPIO_Port GPIOB
#define Blower_Up_SW_Pin GPIO_PIN_1
#define Blower_Up_SW_GPIO_Port GPIOB
#define Blower_Up_SW_EXTI_IRQn EXTI0_1_IRQn
#define Blower_Down_SW_Pin GPIO_PIN_13
#define Blower_Down_SW_GPIO_Port GPIOB
#define Blower_Down_SW_EXTI_IRQn EXTI4_15_IRQn
#define OFF_SW_Pin GPIO_PIN_14
#define OFF_SW_GPIO_Port GPIOB
#define OFF_SW_EXTI_IRQn EXTI4_15_IRQn
#define Intake_SW_Pin GPIO_PIN_15
#define Intake_SW_GPIO_Port GPIOB
#define Intake_SW_EXTI_IRQn EXTI4_15_IRQn
#define DEF_SW_Pin GPIO_PIN_6
#define DEF_SW_GPIO_Port GPIOC
#define DEF_SW_EXTI_IRQn EXTI4_15_IRQn
#define Intake_LED_Pin GPIO_PIN_8
#define Intake_LED_GPIO_Port GPIOC
#define DEF_LED_Pin GPIO_PIN_9
#define DEF_LED_GPIO_Port GPIOC
#define AC_LED_Pin GPIO_PIN_8
#define AC_LED_GPIO_Port GPIOA
#define R_DEF_LED_Pin GPIO_PIN_9
#define R_DEF_LED_GPIO_Port GPIOA
#define AC_SW_Pin GPIO_PIN_10
#define AC_SW_GPIO_Port GPIOA
#define AC_SW_EXTI_IRQn EXTI4_15_IRQn
#define R_DEF_SW_Pin GPIO_PIN_11
#define R_DEF_SW_GPIO_Port GPIOA
#define R_DEF_SW_EXTI_IRQn EXTI4_15_IRQn
#define Mode_SW_Pin GPIO_PIN_12
#define Mode_SW_GPIO_Port GPIOA
#define Mode_SW_EXTI_IRQn EXTI4_15_IRQn
#define AUTO_LED_Pin GPIO_PIN_2
#define AUTO_LED_GPIO_Port GPIOD
#define Airmix_Up_SW_Pin GPIO_PIN_7
#define Airmix_Up_SW_GPIO_Port GPIOB
#define Airmix_Up_SW_EXTI_IRQn EXTI4_15_IRQn
#define Airmix_Down_SW_Pin GPIO_PIN_8
#define Airmix_Down_SW_GPIO_Port GPIOB
#define Airmix_Down_SW_EXTI_IRQn EXTI4_15_IRQn
#define AUTO_SW_Pin GPIO_PIN_9
#define AUTO_SW_GPIO_Port GPIOB
#define AUTO_SW_EXTI_IRQn EXTI4_15_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
