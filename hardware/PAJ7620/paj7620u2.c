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
** Descriptions:		PAJ7620U2 ��������
**---------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "paj7620u2.h"
#include "paj7620u2_cfg.h"
#include "gs_interface.h"
#include "delay.h"
#include "user_iic.h"	

//��ʼ��PAJ7620U2
uint8_t paj7620u2_init(void)
{
		
	  IIC_GPIO_Init();               //��ʼ��IIC���õ���IO��	
		gs_wakeup();                   //����PAJ7620U2
		delay_ms(5);                //����ʱ��>700us
		gs_wakeup();                   //����PAJ7620U2
		delay_ms(5);                //����ʱ��>700us
	  gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//����BANK0�Ĵ�������
		if(gs_read_byte(0x00) != 0x20) //����PAJ7620U2
		{
			return GS_WAKEUP_ERR; //����ʧ��
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//����BANK0�Ĵ�������
		for(uint8_t i=0;i<GS_INIT_ARRAY_SIZE;i++)
		{
			gs_write_byte(initial_register_array[i][0],initial_register_array[i][1]);//д���ʼ����������
		}
		//д���ʼ����������ʱ�����BANK1���������л���BANK0�Ĵ�������
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);
		return GS_SUCCESS; 
}

//��ȡ����ʶ����
uint8_t get_gesture_result(uint16_t *p_gesture)
{
		uint8_t status;
		uint8_t read_buf[2];

    status = gs_read_bytes(PAJ_INT_FLAG1,read_buf,2);//��ȡ����״̬			
		if(!status)
		{   
			*p_gesture =  (uint16_t)(read_buf[1]<<8) | read_buf[0];
			return GS_SUCCESS;
		}
		else return GS_GESTURE_ERR; 
}
//��ȡ�ӽ������
uint8_t get_ps_result(uint8_t *p_brightness, uint16_t *p_size)
{
		uint8_t read_buf[2];

		*p_brightness = gs_read_byte(PAJ_OBJECT_BRIGHTNESS);//��ȡ��������
		read_buf[0] = gs_read_byte(PAJ_OBJECT_SIZE_1);//��ȡ�����С
		read_buf[1] = gs_read_byte(PAJ_OBJECT_SIZE_2);
		*p_size = ((uint16_t)read_buf[1] & 0x0f)<<8 | read_buf[0];
		
		return GS_SUCCESS;
}
//д������ʶ���ʼ������
void gesture_init(void)
{
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//����BANK0�Ĵ�������
		for(uint8_t i=0; i<GS_GESTURE_ARRAY_SIZE; i++)
		{
			  gs_write_byte(gesture_arry[i][0],gesture_arry[i][1]);//����ʶ��ģʽ��ʼ��
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//д���ʼ����������ʱ�����BANK1���������л���BANK0�Ĵ�������
}
//д��ӽ�����ʼ������
void ps_init(void)
{
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//����BANK0�Ĵ�������
		for(uint8_t i=0;i<GS_PROXIM_ARRAY_SIZE;i++)
		{
			gs_write_byte(proximity_arry[i][0],proximity_arry[i][1]);//�ӽ����ģʽ��ʼ��
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//д���ʼ����������ʱ�����BANK1���������л���BANK0�Ĵ�������
}

