#ifndef _ADC_H
#define _ADC_H


#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"

void Adc_Init(void);
u16 Get_Adc(u8 ch);
float Get_battery_volt(void);

#endif
