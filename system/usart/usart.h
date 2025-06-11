#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

extern u8 USART3_RX_BUF[300];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART3_RX_STA;       //接收状态标记	

extern char USART_ReceiveString[50];
extern int Receive_sum;	
extern char USART2_ReceiveString[50];													//接收PC端发送过来的字符
extern int Receive_Flag_2;															//接收消息标志位
extern int Receive_sum_2;	
extern char USART3_ReceiveString[256];													//接收PC端发送过来的字符
extern int Receive_sum_3;

//如果想串口中断接收，请不要注释以下宏定义
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

void USART1_Reflash(void);//串口1从0开始重新接收数据
void USART2_Reflash(void);//串口2从0开始重新接收数据
void USART3_Reflash(void);//串口3从0开始重新接收数据
#endif


