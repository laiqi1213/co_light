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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_B_Pin GPIO_PIN_13
#define KEY_B_GPIO_Port GPIOC
#define KEY_SW_Pin GPIO_PIN_14
#define KEY_SW_GPIO_Port GPIOC
#define KEY_A_Pin GPIO_PIN_15
#define KEY_A_GPIO_Port GPIOC
#define AD_GET_Pin GPIO_PIN_2
#define AD_GET_GPIO_Port GPIOC
#define LED_VOLT_Pin GPIO_PIN_3
#define LED_VOLT_GPIO_Port GPIOC
#define FSYNC_Pin GPIO_PIN_3
#define FSYNC_GPIO_Port GPIOA
#define DAC_OUT1_Pin GPIO_PIN_4
#define DAC_OUT1_GPIO_Port GPIOA
#define SPI_SCLK_Pin GPIO_PIN_5
#define SPI_SCLK_GPIO_Port GPIOA
#define SPI_MOSI_Pin GPIO_PIN_7
#define SPI_MOSI_GPIO_Port GPIOA
#define TXD_Pin GPIO_PIN_10
#define TXD_GPIO_Port GPIOC
#define RXD_Pin GPIO_PIN_11
#define RXD_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_12
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOB
#define OLED_CLK_Pin GPIO_PIN_8
#define OLED_CLK_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
