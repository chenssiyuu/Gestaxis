#ifndef _iic_
#define _iic_

#include "delay.h"
#include "stm32f10x.h"

#define IIC_SCL_Pin  GPIO_Pin_5
#define IIC_SDA_Pin  GPIO_Pin_7
#define GPIO_IIC     GPIOA
#define RCC_APB2Periph_GPIOIIC RCC_APB2Periph_GPIOA


//#define IIC_SDA_OUT()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00300000;}//设置为SDA输出
//#define IIC_SDA_IN()   {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00800000;}//设置为SDA输入

#define IIC_SDA_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)8<<28;}
#define IIC_SDA_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)3<<28;}

#define SDA_PIN_OUT       PAout(7)
#define SCL_PIN_OUT       PAout(5)
#define SDA_PIN_IN        PAin(7)          
  
void IIC_Init_2(void);
void IIC_Start_2(void);
void IIC_Stop_2(void);
u8 IIC_Wait_Ack_2(void);
void IIC_Ack_2(void);
void IIC_Nack_2(void);
void IIC_Send_Byte_2(u8 buf);
u8 IIC_Read_Byte_2(unsigned char ask);


#endif

