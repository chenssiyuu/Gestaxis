#ifndef _PAJ7620U2_H__
#define _PAJ7620U2_H__

//������붨��
#define GS_SUCCESS           0x00   //�����ɹ�
#define GS_WAKEUP_ERR        0x01   //PAJ7620U2����ʧ��
#define GS_GESTURE_ERR       0x02   //��ȡ�������ݴ���
#define GS_ERR               0xEE   //��������

//BANK����
#define PAJ_REGITER_BANK_SEL 0xEF    //BANKѡ��Ĵ���
#define PAJ_BANK0            0x00    //BANK0
#define PAJ_BANK1            0x01    //BANK1

//BANK0 �Ĵ�����
#define PAJ_SUSPEND                0x03 //�豸����
#define PAJ_INT_EN_FLAG1           0x41 //���Ƽ���жϼĴ���1
#define PAJ_INT_EN_FLAG2           0x42 //����/�ӽ�����жϼĴ���2
#define PAJ_INT_FLAG1              0x43 //���Ƽ���жϱ�־�Ĵ���1
#define PAJ_INT_FLAG2              0x44 //���Ƽ���жϱ�־�Ĵ���2
#define PAJ_STATE                  0x45 //��ȡ���Ƽ�⹤��״̬
#define PAJ_PS_HIGH_THRESHOLD      0x69 //�����ͺ�߷�ֵ�����ڽӽ����ģʽ�£�
#define PAJ_PS_LOW_THRESHOLD       0x6A //�����ͺ�ͷ�ֵ
#define PAJ_PS_APPROACH_STATE      0x6B //�ӽ�״̬ ��=1��8 bits PS data>= PS high threshold ,=0:8 bits PS data<= Low threshold�����ڽӽ����ģʽ�������ã�
#define PAJ_PS_DATA                0x6C //�ӽ�����
#define PAJ_OBJECT_BRIGHTNESS      0xB0 //�������ȣ����255��
#define PAJ_OBJECT_SIZE_1          0xB1 //�����С�Ͱ�λ��bit7:0��(���900)
#define PAJ_OBJECT_SIZE_2          0xB2 //�����С����λ��bit3:0��

//BANK1 �Ĵ�����
#define PAJ_SET_PS_GAIN         0x44 //���ü�������С (0:1x gain 1:2x gain)
#define PAJ_SET_IDLE_S1_STEP_0  0x67 //����S1����Ӧ����
#define PAJ_SET_IDLE_S1_STEP_1  0x68 
#define PAJ_SET_IDLE_S2_STEP_0  0x69 //����S2����Ӧ����
#define PAJ_SET_IDLE_S2_STEP_1  0x6A 
#define PAJ_SET_OP_TO_S1_STEP_0 0x6B //����OP��S1�Ĺ���ʱ��
#define PAJ_SET_OP_TO_S1_STEP_1 0x6C
#define PAJ_SET_S1_TO_S2_STEP_0 0x6D //����S1��S2�Ĺ���ʱ��
#define PAJ_SET_S1_TO_S2_STEP_1 0x6E
#define PAJ_OPERATION_ENABLE    0x72 //����PAJ7620U2ʹ�ܼĴ���

//����ʶ����
#define BIT(x) 1<<(x)

#define GESTURE_UP              BIT(0) //����  ��up��
#define GESTURE_DOWM            BIT(1) //����  ��down��
#define GESTURE_RIGHT            BIT(2) //����  ��right��
#define GESTURE_LEFT           BIT(3) //����  ��left��
#define GESTURE_FORWARD         BIT(4) //��ǰ  ��forward��
#define GESTURE_BACKWARD        BIT(5) //���  ��backward��
#define GESTURE_CLOCKWISE       BIT(6) //˳ʱ�루circle-clockwise��
#define GESTURE_COUNT_CLOCKWISE BIT(7) //��ʱ�루circle-counter clockwise��
#define GESTURE_WAVE            BIT(8) //�Ӷ�  ��wave��

uint8_t paj7620u2_init(void);
uint8_t get_gesture_result(uint16_t *p_gesture);
uint8_t get_ps_result(uint8_t *p_brightness,uint16_t *p_size);
void gesture_init(void);
void ps_init(void);

#endif


