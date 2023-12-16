/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     APP.c
* Description: Application Main Program
***************************************************************************************************/
#include "APP.h"
#include "main.h"

/* State Machines Variables ---------------------------------------------------*/
#define DEFAULT					0
#define FIND_DEBUG				1
#define GET_SETTINGS 			2
#define GET_MSG_P1				3
#define GET_MSG_P2				4
#define MOLLY_P1				5
#define MOLLY_P2				6
#define GET_MSG_P3				7
#define FINISH_MOLLY			8
#define FINISH_PROGRAM			9

/******************************************************************************
* Function:    	void App_Init(void)
* Description: 	Initializes application and resets all GPIO pins
* Parameters:  	(none)
* Returns:     		(none)
******************************************************************************/
void App_Init(void)
{
    //resets all nodes
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13 ,GPIO_PIN_RESET);
}


/******************************************************************************
* Function:    	void App_Update(void)
* Description: 	Updates state of the application.
* Parameters:  	(none)
* Returns:     		(none)
******************************************************************************/
void App_Update(void)
{
	switch(Get_Application_State())
	{
		case MOLLY_DEV1:
			Dev1_Molly_App();
			break;

		case MOLLY_DEV2:
			Dev2_Molly_App();
			break;

        case PROGRAM_DEV1:
        	Dev1_Program_App();
			break;

        case PROGRAM_DEV2:
        	Dev2_Program_App();
			break;

        case PROGRAM_DEV3:
        	Dev3_Program_App();
            break;

        case PROGRAM_DEV4:
        	Dev4_Program_App();
            break;

        case SEN_SELECT:
            Sensor_Select_App();
            break;

        case SET_CHG_STATE:
            Set_Charger_App();
            break;

        case SET_DEV_PWR:
            Set_Device_Power_App();
            break;

		case MONITOR:
			Dev1_Check_Flag();
			Dev3_Check_Flag();
			Dev2_Check_Flag();
			Dev4_Check_Flag();
			break;
	}
}
