#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h" 
#include "./CONTROL/control.h"
#include "./LED/bsp_led.h"
#include "stdio.h"

#define KeyPressMINCount 0
#define KeyLongPressCount 1000
#define DefaultKeyInterfaceStatus 0x07

typedef struct
{
	uint8_t KeyValue;
	uint8_t KeyWaitServeFlag;
}KeyServeTypedef;

void KeyGPIOInit(void);
void Period5msKeyScan(void);
void Task1_KeyServe(float Angle);
void Task2_KeyServe(float Yaw,float Angle);
void Task3_KeyServe();
#endif
