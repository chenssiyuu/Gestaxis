#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	    //ʹ��PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			    //LED0-->PA.10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);			     //��ʼ��GPIOA.10
  GPIO_SetBits(GPIOC,GPIO_Pin_13);					//PB.5 �����
}

void Control_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	    //ʹ��PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;			    //LED0-->PA.10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);			     //��ʼ��GPIOA.10
  GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);					//PB.5 �����
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //ʹ��PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6;			    //LED0-->PA.10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA.10
  GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_6);					//PB.5 �����
}

void Sensor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //ʹ��PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			    //LED0-->PA.10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA.10
}

void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //ʹ��PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;			    //LED0-->PA.10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA.10
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);					//PB.5 �����
}

