/**********************************************************
文件名：mqtt.c
功能：连接云端
备注：无
**********************************************************/
#include "mqtt.h"
#include "delay.h"
#include "stdio.h"	
#include <string.h>
#include "usart.h"
#include "usart_use.h"


/***********************变量配置**************************/
char MQTTUSERCFG[256] = {"AT+MQTTUSERCFG=0,1,\"NULL\",\"stm32&a1c7s78tLfY\",\"208A758D5A114762CA384CF751961371B0576D94\",0,0,\"\"\r\n"};
char MQTTCLIENTID[128] = {"AT+MQTTCLIENTID=0,\"a1c7s78tLfY|securemode=2\\,signmethod=hmacsha1\\,timestamp=1748713693150|\"\r\n"};
char MQTTCONNET[128] = {"AT+MQTTCONN=0,\"a1c7s78tLfY.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,0\r\n"};
char MQTTPUB[256] = {"AT+MQTTPUB=0,\"/sys/a1c7s78tLfY/stm32/thing/event/property/post\",\"{\\\"params\\\":{\\\"pos\\\":1\\,\\\"tim1\\\":100\\,\\\"tim2\\\":100\\,\\\"tim3\\\":100\\,\\\"tim4\\\":100\\,\\\"tim5\\\":100\\}}\",1,0\r\n"};
/**********************************************************/
//MQTTPUB上传字符串要加""

/*********************ESP8266联网指令**********************/
void MQTT1_Init(void)
{
	
	USART_SendString(USART3,"AT+RST\r\n");                           //esp8266复位
	delay_ms(1000);
	
	USART_SendString(USART3,"AT\r\n");                           //esp8266是否正常工作
	delay_ms(500);
	
	USART_SendString(USART3,"AT+CWMODE=1\r\n");    
	delay_ms(500);

	USART_SendString(USART3,"AT+CWJAP=\"esp\",\"11112222\"\r\n");  
	delay_ms(1500);

	USART_SendString(USART3,"AT+RST\r\n");                           //esp8266复位		不能删掉！！
	delay_ms(1000);

	USART_SendString(USART3,MQTTUSERCFG); 
	delay_ms(500);
	
	USART_SendString(USART3,MQTTCLIENTID); 
	delay_ms(500);

	USART_SendString(USART3,MQTTCONNET);     
	delay_ms(1000);
	delay_ms(1000);

	USART_SendString(USART3,MQTTPUB);   
	delay_ms(1000);	
}
/**********************************************************/


/*********************ESP8266上传数据**********************/
void MQTT_Send(void)
{
	USART_SendString(USART3,MQTTPUB); 
}
/**********************************************************/
