#include "sevenway.h"
#include "usart.h"

uint8_t send[2] = {0x57, 0x01};
uint8_t back[3];
uint8_t data;
volatile int error = 0;
volatile uint8_t line_data = 0;
static const int weight[7] = {-10, -6, -3, 0, 3, 6, 10};

static int SevenWay_CalcErrorByBits(uint8_t value)
{
	int sum = 0;
	int count = 0;
	uint8_t bit_buf = value & 0x7F;

	for(int i = 0; i < 7; i++)
	{
		if((bit_buf & (1 << i)) == 0)
		{
			sum += weight[i];
			count++;
		}
	}

	if(count == 0)
	{
		return 0;
	}

	if(count >= 6)
	{
		return 0;
	}

	return sum / count;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart != &huart2)
	{
		return;
	}

	if (back[0] == 0x75 && back[2] == 0x02)
	{
		data = back[1];
		line_data = data;
		errordo();  
	}

	HAL_UART_Transmit_IT(&huart2, send, 2);
	HAL_UART_Receive_IT(&huart2, back, 3);
}

void errordo(void)
{
	int temp_err = 0;  
	switch (data)
	{
	case 0x7E:
		temp_err = -10;
		break; // 111 1110
	case 0x7C:
		temp_err = -9;
		break; // 111 1100
	case 0x78:
		temp_err = -5;
		break; // 111 1000
	case 0x79:
		temp_err = -4;
		break; // 111 1001
	case 0x71:
		temp_err = -2;
		break; // 111 0001
	case 0x73:
		temp_err = -1;
		break; // 111 0011
	case 0x63:
		temp_err = 0;
		break; // 110 0011
	case 0x77:
		temp_err = 0;
		break; // 111 0111
	case 0x67:
		temp_err = 1;
		break; // 110 0111
	case 0x47:
		temp_err = 2;
		break; // 100 0111
	case 0x4F:
		temp_err = 4;
		break; // 100 1111
	case 0x0F:
		temp_err = 5;
		break; // 000 1111
	case 0x07:
		temp_err = 9;
		break; // 000 0111
	case 0x03:
		temp_err = 10;
		break; // 000 0011
	case 0x1F:
		temp_err = 9;
		break; // 001 1111
	case 0x3F:
		temp_err = 10;
		break; // 011 1111
	case 0x7F:
		temp_err = 0;
		break;
	default:
		temp_err = SevenWay_CalcErrorByBits(data);
		break;
	}
	error = temp_err * 40;
}

void SevenWay_UART_Init(void)
{
    HAL_UART_Transmit_IT(&huart2, send, 2);
    HAL_UART_Receive_IT(&huart2, back, 3);
}

