/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : key.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: key.h ��������ͷ�ļ�
 */
/*************************************************************************/
#ifndef __KEY_H
#define __KEY_H
#include "stm8s_gpio.h"
#include "stm8s_adc2.h"

// �ṹ�嶨��
//״̬����
typedef enum {local, remote} StatusType;
//״̬�ṹ�嶨��
typedef struct _STATUS_FLAG_
{
	uint8_t heat:1;					//�����������־,0,����,1,����
	uint8_t move:1;					//����˶�����־,0,δ�˶�,1,�˶���
	uint8_t overclose:1;			//����ط����г̱�־,0,δ���г�,1,���г�
	uint8_t overopen:1;			//����������г̱�־,0,δ���г�,1,���г�
	uint8_t local:1;				//���Զ���͵�״̬��־,0,�͵�,1,Զ��
	uint8_t set:1;					//�˵�����״̬��־,0,��ͨ,1,����
	uint8_t light:1;				//��屳��״̬��־,0,������,1,������
	uint8_t reserve:1;				//Ԥ��
}FlagTypeStr;
//ADC�ɼ�ֵ����
typedef struct _ADC_VALUE_
{
	uint16_t shift;					//��λADCֵ
	uint16_t current;				//����ADCֵ
}ADCValueStr;
// �궨��
// ����
#define LOWPOWER	420000u			//7*60*1000 7min����ʱ��
// KEY ����
#define HR1			GPIO_PIN_5		//G5�� DOWN
#define HR2			GPIO_PIN_6		//G6�� ESC
#define HR3			GPIO_PIN_7		//G7�� SET
#define HR4			GPIO_PIN_4		//E4�� UP
// KEY��ֵ����
#define UP			0xD0			//UP ������ֵ
#define DOWN		0xE0			//DOWN ������ֵ
#define ESC			0xB0			//ESC ������ֵ
#define SET			0x70			//SET ������ֵ
// LED ����
#define ERRLED		GPIO_PIN_7		//D7�� ��ɫ���ϵ�
#define GREENLED	GPIO_PIN_5		//D5�� ��ɫ�͵�״ָ̬ʾ��
#define BLUELED		GPIO_PIN_6		//D6�� ��ɫԶ��״ָ̬ʾ��
#define LED_PORT	GPIOD 
// �������� ����1 ����2 ��ֹͣ ��ֹͣ
#define ERR1		GPIO_PIN_3		//B3�� 9_1
#define ERR2		GPIO_PIN_2		//B2�� 9_2
#define CLOSE		GPIO_PIN_1		//B1�� 9_3
#define OPEN		GPIO_PIN_0		//B0�� 9_4
#define OUT_PORT	GPIOB
// ���붨�� ��������ź� U V W ���������ź� REMOTE Զ���͵��ź�
#define REMOTE		GPIO_PIN_7		//E7�� 9_10
#define HEAT_PIN	GPIO_PIN_6		//E6�� 9_5
#define HEAT_PORT	GPIOE			
#define UV_PIN		GPIO_PIN_1		//C1�� 9_6
#define VW_PIN		GPIO_PIN_2		//C2�� 9_7
#define WU_PIN		GPIO_PIN_3		//C3�� 9_8
// ADC���� ��������AD�ź� ����������AD�ź� �г�����AD�ź�
#define CURRENT		GPIO_PIN_7		//B7�� 9_9 ��������
#define SENSOR		GPIO_PIN_7		//F7�� SENSOR
#define R_RE		GPIO_PIN_4		//B4�� �г�����

//LED ����
#define LED_LightON( LED )  GPIO_WriteLow(LED_PORT, LED)
#define LED_LightOFF( LED)	GPIO_WriteHigh(LED_PORT, LED)

//��������
extern uint8_t ADC_Counter ;		//ADCͨ���ɼ�������
extern uint8_t ADC_Channel ;		//Ĭ��ADCΪ����ͨ��,λ�Ʋɼ�
extern uint16_t Shift_Step ;		//λ��ADCƫ�ƶ��ٿ�ʼֹͣ���ת��
extern uint8_t status;				//��ǰ״̬(Զ����͵�)
extern uint32_t light_flag;		//����Ʊ�־
extern FlagTypeStr flag;			//״̬��־
extern ADCValueStr ValidADC;		//��ЧADCֵ
extern ADCValueStr RealADC;			//ʵʱADCֵ
extern ADCValueStr UnitADC;			//����ADCֵ
//��������
void Delay(uint32_t ms);
void Key_Init(void);
void LED_Init(void);
uint8_t Key_Read(void);
void InOut_Init(void);
void ADC_Shift_Init(void);			//����(δʹ��)
void TIM4_Init(void);
uint8_t Analysis_key(uint8_t key);
void Motor_Out(uint8_t action, FunctionalState statu);
void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel);
void Shift_Protect(void);
void Current_Protect(void);















#endif//__KEY_H