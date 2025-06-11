//dht11.c����
#include "dht11.h"
#include "delay.h"
 
uint8_t dat[5]={0x00,0x00,0x00,0x00,0x00};
uint8_t sum=0;
 
//��ʼ��Ϊ���
void DHT11_GPIO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);		
}
//��ʼ��Ϊ����
void DHT11_GPIO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					
}
 
//��һ���ֽ�
uint8_t DHT_Read_Byte(void)
{
	uint8_t temp;
	uint8_t ReadDat=0;
	
	uint8_t retry = 0;	
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		//�����źŵ͵�ƽ50us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)
		{		
			delay_us(1);
			retry++;		
		}
		retry=0;
		delay_us(30);
		temp=0;//�����ź�0��temp=0
		//����0�źŸߵ�ƽ����28us������1�źŸߵ�ƽ70us����ʱ30us��ȷ������0��1
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1) temp=1;		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&retry<100)//����1�źŸߵ�ƽʣ��40us
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
	
	//��������Ϊ��������Ϳ�ʼ�źŵ͵�ƽ18ms���ߵ�ƽ40us
	DHT11_GPIO_OUT();
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	delay_ms(18);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	delay_us(40);
	//��������Ϊ���룬��鲢������Ӧ�źŵ͵�ƽ80us���ߵ�ƽ80us
	DHT11_GPIO_IN();
	delay_us(20);
	//��ʱ20us���͵�ƽ80us����ʣ60us������Ƿ��ǵ͵�ƽ��ȷ���Ƿ�����Ӧ�ź�
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	{
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)//������Ӧ�źŵ͵�ƽʣ��60us
		{
			delay_us(1);
			retry++;			
		}
		retry=0;//����100us�Զ��������У����⿨��
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&retry<100)//������Ӧ�źŸߵ�ƽ80us
		{
			delay_us(1);
			retry++;			
		}
		retry=0;
		//����8�ֽ�����
		for(i=0;i<5;i++)
		{
			dat[i]=DHT_Read_Byte();
		}
		delay_us(50);//DHT11��������50us��Ϊ�����źţ�����ʹ���������
				
//		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&retry<100)//������Ӧ�źŵ͵�ƽʣ��60us
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
