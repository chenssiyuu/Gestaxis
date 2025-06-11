/****************************************Copyright (c)************************************************
**                                      [����ķ�Ƽ�]
**                                        IIKMSIK 
**                            �ٷ����̣�https://acmemcu.taobao.com
**                            �ٷ���̳��http://www.e930bbs.com
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
** Descriptions:		PAJ7620U2 I2C�ӿ�����
**---------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"
#include "user_iic.h"
#include "paj7620u2.h"
#include "gs_interface.h"


/*************************************************************************
 * ��  �� : ��ָ���ļĴ���д��һ���ֽ�����
 * ��  �� : regAddr[in]���Ĵ�����ַ
 *        : regDat[in]��д�������
 * ����ֵ : GS_SUCCESS:д�Ĵ����ɹ����������������������
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
 * ��  �� : ��ָ���Ĵ�����ȡһ���ֽ�����
 * ��  �� : regAddr[in]���Ĵ�����ַ
 * ����ֵ : ��ȡ�����ݣ��������������������
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
 * ��  �� : ��ȡָ���Ĵ����Ķ���ֽ�����
 * ��  �� : regAddr[in]���Ĵ�����ַ
 *        : *buf[out]��ָ�򱣴�������ݵĻ���
 *        : len[in]�����������ݳ��ȣ��ֽ�����
 * ����ֵ : GS_SUCCESS:�����ɹ����������������������
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
//����PAJ7620U2�������ʽ��S(��ʼ����) + (I2C ADDRESS + W) + P(ֹͣ����)
void gs_wakeup(void)
{
	IIC_Start();
	IIC_Send_Byte(PAJ7620U2_I2C_ADDR);
	IIC_Stop();
}









