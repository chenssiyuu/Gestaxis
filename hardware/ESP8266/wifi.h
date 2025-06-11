#ifndef __WIFI_H
#define __WIFI_H

#include "sys.h"
/*����AP�궨��*/
#define SSID "Tenda_2B2B20"
#define PWD  "18768803909"

/*���ӷ������궨��*/
#define TCP "TCP"
#define UDP "UDP"
#define IP  "122.114.122.174"
#define PORT 40915

#define Net_SendString(str) Usart3_SendString(str)
#define Net_SendBuf(buf,len) Usart3_SendBuf(buf,len)

u8 FindStr(char* dest,char* src,u16 retry_nms);

typedef struct
{
	u8 *rxbuf;u16 rxlen;
	u8 *txbuf;u16 txlen;
	
	u8 (*Check)(void);
	u8 (*Init)(u8 *prx,u16 rxlen,u8 *ptx,u16 txlen);
	void (*Restore)(void);
	u8 (*ConnectAP)(char *ssid,char *pswd);
	u8 (*ConnectServer)(char* mode,char *ip,u16 port);
	u8 (*DisconnectServer)(void);
	u8 (*OpenTransmission)(void);
	void (*CloseTransmission)(void);		
	void (*SendString)(char *str);
	void (*SendBuf)(u8 *buf,u16 len);
}_typdef_net;

extern _typdef_net _net;

#endif

/*********************************************END OF FILE********************************************/

