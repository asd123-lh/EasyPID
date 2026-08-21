#ifndef __SEVENWAY_H__
#define __SEVENWAY_H__
#include "main.h"
extern volatile int error;
extern volatile uint8_t line_data;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void errordo(void);
void SevenWay_UART_Init(void);

#endif
