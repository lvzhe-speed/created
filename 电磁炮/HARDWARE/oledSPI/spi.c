#include "spi.h"


u8 SPI1_ReadWriteByte(u8 Txdata)
{
	u16 i;
	while((SPI1->SR&1<<1)==0)//�ȴ�����Ϊ��
	{
		i++;
		if(i>0xfffe)return 0;
	}
	i=0;
	SPI1->DR=Txdata;
	while((SPI1->SR&1<<0)==0)//�ȴ�����Ϊ�ǿ�
	{
		i++;
		if(i>0xfffe)return 0;
	}

	return SPI1->DR;

}

void SPI1_SetSpeed(u8 SPI_SPEED)
{
	SPI_SPEED&=0X07;
	SPI1->CR1&=0xffc7;//����ٶ�
	SPI1->CR1|=SPI_SPEED<<3;
	SPI1->CR1|=1<<6;
}


void SPI1_Init()
{
	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ�� 	 
	RCC->APB2ENR|=1<<12;      //SPI1ʹ��
	
	GPIOA->CRL&=0X000FFFFF;
	GPIOA->CRL|=0XBBB00000;//PA5.6.7���� 	    
	GPIOA->ODR|=7<<5;    //PA5.6.7����
	
	SPI1->CR1|=0<<10;//ȫ˫��
	SPI1->CR1|=1<<9;//�豸�������
	SPI1->CR1|=1<<8;
	SPI1->CR1|=1<<2;//���豸
	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ
	SPI1->CR1|=1<<1;//ʱ�Ӽ��ԣ�����ʱʱ�Ӹߵ�ƽ
	SPI1->CR1|=1<<0;//ʱ����λ�������ڵڶ���ʱ�ӱ��ز���
	SPI1->CR1|=7<<3;//�����ʿ���
	SPI1->CR1|=0<<7;//�ȷ�MSB
	SPI1->CR1|=1<<6;//ʹ��spi
	
SPI1_ReadWriteByte(0xff);//��������

}

void SPI_OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );

	//Ƭѡ�źų�ʼ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	SPI1_Init();		   //��ʼ��SPI
	SPI1_SetSpeed(SPI_SPEED_4);	//����Ϊ18Mʱ��,����ģʽ
}  


/*************************************************************************/
/*��������: д����                                                        */
/*************************************************************************/
void WriteCmd(unsigned char cmd)
{
	OLED_CS_LOW;
	OLED_DC_LOW;
    SPI1_ReadWriteByte(cmd);
}
/*************************************************************************/
/*��������: д����                                                        */
/*************************************************************************/
void WriteData(unsigned char data)
{
	OLED_CS_LOW;
	OLED_DC_HIGH;
    SPI1_ReadWriteByte(data);
}


