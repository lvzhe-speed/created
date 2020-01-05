#include "spi.h"


u8 SPI1_ReadWriteByte(u8 Txdata)
{
	u16 i;
	while((SPI1->SR&1<<1)==0)//等待发送为空
	{
		i++;
		if(i>0xfffe)return 0;
	}
	i=0;
	SPI1->DR=Txdata;
	while((SPI1->SR&1<<0)==0)//等待接收为非空
	{
		i++;
		if(i>0xfffe)return 0;
	}

	return SPI1->DR;

}

void SPI1_SetSpeed(u8 SPI_SPEED)
{
	SPI_SPEED&=0X07;
	SPI1->CR1&=0xffc7;//清除速度
	SPI1->CR1|=SPI_SPEED<<3;
	SPI1->CR1|=1<<6;
}


void SPI1_Init()
{
	RCC->APB2ENR|=1<<2;       //PORTA时钟使能 	 
	RCC->APB2ENR|=1<<12;      //SPI1使能
	
	GPIOA->CRL&=0X000FFFFF;
	GPIOA->CRL|=0XBBB00000;//PA5.6.7复用 	    
	GPIOA->ODR|=7<<5;    //PA5.6.7上拉
	
	SPI1->CR1|=0<<10;//全双工
	SPI1->CR1|=1<<9;//设备软件管理
	SPI1->CR1|=1<<8;
	SPI1->CR1|=1<<2;//主设备
	SPI1->CR1|=0<<11;//8bit数据格式
	SPI1->CR1|=1<<1;//时钟极性：空闲时时钟高电平
	SPI1->CR1|=1<<0;//时钟相位，数据在第二个时钟边沿采样
	SPI1->CR1|=7<<3;//波特率控制
	SPI1->CR1|=0<<7;//先发MSB
	SPI1->CR1|=1<<6;//使能spi
	
SPI1_ReadWriteByte(0xff);//启动传输

}

void SPI_OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );

	//片选信号初始化
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	SPI1_Init();		   //初始化SPI
	SPI1_SetSpeed(SPI_SPEED_4);	//设置为18M时钟,高速模式
}  


/*************************************************************************/
/*函数功能: 写命令                                                        */
/*************************************************************************/
void WriteCmd(unsigned char cmd)
{
	OLED_CS_LOW;
	OLED_DC_LOW;
    SPI1_ReadWriteByte(cmd);
}
/*************************************************************************/
/*函数功能: 写数据                                                        */
/*************************************************************************/
void WriteData(unsigned char data)
{
	OLED_CS_LOW;
	OLED_DC_HIGH;
    SPI1_ReadWriteByte(data);
}


