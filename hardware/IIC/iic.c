#include "iic.h"


/*********iic��ʼ��************/

void IIC_Init_2(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOIIC, ENABLE);  //APB2ʱ��
  
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;  //����IIC_SCL_Pin��IIC_SDA_Pin��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //�����ٶ�50MHZ��Ĭ�ϣ�
	
	GPIO_Init(GPIO_IIC, &GPIO_InitStructure);	 //ʹ��������������������
	
	SDA_PIN_OUT=1;  //�����ͷ����ߣ�����
	SCL_PIN_OUT=1;  //�����ͷ����ߣ�����
}

/*********iic��ʼ��************/




/***********iic����************/

void IIC_Start_2(void)    //������ʽ����SCL�ߵ�ƽ�ڼ佫SDA�ɸ��õ�
{
	IIC_SDA_OUT();  //����IICΪ���
	SDA_PIN_OUT=1;  //����SDA�ߵ�ƽ����
	SCL_PIN_OUT=1;  //����SCL�ߵ�ƽ����
	delay_us(4);
	SDA_PIN_OUT=0;  //��ʱSCL�ߵ�ƽ��SDA�ɸ��õ�
	delay_us(4);
	SCL_PIN_OUT=0;  //ǯסI2C���ߣ�׼�����ͻ�������� 
}

/***********iic����************/



/***********iicֹͣ************/

void IIC_Stop_2(void)   //ֹͣ��ʽ����SCL�ߵ�ƽ�ڼ佫SDA�ɵ��ø�
{
	IIC_SDA_OUT();  //����IICΪ���
  SCL_PIN_OUT=0;	//����SCL�͵�ƽ����
	SDA_PIN_OUT=0;  //����SDA�͵�ƽ����
	delay_us(4);
	SCL_PIN_OUT=1;  //����SCL������ֹͣ����
  delay_us(4);
	SDA_PIN_OUT=1;  //��ʱSCL�ߵ�ƽ��SDA�ɸ��õͣ�ֹͣ�ź���Ч
}

/***********iicֹͣ************/




/*********iic�ȴ�Ӧ��**********/  //�����ȴ�Ӧ��ͷ�Ӧ������

u8 IIC_Wait_Ack_2(void)  //�ͷŵ����߶�ȡSDA���ж��Ƿ��и�����
{
	u8 i=0;
	IIC_SDA_IN();   //����IICΪ����
  SDA_PIN_OUT=1;  //����SDA�ߵ�ƽ����
	delay_us(4);
	SCL_PIN_OUT=1;  //����SCL�ߵ�ƽ����
	delay_us(4);
	while(SDA_PIN_IN)  //�ȴ����ж���
	{
		i++;
		if(i>250) 
		{		
      IIC_Stop_2();			//���i>255�������Ӧ���źţ�iicֹͣ
			return 1;
		}
	}
	SCL_PIN_OUT=0;//ʱ�����0 
	return 0;
}

/*********iic�ȴ�Ӧ��**********/




/***********iicӦ��************/

void IIC_Ack_2(void)  //����Ӧ��SDAһֱ���ڵ͵�ƽ��SCL�ɵͱ��
{
	IIC_SDA_OUT();  //����IICΪ���
	SCL_PIN_OUT=0;  //����SCL�͵�ƽ����
	SDA_PIN_OUT=0;  //����SDA�͵�ƽ����
	delay_us(4);
	SCL_PIN_OUT=1;  //SCL�ɵͱ�ߣ�����Ӧ��
	delay_us(4);
	SCL_PIN_OUT=0;  //SCL���ͻص�ԭλ׼����һ��Ӧ��
}

/***********iicӦ��************/




/**********iic��Ӧ��***********/

void IIC_Nack_2(void)  //������Ӧ��SDAһֱ���ڸߵ�ƽ��SCL�ɵͱ��
{
	IIC_SDA_OUT();  //����IICΪ���
	SCL_PIN_OUT=0;  //����SCL�͵�ƽ����
	SDA_PIN_OUT=1;  //����SDA�ߵ�ƽ����
	delay_us(4);
	SCL_PIN_OUT=1;  //SCL�ɵͱ�߲�����Ӧ��
	delay_us(4);
	SCL_PIN_OUT=0;  //SCL���ͻص�ԭλ׼����һ��Ӧ��
}	

/**********iic��Ӧ��***********/




/*********iic��������**********/

void IIC_Send_Byte_2(u8 buf)  //SCL������ʱ��ȡSDA��ʱ��״̬������
{
  u8 i;
	IIC_SDA_OUT();     //����IICΪ���
	SCL_PIN_OUT=0;     //SCL���ͣ����촫����������
	for(i=1;i<=8;i++)  //��λ���ݴ���
	{
		SDA_PIN_OUT=(buf>>(8-i))&0x01; //�Ȱ�Ҫ���͵����ַ���SDA
		delay_us(4);
		SCL_PIN_OUT=1;  //SCL�ɵͱ�ߣ���������
		delay_us(4);
		SCL_PIN_OUT=0;  //SCL��ԭ׼����һ�����ݵĴ���
		delay_us(4);		
	}
}

/*********iic��������**********/




/*********iic��������**********/

u8 IIC_Read_Byte_2(unsigned char ask)  //ask = 1ΪӦ�� �� 
{
	unsigned char  i,buf=0;
	IIC_SDA_IN();     //����iicΪ����
	for(i=0;i<8;i++)  //����8λ����
	{
	   SCL_PIN_OUT=0; //SCL���������������
	   delay_us(4);
	   SCL_PIN_OUT=1; //SCL�ɵͱ�ߣ���������
	   buf <<=1;      //���ϰѽ��յ�����������λ�ƶ�
	   if(SDA_PIN_IN) //SDA�ĸߵ���Ϊ���������
		   buf++;       //�����������Ϊ�����bufλ��1��ʹ������ͬ�����ݣ���Ϊ�����Զ�����Ϊ0
	    delay_us(4);
	}
	if(!ask)         //�ظ���Ӧ��
		IIC_Nack_2();
	else             //�ظ�Ӧ��
		IIC_Ack_2();
	return buf;      //���ؽ�������
}

/*********iic��������**********/

