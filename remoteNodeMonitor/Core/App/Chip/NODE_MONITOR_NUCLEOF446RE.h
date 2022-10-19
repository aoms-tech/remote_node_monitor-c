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


/* Program States -----------------------------------------------------------*/
#define MONITOR									0
#define MOLLY_SKYLA1							1
#define MOLLY_SKYLA2						2


/* Setup Functions -----------------------------------------------------------*/
void Error_Handler(void);
void Chip_Init();
void Chip_Update();

uint8_t Get_Application_State(void);

uint8_t Skyla1_DataReady(void);
uint8_t Skyla1_Find_Word(char* word);
uint8_t Skyla1_GetData(uint16_t head_subtracter);
uint8_t Skyla2_DataReady(void);
uint8_t Skyla2_Find_Word(char* word);
uint8_t Skyla2_GetData(uint16_t head_subtracter);
void PrettySend_Skyla_Info_toPi(uint8_t *payload, uint8_t skyla_num, uint8_t before_bool);

void Skyla1_Molly_App(void);
void Skyla2_Molly_App(void);

void Skyla1_Check_Flag(void);
void Creed1_Check_Flag(void);
void Skyla2_Check_Flag(void);
void Creed2_Check_Flag(void);

//LOGGERS 2,3
//#define SKYLA2_TX_EN_Port						GPIOC
//#define SKYLA2_TX_EN_Pin						GPIO_PIN_10
//#define SKYLA1_TX_EN_Port						GPIOC
//#define SKYLA1_TX_EN_Pin						GPIO_PIN_11

//LOGGER 1
#define SKYLA2_TX_EN_Port						GPIOC
#define SKYLA2_TX_EN_Pin						GPIO_PIN_11
#define SKYLA1_TX_EN_Port						GPIOC
#define SKYLA1_TX_EN_Pin						GPIO_PIN_10

#define CHRG_EN_Port								GPIOC
#define CHRG_EN_Pin								GPIO_PIN_1

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

