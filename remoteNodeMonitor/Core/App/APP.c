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
    HAL_GPIO_WritePin(DEV2_4_MUX_INH ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_LTCH_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_SEN_PWR ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_LTCH_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_SEN_PWR ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV4_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV4_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_UART_RX_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_CHG_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_VCC_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_SEL_C ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_SEL_B ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_SEL_A ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_SEL_B ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_SEL_C ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_MUX_INH ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV2_4_SEL_A ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV3_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV3_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_UART_RX_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_CHG_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEV1_3_VCC_EN ,GPIO_PIN_RESET);

    Power_Dev_ON(BOTH);
    Sensor_Select_App();
}


/******************************************************************************
* Function:    	void App_Update(void)
* Description: 	Updates state of the application.
* Parameters:  	(none)
* Returns:     		(none)
******************************************************************************/
void App_Update(void)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)Get_Application_State(), sizeof(Get_Application_State()), 500);
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
