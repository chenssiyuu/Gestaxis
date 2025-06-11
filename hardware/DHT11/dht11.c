//dht11.c程序
#include "dht11.h"
#include "delay.h"
 
uint8_t dat[5]={0x00,0x00,0x00,0x00,0x00};
uint8_t sum=0;
 
//初始化为输出
void DHT11_GPIO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);		
}
//初始化为输入
void DHT11_GPIO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					
}
 
//读一个字节
uint8_t DHT_Read_Byte(void)
{
	uint8_t temp;
	uint8_t ReadDat=0;
	
	uint8_t retry = 0;	
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		//数据信号低电平50us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)
		{		
			delay_us(1);
			retry++;		
		}
		retry=0;
		delay_us(30);
		temp=0;//数字信号0，temp=0
		//数字0信号高电平持续28us，数字1信号高电平70us，延时30us以确认数字0或1
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1) temp=1;		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&retry<100)//数字1信号高电平剩余40us
		{		
			delay_us(1);
			retry++;
		}
		retry=0;
		ReadDat<<=1;
		ReadDat|=temp;
	}	
	return ReadDat;
}
 
uint8_t DHT_Read(void)
{
	uint8_t i;
	uint8_t retry = 0;
	
	//主机设置为输出，发送开始信号低电平18ms，高电平40us
	DHT11_GPIO_OUT();
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	delay_ms(18);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	delay_us(40);
	//主机设置为输入，检查并接收响应信号低电平80us，高电平80us
	DHT11_GPIO_IN();
	delay_us(20);
	//延时20us，低电平80us，还剩60us，检查是否是低电平以确定是否有响应信号
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	{
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)//接收响应信号低电平剩余60us
		{
			delay_us(1);
			retry++;			
		}
		retry=0;//超过100us自动向下运行，以免卡死
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&retry<100)//接收响应信号高电平80us
		{
			delay_us(1);
			retry++;			
		}
		retry=0;
		//接收8字节数据
		for(i=0;i<5;i++)
		{
			dat[i]=DHT_Read_Byte();
		}
		delay_us(50);//DHT11拉低总线50us作为结束信号，或者使用以下语句
				
//		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)//接收响应信号低电平剩余60us
//		{
//			SysTick_Delay_us(1);
//			retry++;			
//		}
//		retry=0;
		
	}
	sum=dat[0]+dat[1]+dat[2]+dat[3];
	if(dat[4]==sum)
	{
		return 1;
	}
	else
		return 0;
}
