#include "sys.h"
#include "usart.h"	
#include "usart_use.h"
#include "delay.h"
#include "led.h"

char Disinfect_str[8]= {0x5A, 0xA5, 0x05 ,0x82,0x16,0x00,0x00,0x01};	
char Control[] = {0x01,0x02,0x03,0x04,0x05};
char write_led[8]={0x5A,0xA5,0x05,0x82,0x15,0x00,0x00,0x02};
char write_distection[8]={0x5A,0xA5,0x05,0x82,0x16,0x00,0x00,0x00};

char write_weather_0[8] = {0x5A, 0xA5, 0x05 ,0x82,0x10,0x00,0x00,0x00};	
char write_weather_1[8] = {0x5A, 0xA5, 0x05 ,0x82,0x10,0x00,0x00,0x01};	
char write_weather_2[8] = {0x5A, 0xA5, 0x05 ,0x82,0x10,0x00,0x00,0x02};

char write_weather_L_0[8] = {0x5A, 0xA5, 0x05 ,0x82,0x11,0x00,0x00,0x00};	
char write_weather_L_1[8] = {0x5A, 0xA5, 0x05 ,0x82,0x11,0x00,0x00,0x01};	
char write_weather_L_2[8] = {0x5A, 0xA5, 0x05 ,0x82,0x11,0x00,0x00,0x02};	



u16 LED_NUM = 0;//ż��Ϊ�ص�״̬������Ϊ����״̬
void uart1_init(u32 bound)
{
    //GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}

void uart2_init(u32 bound)
{
    //GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
     //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
		USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}

void uart3_init(u32 bound)
{
    //GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
	
     //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart1 NVIC ����

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

}

char USART_ReceiveString[50];													//����PC�˷��͹������ַ�
int Receive_Flag = 0;															//������Ϣ��־λ
int Receive_sum = 0;	

void USART1_IRQHandler(void)
{
		///////////��Ļ�����жϽ������ݳ���////////////////
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)							//�Ƿ���յ���һ�����ݣ�һ���ֽڣ�
	{			
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);							//���պ�����ձ�־λ,��һ�������ݽ������ܽ���
			USART_ReceiveString[Receive_sum] = USART_ReceiveData(USART1);		//ͨ��USART1���ڽ����ַ�
			Receive_sum++;														//�����±�++
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)							//�Ƿ���յ���һ֡���ݣ�����ֽڣ�
	{		
			USART1->SR;
		  USART1->DR;//��SR��DR�����IDLE�ж�

			USART1_Use();		//������Ļ���ڻظ�����
		
		  USART1_Reflash();
	}
		///////////////////////////////////////////////////
} 

void USART1_Reflash(void)//����1��0��ʼ���½�������
{
	for(int i = 0;i<20;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum = 0;
}
	
char USART2_ReceiveString[50];													//����PC�˷��͹������ַ�
int Receive_Flag_2 = 0;															//������Ϣ��־λ
int Receive_sum_2 = 0;	

void USART2_IRQHandler(void)
{
		///////////���������жϽ������ݳ���////////////////
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)							//�Ƿ���յ���һ�����ݣ�һ���ֽڣ�
	{			
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);							//���պ�����ձ�־λ,��һ�������ݽ������ܽ���
			USART2_ReceiveString[Receive_sum_2] = USART_ReceiveData(USART2);		//ͨ��USART1���ڽ����ַ�
			Receive_sum_2++;														//�����±�++
	}
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)							//�Ƿ���յ���һ֡���ݣ�����ֽڣ�
	{		
			USART2->SR;
		  USART2->DR;//��SR��DR�����IDLE�ж�
			
			
		
		  USART2_Reflash();
	}
		///////////////////////////////////////////////////

}

void USART2_Reflash(void)//����1��0��ʼ���½�������
{
	for(int i = 0;i<20;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum_2 = 0;
}


char USART3_ReceiveString[256];													//����PC�˷��͹������ַ�
int Receive_Flag_3 = 0;															//������Ϣ��־λ
int Receive_sum_3 = 0;	

void USART3_IRQHandler(void)                	//����1�жϷ������
	{
		if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)							//�Ƿ���յ���һ�����ݣ�һ���ֽڣ�
			{			
					USART_ClearITPendingBit(USART3,USART_IT_RXNE);							//���պ�����ձ�־λ,��һ�������ݽ������ܽ���
					USART3_ReceiveString[Receive_sum_3] = USART_ReceiveData(USART3);		//ͨ��USART1���ڽ����ַ�
					Receive_sum_3++;														//�����±�++
			}
			if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET)							//�Ƿ���յ���һ֡���ݣ�����ֽڣ�
			{		
					USART3->SR;
					USART3->DR;//��SR��DR�����IDLE�ж�
				

				  USART3_Reflash();
			}

}

void USART3_Reflash(void)//����1��0��ʼ���½�������
{
	for(int i = 0;i<256;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum_3 = 0;
}
