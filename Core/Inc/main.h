/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "entry.h"
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
#define ONB_LED_Pin GPIO_PIN_13
#define ONB_LED_GPIO_Port GPIOC
#define ONB_KEY_Pin GPIO_PIN_0
#define ONB_KEY_GPIO_Port GPIOA
#define SHARP_3_Pin GPIO_PIN_4
#define SHARP_3_GPIO_Port GPIOA
#define SHARP_4_Pin GPIO_PIN_5
#define SHARP_4_GPIO_Port GPIOA
#define DISPLAY_SCL_Pin GPIO_PIN_8
#define DISPLAY_SCL_GPIO_Port GPIOA
#define DISPLAY_SDA_Pin GPIO_PIN_4
#define DISPLAY_SDA_GPIO_Port GPIOB
#define PWM_CH1_Pin GPIO_PIN_6
#define PWM_CH1_GPIO_Port GPIOB
#define PWM_CH2_Pin GPIO_PIN_7
#define PWM_CH2_GPIO_Port GPIOB
#define PWM_CH3_Pin GPIO_PIN_8
#define PWM_CH3_GPIO_Port GPIOB
#define PWM_CH4_Pin GPIO_PIN_9
#define PWM_CH4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define TIM1_START HAL_TIM_Base_Start(&htim1)
#define TIM1_STOP HAL_TIM_Base_Stop(&htim1);
#define TIM6_IT_START HAL_TIM_Base_Start_IT(&htim6)
#define TIM6_IT_STOP HAL_TIM_Base_Stop_IT(&htim6)
#define TIM10_IT_START HAL_TIM_Base_Start_IT(&htim10)
#define TIM10_IT_STOP HAL_TIM_Base_Stop_IT(&htim10)
#define TIM11_IT_START HAL_TIM_Base_Start_IT(&htim11)
#define TIM11_IT_STOP HAL_TIM_Base_Stop_IT(&htim11)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
