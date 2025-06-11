#ifndef _usart_use_
#define _usart_use_

#include "stm32f10x.h"
#include "usart.h"

void uart_3_use(void);

void USART_SendString(USART_TypeDef* USARTx, char DataString[]);
void USART_SendHEX(USART_TypeDef* USARTx, char DataString[],int NUM);

void USART1_Use(void);

#endif
