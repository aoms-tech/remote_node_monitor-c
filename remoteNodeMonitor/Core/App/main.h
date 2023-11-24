/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
//pin alias

#define DEV2_4_MUX_INH      GPIOA,GPIO_PIN_4    //node2
#define DEV1_3_LTCH_EN      GPIOA,GPIO_PIN_5    //node1
#define DEV1_3_SEN_PWR      GPIOA,GPIO_PIN_8    //node1
#define DEV2_4_LTCH_EN      GPIOA,GPIO_PIN_15   //node2

#define DEV2_4_SEN_PWR      GPIOB,GPIO_PIN_0    //node2
#define DEV2_PWR_EN         GPIOB,GPIO_PIN_4    //s2
#define DEV4_PWR_EN         GPIOB,GPIO_PIN_5    //c2
#define DEV2_UPDI_EN        GPIOB,GPIO_PIN_6    //s2
#define DEV4_UPDI_EN        GPIOB,GPIO_PIN_7    //c2
#define DEV2_4_UART_RX_EN   GPIOB,GPIO_PIN_8    //node2
#define DEV2_CHG_EN         GPIOB,GPIO_PIN_9    //node2
#define DEV2_4_VCC_EN       GPIOB,GPIO_PIN_12   //node2
#define DEV2_4_SEL_C        GPIOB,GPIO_PIN_13   //node2
#define DEV2_4_SEL_B        GPIOB,GPIO_PIN_14   //node2

#define DEV1_3_SEL_A        GPIOC,GPIO_PIN_0    //node1
#define DEV1_3_SEL_B        GPIOC,GPIO_PIN_1    //node1
#define DEV1_3_SEL_C        GPIOC,GPIO_PIN_2    //node1
#define DEV1_3_MUX_INH      GPIOC,GPIO_PIN_3    //node1
#define DEV2_4_SEL_A        GPIOC,GPIO_PIN_4    //node2
#define DEV1_PWR_EN         GPIOC,GPIO_PIN_6    //s1
#define DEV3_PWR_EN         GPIOC,GPIO_PIN_7    //c1
#define DEV1_UPDI_EN        GPIOC,GPIO_PIN_8    //s1
#define DEV3_UPDI_EN        GPIOC,GPIO_PIN_9    //c1
#define DEV1_3_UART_RX_EN   GPIOC,GPIO_PIN_10   //node1
#define DEV1_CHG_EN         GPIOC,GPIO_PIN_11
#define DEV1_3_VCC_EN       GPIOC,GPIO_PIN_13   //node1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
