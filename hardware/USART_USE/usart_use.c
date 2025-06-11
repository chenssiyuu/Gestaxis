#include "usart_use.h"
#include "led.h"
#include "delay.h"
#include "string.h"
#include "usart.h"


char product_1[56] = {0x7E,0x05,0x41,0x00,0x01,0x45,0xEF,
                      0x7E,0x05,0x41,0x00,0x02,0x46,0xEF,
                      0x7E,0x05,0x41,0x00,0x03,0x47,0xEF,
                      0x7E,0x05,0x41,0x00,0x04,0x40,0xEF,
                      0x7E,0x05,0x41,0x00,0x05,0x41,0xEF,
                      0x7E,0x05,0x41,0x00,0x06,0x42,0xEF,
											0x7E,0x05,0x41,0x00,0x07,0x43,0xEF,
											0x7E,0x05,0x41,0x00,0x08,0x4C,0xEF};

extern u8 cnt[];
extern u8 pre_position;
extern u8 current_position;
											
void small_motor_start(void)
{
	if(current_position == 1)
	{
		control_1 = 1;
		control_2 = 0;
		control_3 = 0;
		control_4 = 0;
		control_5 = 0;
	}
	else if(current_position == 2)
	{
		control_1 = 0;
		control_2 = 1;
		control_3 = 0;
		control_4 = 0;
		control_5 = 0;
	}
	else if(current_position == 3)
	{
		control_1 = 0;
		control_2 = 0;
		control_3 = 1;
		control_4 = 0;
		control_5 = 0;
	}
	else if(current_position == 4)
	{
		control_1 = 0;
		control_2 = 0;
		control_3 = 0;
		control_4 = 1;
		control_5 = 0;
	}
	else if(current_position == 5)
	{
		control_1 = 0;
		control_2 = 0;
		control_3 = 0;
		control_4 = 0;
		control_5 = 5;
	}
}

void motor_start(void)
{
		if(current_position>pre_position)
		{
			control_1 = 0;
			control_2 = 0;
			control_3 = 0;
			control_4 = 0;
			control_5 = 0;
			IN1 = 0;
			IN2 = 1;//电机开始正转
			delay_ms(500);
			for(u8 i = (current_position-pre_position) ; i>0 ; i--)
			{
				while(sensor);
				delay_ms(500);
			}
			IN1 = 1;
			IN2 = 1;//电机停止
			small_motor_start();
		}
		else if(current_position<pre_position)
		{
			control_1 = 0;
			control_2 = 0;
			control_3 = 0;
			control_4 = 0;
			control_5 = 0;
			IN1 = 1;
			IN2 = 0;//电机开始反转
			delay_ms(500);
			for(u8 i = (pre_position-current_position) ; i>0 ; i--)
			{
				while(sensor);
				delay_ms(500);
			}
			IN1 = 1;
			IN2 = 1;//电机停止
			small_motor_start();
		}
}

void USART_SendString(USART_TypeDef* USARTx, char DataString[])
{
	long i = 0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);										//发送字符前清空标志位（否则缺失字符串的第一个字符）
	while(DataString[i] != '\0')												//字符串结束符
	{
		USART_SendData(USARTx,DataString[i]);									//每次发送字符串的一个字符
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);					//等待数据发送成功
//		USART_ClearFlag(USARTx,USART_FLAG_TC);									//发送字符后清空标志位
		i++;
	}
}


void USART_SendHEX(USART_TypeDef* USARTx, char DataString[],int NUM)
{
	int i = 0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);										//发送字符前清空标志位（否则缺失字符串的第一个字符）
	for(i=0;i<NUM;i++)
	{
		USART_SendData(USARTx,DataString[i]);									//每次发送字符串的一个字符
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);					//等待数据发送成功
//		USART_ClearFlag(USARTx,USART_FLAG_TC);									//发送字符后清空标志位
	}
}


extern u8 voice_flag;		//语音开关状态，0-关，1-开
extern char MQTTPUB[256];//mqtt.c
void USART1_Use(void)
{
		for(int i = 0; i < 20; i++)
		{		
			if((USART_ReceiveString[0] == 0x5A) && (USART_ReceiveString[1] == 0xA5) && (USART_ReceiveString[2] == 0x06) && (USART_ReceiveString[3] == 0x83) && (USART_ReceiveString[4] == 0x10))			
			{
				/*********************当前显示页面***********************/
				/**************5A A5 06 83 10 50 01 00 03***************/
				if(USART_ReceiveString[5] == 0x50)
				{
						if(USART_ReceiveString[8] != 0x00)		
						{	
								current_position = USART_ReceiveString[i+8];		//读取当前页面
								if(current_position!=pre_position)
								{
									motor_start();
									cnt[current_position-1]++;
									pre_position = current_position;
									if(voice_flag ==1)
									{
										USART_SendHEX(USART2,&product_1[(pre_position-1)*7],7);	
									}
								}
						}		
						MQTTPUB[86] = current_position + '0';		//当前展位
				}
				/*********************语音开关状态***********************/
				/**************5A A5 06 83 10 40 01 00 01***************/
				else if(USART_ReceiveString[5] == 0x40)
				{
						if(USART_ReceiveString[8] == 0x00)		//语音开关-关
						{	
								voice_flag = 0;
						}		
						else if(USART_ReceiveString[8] == 0x01)		//语音开关-开
						{	
								voice_flag = 1;
						}
				}
					
				break;	
				
			}						
		}

}

