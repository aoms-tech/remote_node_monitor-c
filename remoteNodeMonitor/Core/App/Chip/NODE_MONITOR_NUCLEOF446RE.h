/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     	TIBERIUS_NUCLEOF446RE.h
* Description: 	Tiberius' Nucleo-specific functions header.
***************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include <stdlib.h>
#include <string.h>
#include "DataTypes.h"


/* Setup Functions -----------------------------------------------------------*/
void Error_Handler(void);
void Chip_Init();
void Chip_Update();

uint8_t Brd_UART_DataReady(void);
uint8_t Brd_Find_Word(char* word);
uint8_t Brd_UART_GetData(uint16_t head_subtracter);
void PrettySend_Skyla_Info_toPi(uint8_t *payload, uint8_t skyla_num, uint8_t before_bool);

void Pi_Check_Program_Flag(void);
void Skyla1_Check_Flag(void);
void Creed1_Check_Flag(void);
void Skyla2_Check_Flag(void);
void Creed2_Check_Flag(void);

#define UART_MUX_INH_Port					GPIOC
#define UART_MUX_INH_Pin						GPIO_PIN_10
#define UART_MUX_SELA_Port					GPIOC
#define UART_MUX_SELA_Pin					GPIO_PIN_11

/* Chip default defines ------------------------------------------------------*/
#define USART_TX_Pin 								GPIO_PIN_2		// A2
#define USART_TX_GPIO_Port 					GPIOA				// A2
#define USART_RX_Pin 								GPIO_PIN_3		// A3
#define USART_RX_GPIO_Port 					GPIOA				// A3
#define TMS_Pin 										GPIO_PIN_13		// A13
#define TMS_GPIO_Port 							GPIOA				// A13
#define TCK_Pin 										GPIO_PIN_14		// A14
#define TCK_GPIO_Port 							GPIOA				// A14
#define SWO_Pin 										GPIO_PIN_3		// B3
#define SWO_GPIO_Port 							GPIOB				// B3

