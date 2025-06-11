#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

extern u8 USART3_RX_BUF[300];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART3_RX_STA;       //����״̬���	

extern char USART_ReceiveString[50];
extern int Receive_sum;	
extern char USART2_ReceiveString[50];													//����PC�˷��͹������ַ�
extern int Receive_Flag_2;															//������Ϣ��־λ
extern int Receive_sum_2;	
extern char USART3_ReceiveString[256];													//����PC�˷��͹������ַ�
extern int Receive_sum_3;

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

void USART1_Reflash(void);//����1��0��ʼ���½�������
void USART2_Reflash(void);//����2��0��ʼ���½�������
void USART3_Reflash(void);//����3��0��ʼ���½�������
#endif


