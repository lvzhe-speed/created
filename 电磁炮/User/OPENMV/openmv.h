#ifndef __OPENMV_H
#define __OPENMV_H

#include "./USART/bsp_usart.h"

#define OpenMVCenterX 80.0 //openMVˮƽ��Ұ����

typedef struct
{
	int CurrentPositionX;//Ŀ���ھ�ͷ�е�ˮƽλ��0~160
	int CurrentPositionY;//Ŀ���ھ�ͷ�е�ˮƽλ��0~120����ǰδʹ�ã�
	int CurrentPositionS;//Ŀ���뾵ͷ�ľ���
}PositionTypedef;

extern int PositionX;
extern uint8_t PositionXUpdataFlag;
extern uint32_t TargetDistance;
extern uint8_t TargetDistanceUpdataFlag;

//uint8_t GetTargetPosition(PositionTypedef* PositionPtr);//��ȡ��ǰλ����Ϣ��openmv�Ӵ���2��
void UpdataPositionData(void);//����λ������
int GetPositionXData(void);
uint32_t GetDistanceData(void);

#endif
