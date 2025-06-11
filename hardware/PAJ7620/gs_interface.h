#ifndef _GS_INTERFACE_H__
#define _GS_INTERFACE_H__
#include "stm32f10x.h"



//PAJ7620U2 I2Cµÿ÷∑
#define PAJ7620U2_I2C_ADDR    (0x73 << 1)


void gs_wakeup(void);
uint8_t gs_write_byte(uint8_t regAddr,uint8_t regDat);
uint8_t gs_read_byte(uint8_t regAddr);
uint8_t gs_read_bytes(uint8_t regAddr,uint8_t *buf,uint16_t len);
#endif


