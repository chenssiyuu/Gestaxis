
/***********************ͷ�ļ�****************************/

#include "stm32f10x.h"
#include "usart_use.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
#include "mqtt.h"
#include "paj7620u2.h"
#include "user_iic.h"	

extern char MQTTPUB[256];//mqtt.c

u8 current_position = 1;//��ǰ��ʾҳ��
u8 set_position = 1;//�趨λ��
u8 pre_position = 1;

u8 cnt[5] = {0,0,0,0,0};

char position_str[7]={0x5A,0xA5,0x04,0x83,0x10,0x50,0x01};	//��ȡ��Ļ��ʱ����ʾҳ��
char voice_str[7]={0x5A,0xA5,0x04,0x83,0x10,0x40,0x01};				//��ȡ��������״̬
char page_str[8]={0x5A,0xA5,0x05,0x82,0x10,0x50,0x00,0x01};		//ҳ���л�ָ�Ĭ����ʾ��һҳ


u16 cx = 0;
u8 voice_flag = 0;		//��������״̬��0-�أ�1-��
extern char product_1[56];
void Change_Value(void);
void test_en(void);
void get_gesture(void);


uint16_t gesture_result;

/***********************��ʼ��****************************/
void All_Init()
{
		delay_init();//��ʱ��ʼ��
		NVIC_Configuration();//�ж����ȼ�

		Control_Init();
		Motor_Init();
		Sensor_Init();

		IN1 = 1;
		IN2 = 1;//���ֹͣ	
	
			//��ʼ��PAJ7620U2����ʶ��ģ��
		delay_ms(1000);
		if(paj7620u2_init() != GS_SUCCESS)
		{
			while(1)
			{
			}
		}
		delay_ms(1000);
		gesture_init(); //����ʶ���ʼ��
		
		uart2_init(9600);//���ڳ�ʼ��
		USART_SendHEX(USART2,&product_1[49],7);
		delay_ms(1500);
		delay_ms(1500);
		
		uart3_init(115200);//���ڳ�ʼ��		ESP8266
		MQTT1_Init();  			 //mqtt��ʼ��			
		
		USART_SendHEX(USART2,&product_1[42],7);
		delay_ms(1500);
		delay_ms(1500);
		uart1_init(115200);//���ڳ�ʼ��		��Ļ
		
	
}


/***********************������****************************/

int main(void)
{
	All_Init();
	while(1)
	{
		get_gesture();
		
		USART_SendHEX(USART1,position_str,7);		//��ȡ��ǰ��Ļҳ��
		delay_ms(500);
		USART_SendHEX(USART1,voice_str,7);			//��ȡ��������״̬
		delay_ms(500);
		
		Change_Value();
	}
}

/*************************END******************************/


void get_gesture(void)
{
	if(get_gesture_result(&gesture_result) == GS_SUCCESS)//��ȡ����ʶ����
	{
		if(gesture_result == GESTURE_LEFT)//��
		{
			current_position++;			
			if((current_position>0)&&(current_position<6))
			{
				page_str[7] = current_position;		//ҳ���л�Ϊ��ǰչƷ��ҳ��
				USART_SendHEX(USART1,page_str,8); //����ҳ���л�ָ���Ļ
			}
		}
		else if(gesture_result == GESTURE_RIGHT)//�һ�
		{
			current_position--;			
			if((current_position>0)&&(current_position<6))
			{
				page_str[7] = current_position;		//ҳ���л�Ϊ��ǰչƷ��ҳ��
				USART_SendHEX(USART1,page_str,8); //����ҳ���л�ָ���Ļ
			}
		}
		if(current_position == 0)
		{
			current_position = 1;			
			USART_SendHEX(USART2,&product_1[35],7);	
		}
		else if(current_position == 6)
		{
			current_position = 5;			
			USART_SendHEX(USART2,&product_1[35],7);	
		}
	}
}


void Change_Value(void)
{
		MQTTPUB[86] = current_position + '0';		//��ǰչλ

		MQTTPUB[98]  = cnt[0]/100 + '0';			//չλ1ͣ������
		MQTTPUB[99]  = cnt[0]/10%10 + '0';
		MQTTPUB[100] = cnt[0]%10 + '0';
	
		MQTTPUB[112] = cnt[1]/100 + '0';			//չλ2ͣ������
		MQTTPUB[113] = cnt[1]/10%10 + '0';
		MQTTPUB[114] = cnt[1]%10 + '0';
	
		MQTTPUB[126] = cnt[2]/100 + '0';			//չλ3ͣ������
		MQTTPUB[127] = cnt[2]/10%10 + '0';
		MQTTPUB[128] = cnt[2]%10 + '0';
	
		MQTTPUB[140] = cnt[3]/100 + '0';			//չλ4ͣ������
		MQTTPUB[141] = cnt[3]/10%10 + '0';
		MQTTPUB[142] = cnt[3]%10 + '0';
		
		MQTTPUB[154] = cnt[4]/100 + '0';			//չλ5ͣ������
		MQTTPUB[155] = cnt[4]/10%10 + '0';
		MQTTPUB[156] = cnt[4]%10 + '0';
		
		MQTT_Send();
}


