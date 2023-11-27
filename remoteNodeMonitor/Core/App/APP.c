/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     APP.c
* Description: Application Main Program
***************************************************************************************************/
#include "APP.h"
#include "main.h"

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

    Power_Dev_ON();
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
	switch(Get_Application_State())
	{
		case MOLLY_DEV1:
			Skyla1_Molly_App();
			break;

		case MOLLY_DEV2:
			Skyla2_Molly_App();
			break;

        case PROGRAM_DEV1:
            Skyla1_Program_App();
			break;

        case PROGRAM_DEV2:
            Skyla2_Program_App();
			break;

        case PROGRAM_DEV3:
            Creed1_Program_App();
            break;

        case PROGRAM_DEV4:
            Creed2_Program_App();
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
			Skyla1_Check_Flag();
			Creed1_Check_Flag();
			Skyla2_Check_Flag();
			Creed2_Check_Flag();
			break;
	}
}