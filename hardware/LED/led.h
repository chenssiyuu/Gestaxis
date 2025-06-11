#ifndef _led_
#define _led_

#include "sys.h"
#include "stm32f10x.h"

#define LED PCout(13)
#define control_1 PBout(12)
#define control_2 PBout(13)
#define control_3 PBout(14)
#define control_4 PAout(6)
#define control_5 PAout(4)
#define sensor PAin(5)
#define IN1 PAout(11)
#define IN2 PAout(12)

void LED_Init(void);
void Control_Init(void);
void Sensor_Init(void);
void Motor_Init(void);

#endif


