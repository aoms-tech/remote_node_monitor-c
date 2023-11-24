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
    //Resets GPIO
    HAL_GPIO_WritePin(NODE1_SEN_PWR ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_MUX_INH ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_UART_RX_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_LTCH_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_SEL_A ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_SEL_B ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE1_SEL_C ,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(NODE2_SEN_PWR ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_MUX_INH ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_UART_RX_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_LTCH_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_SEL_A ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_SEL_B ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NODE2_SEL_C ,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SKYLA1_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA1_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA1_CHG_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA1_VCC_EN ,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SKYLA2_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA2_UPDI_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA2_CHG_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SKYLA2_VCC_EN ,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(NOTECARD1_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CREED1_UPDI_EN ,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(NOTECARD2_PWR_EN ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CREED2_UPDI_EN ,GPIO_PIN_RESET);



    //
    HAL_GPIO_WritePin(NODE1_SEN_PWR ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(NODE1_LTCH_EN ,GPIO_PIN_SET);

    HAL_GPIO_WritePin(NODE2_SEN_PWR ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(NODE2_LTCH_EN ,GPIO_PIN_SET);

    HAL_GPIO_WritePin(SKYLA1_PWR_EN ,GPIO_PIN_SET);
    if():
        HAL_GPIO_WritePin(SKYLA1_CHG_EN ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(SKYLA2_PWR_EN ,GPIO_PIN_SET);
    if():
        HAL_GPIO_WritePin(SKYLA2_CHG_EN ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(NOTECARD1_PWR_EN ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(NOTECARD2_PWR_EN ,GPIO_PIN_SET);
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
		case MOLLY_SKYLA1:
			Skyla1_Molly_App();
			break;

		case MOLLY_SKYLA2:
			Skyla2_Molly_App();
			break;

        case PROGRAM_SKYLA1:
            Skyla1_Program_App();
			break;

        case PROGRAM_SKYLA2:
            Skyla2_Program_App();
			break;

        case PROGRAM_CREED1:
            Creed1_Program_App();
            break;

        case PROGRAM_CREED2:
            Creed2_Program_App();
            break;

        case SEN_SELECT:
            Sensor_Selector();
            break;

        case SET_CHG_STATE:
                
            break;

		case MONITOR:
			Skyla1_Check_Flag();
			Creed1_Check_Flag();
			Skyla2_Check_Flag();
			Creed2_Check_Flag();
			break;
	}
}