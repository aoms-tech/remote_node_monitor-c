/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     	TIBERIUS_NUCLEOF446RE.c
* Description: 	Tiberius' Nucleo-specific functions.
***************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "NODE_MONITOR_NUCLEOF446RE.h"

#include "string.h"
#include "stdio.h"


/* Private Functions ------------------------------------------------------------*/
void SystemClock_Config(void);

/* State Machines Variables ---------------------------------------------------*/
#define DEFAULT					0
#define FIND_DEBUG			1
#define GET_SETTINGS 			2
#define GET_MSG_P1				3
#define GET_MSG_P2			4
#define MOLLY_P1				5
#define MOLLY_P2				6
#define GET_MSG_P3			7
#define FINISH_MOLLY			8

uint8_t molly_skyla1_state = DEFAULT;
uint8_t molly_skyla2_state = DEFAULT;
uint8_t application_state = MONITOR;

/* Raspberry Pi UART Variables -----------------------------------------------*/
#define pi_buffer_size 5000
uint8_t pi_uart_rxBuffer[pi_buffer_size] = {0};
uint16_t pi_array_end = 0;
uint8_t pi_uart_rxData;

#define getinfo_buffer_size 											300
#define num_machine_readable_fields							37
uint8_t getinfo_buffer[getinfo_buffer_size];
char* pretty_getinfo_buffer[32];
uint8_t getinfo_fields_found_count = 0;
uint8_t getinfo_find_fields = 0;
uint16_t getinfo_buffer_head = 0;
uint8_t * brd_msg;

/* SKYLA1 UART Variables ------------------------------------------------------*/
#define skyla1_uart_buffer_size 5000
uint8_t skyla1_uart_rxBuffer[skyla1_uart_buffer_size] = {0};
uint16_t skyla1_array_start = 0;
uint16_t skyla1_array_end = 0;
uint16_t skyla1_send_flag = 0;
uint8_t skyla1_uart_rxData;
uint8_t skyla1_new_data = 0;
uint8_t * payload;

/* CREED1 UART Variables ------------------------------------------------------*/
#define creed1_uart_buffer_size 5000
uint8_t creed1_uart_rxBuffer[creed1_uart_buffer_size] = {0};
uint16_t creed1_array_start = 0;
uint16_t creed1_array_end = 0;
uint16_t creed1_send_flag = 0;
uint8_t creed1_uart_rxData;

/* SKYLA2 UART Variables ------------------------------------------------------*/
#define skyla2_uart_buffer_size 5000
uint8_t skyla2_uart_rxBuffer[skyla2_uart_buffer_size] = {0};
uint16_t skyla2_array_start = 0;
uint16_t skyla2_array_end = 0;
uint16_t skyla2_send_flag = 0;
uint8_t skyla2_uart_rxData;
uint8_t skyla2_new_data = 0;

/* CREED2 UART Variables ------------------------------------------------------*/
#define creed2_uart_buffer_size 5000
uint8_t creed2_uart_rxBuffer[creed2_uart_buffer_size] = {0};
uint16_t creed2_array_start = 0;
uint16_t creed2_array_end = 0;
uint16_t creed2_send_flag = 0;
uint8_t creed2_uart_rxData;


/******************************************************************************
* Function:    	void Chip_Init(void)
* Description: 	This routine sets up the chip
* Parameters:  	(none)
* Returns:     		(none)
******************************************************************************/
void Chip_Init(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();			// RASPBERRY PI
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();			// SKYLA1
  MX_UART4_Init();					// CREED1
  MX_UART5_Init();					// SKYLA2
  MX_USART6_UART_Init();			// CREED2

  HAL_UART_Receive_IT(&huart1, &pi_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart3, &skyla1_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart4, &creed1_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart5, &skyla2_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart6, &creed2_uart_rxData, 1);
}


