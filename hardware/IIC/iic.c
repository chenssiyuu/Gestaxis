#include "iic.h"


/*********iic初始化************/

void IIC_Init_2(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOIIC, ENABLE);  //APB2时钟
  
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;  //设置IIC_SCL_Pin、IIC_SDA_Pin两个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //设置速度50MHZ（默认）
	
	GPIO_Init(GPIO_IIC, &GPIO_InitStructure);	 //使能上面三个函数的配置
	
	SDA_PIN_OUT=1;  //上拉释放总线，空闲
	SCL_PIN_OUT=1;  //上拉释放总线，空闲
}

/*********iic初始化************/




/***********iic启动************/

void IIC_Start_2(void)    //启动方式，在SCL高电平期间将SDA由高置低
{
	IIC_SDA_OUT();  //设置IIC为输出
	SDA_PIN_OUT=1;  //制造SDA高电平环境
	SCL_PIN_OUT=1;  //制造SCL高电平环境
	delay_us(4);
	SDA_PIN_OUT=0;  //此时SCL高电平，SDA由高置低
	delay_us(4);
	SCL_PIN_OUT=0;  //钳住I2C总线，准备发送或接收数据 
}

/***********iic启动************/



/***********iic停止************/

void IIC_Stop_2(void)   //停止方式，在SCL高电平期间将SDA由低置高
{
	IIC_SDA_OUT();  //设置IIC为输出
  SCL_PIN_OUT=0;	//制造SCL低电平环境
	SDA_PIN_OUT=0;  //制造SDA低电平环境
	delay_us(4);
	SCL_PIN_OUT=1;  //拉高SCL，制造停止环境
  delay_us(4);
	SDA_PIN_OUT=1;  //此时SCL高电平，SDA由高置低，停止信号生效
}

/***********iic停止************/




/*********iic等待应答**********/  //包括等待应答和非应答两种

u8 IIC_Wait_Ack_2(void)  //释放掉总线读取SDA置判断是否有负脉冲
{
	u8 i=0;
	IIC_SDA_IN();   //设置IIC为输入
  SDA_PIN_OUT=1;  //制造SDA高电平环境
	delay_us(4);
	SCL_PIN_OUT=1;  //制造SCL高电平环境
	delay_us(4);
	while(SDA_PIN_IN)  //等待中判断中
	{
		i++;
		if(i>250) 
		{		
      IIC_Stop_2();			//如果i>255则产生非应答信号，iic停止
			return 1;
		}
	}
	SCL_PIN_OUT=0;//时钟输出0 
	return 0;
}

/*********iic等待应答**********/




/***********iic应答************/

void IIC_Ack_2(void)  //产生应答：SDA一直处于低电平，SCL由低变高
{
	IIC_SDA_OUT();  //设置IIC为输出
	SCL_PIN_OUT=0;  //制造SCL低电平条件
	SDA_PIN_OUT=0;  //制造SDA低电平条件
	delay_us(4);
	SCL_PIN_OUT=1;  //SCL由低变高，产生应答
	delay_us(4);
	SCL_PIN_OUT=0;  //SCL拉低回到原位准备下一次应答
}

/***********iic应答************/




/**********iic非应答***********/

void IIC_Nack_2(void)  //产生非应答：SDA一直处于高电平，SCL由低变高
{
	IIC_SDA_OUT();  //设置IIC为输出
	SCL_PIN_OUT=0;  //制造SCL低电平环境
	SDA_PIN_OUT=1;  //制造SDA高电平环境
	delay_us(4);
	SCL_PIN_OUT=1;  //SCL由低变高产生非应答
	delay_us(4);
	SCL_PIN_OUT=0;  //SCL拉低回到原位准备下一次应答
}	

/**********iic非应答***********/




/*********iic发送数据**********/

void IIC_Send_Byte_2(u8 buf)  //SCL上升沿时读取SDA此时的状态并传送
{
  u8 i;
	IIC_SDA_OUT();     //设置IIC为输出
	SCL_PIN_OUT=0;     //SCL拉低，制造传输数据条件
	for(i=1;i<=8;i++)  //八位数据传输
	{
		SDA_PIN_OUT=(buf>>(8-i))&0x01; //先把要传送的数字放入SDA
		delay_us(4);
		SCL_PIN_OUT=1;  //SCL由低变高，传输数据
		delay_us(4);
		SCL_PIN_OUT=0;  //SCL复原准备下一次数据的传输
		delay_us(4);		
	}
}

/*********iic发送数据**********/




/*********iic接收数据**********/

u8 IIC_Read_Byte_2(unsigned char ask)  //ask = 1为应答 ； 
{
	unsigned char  i,buf=0;
	IIC_SDA_IN();     //设置iic为输入
	for(i=0;i<8;i++)  //接收8位数据
	{
	   SCL_PIN_OUT=0; //SCL拉低制造接收条件
	   delay_us(4);
	   SCL_PIN_OUT=1; //SCL由低变高，接收数据
	   buf <<=1;      //不断把接收到的数字往高位移动
	   if(SDA_PIN_IN) //SDA的高低则为传输的数据
		   buf++;       //若传输的数据为高则把buf位置1，使其存放相同的数据；若为低则自动保持为0
	    delay_us(4);
	}
	if(!ask)         //回复非应答
		IIC_Nack_2();
	else             //回复应答
		IIC_Ack_2();
	return buf;      //返回接收数据
}

/*********iic接收数据**********/

