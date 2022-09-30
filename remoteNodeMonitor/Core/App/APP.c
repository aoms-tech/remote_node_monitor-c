/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     APP.c
* Description: Application Main Program
***************************************************************************************************/
#include "APP.h"
#include <string.h>


/******************************************************************************
* Function:    	void App_Init(void)
* Description: 	Initializes application.
* Parameters:  	(none)
* Returns:     		(none)
******************************************************************************/
void App_Init(void)
{
	HAL_GPIO_WritePin(UART_MUX_SELA_Port, UART_MUX_SELA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART_MUX_INH_Port, UART_MUX_INH_Pin, GPIO_PIN_RESET);
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

		case MONITOR:
//			HAL_UART_Transmit(&huart1, (uint8_t*)"L|monitor mode \n", 16, 500);
			Skyla1_Check_Flag();
			Creed1_Check_Flag();
			Skyla2_Check_Flag();
			Creed2_Check_Flag();
			break;
	}
}
