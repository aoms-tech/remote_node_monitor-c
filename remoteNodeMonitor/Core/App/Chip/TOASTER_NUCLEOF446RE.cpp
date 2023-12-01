/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     	TIBERIUS_NUCLEOF446RE.c
* Description: 	Tiberius' Nucleo-specific functions.
***************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "TOASTER_NUCLEOF446RE.h"
#include "string.h"
#include "stdio.h"
#include "main.h"
#include <vector>
#include <string>

//test change

/* Private Functions ------------------------------------------------------------*/
void SystemClock_Config(void);

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

uint8_t molly_dev1_state = DEFAULT;
uint8_t molly_dev2_state = DEFAULT;

uint8_t program_dev1_state = DEFAULT;
uint8_t program_dev2_state = DEFAULT;
uint8_t program_dev3_state = DEFAULT;
uint8_t program_dev4_state = DEFAULT;

uint8_t application_state = MONITOR;

/* Raspberry Pi UART Variables -----------------------------------------------*/
#define pi_buffer_size 5000
uint8_t pi_uart_rxBuffer[pi_buffer_size] = {0};
uint16_t pi_array_end = 0;
uint8_t pi_uart_rxData;

#define getinfo_buffer_size 						300
#define num_machine_readable_fields					37
uint8_t getinfo_buffer[getinfo_buffer_size];
char* pretty_getinfo_buffer[32];
uint8_t getinfo_fields_found_count = 0;
uint8_t getinfo_find_fields = 0;
uint16_t getinfo_buffer_head = 0;
uint8_t * brd_msg;

//#define Pi <--> Nucleo UART com consts
#define SETMODE_OBSERVE						'a'
#define SETMODE_VALIDATE					'b'
#define SETMODE_MOLLY_DEV1					'c'
#define SETMODE_MOLLY_DEV2					'd'
#define SETMODE_PROGRAM_DEV1				'e'
#define SETMODE_PROGRAM_DEV2				'f'
#define SETMODE_PROGRAM_DEV3				'g'
#define SETMODE_PROGRAM_DEV4				'h'
#define SETMODE_SENS_SELECT					'i'
#define SETMODE_SET_CHG_STATE				'j'
#define SETMODE_SET_DEV_PWR					'k'

#define PI_PROCESS_FIN 						'`'

/* SKYLA1 UART Variables ------------------------------------------------------*/
#define dev1_uart_buffer_size 5000
uint8_t dev1_uart_rxBuffer[dev1_uart_buffer_size] = {0};
uint16_t dev1_array_start = 0;
uint16_t dev1_array_end = 0;
uint16_t dev1_send_flag = 0;
uint8_t dev1_uart_rxData;
uint8_t dev1_new_data = 0;
uint8_t * payload;

/* CREED1 UART Variables ------------------------------------------------------*/
#define dev3_uart_buffer_size 5000
uint8_t dev3_uart_rxBuffer[dev3_uart_buffer_size] = {0};
uint16_t dev3_array_start = 0;
uint16_t dev3_array_end = 0;
uint16_t dev3_send_flag = 0;
uint8_t dev3_uart_rxData;

/* SKYLA2 UART Variables ------------------------------------------------------*/
#define dev2_uart_buffer_size 5000
uint8_t dev2_uart_rxBuffer[dev2_uart_buffer_size] = {0};
uint16_t dev2_array_start = 0;
uint16_t dev2_array_end = 0;
uint16_t dev2_send_flag = 0;
uint8_t dev2_uart_rxData;
uint8_t dev2_new_data = 0;

/* CREED2 UART Variables ------------------------------------------------------*/
#define dev4_uart_buffer_size 5000
uint8_t dev4_uart_rxBuffer[dev4_uart_buffer_size] = {0};
uint16_t dev4_array_start = 0;
uint16_t dev4_array_end = 0;
uint16_t dev4_send_flag = 0;
uint8_t dev4_uart_rxData;

