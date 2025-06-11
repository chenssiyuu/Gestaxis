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
** Descriptions:		PAJ7620U2 驱动程序
**---------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "paj7620u2.h"
#include "paj7620u2_cfg.h"
#include "gs_interface.h"
#include "delay.h"
#include "user_iic.h"	

//初始化PAJ7620U2
uint8_t paj7620u2_init(void)
{
		
	  IIC_GPIO_Init();               //初始化IIC所用到的IO口	
		gs_wakeup();                   //唤醒PAJ7620U2
		delay_ms(5);                //唤醒时间>700us
		gs_wakeup();                   //唤醒PAJ7620U2
		delay_ms(5);                //唤醒时间>700us
	  gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//进入BANK0寄存器区域
		if(gs_read_byte(0x00) != 0x20) //唤醒PAJ7620U2
		{
			return GS_WAKEUP_ERR; //唤醒失败
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//进入BANK0寄存器区域
		for(uint8_t i=0;i<GS_INIT_ARRAY_SIZE;i++)
		{
			gs_write_byte(initial_register_array[i][0],initial_register_array[i][1]);//写入初始化配置数据
		}
		//写入初始化配置数据时会进入BANK1，这里再切换回BANK0寄存器区域
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);
		return GS_SUCCESS; 
}

//读取手势识别结果
uint8_t get_gesture_result(uint16_t *p_gesture)
{
		uint8_t status;
		uint8_t read_buf[2];

    status = gs_read_bytes(PAJ_INT_FLAG1,read_buf,2);//读取手势状态			
		if(!status)
		{   
			*p_gesture =  (uint16_t)(read_buf[1]<<8) | read_buf[0];
			return GS_SUCCESS;
		}
		else return GS_GESTURE_ERR; 
}
//读取接近检测结果
uint8_t get_ps_result(uint8_t *p_brightness, uint16_t *p_size)
{
		uint8_t read_buf[2];

		*p_brightness = gs_read_byte(PAJ_OBJECT_BRIGHTNESS);//读取物体亮度
		read_buf[0] = gs_read_byte(PAJ_OBJECT_SIZE_1);//读取物体大小
		read_buf[1] = gs_read_byte(PAJ_OBJECT_SIZE_2);
		*p_size = ((uint16_t)read_buf[1] & 0x0f)<<8 | read_buf[0];
		
		return GS_SUCCESS;
}
//写入手势识别初始化配置
void gesture_init(void)
{
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//进入BANK0寄存器区域
		for(uint8_t i=0; i<GS_GESTURE_ARRAY_SIZE; i++)
		{
			  gs_write_byte(gesture_arry[i][0],gesture_arry[i][1]);//手势识别模式初始化
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//写入初始化配置数据时会进入BANK1，这里再切换回BANK0寄存器区域
}
//写入接近检测初始化配置
void ps_init(void)
{
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//进入BANK0寄存器区域
		for(uint8_t i=0;i<GS_PROXIM_ARRAY_SIZE;i++)
		{
			gs_write_byte(proximity_arry[i][0],proximity_arry[i][1]);//接近检测模式初始化
		}
		gs_write_byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);//写入初始化配置数据时会进入BANK1，这里再切换回BANK0寄存器区域
}

