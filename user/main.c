
/***********************头文件****************************/

#include "stm32f10x.h"
#include "usart_use.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
#include "mqtt.h"
#include "paj7620u2.h"
#include "user_iic.h"	

extern char MQTTPUB[256];//mqtt.c

u8 current_position = 1;//当前显示页面
u8 set_position = 1;//设定位置
u8 pre_position = 1;

u8 cnt[5] = {0,0,0,0,0};

char position_str[7]={0x5A,0xA5,0x04,0x83,0x10,0x50,0x01};	//读取屏幕此时的显示页面
char voice_str[7]={0x5A,0xA5,0x04,0x83,0x10,0x40,0x01};				//读取语音开关状态
char page_str[8]={0x5A,0xA5,0x05,0x82,0x10,0x50,0x00,0x01};		//页面切换指令，默认显示第一页


u16 cx = 0;
u8 voice_flag = 0;		//语音开关状态，0-关，1-开
extern char product_1[56];
void Change_Value(void);
void test_en(void);
void get_gesture(void);


uint16_t gesture_result;

/***********************初始化****************************/
void All_Init()
{
		delay_init();//延时初始化
		NVIC_Configuration();//中断优先级

		Control_Init();
		Motor_Init();
		Sensor_Init();

		IN1 = 1;
		IN2 = 1;//电机停止	
	
			//初始化PAJ7620U2手势识别模块
		delay_ms(1000);
		if(paj7620u2_init() != GS_SUCCESS)
		{
			while(1)
			{
			}
		}
		delay_ms(1000);
		gesture_init(); //手势识别初始化
		
		uart2_init(9600);//串口初始化
		USART_SendHEX(USART2,&product_1[49],7);
		delay_ms(1500);
		delay_ms(1500);
		
		uart3_init(115200);//串口初始化		ESP8266
		MQTT1_Init();  			 //mqtt初始化			
		
		USART_SendHEX(USART2,&product_1[42],7);
		delay_ms(1500);
		delay_ms(1500);
		uart1_init(115200);//串口初始化		屏幕
		
	
}


/***********************主函数****************************/

int main(void)
{
	All_Init();
	while(1)
	{
		get_gesture();
		
		USART_SendHEX(USART1,position_str,7);		//读取当前屏幕页面
		delay_ms(500);
		USART_SendHEX(USART1,voice_str,7);			//读取语音开关状态
		delay_ms(500);
		
		Change_Value();
	}
}

/*************************END******************************/


void get_gesture(void)
{
	if(get_gesture_result(&gesture_result) == GS_SUCCESS)//获取手势识别结果
	{
		if(gesture_result == GESTURE_LEFT)//左滑
		{
			current_position++;			
			if((current_position>0)&&(current_position<6))
			{
				page_str[7] = current_position;		//页面切换为当前展品的页面
				USART_SendHEX(USART1,page_str,8); //发送页面切换指令到屏幕
			}
		}
		else if(gesture_result == GESTURE_RIGHT)//右滑
		{
			current_position--;			
			if((current_position>0)&&(current_position<6))
			{
				page_str[7] = current_position;		//页面切换为当前展品的页面
				USART_SendHEX(USART1,page_str,8); //发送页面切换指令到屏幕
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
		MQTTPUB[86] = current_position + '0';		//当前展位

		MQTTPUB[98]  = cnt[0]/100 + '0';			//展位1停留次数
		MQTTPUB[99]  = cnt[0]/10%10 + '0';
		MQTTPUB[100] = cnt[0]%10 + '0';
	
		MQTTPUB[112] = cnt[1]/100 + '0';			//展位2停留次数
		MQTTPUB[113] = cnt[1]/10%10 + '0';
		MQTTPUB[114] = cnt[1]%10 + '0';
	
		MQTTPUB[126] = cnt[2]/100 + '0';			//展位3停留次数
		MQTTPUB[127] = cnt[2]/10%10 + '0';
		MQTTPUB[128] = cnt[2]%10 + '0';
	
		MQTTPUB[140] = cnt[3]/100 + '0';			//展位4停留次数
		MQTTPUB[141] = cnt[3]/10%10 + '0';
		MQTTPUB[142] = cnt[3]%10 + '0';
		
		MQTTPUB[154] = cnt[4]/100 + '0';			//展位5停留次数
		MQTTPUB[155] = cnt[4]/10%10 + '0';
		MQTTPUB[156] = cnt[4]%10 + '0';
		
		MQTT_Send();
}