using namespace std;

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
  MX_USART3_UART_Init();			// SKYLA2
  MX_UART4_Init();					// CREED1
  MX_UART5_Init();					// CREED2
  MX_USART6_UART_Init();			// SKYLA1

  HAL_UART_Receive_IT(&huart1, &pi_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart3, &dev2_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart4, &dev3_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart5, &dev4_uart_rxData, 1);
  HAL_UART_Receive_IT(&huart6, &dev1_uart_rxData, 1);
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
		switch (pi_uart_rxData)	{
			case SETMODE_MOLLY_DEV1:
				application_state = MOLLY_DEV1;
				break;
			case SETMODE_MOLLY_DEV2:
				application_state = MOLLY_DEV2;
				break;
			case SETMODE_PROGRAM_DEV1:
				application_state = PROGRAM_DEV1;
				break;
			case SETMODE_PROGRAM_DEV2:
				application_state = PROGRAM_DEV2;
				break;
			case SETMODE_PROGRAM_DEV3:
				application_state = PROGRAM_DEV3;
				break;
			case SETMODE_PROGRAM_DEV4:
				application_state = PROGRAM_DEV4;
				break;
			case SETMODE_SENS_SELECT:
				application_state = SEN_SELECT;
				break;
			case SETMODE_SET_CHG_STATE:
				application_state = SET_CHG_STATE;
				break;
			case SETMODE_SET_DEV_PWR:
				application_state = SET_DEV_PWR;
				break;
		}
		pi_array_end = (pi_array_end+1)%pi_buffer_size;
		HAL_UART_Receive_IT(&huart1, &pi_uart_rxData, 1);
	}
	else if(huart->Instance == USART3)
	{
		dev1_uart_rxBuffer[dev1_array_end] = dev1_uart_rxData;
		if(dev1_uart_rxData == '\n' || dev1_uart_rxData == '\r')
			dev1_send_flag = dev1_array_end;
		dev1_new_data = 1;
		dev1_array_end = (dev1_array_end+1)%dev1_uart_buffer_size;
		HAL_UART_Receive_IT(&huart3, &dev1_uart_rxData, 1);
	}
	else if(huart->Instance == UART4)
	{
		dev3_uart_rxBuffer[dev3_array_end] = dev3_uart_rxData;
		if(dev3_uart_rxData == '\n' || dev3_uart_rxData == '\r')
			dev3_send_flag = dev3_array_end;
		dev3_array_end = (dev3_array_end+1)%dev3_uart_buffer_size;
		HAL_UART_Receive_IT(&huart4, &dev3_uart_rxData, 1);
	}
	else if(huart->Instance == UART5)
	{
		dev2_uart_rxBuffer[dev2_array_end] = dev2_uart_rxData;
		if(dev2_uart_rxData == '\n' || dev2_uart_rxData == '\r')
			dev2_send_flag = dev2_array_end;
		dev2_new_data = 1;
		dev2_array_end = (dev2_array_end+1)%dev2_uart_buffer_size;
		HAL_UART_Receive_IT(&huart5, &dev2_uart_rxData, 1);
	}
	else if(huart->Instance == USART6)
	{
		dev4_uart_rxBuffer[dev4_array_end] = dev4_uart_rxData;
		if(dev4_uart_rxData == '\n' || dev4_uart_rxData == '\r')
			dev4_send_flag = dev4_array_end;
		dev4_array_end = (dev4_array_end+1)%dev4_uart_buffer_size;
		HAL_UART_Receive_IT(&huart6, &dev4_uart_rxData, 1);
	}
}

uint8_t Get_Application_State(void)
{
	return application_state;
}

uint8_t Dev1_DataReady(void)
{
	return dev1_new_data;
}

uint8_t Dev2_DataReady(void)
{
	return dev2_new_data;
}

uint8_t Dev1_GetData(uint16_t head_subtracter)
{
	dev1_new_data = 0;
	return dev1_uart_rxBuffer[(dev1_uart_buffer_size-1-head_subtracter+dev1_array_end)%dev1_uart_buffer_size];
}

uint8_t Dev2_GetData(uint16_t head_subtracter)
{
	dev2_new_data = 0;
	return dev2_uart_rxBuffer[(dev2_uart_buffer_size-1-head_subtracter+dev2_array_end)%dev2_uart_buffer_size];
}

