
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h" 
#include "delay.h"
#include "math.h"
#include "stdio.h"
#include "spi.h"


u8 OLED_GRAM[128][8];




	  	
//开启OLED显示    
void OLED_Display_On(void)
{
	WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X14);  //开启电荷泵
    WriteCmd(0XAF);  //OLED唤醒

}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	 WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X10);  //关闭电荷泵
    WriteCmd(0XAE);  //OLED休眠

}		

void OLED_Clear()
{
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
	
}

void Set_Pose(u8 Xpose,u8 Ypose)
{
	u8 page_dress,Column_high_dress,Column_low_dress;
	if(Xpose>127||Ypose>63)return;
	page_dress=Ypose/8;	//计算在哪一页
	Column_low_dress=Xpose&0x0f;
	Column_high_dress=(Xpose&0xf0)>>4;
	WriteCmd(0xb0+page_dress);//确定要写入的页
	WriteCmd(0x00+Column_low_dress);
	WriteCmd(0x10+Column_high_dress);
}




//按页写入单片机的GRAM
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 page,column,point;
	if(x>127||y>63)return;
	page=7-y/8; 
	column=x;
	point=1<<(7-y%8);
	if(t)OLED_GRAM[column][page]|=point;
	else OLED_GRAM[column][page]&=~point;
	
}



void OLED_ShowChar(u8 x,u8 y,u8 str,u8 size,u8 mode)
{
	u8 temp;
	u8 y0=y;
	u8 chr=str-' ';//字符偏移量
	u8 i,t,j;
	u8 sum_size=(size/8+((size%8)?1:0))*(size/2);//得到一个字符总共有多少个字节
	
	for(i=0;i<sum_size;i++)
	{
		if(size==12)temp=asc2_1206[chr][i];
		else if(size==16)temp=asc2_1608[chr][i];
		else if(size==24)temp=asc2_2412[chr][i];
		else return;
		for(j=0;j<8;j++)
		{
			t=temp&0x80;//取出字库中的数据
			temp<<=1;
			if(t)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			y++;
			if((y-y0)==size)//超出字体长度
			{
				y=y0;
				x++;
				break;//跳出这个循环
			}
			
		}
		
	}


}

void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		WriteCmd(0xb0+i);   //设置页地址（0~7）
        WriteCmd(0x00);      //设置显示位置—列低地址
        WriteCmd(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)WriteData(OLED_GRAM[n][i]); 

	}   

}

//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}


void OLED_ShowString(u8 x,u8 y,u8*str,u8 size)
{
	while(*str<='~'&&*str>=' ')
	{
		if(x>(128-size/2))x=0;//防止字符超出屏幕
		OLED_ShowChar(x,y,*str,size,1);
		x=x+size/2;
		str++;
	}

}

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 size)
{
	int length;
	int i;
	u8 temp;
	length=(int)log10(num) + 1;//得到数字的位数
	for(i=length;i>0;i--)
	{
		if(x>(128-size/2))x=0;
		temp=num/(int)(pow(10,i-1));
		OLED_ShowChar(x,y,temp+'0',size,1);
		num%=(int)(pow(10,i-1));
		x+=(size/2);
	}

}


void OLED_HorizontalScroll(u8 page_start,u8 page_over)
{
	WriteCmd(0X2E);//启动水平滚动需要禁止否则RAM里的内容出错
	WriteCmd(0x29);//:向右水平滚动
	WriteCmd(0x00);//A:空字节
	WriteCmd(0x00+page_start);//B:水平起始页
	WriteCmd(0x03);//C:水平滚动的速度
	WriteCmd(0x00+page_over);//D:水平结束页
	WriteCmd(0X00);//E:每次垂直滚动的位移
	WriteCmd(0x2f);//启动滚动
}
void OLED_StopHorizontalScroll()
{
	WriteCmd(0X2E);
}

void OLED_Init()
{

	SPI_OLED_Init();
delay_ms(100);
 	WriteCmd(0xAE); //关闭显示
	WriteCmd(0xD5); //设置时钟分频因子,震荡频率
	WriteCmd(0x80);   //[3:0],分频因子;[7:4],震荡频率
	WriteCmd(0xA8); //设置驱动路数,设置复用率
	WriteCmd(0X3F); //默认0X3F(1/64) 
	WriteCmd(0xD3); //设置显示偏移
	WriteCmd(0X00); //默认为0，设置屏幕起始行

	WriteCmd(0x40); //设置显示开始行 [5:0],行数.
													    
	WriteCmd(0x8D); //电荷泵设置
	WriteCmd(0x14); //bit2，开启/关闭
	WriteCmd(0x20); //设置内存地址模式
	WriteCmd(0x02); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	WriteCmd(0xA1); //段重定义设置,bit0:0,0->0;1,0->127;
	WriteCmd(0xC0); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	WriteCmd(0xDA); //设置COM硬件引脚配置
	WriteCmd(0x12); //[5:4]配置
		 
	WriteCmd(0x81); //对比度设置
	WriteCmd(0x7F); //1~255;默认0X7F (亮度设置,越大越亮)
	WriteCmd(0xD9); //设置预充电周期
	WriteCmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	WriteCmd(0xDB); //设置VCOMH 电压倍率
	WriteCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	WriteCmd(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	WriteCmd(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	WriteCmd(0xAF); //开启显示	 
	OLED_Clear();


}

//用于画线的画点函数
void OLED_DrawLinePoint(u8 x,u8 y)
{
u8 page,column,point;
	if(x>127||y>63)return;
	page=y/8;
	column=x;
	point=1<<(y%8);
	OLED_GRAM[column][page]|=point;
	
}

void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
		u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
	OLED_DrawLinePoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  


}


//显示小数
void OLED_ShowDecimalNumber(u8 x,u8 y,float num,u8 size)
{
	char buffer[8];
	sprintf(buffer,"%5.2f",num);//将数字转换成字符
	OLED_ShowString(x,y,(u8*)buffer,size);
}




