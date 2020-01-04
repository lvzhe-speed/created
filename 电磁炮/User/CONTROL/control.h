#ifndef __CONTRL_H
#define __CONTRL_H

#include "stm32f10x.h"   
#include "./OPENMV/openmv.h"
#include "./LED/bsp_led.h"

#define LevelMotorScale 1000.0 //ˮƽ�����ʱ���Ƚ�ֵ��90�ȽǱ���
#define ElevationMotorScale 960.0//���������ʱ���Ƚ�ֵ��90�ȽǱ���

#define LevelTimValue 1450.0 //��̨����0ʱ��ʱ���Ƚ�ͨ�����趨ֵ
#define Elevation45Angle LevelTimValue-ElevationMotorScale/2//45�����Ƕ�Ӧ��ʱ���Ƚ�ֵ
#define CenterTimValue 1450.0 //��̨λ��ˮƽ����ʱ��ʱ���Ƚ�ͨ�����趨ֵ
#define MAXCenterDeviation CenterTimValue+LevelMotorScale/3.0//���ˮƽƫת��90
#define MINCenterDeviation CenterTimValue-LevelMotorScale/3.0//��Сˮƽƫת��-90

#define UnitAngle 0.05//���嵥λ�Ƕȱ��ڿ���

extern uint8_t ShootFlag,ChargeFlag,AotoChargeAndShootFlag;//���䣬�����Ʊ�־λ����TIM4��������ʱ��

void SetCenterDeviation(float DeviationAngle);//������̨��ˮƽ�����ߵ�ƫ��
void ChangeCenterDeviation(float ChangeAngle);//�ڵ�ǰ�����ϸı���������ƫ��
float GetCenterDeviation(void);//��ȡ��ǰ�趨��������ƫ��
void SetElevation(float Angle);//��������
void ChangeElevation(float ChangeAngle);//�ڵ�ǰ�����ϸı�����
float GetElevation(void);//��ȡ����

void TrackTarget(void);//����Ŀ��λ�ã�ʹ��ͷ����Ŀ��

void ShootAndChargeGPIOInit(void);//���䣬�����ƽų�ʼ��
void Shoot(void);//����
void Charge(void);//���
void AotoChargeAndShoot(void);//�Զ����ͷ���

#endif
