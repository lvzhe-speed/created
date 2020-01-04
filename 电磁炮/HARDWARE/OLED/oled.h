#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"
   




//OLED控制用函数
	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
void WriteCmd(u8 cmd);	
void WriteDate(u8 date);					   		    
void OLED_Init(void);
void OLED_Clear(void);
void Set_Pose(u8 Xpose,u8 Ypose);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 str,u8 size,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *str,u8 size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 size);
void OLED_HorizontalScroll(u8 page_start,u8 page_over);//水平滚动
void OLED_StopHorizontalScroll();//禁止滚动
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_DrawLinePoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_ShowDecimalNumber(u8 x,u8 y,float num,u8 size);
#endif  


	 

