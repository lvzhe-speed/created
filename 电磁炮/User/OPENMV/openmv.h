#ifndef __OPENMV_H
#define __OPENMV_H

#include "./USART/bsp_usart.h"

#define OpenMVCenterX 80.0 //openMV水平视野中心

typedef struct
{
	int CurrentPositionX;//目标在镜头中的水平位置0~160
	int CurrentPositionY;//目标在镜头中的水平位置0~120（当前未使用）
	int CurrentPositionS;//目标与镜头的距离
}PositionTypedef;

extern int PositionX;
extern uint8_t PositionXUpdataFlag;
extern uint32_t TargetDistance;
extern uint8_t TargetDistanceUpdataFlag;

//uint8_t GetTargetPosition(PositionTypedef* PositionPtr);//获取当前位置信息（openmv接串口2）
void UpdataPositionData(void);//更新位置数据
int GetPositionXData(void);
uint32_t GetDistanceData(void);

#endif
