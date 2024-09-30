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
#ifndef __CUBEMX_H
#define __CUBEMX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
void cubemx_init(void);
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ONB_LED_Pin GPIO_PIN_13
#define ONB_LED_GPIO_Port GPIOC
#define SHARP_1_Pin GPIO_PIN_2
#define SHARP_1_GPIO_Port GPIOA
#define SHARP_2_Pin GPIO_PIN_3
#define SHARP_2_GPIO_Port GPIOA
#define SHARP_3_Pin GPIO_PIN_4
#define SHARP_3_GPIO_Port GPIOA
#define SHARP_4_Pin GPIO_PIN_5
#define SHARP_4_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_1
#define BTN1_GPIO_Port GPIOB
#define BTN1_EXTI_IRQn EXTI1_IRQn
#define GYRO_SCL_Pin GPIO_PIN_10
#define GYRO_SCL_GPIO_Port GPIOB
#define DISPLAY_SCL_Pin GPIO_PIN_8
#define DISPLAY_SCL_GPIO_Port GPIOA
#define GYRO_SDA_Pin GPIO_PIN_3
#define GYRO_SDA_GPIO_Port GPIOB
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

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __CUBEMX_H */
