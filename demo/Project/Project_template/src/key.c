/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : key.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: key.c ��������
 */
/*************************************************************************/
#include "stm8s_gpio.h"
#include "JLX12864G.h"
#include "key.h"
#include "menu.h"

/******************************��������***********************************/
uint8_t ADC_Counter = 0;
uint8_t ADC_Channel = ADC2_CHANNEL_4;		//Ĭ��ADCΪ����ͨ��,λ�Ʋɼ�
ADCValueStr RealADC;						//ʵʱADCֵ
ADCValueStr UnitADC;						//����ADCֵ
ADCValueStr ValidADC;						//��ЧADCֵ
FlagTypeStr flag = 0;					    //״̬��־
uint16_t Shift_Step = 20;					//λ��ADCƫ�ƶ��ٿ�ʼֹͣ���ת��
uint8_t status;								//��ǰ״̬(Զ����͵�)
uint32_t light_flag = 1;					//����Ʊ�־,Ϊ0ʱ�����м���


/******************************��������***********************************/
/***************************************************************************/
//����:	void Delay(uint8_t ms)
//˵��:	��ʱʱ��ms
//����: ms ��ʱʱ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Delay(uint32_t ms)
{
	uint8_t i;
	while (ms != 0)
	{
		ms--;
		for(i=0;i<100;i++);
	}
}
/***************************************************************************/
//����:	void Key_Init(void)
//˵��:	��ʼ��KEY
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Key_Init(void)
{
	//���ð���1 2 3Ϊ����
	GPIO_Init(GPIOG,(GPIO_Pin_TypeDef)(HR1|HR2|HR3),GPIO_MODE_IN_PU_NO_IT);
	//���ð���4
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)HR4,GPIO_MODE_IN_PU_NO_IT);
}
/***************************************************************************/
//����:	void LED_Init(void)
//˵��:	��ʼ��LED
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LED_Init(void)
{
	//��ʼ��LED IOΪ����
	GPIO_Init(LED_PORT,(GPIO_Pin_TypeDef)(ERRLED|GREENLED|BLUELED),GPIO_MODE_OUT_PP_HIGH_FAST);

	 //�жϵ����������
	if(GPIO_ReadInputPin(HEAT_PORT, HEAT_PIN))
	{
		//�������ϵ�
		LED_LightON(ERRLED);
	}
	if(!GPIO_ReadInputPin(GPIOE,(GPIO_Pin_TypeDef)(REMOTE)))
	{
		LED_LightON(BLUELED);			//��Զ��ָʾ��
		flag.local = remote;
	}
	else
	{
		LED_LightON(GREENLED);			//�򿪾͵�ָʾ��
		flag.local = local;
	}
        
}
/***************************************************************************/
//����:	void InOut_Init(void)
//˵��:	��ʼ����������ӿ� ������ȹܽ�Ϊ�жϹܽ�
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void InOut_Init(void)
{
	//��ʼ������OUT IOΪ�����������
	GPIO_Init(OUT_PORT,(GPIO_Pin_TypeDef)(ERR1|ERR2|OPEN|CLOSE),GPIO_MODE_OUT_PP_HIGH_FAST);
	//��ʼ������IN IOΪ��������C�� ��������UV_PIN VW_PIN WU_PIN
	GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)(UV_PIN|VW_PIN|WU_PIN),GPIO_MODE_IN_PU_NO_IT);
	//��ʼ������IN IOΪ��������E�� Զ���͵�REMOTE �ж�ģʽ
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(REMOTE),GPIO_MODE_IN_FL_IT);
	//��ʼ������IN IOΪ��������E�� �����������HEAT_PIN Ϊ�ж�����
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(HEAT_PIN),GPIO_MODE_IN_FL_IT);

	//��ʼ�����Ϊ�ߵ�ƽ
	GPIO_WriteHigh(OUT_PORT,(GPIO_Pin_TypeDef)(ERR1|ERR2|OPEN|CLOSE));
	//�ֺϿ������״̬,0�ֺ����ʹ��,1�ֺ����ʧ��
	flag.overclose = 0;
	flag.overopen = 0;
	
	//ʹ���������½��ش����ж�(Զ���͵�Ϊ�������½��ش����ж�,��������ж�Ϊ�½����ж� )
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_RISE_FALL);
}
/***************************************************************************/
//����:	uint8_t Key_Read(void)
//˵��:	��ʼ��LED
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
uint8_t Key_Read(void)
{
	uint8_t keydata = 0;
	static uint8_t keyup = 0;
	//��ȡ����ֵ ����˳�����λ�ֱ����HR1 HR2 HR3 HR4
	keydata = GPIO_ReadInputPin(GPIOG, (GPIO_Pin_TypeDef)(HR1|HR2|HR3));
	keydata |= GPIO_ReadInputPin(GPIOE, (GPIO_Pin_TypeDef)HR4);
	
	//ȥ����
	if(keyup && (keydata ^ 0xf0))
	{
		keyup = 0;
		//��ʱ10ms
		Delay(10);
		//��ȡ����ֵ
		keydata = GPIO_ReadInputPin(GPIOG, (GPIO_Pin_TypeDef)(HR1|HR2|HR3));
		keydata |= GPIO_ReadInputPin(GPIOE, (GPIO_Pin_TypeDef)HR4);
		if(keydata ^ 0xf0)
		{
			//��������ˢ�±����־
			if(light_flag == 0)
			{
				LCD_BacklightCmd(ENABLE);
				light_flag = 1;
				keydata = 0;
			}	
			return keydata;
		}	
	}
	else if((keydata ^ 0xf0) == 0)
	{
		keyup = 1;
		return 0;
	}
        
	return 0;
}
/***************************************************************************/
//����:	void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel)
//˵��:	ͨ��ADC��ʼ������
//����: ADC2_Channel ADC2ͨ����,ADC2_SchmittTrigg_Channel ADC2˹���ش���ͨ����
//���: ��
//�༭: zlb
//ʱ��: 2015.12.22
/***************************************************************************/
void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel)
{
	// ADC�ָ�Ĭ��ֵ
	ADC2_DeInit();
	//ѭ��ģʽ 
	ADC2_Init(ADC2_CONVERSIONMODE_SINGLE , ADC2_Channel, ADC2_PRESSEL_FCPU_D18,\
		ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SchmittTrigg_Channel, DISABLE);
	
	//ʹ��ADC
	ADC2_Cmd(ENABLE);
	//ʹ���ж�
	ADC2_ITConfig(ENABLE);
	//��ʼ��ADC����
	RealADC.current = 0;
	RealADC.shift = 0;
	UnitADC.current = 0;
	//ȫ����ȫ�������趨֮����Ҫ���¸���ֵ
	UnitADC.shift = (ParaData.Basic_data.allopen - ParaData.Basic_data.allclose)/100;
	UnitADC.shift = (ParaData.Basic_data.deadzone * UnitADC.shift)/10;
}
/***************************************************************************/
//����:	void ADC_Shift_Init(void)
//˵��:	��ʼ��λ�ƴ�����ADC(����)
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void ADC_Shift_Init(void)
{
	// ADC�ָ�Ĭ��ֵ
	ADC2_DeInit();
	//ѭ��ģʽ 
	ADC2_Init(ADC2_CONVERSIONMODE_CONTINUOUS , ADC2_CHANNEL_4, ADC2_PRESSEL_FCPU_D18,\
		ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SCHMITTTRIG_CHANNEL4,DISABLE);
	ADC2_ITConfig(DISABLE);
	
	//ʹ��ADC
	ADC2_Cmd(ENABLE);
	//��ʼת��
	ADC2_StartConversion();
}
/***************************************************************************/
//����:	void TIM4_Init(void)
//˵��:	TIM4��ʱ���жϳ�ʼ��
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void TIM4_Init(void)
{
	TIM4_DeInit();
	//��ʼ��TIM4Ϊ�ڲ�ʱ��64��Ƶ ��������Ϊ1ms 0-249
	TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249);
	//����TIM4�����ж�
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	//ʹ��TIM4
	TIM4_Cmd(ENABLE);
}
/***************************************************************************/
//����:	uint8_t Analysis_key(uint8_t key)
//˵��:	����˵��а���������
//����: key ���밴��ֵ
//���: ������Ҫ�����޸ĺ�İ���ֵ
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
uint8_t Analysis_key(uint8_t key)
{
	switch(key)
	{
		case ESC:
			return key;
		case SET:
			keyset ++;
			break;
		case UP:
			keyup ++;
			break;
		case DOWN:
			keydown ++;
			break;
		default:
			return key;
			break;
	}
	return 0;
}
/***************************************************************************/
//����:	void Motor_Out(uint8_t action, FunctionalState statu)
//˵��:	��������������,ʹ�ܵ����ת��ʧ�ܵ����ת
//����: action �����߹��˶�, statu ״̬Ϊʹ�ܻ�ʧ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Motor_Out(uint8_t action, FunctionalState statu)
{
	if(statu == ENABLE)
	{
		GPIO_WriteHigh(OUT_PORT, action);
	}
	else
	{
		GPIO_WriteLow(OUT_PORT, action);
	}
}
/***************************************************************************/
//����:	void Shift_Protect(void)
//˵��:	λ�Ʊ�������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2016.1.23
/***************************************************************************/
void Shift_Protect(void)
{
	//�����Ƿ񳬹�����ֵ(��ȷ������ADֵ�Ĵ�С��ϵ,��Ҫ��ӱȽϳ���)
	if(ValidADC.shift < (ParaData.Basic_data.allclose + Shift_Step))
	{
		Motor_Out(CLOSE, DISABLE);
		flag.overclose = 1;
	}
	else if(ValidADC.shift > (ParaData.Basic_data.allopen - Shift_Step))
	{
		Motor_Out(OPEN, DISABLE);
		flag.overopen = 1;
	}
	else
	{
		Motor_Out(CLOSE, ENABLE);
		Motor_Out(OPEN, ENABLE);
		flag.overopen = 0;
		flag.overclose = 0;
	}
}
/***************************************************************************/
//����:	void Current_Protect(void)
//˵��:	����������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2016.1.23
/***************************************************************************/
void Current_Protect(void)
{
	//�����Ƿ����
}















