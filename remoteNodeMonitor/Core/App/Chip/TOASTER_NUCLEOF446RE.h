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


/* Program States -----------------------------------------------------------*/
#define MONITOR								0
#define VALIDATE                            1
#define MOLLY_DEV1						    2
#define MOLLY_DEV2						    3
#define PROGRAM_DEV1						4
#define PROGRAM_DEV2						5
#define PROGRAM_DEV3						6
#define PROGRAM_DEV4						7
#define SEN_SELECT                          8
#define SET_CHG_STATE                       9 
#define SET_DEV_PWR                         10



/* Sensors Select ------------------------------------------------------------*/
#define SENS_SEL_A_STATE(x) ((x & ((1 << 1)-1)) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define SENS_SEL_B_STATE(x) ((x & ((1 << 2)-1)) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define SENS_SEL_C_STATE(x) ((x & ((1 << 3)-1)) ? GPIO_PIN_SET : GPIO_PIN_RESET)

#define SENS_TMP                            0
#define SENS_3TMP                           1
#define SENS_DS                             2
#define SENS_SHT                            3

#define NUM_SENS_AVAILABLE                  4

/* Node Select ---------------------------------------------------------------*/
#define BOTH                                0
#define NODE1                               1
#define NODE2                               2

#define OFF                                 0
#define ON                                  1
#define CYCLE                               2

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

void Skyla1_Program_App(void);
void Skyla2_Program_App(void);
void Creed1_Program_App(void);
void Creed2_Program_App(void);

void Set_Device_Power_App(void);
void Power_Dev_OFF(uint8_t = BOTH);
void Power_Dev_ON(uint8_t = BOTH);

void Sensor_Select_App(void);
void Set_Charger_App(void);

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

#define CHRG_EN_Port							GPIOC
#define CHRG_EN_Pin								GPIO_PIN_1

/* Chip default defines ------------------------------------------------------*/
#define USART_TX_Pin 							GPIO_PIN_2		// A2
#define USART_TX_GPIO_Port 					    GPIOA			// A2
#define USART_RX_Pin 							GPIO_PIN_3		// A3
#define USART_RX_GPIO_Port 					    GPIOA			// A3
#define TMS_Pin 								GPIO_PIN_13		// A13
#define TMS_GPIO_Port 							GPIOA			// A13
#define TCK_Pin 								GPIO_PIN_14		// A14
#define TCK_GPIO_Port 							GPIOA			// A14
#define SWO_Pin 								GPIO_PIN_3		// B3
#define SWO_GPIO_Port 							GPIOB			// B3