/******************************************************************************
* Function:    	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
* Description: 	This routine runs when UART lines trigger the RX interrupt. It
* 				stores RX data into buffers.
* Parameters:  	*huart --> the uart that triggered the interrupt
* Returns:     		(none)
******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		pi_uart_rxBuffer[pi_array_end] = pi_uart_rxData;
		if(pi_uart_rxData == 'p')
			application_state = MOLLY_SKYLA1;
		else if(pi_uart_rxData == 'q')
			application_state = MOLLY_SKYLA2;
		pi_array_end = (pi_array_end+1)%pi_buffer_size;
		HAL_UART_Receive_IT(&huart1, &pi_uart_rxData, 1);
	}
	else if(huart->Instance == USART3)
	{
		skyla1_uart_rxBuffer[skyla1_array_end] = skyla1_uart_rxData;
		if(skyla1_uart_rxData == '\n' || skyla1_uart_rxData == '\r')
			skyla1_send_flag = skyla1_array_end;
		skyla1_new_data = 1;
		skyla1_array_end = (skyla1_array_end+1)%skyla1_uart_buffer_size;
		HAL_UART_Receive_IT(&huart3, &skyla1_uart_rxData, 1);
	}
	else if(huart->Instance == UART4)
	{
		creed1_uart_rxBuffer[creed1_array_end] = creed1_uart_rxData;
		if(creed1_uart_rxData == '\n' || creed1_uart_rxData == '\r')
			creed1_send_flag = creed1_array_end;
		creed1_array_end = (creed1_array_end+1)%creed1_uart_buffer_size;
		HAL_UART_Receive_IT(&huart4, &creed1_uart_rxData, 1);
	}
	else if(huart->Instance == UART5)
	{
		skyla2_uart_rxBuffer[skyla2_array_end] = skyla2_uart_rxData;
		if(skyla2_uart_rxData == '\n' || skyla2_uart_rxData == '\r')
			skyla2_send_flag = skyla2_array_end;
		skyla2_new_data = 1;
		skyla2_array_end = (skyla2_array_end+1)%skyla2_uart_buffer_size;
		HAL_UART_Receive_IT(&huart5, &skyla2_uart_rxData, 1);
	}
	else if(huart->Instance == USART6)
	{
		creed2_uart_rxBuffer[creed2_array_end] = creed2_uart_rxData;
		if(creed2_uart_rxData == '\n' || creed2_uart_rxData == '\r')
			creed2_send_flag = creed2_array_end;
		creed2_array_end = (creed2_array_end+1)%creed2_uart_buffer_size;
		HAL_UART_Receive_IT(&huart6, &creed2_uart_rxData, 1);
	}
}

uint8_t Get_Application_State(void)
{
	return application_state;
}

uint8_t Skyla1_DataReady(void)
{
	return skyla1_new_data;
}

uint8_t Skyla2_DataReady(void)
{
	return skyla2_new_data;
}

uint8_t Skyla1_GetData(uint16_t head_subtracter)
{
	skyla1_new_data = 0;
	return skyla1_uart_rxBuffer[(skyla1_uart_buffer_size-1-head_subtracter+skyla1_array_end)%skyla1_uart_buffer_size];
}

uint8_t Skyla2_GetData(uint16_t head_subtracter)
{
	skyla2_new_data = 0;
	return skyla2_uart_rxBuffer[(skyla2_uart_buffer_size-1-head_subtracter+skyla2_array_end)%skyla2_uart_buffer_size];
}

uint8_t Skyla1_Find_Word(char* word)
{
	if(Skyla1_DataReady())
	{
		uint16_t word_length = strlen(word);
		char current_word[255] = {0};
		for(uint16_t i = 0; i<word_length; i++)
			current_word[word_length-1-i] = Skyla1_GetData(i);

		if(strcmp(current_word, word) == 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

uint8_t Skyla2_Find_Word(char* word)
{
	if(Skyla2_DataReady())
	{
		uint16_t word_length = strlen(word);
		char current_word[255] = {0};
		for(uint16_t i = 0; i<word_length; i++)
			current_word[word_length-1-i] = Skyla2_GetData(i);

		if(strcmp(current_word, word) == 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

uint8_t * Skyla1_GetInfo(void)
{
	if(Skyla1_DataReady())
	{
		if(getinfo_find_fields)
		{
			char curr_char = Skyla1_GetData(0);
			getinfo_buffer[getinfo_buffer_head] = curr_char;
			getinfo_buffer_head += 1;

			if(curr_char == '|')
				getinfo_fields_found_count += 1;

			if(getinfo_fields_found_count == num_machine_readable_fields)
				getinfo_buffer[0] = '1';
		}
		else
		{
			if(Skyla1_Find_Word("1."))
			{
				getinfo_buffer[1] = '.';
				getinfo_buffer_head = getinfo_buffer_head + 1;
				getinfo_find_fields = 1;
			}
		}
	}
	return getinfo_buffer;
}

uint8_t * Skyla2_GetInfo(void)
{
	if(Skyla2_DataReady())
	{
		if(getinfo_find_fields)
		{
			char curr_char = Skyla2_GetData(0);
			getinfo_buffer[getinfo_buffer_head] = curr_char;
			getinfo_buffer_head += 1;

			if(curr_char == '|')
				getinfo_fields_found_count += 1;

			if(getinfo_fields_found_count == num_machine_readable_fields)
				getinfo_buffer[0] = '1';
		}
		else
		{
			if(Skyla2_Find_Word("1."))
			{
				getinfo_buffer[1] = '.';
				getinfo_buffer_head = getinfo_buffer_head + 1;
				getinfo_find_fields = 1;
			}
		}
	}
	return getinfo_buffer;
}

char* titles[num_machine_readable_fields] = {
			"Firmware Version",						"Hardware Version",					"Device ID",								"MCP7411 UID",							"Date",
			"Day of Week",								"Time",										"Timestamp",							"External Sensor Frequency",			"Node Status Frequency",
			"AT25SF128A MID",						"AT25SF128A Device ID",			"AT25SF128A UID",					"Data Logger Next Pointer",			"Data Logger Read Pointer",
			"Data Logger Origin Pointer",		"Data Logger Read Count",		"Data Logger Origin Count",		"Internal Temperature",					"Creed Firmware Version",
			"Creed Hardware Version",			"Battery Voltage",						"Internal Humidity",					"Internal Sensor Frequency",			"Application Key",
			"Network Key",								"Fuse Settings",						"Creed Transmit Frequency",		"RTCC Trim Value",						"Data Logger Send Pointer",
			"Build Version",								"Creed Settings",						"RTCC Control Value",				"Data Logger Next Sector",			"Data Logger Read Sector",
			"Data Logger Origin Sector",			"Data Logger Send Sector"
};
void PrettySend_Skyla_Info_toPi(uint8_t *payload, uint8_t skyla_num, uint8_t before_bool)
{
	char* tokens = strtok((char*) payload, "|");
	uint8_t counter = 0;

	while( tokens != NULL )
	{
		if(skyla_num == 1)
			HAL_UART_Transmit(&huart1, (uint8_t*)"S1|", 3, 1000);
		else
			HAL_UART_Transmit(&huart1, (uint8_t*)"S2|", 3, 1000);

		if(before_bool)
			HAL_UART_Transmit(&huart1, (uint8_t*)"B|", 2, 1000);
		else
			HAL_UART_Transmit(&huart1, (uint8_t*)"A|", 2, 1000);

		HAL_UART_Transmit(&huart1, (uint8_t*)titles[counter], strlen(titles[counter]), 1000);
		HAL_UART_Transmit(&huart1, (uint8_t*)"| ", 2, 1000);
		HAL_UART_Transmit(&huart1, (uint8_t*)tokens, strlen(tokens), 1000);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 1000);

		tokens = strtok(NULL, "|");
		counter += 1;
		HAL_Delay(10);
	}
}

void Skyla1_Molly_App(void)
{
	switch(molly_skyla1_state)
	{
		case FIND_DEBUG:
			if(Skyla1_Find_Word("DEBUG"))
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"L|Found debug\n", 14, 1000);
				HAL_UART_Transmit(&huart3, (uint8_t*)"DEBUG", 5, 1000);
				molly_skyla1_state = GET_SETTINGS;
			}
			break;

		case GET_SETTINGS:
			memset(pi_uart_rxBuffer, 0, pi_buffer_size);
			pi_array_end = 0;
			HAL_UART_Transmit(&huart1, (uint8_t*)"send payload \r\n", 15, 1000);
			HAL_Delay(100);

			HAL_UART_Transmit(&huart1, (uint8_t*)"L| PL:", 6, 1000);
			HAL_UART_Transmit(&huart1, (uint8_t*)(char*)pi_uart_rxBuffer, strlen((char*)pi_uart_rxBuffer), 1000);
			HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 1000);

			payload = pi_uart_rxBuffer;

			HAL_UART_Transmit(&huart3, (uint8_t*)"$", 1, 500);
			molly_skyla1_state = GET_MSG_P1;
			break;

		case GET_MSG_P1:
			if(Skyla1_Find_Word("NACK"))
			{
				memset(getinfo_buffer, 0, getinfo_buffer_size);
				getinfo_buffer_head = 1;
				getinfo_fields_found_count = 0;
				getinfo_find_fields = 0;
				HAL_UART_Transmit(&huart3, (uint8_t*)"#", 1, 500);
				molly_skyla1_state = GET_MSG_P2;
			}
			break;

		case GET_MSG_P2:
			brd_msg = Skyla1_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 1, 1);
				molly_skyla1_state = MOLLY_P1;
			}
			break;

		case MOLLY_P1:
			if(Skyla1_Find_Word("N"))
					skyla1_new_data = 0;
			char strC[500];
			char * settings_char = "$$";
			strncpy(strC, settings_char, 1);
			strC[1] = '\0';
			strcat(strC, (char*)payload);
			HAL_UART_Transmit(&huart3, (uint8_t*) strC, strlen(strC), 50);
			molly_skyla1_state = MOLLY_P2;
			break;

		case MOLLY_P2:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| in molly \n", 13, 500);
			while(1)
			{
				if(Skyla1_Find_Word(":"))
				{
					char * curr_string = (char*)&skyla1_uart_rxBuffer[skyla1_array_start+1];
					char * find_pass = strstr(curr_string, "PASS");
					char * find_fail = strstr(curr_string, "FAIL");
					if(find_pass != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD PASS \n", 15, 500);
						HAL_UART_Transmit(&huart3, (uint8_t*)"#", 1, 500);
						memset(getinfo_buffer, 0, getinfo_buffer_size);
						getinfo_buffer_head = 1;
						getinfo_fields_found_count = 0;
						getinfo_find_fields = 0;
						molly_skyla1_state = GET_MSG_P3;
						break;
					}
					else if(find_fail != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD FAIL!!! \n", 18, 500);
						molly_skyla1_state = FINISH_MOLLY;
						break;
					}
					skyla1_array_start = skyla1_array_end;
				}
			}
			break;

		case GET_MSG_P3:
			brd_msg = Skyla1_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 1, 0);
				molly_skyla1_state = FINISH_MOLLY;
			}
			break;

		case FINISH_MOLLY:
			HAL_GPIO_WritePin(SKYLA1_TX_EN_Port, SKYLA1_TX_EN_Pin, GPIO_PIN_RESET);
			HAL_UART_Transmit(&huart1, (uint8_t*)"molly complete \r\n", 17, 1000);
			molly_skyla1_state = DEFAULT;
			application_state = MONITOR;
			break;

		default:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| Received molly command. \r\n", 29, 1000);
			HAL_GPIO_WritePin(SKYLA1_TX_EN_Port, SKYLA1_TX_EN_Pin, GPIO_PIN_SET);
			molly_skyla1_state = FIND_DEBUG;
			break;
	}
}

void Skyla2_Molly_App(void)
{
	switch(molly_skyla2_state)
	{
		case FIND_DEBUG:
			if(Skyla2_Find_Word("DEBUG"))
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"L|Found debug\n", 14, 1000);
				HAL_UART_Transmit(&huart5, (uint8_t*)"DEBUG", 5, 1000);
				molly_skyla2_state = GET_SETTINGS;
			}
			break;

		case GET_SETTINGS:
			memset(pi_uart_rxBuffer, 0, pi_buffer_size);
			pi_array_end = 0;
			HAL_UART_Transmit(&huart1, (uint8_t*)"send payload \r\n", 15, 1000);
			HAL_Delay(100);

			HAL_UART_Transmit(&huart1, (uint8_t*)"L| PL:", 6, 1000);
			HAL_UART_Transmit(&huart1, (uint8_t*)(char*)pi_uart_rxBuffer, strlen((char*)pi_uart_rxBuffer), 1000);
			HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 1000);

			payload = pi_uart_rxBuffer;

			HAL_UART_Transmit(&huart5, (uint8_t*)"$", 1, 500);
			molly_skyla2_state = GET_MSG_P1;
			break;

		case GET_MSG_P1:
			if(Skyla2_Find_Word("NACK"))
			{
				memset(getinfo_buffer, 0, getinfo_buffer_size);
				getinfo_buffer_head = 1;
				getinfo_fields_found_count = 0;
				getinfo_find_fields = 0;
				HAL_UART_Transmit(&huart5, (uint8_t*)"#", 1, 500);
				molly_skyla2_state = GET_MSG_P2;
			}
			break;

		case GET_MSG_P2:
			brd_msg = Skyla2_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 2, 1);
				molly_skyla2_state = MOLLY_P1;
			}
			break;

		case MOLLY_P1:
			if(Skyla2_Find_Word("N"))
					skyla1_new_data = 0;
			char strC[500];
			char * settings_char = "$$";
			strncpy(strC, settings_char, 1);
			strC[1] = '\0';
			strcat(strC, (char*)payload);
			HAL_UART_Transmit(&huart5, (uint8_t*) strC, strlen(strC), 50);
			molly_skyla2_state = MOLLY_P2;
			break;

		case MOLLY_P2:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| in molly \n", 13, 500);
			while(1)
			{
				if(Skyla2_Find_Word(":"))
				{
					char * curr_string = (char*)&skyla2_uart_rxBuffer[skyla2_array_start+1];
					char * find_pass = strstr(curr_string, "PASS");
					char * find_fail = strstr(curr_string, "FAIL");
					if(find_pass != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD PASS \n", 15, 500);
						HAL_UART_Transmit(&huart5, (uint8_t*)"#", 1, 500);
						memset(getinfo_buffer, 0, getinfo_buffer_size);
						getinfo_buffer_head = 1;
						getinfo_fields_found_count = 0;
						getinfo_find_fields = 0;
						molly_skyla2_state = GET_MSG_P3;
						break;
					}
					else if(find_fail != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD FAIL!!! \n", 18, 500);
						molly_skyla2_state = FINISH_MOLLY;
						break;
					}
					skyla2_array_start = skyla2_array_end;
				}
			}
			break;

		case GET_MSG_P3:
			brd_msg = Skyla2_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 2, 0);
				molly_skyla2_state = FINISH_MOLLY;
			}
			break;

		case FINISH_MOLLY:
			HAL_GPIO_WritePin(SKYLA2_TX_EN_Port, SKYLA2_TX_EN_Pin, GPIO_PIN_RESET);
			HAL_UART_Transmit(&huart1, (uint8_t*)"molly complete \r\n", 17, 1000);
			molly_skyla2_state = DEFAULT;
			application_state = MONITOR;
			break;

		default:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| Received molly command. \r\n", 29, 1000);
			HAL_GPIO_WritePin(SKYLA2_TX_EN_Port, SKYLA2_TX_EN_Pin, GPIO_PIN_SET);
			molly_skyla2_state = FIND_DEBUG;
			break;
	}
}

void Skyla1_Check_Flag(void)
{
	if(skyla1_send_flag != skyla1_array_start){
		uint16_t num_bytes;
		if(skyla1_send_flag > skyla1_array_start){
			num_bytes = skyla1_send_flag - skyla1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS1|", 4, 500);
			HAL_UART_Transmit(&huart1, &skyla1_uart_rxBuffer[skyla1_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = skyla1_uart_buffer_size - skyla1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS1|", 4, 500);
			HAL_UART_Transmit(&huart1, &skyla1_uart_rxBuffer[skyla1_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &skyla1_uart_rxBuffer[0], skyla1_send_flag, 500);
		}
		skyla1_array_start = skyla1_send_flag;
	}
}

void Creed1_Check_Flag(void)
{
	if(creed1_send_flag != creed1_array_start){
		uint16_t num_bytes;
		if(creed1_send_flag > creed1_array_start){
			num_bytes = creed1_send_flag - creed1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC1|", 4, 500);
			HAL_UART_Transmit(&huart1, &creed1_uart_rxBuffer[creed1_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = creed1_uart_buffer_size - creed1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC1|", 4, 500);
			HAL_UART_Transmit(&huart1, &creed1_uart_rxBuffer[creed1_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &creed1_uart_rxBuffer[0], creed1_send_flag, 500);
		}
		creed1_array_start = creed1_send_flag;
	}
}

void Skyla2_Check_Flag(void)
{
	if(skyla2_send_flag != skyla2_array_start){
		uint16_t num_bytes;
		if(skyla2_send_flag > skyla2_array_start){
			num_bytes = skyla2_send_flag - skyla2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS2|", 4, 500);
			HAL_UART_Transmit(&huart1, &skyla2_uart_rxBuffer[skyla2_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = skyla2_uart_buffer_size - skyla2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS2|", 4, 500);
			HAL_UART_Transmit(&huart1, &skyla2_uart_rxBuffer[skyla2_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &skyla2_uart_rxBuffer[0], skyla2_send_flag, 500);
		}
		skyla2_array_start = skyla2_send_flag;
	}
}

void Creed2_Check_Flag(void)
{
	if(creed2_send_flag != creed2_array_start){
		uint16_t num_bytes;
		if(creed2_send_flag > creed2_array_start){
			num_bytes = creed2_send_flag - creed2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC2|", 4, 500);
			HAL_UART_Transmit(&huart1, &creed2_uart_rxBuffer[creed2_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = creed2_uart_buffer_size - creed2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC2|", 4, 500);
			HAL_UART_Transmit(&huart1, &creed2_uart_rxBuffer[creed2_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &creed2_uart_rxBuffer[0], creed2_send_flag, 500);
		}
		creed2_array_start = creed2_send_flag;
	}
}


/******************************************************************************
* Function:    	void Chip_Update(void)
* Description: 	This routine update any low level chip functions
* Parameters:  	(none)
* Returns:    	 	(none)
******************************************************************************/
void Chip_Update(void)
{

}


/******************************************************************************
* Function:    	void SystemClock_Config(void)
* Description: 	Configures the system's clock. Built-in to main.c of generated
* 				files by STM32CubeIDE.
* Parameters:  	(none)
* Returns:     	(none)
******************************************************************************/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


/******************************************************************************
* Function:    	void Error_Handler(void)
* Description: 	This function is executed in case of error occurrence. Built-
* 				in to main.c of generated files by STM32CubeIDE.
* Parameters:  	(none)
* Returns:     	(none)
******************************************************************************/
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}


/******************************************************************************
* Function:    	void assert_failed(uint8_t *file, uint32_t line)
* Description: 	Reports the name of the source file and the source line number
*	         	where the assert_param error has occurred. Built-in to main.c
*	         	of generated files by STM32CubeIDE.
* Parameters:  	file		--> pointer to the source file name
* 				line		--> assert_param error line source number
* Returns:     	(none)
******************************************************************************/
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
