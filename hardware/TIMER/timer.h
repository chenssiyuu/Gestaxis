#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"
#include "stm32f10x_tim.h"

extern u16 flag;
extern u16 flag_2;
extern u16 num;
void TIM2_Int_Init(u16 arr,u16 psc);
 
#endif
