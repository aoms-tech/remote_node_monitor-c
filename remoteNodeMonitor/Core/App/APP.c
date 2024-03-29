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
	HAL_GPIO_WritePin(SKYLA1_TX_EN_Port, SKYLA1_TX_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SKYLA2_TX_EN_Port, SKYLA2_TX_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CHRG_EN_Port, CHRG_EN_Pin, GPIO_PIN_RESET);
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

		case MONITOR:
			Skyla1_Check_Flag();
			Creed1_Check_Flag();
			Skyla2_Check_Flag();
			Creed2_Check_Flag();
			break;
	}
}
