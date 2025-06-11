#ifndef _PAJ7620U2_H__
#define _PAJ7620U2_H__

//错误代码定义
#define GS_SUCCESS           0x00   //操作成功
#define GS_WAKEUP_ERR        0x01   //PAJ7620U2唤醒失败
#define GS_GESTURE_ERR       0x02   //读取手势数据错误
#define GS_ERR               0xEE   //操作错误

//BANK定义
#define PAJ_REGITER_BANK_SEL 0xEF    //BANK选择寄存器
#define PAJ_BANK0            0x00    //BANK0
#define PAJ_BANK1            0x01    //BANK1

//BANK0 寄存器组
#define PAJ_SUSPEND                0x03 //设备挂起
#define PAJ_INT_EN_FLAG1           0x41 //手势检测中断寄存器1
#define PAJ_INT_EN_FLAG2           0x42 //手势/接近检测中断寄存器2
#define PAJ_INT_FLAG1              0x43 //手势检测中断标志寄存器1
#define PAJ_INT_FLAG2              0x44 //手势检测中断标志寄存器2
#define PAJ_STATE                  0x45 //获取手势检测工作状态
#define PAJ_PS_HIGH_THRESHOLD      0x69 //设置滞后高阀值（仅在接近检测模式下）
#define PAJ_PS_LOW_THRESHOLD       0x6A //设置滞后低阀值
#define PAJ_PS_APPROACH_STATE      0x6B //接近状态 （=1：8 bits PS data>= PS high threshold ,=0:8 bits PS data<= Low threshold，仅在接近检测模式下起作用）
#define PAJ_PS_DATA                0x6C //接近数据
#define PAJ_OBJECT_BRIGHTNESS      0xB0 //物体亮度（最大255）
#define PAJ_OBJECT_SIZE_1          0xB1 //物体大小低八位（bit7:0）(最大900)
#define PAJ_OBJECT_SIZE_2          0xB2 //物体大小高四位（bit3:0）

//BANK1 寄存器组
#define PAJ_SET_PS_GAIN         0x44 //设置检测增益大小 (0:1x gain 1:2x gain)
#define PAJ_SET_IDLE_S1_STEP_0  0x67 //设置S1的响应因子
#define PAJ_SET_IDLE_S1_STEP_1  0x68 
#define PAJ_SET_IDLE_S2_STEP_0  0x69 //设置S2的响应因子
#define PAJ_SET_IDLE_S2_STEP_1  0x6A 
#define PAJ_SET_OP_TO_S1_STEP_0 0x6B //设置OP到S1的过度时间
#define PAJ_SET_OP_TO_S1_STEP_1 0x6C
#define PAJ_SET_S1_TO_S2_STEP_0 0x6D //设置S1到S2的过度时间
#define PAJ_SET_S1_TO_S2_STEP_1 0x6E
#define PAJ_OPERATION_ENABLE    0x72 //设置PAJ7620U2使能寄存器

//手势识别结果
#define BIT(x) 1<<(x)

#define GESTURE_UP              BIT(0) //向上  （up）
#define GESTURE_DOWM            BIT(1) //向下  （down）
#define GESTURE_RIGHT            BIT(2) //向左  （right）
#define GESTURE_LEFT           BIT(3) //向右  （left）
#define GESTURE_FORWARD         BIT(4) //向前  （forward）
#define GESTURE_BACKWARD        BIT(5) //向后  （backward）
#define GESTURE_CLOCKWISE       BIT(6) //顺时针（circle-clockwise）
#define GESTURE_COUNT_CLOCKWISE BIT(7) //逆时针（circle-counter clockwise）
#define GESTURE_WAVE            BIT(8) //挥动  （wave）

uint8_t paj7620u2_init(void);
uint8_t get_gesture_result(uint16_t *p_gesture);
uint8_t get_ps_result(uint8_t *p_brightness,uint16_t *p_size);
void gesture_init(void);
void ps_init(void);

#endif


