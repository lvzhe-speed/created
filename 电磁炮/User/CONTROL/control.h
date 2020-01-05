#ifndef __CONTRL_H
#define __CONTRL_H

#include "stm32f10x.h"   
#include "./OPENMV/openmv.h"
#include "./LED/bsp_led.h"

#define LevelMotorScale 1000.0 //水平舵机定时器比较值与90度角比例
#define ElevationMotorScale 960.0//俯仰舵机定时器比较值与90度角比例

#define LevelTimValue 1450.0 //炮台仰角0时定时器比较通道的设定值
#define Elevation45Angle LevelTimValue-ElevationMotorScale/2//45度仰角对应定时器比较值
#define CenterTimValue 1450.0 //炮台位于水平中线时定时器比较通道的设定值
#define MAXCenterDeviation CenterTimValue+LevelMotorScale/3.0//最大水平偏转角90
#define MINCenterDeviation CenterTimValue-LevelMotorScale/3.0//最小水平偏转角-90

#define UnitAngle 0.05//定义单位角度便于控制

extern uint8_t ShootFlag,ChargeFlag,AotoChargeAndShootFlag;//发射，充电控制标志位，由TIM4产生控制时序

void SetCenterDeviation(float DeviationAngle);//设置炮台与水平中轴线的偏角
void ChangeCenterDeviation(float ChangeAngle);//在当前基础上改变与中轴线偏角
float GetCenterDeviation(void);//获取当前设定的中轴线偏角
void SetElevation(float Angle);//设置仰角
void ChangeElevation(float ChangeAngle);//在当前基础上改变仰角
float GetElevation(void);//获取仰角

void TrackTarget(void);//跟踪目标位置，使镜头正对目标

void ShootAndChargeGPIOInit(void);//发射，充电控制脚初始化
void Shoot(void);//发射
void Charge(void);//充电
void AotoChargeAndShoot(void);//自动充电和发射

#endif