uint8_t Dev1_Find_Word(char* word)
{
	if(Dev1_DataReady())
	{
		uint16_t word_length = strlen(word);
		char current_word[255] = {0};
		for(uint16_t i = 0; i<word_length; i++)
			current_word[word_length-1-i] = Dev1_GetData(i);

		if(strcmp(current_word, word) == 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

uint8_t Dev2_Find_Word(char* word)
{
	if(Dev2_DataReady())
	{
		uint16_t word_length = strlen(word);
		char current_word[255] = {0};
		for(uint16_t i = 0; i<word_length; i++)
			current_word[word_length-1-i] = Dev2_GetData(i);

		if(strcmp(current_word, word) == 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

uint8_t * Dev1_GetInfo(void)
{
	if(Dev1_DataReady())
	{
		if(getinfo_find_fields)
		{
			char curr_char = Dev1_GetData(0);
			getinfo_buffer[getinfo_buffer_head] = curr_char;
			getinfo_buffer_head += 1;

			if(curr_char == '|')
				getinfo_fields_found_count += 1;

			if(getinfo_fields_found_count == num_machine_readable_fields)
				getinfo_buffer[0] = '1';
		}
		else
		{
			if(Dev1_Find_Word("1."))
			{
				getinfo_buffer[1] = '.';
				getinfo_buffer_head = getinfo_buffer_head + 1;
				getinfo_find_fields = 1;
			}
		}
	}
	return getinfo_buffer;
}

uint8_t * Dev2_GetInfo(void)
{
	if(Dev2_DataReady())
	{
		if(getinfo_find_fields)
		{
			char curr_char = Dev2_GetData(0);
			getinfo_buffer[getinfo_buffer_head] = curr_char;
			getinfo_buffer_head += 1;

			if(curr_char == '|')
				getinfo_fields_found_count += 1;

			if(getinfo_fields_found_count == num_machine_readable_fields)
				getinfo_buffer[0] = '1';
		}
		else
		{
			if(Dev2_Find_Word("1."))
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

void Power_Cycle_Dev(uint8_t dev = BOTH)
{
	printf("Power cycling devices\n");
	Power_Dev_OFF(dev);
	printf("Waiting for 30 seconds...\n");
	for (int i = 0; i > 30; i += 2)
	{
		HAL_Delay(2000);
		printf("%d/30secs\r", i);
	}
	Power_Dev_ON(dev);
}

bool Dev_Restarted(uint16_t dev_send_flag, uint16_t dev_array_start, uint8_t timeout = 30)
{
	uint32_t time_start = HAL_GetTick();

	while (dev_send_flag == dev_array_start)
	{
		uint32_t time_elapsed = (time_start - HAL_GetTick());
		printf("Waiting for device to startup. Time elapsed: %d\n", time_elapsed);

		if (time_elapsed >= (timeout * 1000))
		{
			return false;
		}

		HAL_Delay(1000);
	}

	return true;
}

void Dev1_Molly_App(void)
{
	switch(molly_dev1_state)
	{
		case FIND_DEBUG:
			if(Dev1_Find_Word("DEBUG"))
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"L|Found debug\n", 14, 1000);
				HAL_UART_Transmit(&huart3, (uint8_t*)"DEBUG", 5, 1000);
				molly_dev1_state = GET_SETTINGS;
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
			molly_dev1_state = GET_MSG_P1;
			break;

		case GET_MSG_P1:
			if(Dev1_Find_Word("NACK"))
			{
				memset(getinfo_buffer, 0, getinfo_buffer_size);
				getinfo_buffer_head = 1;
				getinfo_fields_found_count = 0;
				getinfo_find_fields = 0;
				HAL_UART_Transmit(&huart3, (uint8_t*)"#", 1, 500);
				molly_dev1_state = GET_MSG_P2;
			}
			break;

		case GET_MSG_P2:
			brd_msg = Dev1_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 1, 1);
				molly_dev1_state = MOLLY_P1;
			}
			break;

		case MOLLY_P1:
			{
				if(Dev1_Find_Word("N"))
				{
					dev1_new_data = 0;
				}
				char strC[500];
				char * settings_char = "$$";
				strncpy(strC, settings_char, 1);
				strC[1] = '\0';
				strcat(strC, (char*)payload);
				HAL_UART_Transmit(&huart3, (uint8_t*) strC, strlen(strC), 50);
				molly_dev1_state = MOLLY_P2;
				break;
			}

		case MOLLY_P2:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| in molly \n", 13, 500);
			while(1)
			{
				if(Dev1_Find_Word(":"))
				{
					char * curr_string = (char*)&dev1_uart_rxBuffer[dev1_array_start+1];
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
						molly_dev1_state = GET_MSG_P3;
						break;
					}
					else if(find_fail != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD FAIL!!! \n", 18, 500);
						molly_dev1_state = FINISH_MOLLY;
						break;
					}
					dev1_array_start = dev1_array_end;
				}
			}
			break;

		case GET_MSG_P3:
			brd_msg = Dev1_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 1, 0);
				molly_dev1_state = FINISH_MOLLY;
			}
			break;

		case FINISH_MOLLY:
			HAL_GPIO_WritePin(DEV1_3_UART_RX_EN, GPIO_PIN_RESET);
			HAL_UART_Transmit(&huart1, (uint8_t*)"molly complete \r\n", 17, 1000);

			Power_Cycle_Dev(NODE1);
			while(!(Dev_Restarted(dev1_send_flag, dev1_array_start)))
			{
			}

			molly_dev1_state = DEFAULT;
			application_state = MONITOR;
			break;

		default:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| Received molly command. \r\n", 29, 1000);
			HAL_GPIO_WritePin(DEV1_3_UART_RX_EN, GPIO_PIN_SET);
			molly_dev1_state = FIND_DEBUG;
			break;
	}
}

void Dev2_Molly_App(void)
{
	switch(molly_dev2_state)
	{
		case FIND_DEBUG:
			if(Dev2_Find_Word("DEBUG"))
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"L|Found debug\n", 14, 1000);
				HAL_UART_Transmit(&huart5, (uint8_t*)"DEBUG", 5, 1000);
				molly_dev2_state = GET_SETTINGS;
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
			molly_dev2_state = GET_MSG_P1;
			break;

		case GET_MSG_P1:
			if(Dev2_Find_Word("NACK"))
			{
				memset(getinfo_buffer, 0, getinfo_buffer_size);
				getinfo_buffer_head = 1;
				getinfo_fields_found_count = 0;
				getinfo_find_fields = 0;
				HAL_UART_Transmit(&huart5, (uint8_t*)"#", 1, 500);
				molly_dev2_state = GET_MSG_P2;
			}
			break;

		case GET_MSG_P2:
			brd_msg = Dev2_GetInfo();
			if(brd_msg[0] == '1')
			{
				PrettySend_Skyla_Info_toPi(brd_msg, 2, 1);
				molly_dev2_state = MOLLY_P1;
			}
			break;

		case MOLLY_P1:
			{
				if(Dev2_Find_Word("N"))
				{
					dev1_new_data = 0;
				}

				char strC[500];
				char * settings_char = "$$";
				strncpy(strC, settings_char, 1);
				strC[1] = '\0';
				strcat(strC, (char*)payload);
				HAL_UART_Transmit(&huart5, (uint8_t*) strC, strlen(strC), 50);
				molly_dev2_state = MOLLY_P2;
				break;
			}


		case MOLLY_P2:
			HAL_UART_Transmit(&huart1, (uint8_t*)"L| in molly \n", 13, 500);
			while(1)
			{
				if(Dev2_Find_Word(":"))
				{
					char * curr_string = (char*)&dev2_uart_rxBuffer[dev2_array_start+1];
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
						molly_dev2_state = GET_MSG_P3;
						break;
					}
					else if(find_fail != NULL)
					{
						HAL_UART_Transmit(&huart1, (uint8_t*)"L| BOARD FAIL!!! \n", 18, 500);
						molly_dev2_state = FINISH_MOLLY;
						break;
					}
					dev2_array_start = dev2_array_end;
				}
			}
			break;

		case GET_MSG_P3:
			{
				brd_msg = Dev2_GetInfo();
				if(brd_msg[0] == '1')
				{
					PrettySend_Skyla_Info_toPi(brd_msg, 2, 0);
					molly_dev2_state = FINISH_MOLLY;
				}
				break;
			}


		case FINISH_MOLLY:
			{
				HAL_GPIO_WritePin(DEV2_4_UART_RX_EN, GPIO_PIN_RESET);
				HAL_UART_Transmit(&huart1, (uint8_t*)"molly complete \r\n", 17, 1000);
				Power_Cycle_Dev(NODE2);
				while(!(Dev_Restarted(dev2_send_flag, dev2_array_start)))
				{
				}

				molly_dev2_state = DEFAULT;
				application_state = MONITOR;
				break;
			}
		default:
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"L| Received molly command. \r\n", 29, 1000);
				HAL_GPIO_WritePin(DEV2_4_UART_RX_EN, GPIO_PIN_SET);
				molly_dev2_state = FIND_DEBUG;
				break;
			}

	}
}



