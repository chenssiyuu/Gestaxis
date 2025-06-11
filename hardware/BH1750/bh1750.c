#include "bh1750.h"
#include "delay.h"


void bh_data_send(u8 command)
{
    do{
    IIC_Start_2();
    IIC_Send_Byte_2(BHAddWrite);
	  }
		while(IIC_Wait_Ack_2());
	  IIC_Send_Byte_2(command);
	  IIC_Wait_Ack_2();
	  IIC_Stop_2();
}




u16 bh_data_read(void)
{
	u16 buf;
	IIC_Start_2();
	IIC_Send_Byte_2(BHAddRead);
	IIC_Wait_Ack_2();
	buf=IIC_Read_Byte_2(1);
	buf=buf<<8;
	buf+=0x00ff&IIC_Read_Byte_2(0);
	IIC_Stop_2();
	return buf;
}


