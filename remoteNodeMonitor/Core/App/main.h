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


#define DEV2_4_MUX_INH(x)      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (x))    //node2
#define DEV1_3_LTCH_EN(x)     	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (x))    //node1
#define DEV1_PWR_EN(x)         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (x))    //s1
#define DEV3_PWR_EN(x)         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (x))    //c1
#define DEV1_3_SEN_PWR(x)      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (x))    //node1
#define DEV2_4_LTCH_EN(x)      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, (x))   //node2

#define DEV2_4_SEN_PWR(x)      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (x))    //node2
#define DEV2_PWR_EN(x)         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (x))    //s2
#define DEV4_PWR_EN(x)         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (x))    //c2
#define DEV2_UPDI_EN(x)        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (x))    //s2
#define DEV4_UPDI_EN(x)        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (x))    //c2
#define DEV2_4_UART_RX_EN(x)   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (x))    //node2
#define DEV2_CHG_EN(x)         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (x))    //node2
#define DEV2_4_VCC_EN(x)       	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (x))   //node2
#define DEV2_4_SEL_C(x)        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (x))   //node2
#define DEV2_4_SEL_B(x)        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (x))   //node2

#define DEV1_3_SEL_A(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, (x))    //node1
#define DEV1_3_SEL_B(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, (x))    //node1
#define DEV1_3_SEL_C(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, (x))    //node1
#define DEV1_3_MUX_INH(x)      	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, (x))    //node1
#define DEV2_4_SEL_A(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, (x))    //node2
#define DEV1_UPDI_EN(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, (x))    //s1
#define DEV3_UPDI_EN(x)        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (x))    //c1
#define DEV1_3_UART_RX_EN(x)   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, (x))   //node1
#define DEV1_CHG_EN(x)         	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, (x))
#define DEV1_3_VCC_EN(x)     	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (x))   //node1



#define DEV2_4_MUX_INH_RESET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)    //node2
#define DEV1_3_LTCH_EN_RESET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)    //node1
#define DEV1_PWR_EN_RESET         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)    //s1
#define DEV3_PWR_EN_RESET         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)    //c1
#define DEV1_3_SEN_PWR_RESET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)    //node1
#define DEV2_4_LTCH_EN_RESET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)   //node2

#define DEV2_4_SEN_PWR_RESET      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)    //node2
#define DEV2_PWR_EN_RESET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)    //s2
#define DEV4_PWR_EN_RESET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)    //c2
#define DEV2_UPDI_EN_RESET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)    //s2
#define DEV4_UPDI_EN_RESET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)    //c2
#define DEV2_4_UART_RX_EN_RESET   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)    //node2
#define DEV2_CHG_EN_RESET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)    //node2
#define DEV2_4_VCC_EN_RESET       	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)   //node2
#define DEV2_4_SEL_C_RESET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)   //node2
#define DEV2_4_SEL_B_RESET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)   //node2

#define DEV1_3_SEL_A_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET)    //node1
#define DEV1_3_SEL_B_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET)    //node1
#define DEV1_3_SEL_C_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET)    //node1
#define DEV1_3_MUX_INH_RESET      	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET)    //node1
#define DEV2_4_SEL_A_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)    //node2
#define DEV1_UPDI_EN_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET)    //s1
#define DEV3_UPDI_EN_RESET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET)    //c1
#define DEV1_3_UART_RX_EN_RESET   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET)   //node1
#define DEV1_CHG_EN_RESET         	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET)
#define DEV1_3_VCC_EN_RESET     	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)   //node1


#define DEV2_4_MUX_INH_SET			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)    //node2
#define DEV1_3_LTCH_EN_SET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)    //node1
#define DEV1_PWR_EN_SET         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)    //s1
#define DEV3_PWR_EN_SET         	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)    //c1
#define DEV1_3_SEN_PWR_SET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)    //node1
#define DEV2_4_LTCH_EN_SET      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)   //node2

#define DEV2_4_SEN_PWR_SET      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)    //node2
#define DEV2_PWR_EN_SET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)    //s2
#define DEV4_PWR_EN_SET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)    //c2
#define DEV2_UPDI_EN_SET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)    //s2
#define DEV4_UPDI_EN_SET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)    //c2
#define DEV2_4_UART_RX_EN_SET   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)    //node2
#define DEV2_CHG_EN_SET         	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)    //node2
#define DEV2_4_VCC_EN_SET       	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)   //node2
#define DEV2_4_SEL_C_SET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)   //node2
#define DEV2_4_SEL_B_SET        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)   //node2

#define DEV1_3_SEL_A_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET)    //node1
#define DEV1_3_SEL_B_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET)    //node1
#define DEV1_3_SEL_C_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET)    //node1
#define DEV1_3_MUX_INH_SET      	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET)    //node1
#define DEV2_4_SEL_A_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)    //node2
#define DEV1_UPDI_EN_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET)    //s1
#define DEV3_UPDI_EN_SET        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET)    //c1
#define DEV1_3_UART_RX_EN_SET   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET)   //node1
#define DEV1_CHG_EN_SET         	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET)
#define DEV1_3_VCC_EN_SET       	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)   //node1

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
