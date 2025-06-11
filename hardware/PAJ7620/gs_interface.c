/****************************************Copyright (c)************************************************
**                                      [艾克姆科技]
**                                        IIKMSIK 
**                            官方店铺：https://acmemcu.taobao.com
**                            官方论坛：http://www.e930bbs.com
**                                   
**--------------File Info-----------------------------------------------------------------------------
** File name:			     main.c
** Last modified Date:          
** Last Version:		   
** Descriptions:		  
**						
**----------------------------------------------------------------------------------------------------
** Created by:			
** Created date:		2020-5-23
** Version:			    1.0
** Descriptions:		PAJ7620U2 I2C接口驱动
**---------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"
#include "user_iic.h"
#include "paj7620u2.h"
#include "gs_interface.h"


/*************************************************************************
 * 功  能 : 向指定的寄存器写入一个字节数据
 * 参  数 : regAddr[in]：寄存器地址
 *        : regDat[in]：写入的数据
 * 返回值 : GS_SUCCESS:写寄存器成功，如果出错会进入错误处理程序
 *************************************************************************/
uint8_t gs_write_byte(uint8_t regAddr,uint8_t regDat)
{
	  if(!IIC_Start())   return GS_ERR;
    IIC_Send_Byte(PAJ7620U2_I2C_ADDR);
	  if(!IIC_Wait_Ack()){IIC_Stop(); return GS_ERR;}
	  IIC_Send_Byte(regAddr);
	  IIC_Wait_Ack();
	  IIC_Send_Byte(regDat);
    IIC_Wait_Ack();
    IIC_Stop();

	  return GS_SUCCESS;
}
/*************************************************************************
 * 功  能 : 从指定寄存器读取一个字节数据
 * 参  数 : regAddr[in]：寄存器地址
 * 返回值 : 读取的数据，如果出错会进入错误处理程序
 *************************************************************************/
uint8_t gs_read_byte(uint8_t regAddr)
{
    uint8_t dat;
	
	  if(!IIC_Start())   return GS_ERR;
    IIC_Send_Byte(PAJ7620U2_I2C_ADDR);
	  if(!IIC_Wait_Ack()){IIC_Stop(); return GS_ERR;}
	  IIC_Send_Byte(regAddr);
	  IIC_Wait_Ack();
	
	  IIC_Start();
	  IIC_Send_Byte(PAJ7620U2_I2C_ADDR | 0x01);
	  IIC_Wait_Ack();
	  dat = IIC_Read_Byte(0);
	  IIC_Stop();
	  return dat;
}
/*************************************************************************
 * 功  能 : 读取指定寄存器的多个字节数据
 * 参  数 : regAddr[in]：寄存器地址
 *        : *buf[out]：指向保存读出数据的缓存
 *        : len[in]：读出的数据长度（字节数）
 * 返回值 : GS_SUCCESS:操作成功，如果出错会进入错误处理程序
 *************************************************************************/ 
uint8_t gs_read_bytes(uint8_t regAddr,uint8_t *buf,uint16_t len)
{
    if(!IIC_Start())   return GS_ERR;
    IIC_Send_Byte(PAJ7620U2_I2C_ADDR);
	  if(!IIC_Wait_Ack()){IIC_Stop(); return GS_ERR;}
	  IIC_Send_Byte(regAddr);
	  IIC_Wait_Ack();
		
		if(!IIC_Start())   return GS_ERR;
	  IIC_Send_Byte(PAJ7620U2_I2C_ADDR | 0x01);
	  IIC_Wait_Ack();
	  while(len)
	  {
				if(len==1)
				{
					  *(buf+1) = IIC_Read_Byte(0);
				}
				else
				{
					  *buf = IIC_Read_Byte(1);
				}
				buf++;
				len--;
	  }
	  IIC_Stop();
	
	  return GS_SUCCESS;
}
//唤醒PAJ7620U2：命令格式：S(起始条件) + (I2C ADDRESS + W) + P(停止条件)
void gs_wakeup(void)
{
	IIC_Start();
	IIC_Send_Byte(PAJ7620U2_I2C_ADDR);
	IIC_Stop();
}









