#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(ENTER==0||UPER==0||DOWN==0||BACK==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(ENTER==0)return ENTER_PRES;
		else if(UPER==0)return UPER_PRES;
		else if(DOWN==0)return DOWN_PRES; 
		else if(BACK==0)return BACK_PRES;
	}else if(ENTER==1&&UPER==1&&DOWN==1&&BACK==1)key_up=1; 	     
	return 0;// �ް�������
}
