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



u16 LED_NUM = 0;//偶数为关灯状态，奇数为开灯状态
void uart1_init(u32 bound)
{
    //GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟以及复用功能时钟
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}

void uart2_init(u32 bound)
{
    //GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟以及复用功能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟以及复用功能时钟
     //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
		USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启中断
    USART_Cmd(USART2, ENABLE);                    //使能串口 

}

void uart3_init(u32 bound)
{
    //GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART1，GPIOA时钟以及复用功能时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟以及复用功能时钟
	
     //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart1 NVIC 配置

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启中断
    USART_Cmd(USART3, ENABLE);                    //使能串口 

}

char USART_ReceiveString[50];													//接收PC端发送过来的字符
int Receive_Flag = 0;															//接收消息标志位
int Receive_sum = 0;	

void USART1_IRQHandler(void)
{
		///////////屏幕串口中断接收数据程序////////////////
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)							//是否接收到了一个数据（一个字节）
	{			
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);							//接收后先清空标志位,下一次有数据进来才能接收
			USART_ReceiveString[Receive_sum] = USART_ReceiveData(USART1);		//通过USART1串口接收字符
			Receive_sum++;														//数组下标++
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)							//是否接收到了一帧数据（多个字节）
	{		
			USART1->SR;
		  USART1->DR;//先SR再DR，清除IDLE中断

			USART1_Use();		//接收屏幕串口回复数据
		
		  USART1_Reflash();
	}
		///////////////////////////////////////////////////
} 

void USART1_Reflash(void)//串口1从0开始重新接收数据
{
	for(int i = 0;i<20;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum = 0;
}
	
char USART2_ReceiveString[50];													//接收PC端发送过来的字符
int Receive_Flag_2 = 0;															//接收消息标志位
int Receive_sum_2 = 0;	

void USART2_IRQHandler(void)
{
		///////////基础串口中断接收数据程序////////////////
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)							//是否接收到了一个数据（一个字节）
	{			
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);							//接收后先清空标志位,下一次有数据进来才能接收
			USART2_ReceiveString[Receive_sum_2] = USART_ReceiveData(USART2);		//通过USART1串口接收字符
			Receive_sum_2++;														//数组下标++
	}
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)							//是否接收到了一帧数据（多个字节）
	{		
			USART2->SR;
		  USART2->DR;//先SR再DR，清除IDLE中断
			
			
		
		  USART2_Reflash();
	}
		///////////////////////////////////////////////////

}

void USART2_Reflash(void)//串口1从0开始重新接收数据
{
	for(int i = 0;i<20;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum_2 = 0;
}


char USART3_ReceiveString[256];													//接收PC端发送过来的字符
int Receive_Flag_3 = 0;															//接收消息标志位
int Receive_sum_3 = 0;	

void USART3_IRQHandler(void)                	//串口1中断服务程序
	{
		if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)							//是否接收到了一个数据（一个字节）
			{			
					USART_ClearITPendingBit(USART3,USART_IT_RXNE);							//接收后先清空标志位,下一次有数据进来才能接收
					USART3_ReceiveString[Receive_sum_3] = USART_ReceiveData(USART3);		//通过USART1串口接收字符
					Receive_sum_3++;														//数组下标++
			}
			if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET)							//是否接收到了一帧数据（多个字节）
			{		
					USART3->SR;
					USART3->DR;//先SR再DR，清除IDLE中断
				

				  USART3_Reflash();
			}

}

void USART3_Reflash(void)//串口1从0开始重新接收数据
{
	for(int i = 0;i<256;i++)
	{
		USART_ReceiveString[i] = 0;
	}
	Receive_sum_3 = 0;
}
