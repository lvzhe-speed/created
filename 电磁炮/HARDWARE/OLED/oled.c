
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h" 
#include "delay.h"
#include "math.h"
#include "stdio.h"
#include "spi.h"


u8 OLED_GRAM[128][8];




	  	
//����OLED��ʾ    
void OLED_Display_On(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X14);  //������ɱ�
    WriteCmd(0XAF);  //OLED����

}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	 WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X10);  //�رյ�ɱ�
    WriteCmd(0XAE);  //OLED����

}		

void OLED_Clear()
{
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
	
}

void Set_Pose(u8 Xpose,u8 Ypose)
{
	u8 page_dress,Column_high_dress,Column_low_dress;
	if(Xpose>127||Ypose>63)return;
	page_dress=Ypose/8;	//��������һҳ
	Column_low_dress=Xpose&0x0f;
	Column_high_dress=(Xpose&0xf0)>>4;
	WriteCmd(0xb0+page_dress);//ȷ��Ҫд���ҳ
	WriteCmd(0x00+Column_low_dress);
	WriteCmd(0x10+Column_high_dress);
}




//��ҳд�뵥Ƭ����GRAM
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
	u8 chr=str-' ';//�ַ�ƫ����
	u8 i,t,j;
	u8 sum_size=(size/8+((size%8)?1:0))*(size/2);//�õ�һ���ַ��ܹ��ж��ٸ��ֽ�
	
	for(i=0;i<sum_size;i++)
	{
		if(size==12)temp=asc2_1206[chr][i];
		else if(size==16)temp=asc2_1608[chr][i];
		else if(size==24)temp=asc2_2412[chr][i];
		else return;
		for(j=0;j<8;j++)
		{
			t=temp&0x80;//ȡ���ֿ��е�����
			temp<<=1;
			if(t)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			y++;
			if((y-y0)==size)//�������峤��
			{
				y=y0;
				x++;
				break;//�������ѭ��
			}
			
		}
		
	}


}

void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		WriteCmd(0xb0+i);   //����ҳ��ַ��0~7��
        WriteCmd(0x00);      //������ʾλ�á��е͵�ַ
        WriteCmd(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)WriteData(OLED_GRAM[n][i]); 

	}   

}

//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//������ʾ
}


void OLED_ShowString(u8 x,u8 y,u8*str,u8 size)
{
	while(*str<='~'&&*str>=' ')
	{
		if(x>(128-size/2))x=0;//��ֹ�ַ�������Ļ
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
	length=(int)log10(num) + 1;//�õ����ֵ�λ��
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
	WriteCmd(0X2E);//����ˮƽ������Ҫ��ֹ����RAM������ݳ���
	WriteCmd(0x29);//:����ˮƽ����
	WriteCmd(0x00);//A:���ֽ�
	WriteCmd(0x00+page_start);//B:ˮƽ��ʼҳ
	WriteCmd(0x03);//C:ˮƽ�������ٶ�
	WriteCmd(0x00+page_over);//D:ˮƽ����ҳ
	WriteCmd(0X00);//E:ÿ�δ�ֱ������λ��
	WriteCmd(0x2f);//��������
}
void OLED_StopHorizontalScroll()
{
	WriteCmd(0X2E);
}

void OLED_Init()
{

	SPI_OLED_Init();
delay_ms(100);
 	WriteCmd(0xAE); //�ر���ʾ
	WriteCmd(0xD5); //����ʱ�ӷ�Ƶ����,��Ƶ��
	WriteCmd(0x80);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	WriteCmd(0xA8); //��������·��,���ø�����
	WriteCmd(0X3F); //Ĭ��0X3F(1/64) 
	WriteCmd(0xD3); //������ʾƫ��
	WriteCmd(0X00); //Ĭ��Ϊ0��������Ļ��ʼ��

	WriteCmd(0x40); //������ʾ��ʼ�� [5:0],����.
													    
	WriteCmd(0x8D); //��ɱ�����
	WriteCmd(0x14); //bit2������/�ر�
	WriteCmd(0x20); //�����ڴ��ַģʽ
	WriteCmd(0x02); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	WriteCmd(0xA1); //���ض�������,bit0:0,0->0;1,0->127;
	WriteCmd(0xC0); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	WriteCmd(0xDA); //����COMӲ����������
	WriteCmd(0x12); //[5:4]����
		 
	WriteCmd(0x81); //�Աȶ�����
	WriteCmd(0x7F); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	WriteCmd(0xD9); //����Ԥ�������
	WriteCmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	WriteCmd(0xDB); //����VCOMH ��ѹ����
	WriteCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	WriteCmd(0xA4); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	WriteCmd(0xA6); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	WriteCmd(0xAF); //������ʾ	 
	OLED_Clear();


}

//���ڻ��ߵĻ��㺯��
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
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
	OLED_DrawLinePoint(uRow,uCol);//���� 
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


//��ʾС��
void OLED_ShowDecimalNumber(u8 x,u8 y,float num,u8 size)
{
	char buffer[8];
	sprintf(buffer,"%5.2f",num);//������ת�����ַ�
	OLED_ShowString(x,y,(u8*)buffer,size);
}