/******************************************************************************
* Function:    	vector<char> Get_Pi_UART_Data_Last(int num_data = 1)
* Description: 	Returns the last number of data characters from the Pi
* Parameters:  	Number of data char requested
* Returns:     	vector<char> array of last num_data data char from Pi. Returned
*				in received order
******************************************************************************/

vector<char> Get_Pi_UART_Data_Last(uint16_t num_data = 1)
{
	vector<char> pi_selected_data = {};

	for(int i = 0; i < num_data; i++)
	{
		uint16_t arr_data_index = pi_array_end;
		(pi_array_end < i) ? arr_data_index = pi_buffer_size - (i - pi_array_end) : arr_data_index -= i;
		pi_selected_data[i] = pi_uart_rxBuffer[arr_data_index];
	}

	return pi_selected_data;
}

void Reset_Programmer_Relay(void)
{
	HAL_GPIO_WritePin(DEV1_3_VCC_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DEV2_4_VCC_EN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(DEV1_UPDI_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DEV2_UPDI_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DEV3_UPDI_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DEV4_UPDI_EN, GPIO_PIN_RESET);
}

//Dev1 Program
void Dev1_Program_App(void)
{
	switch(program_dev1_state)
	{
		case FINISH_PROGRAM:
			//reset relays 
			HAL_GPIO_WritePin(DEV1_3_VCC_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV1_UPDI_EN, GPIO_PIN_RESET);

			program_dev1_state = DEFAULT;
			application_state = MONITOR;
			break;
		default:
			Reset_Programmer_Relay();
			HAL_GPIO_WritePin(DEV1_3_VCC_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV1_UPDI_EN, GPIO_PIN_SET);

			HAL_UART_Transmit(&huart1, (uint8_t*)"Ready to program Sklya1\r\n", 25, 1000);
			HAL_Delay(100);
			
			while(pi_uart_rxData != PI_PROCESS_FIN)
			{
			}
			
			program_dev1_state = FINISH_PROGRAM;
			break;
	}
}

void Dev2_Program_App(void)
{
	switch(program_dev2_state)
	{
		case FINISH_PROGRAM:
			//reset relays 
			HAL_GPIO_WritePin(DEV2_4_VCC_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV2_UPDI_EN, GPIO_PIN_RESET);

			program_dev2_state = DEFAULT;
			application_state = MONITOR;
			break;
		default:
			Reset_Programmer_Relay();
			HAL_GPIO_WritePin(DEV2_4_VCC_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV2_UPDI_EN, GPIO_PIN_SET);

			HAL_UART_Transmit(&huart1, (uint8_t*)"Ready to program Sklya2\r\n", 25, 1000);
			HAL_Delay(100);
			
			while(pi_uart_rxData != PI_PROCESS_FIN)
			{
			}
			
			program_dev2_state = FINISH_PROGRAM;
			break;
	}
}

void Dev3_Program_App(void)
{
	switch(program_dev3_state)
	{
		case FINISH_PROGRAM:
			//reset relays 
			HAL_GPIO_WritePin(DEV1_3_VCC_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV3_UPDI_EN, GPIO_PIN_RESET);

			program_dev3_state = DEFAULT;
			application_state = MONITOR;
			break;
		default:
			Reset_Programmer_Relay();
			HAL_GPIO_WritePin(DEV1_3_VCC_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV3_UPDI_EN, GPIO_PIN_SET);

			HAL_UART_Transmit(&huart1, (uint8_t*)"Ready to program Creed1\r\n", 25, 1000);
			HAL_Delay(100);
			
			while(pi_uart_rxData != PI_PROCESS_FIN)
			{
			}
			
			program_dev3_state = FINISH_PROGRAM;
			break;
	}
}

void Dev4_Program_App(void)
{
	switch(program_dev4_state)
	{
		case FINISH_PROGRAM:
			//reset relays 
			HAL_GPIO_WritePin(DEV2_4_VCC_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV4_UPDI_EN, GPIO_PIN_RESET);

			program_dev4_state = DEFAULT;
			application_state = MONITOR;
			break;
		default:
			Reset_Programmer_Relay();
			HAL_GPIO_WritePin(DEV2_4_VCC_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV4_UPDI_EN, GPIO_PIN_SET);

			HAL_UART_Transmit(&huart1, (uint8_t*)"Ready to program Creed2\r\n", 25, 1000);
			HAL_Delay(100);
			
			while(pi_uart_rxData != PI_PROCESS_FIN)
			{
			}
			
			program_dev4_state = FINISH_PROGRAM;
			break;
	}
}





void Set_Device_Power_App(void)
{
	vector<char> data = Get_Pi_UART_Data_Last(2);
	uint8_t dev = (uint8_t) data[0];
	uint8_t state = (uint8_t) data[1];

	switch(state)
	{
		case ON:
			Power_Dev_ON(dev);
			break;
	
		case OFF:
			Power_Dev_OFF(dev);
			break;

		case CYCLE:
			Power_Cycle_Dev(dev);
			break;

		default:
			printf("Invalid state selected\n");
			break;
	}

	HAL_UART_Transmit(&huart1, (uint8_t*)"Power State Set \n", 17, 500);
	application_state = DEFAULT;
}

void Power_Dev_OFF(uint8_t dev)
{
	switch(dev)
	{
		case BOTH:
			Power_Dev_OFF(NODE1);
			Power_Dev_OFF(NODE2);
			break;
		case NODE1:
			printf("Powering off Node1\n");
			HAL_GPIO_WritePin(DEV1_3_SEN_PWR ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV1_3_UART_RX_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV1_3_LTCH_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV1_PWR_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV3_PWR_EN ,GPIO_PIN_RESET);
			break;
		case NODE2:
			printf("Powering off Node2\n");
			HAL_GPIO_WritePin(DEV2_4_SEN_PWR ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV2_4_UART_RX_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV2_4_LTCH_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV2_PWR_EN ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV4_PWR_EN ,GPIO_PIN_RESET);
			break;
		default:
			printf("Invalid node selected\n");
			break;
	}
}

void Power_Dev_ON(uint8_t dev)
{
	switch(dev)
	{
		case BOTH:
			Power_Dev_OFF(NODE1);
			Power_Dev_OFF(NODE2);
			break;
		case NODE1:
			{
				HAL_GPIO_WritePin(DEV1_3_SEN_PWR, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV1_3_UART_RX_EN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV1_3_LTCH_EN ,GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV1_PWR_EN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV3_PWR_EN, GPIO_PIN_SET);
				bool dev1_on = false;
				dev1_on = Dev_Restarted(dev1_send_flag, dev1_array_start);
				if(dev1_on)
				{
					HAL_UART_Transmit(&huart1, (uint8_t*)"Dev1 ON\n", 8, 500);
				}
				break;
			}

		case NODE2:
			{
				HAL_GPIO_WritePin(DEV2_4_SEN_PWR, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV2_4_UART_RX_EN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV2_4_LTCH_EN ,GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV2_PWR_EN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(DEV4_PWR_EN, GPIO_PIN_SET);
				bool dev2_on = false;
				dev2_on = Dev_Restarted(dev2_send_flag, dev2_array_start);
				if(dev2_on)
				{
					HAL_UART_Transmit(&huart2, (uint8_t*)"Dev2 ON\n", 8, 500);
				}
				break;
			}

		default:
			{
				printf("Invalid node selected\n");
				break;
			}
	}
}


void Set_Sensor(uint8_t node = BOTH, uint8_t selected_sensor = 0)
{
	if (selected_sensor > (NUM_SENS_AVAILABLE-1))
	{
		printf("Invalid Sensor Selected\n");
		return;
	}

	string sensorName[NUM_SENS_AVAILABLE] = {
	    "TMP107",
	    "3x TMP107",
	    "DS18B20",
	    "SHT30"
	};

	switch(node)
	{
		case BOTH:
			Set_Sensor(NODE1, selected_sensor);
			Set_Sensor(NODE2, selected_sensor);
			break;
		case NODE1:
			HAL_GPIO_WritePin(DEV1_3_LTCH_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV1_3_MUX_INH, GPIO_PIN_RESET);

			Power_Dev_OFF(NODE1);

			HAL_GPIO_WritePin(DEV1_3_SEL_A, SENS_SEL_A_STATE(selected_sensor));
			HAL_GPIO_WritePin(DEV1_3_SEL_B, SENS_SEL_B_STATE(selected_sensor));
			HAL_GPIO_WritePin(DEV1_3_SEL_C, SENS_SEL_C_STATE(selected_sensor));

			printf("Node 1 %s sensor selected\n", sensorName[selected_sensor]);

			HAL_GPIO_WritePin(DEV1_3_LTCH_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV1_3_MUX_INH, GPIO_PIN_SET);
			break;
		case NODE2:
			HAL_GPIO_WritePin(DEV2_4_LTCH_EN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DEV2_4_MUX_INH, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(DEV2_4_SEL_A, SENS_SEL_A_STATE(selected_sensor));
			HAL_GPIO_WritePin(DEV2_4_SEL_B, SENS_SEL_B_STATE(selected_sensor));
			HAL_GPIO_WritePin(DEV2_4_SEL_C, SENS_SEL_C_STATE(selected_sensor));

			printf("Node 2 %s sensor selected\n", sensorName[selected_sensor]);

			HAL_GPIO_WritePin(DEV2_4_LTCH_EN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DEV2_4_MUX_INH, GPIO_PIN_SET);
			break;
		default:
			printf("Invalid Node Selected\n");
			break;
	}
}

void Sensor_Select_App(void)
{
	vector<char> data = Get_Pi_UART_Data_Last(2);
	char node = (uint8_t) data[0];
	char sens_num = (uint8_t) data[1];

	Set_Sensor(node, sens_num);

	application_state = DEFAULT;
}

void Set_Charger_State(int node = BOTH, bool charger_state = true)
{
	switch(node)
	{
		case BOTH:
			Set_Charger_State(NODE1, charger_state);
			Set_Charger_State(NODE2, charger_state);
		case NODE1:
			HAL_GPIO_WritePin(DEV1_CHG_EN, (GPIO_PinState)charger_state);
		case NODE2:
			HAL_GPIO_WritePin(DEV1_CHG_EN, (GPIO_PinState)charger_state);
		default:
			printf("Invalid device selected");
	}	
}


void Set_Charger_App(void)
{
	vector<char> data = Get_Pi_UART_Data_Last(2);
	char node = (uint8_t) data[0];
	char chg_state = (uint8_t) data[1];

	Set_Charger_State(node, chg_state);

	application_state = DEFAULT;
}


void Dev1_Check_Flag(void)
{
	if(dev1_send_flag != dev1_array_start){
		uint16_t num_bytes;
		if(dev1_send_flag > dev1_array_start){
			num_bytes = dev1_send_flag - dev1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS1|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev1_uart_rxBuffer[dev1_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = dev1_uart_buffer_size - dev1_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS1|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev1_uart_rxBuffer[dev1_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &dev1_uart_rxBuffer[0], dev1_send_flag, 500);
		}
		dev1_array_start = dev1_send_flag;
	}
}

void Dev3_Check_Flag(void)
{
	if(dev3_send_flag != dev3_array_start){
		uint16_t num_bytes;
		if(dev3_send_flag > dev3_array_start){
			num_bytes = dev3_send_flag - dev3_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC1|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev3_uart_rxBuffer[dev3_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = dev3_uart_buffer_size - dev3_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC1|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev3_uart_rxBuffer[dev3_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &dev3_uart_rxBuffer[0], dev3_send_flag, 500);
		}
		dev3_array_start = dev3_send_flag;
	}
}

void Dev2_Check_Flag(void)
{
	if(dev2_send_flag != dev2_array_start){
		uint16_t num_bytes;
		if(dev2_send_flag > dev2_array_start){
			num_bytes = dev2_send_flag - dev2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS2|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev2_uart_rxBuffer[dev2_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = dev2_uart_buffer_size - dev2_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nS2|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev2_uart_rxBuffer[dev2_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &dev2_uart_rxBuffer[0], dev2_send_flag, 500);
		}
		dev2_array_start = dev2_send_flag;
	}
}

void Dev4_Check_Flag(void)
{
	if(dev4_send_flag != dev4_array_start){
		uint16_t num_bytes;
		if(dev4_send_flag > dev4_array_start){
			num_bytes = dev4_send_flag - dev4_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC2|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev4_uart_rxBuffer[dev4_array_start+1], num_bytes, 500);
		}
		else
		{
			num_bytes = dev4_uart_buffer_size - dev4_array_start;
			HAL_UART_Transmit(&huart1, (uint8_t*)"\nC2|", 4, 500);
			HAL_UART_Transmit(&huart1, &dev4_uart_rxBuffer[dev4_array_start+1], num_bytes, 500);
			HAL_UART_Transmit(&huart1, &dev4_uart_rxBuffer[0], dev4_send_flag, 500);
		}
		dev4_array_start = dev4_send_flag;
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
