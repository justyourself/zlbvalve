/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : flash.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2016-1-3
 * Version    : V1.0
 * Change     :
 * Description: �������溯��,����EEPROM�������б���
 */
/*************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "flash_eeprom.h"

//�Զ���ṹ��

//�����˵����ݽṹ,ȫ������16λ������Ϊ���淽���������
//�ڴ�ռ�Ƚϴ�,�����ڴ洢����������
typedef struct _BASIC_DATA_
{
  uint16_t  language;					//����ѡ��
  uint16_t  allopen;					//ȫ��
  uint16_t  allclose;					//ȫ��
  uint16_t  out4ma;						//���4mAУ׼
  uint16_t  out20ma;					//���20mAУ׼
  uint16_t  deadzone;					//����
  uint16_t  errtype;					//�źŹ�������
  uint16_t  errplace;					//�źŹ���λ��
  uint16_t  powerofftype;				//�ϵ綯������
  uint16_t  poweroffplace;				//�ϵ����λ��
  uint16_t  rlstatus;					//Զ���͵�״̬	
}BasicDataStr;
//�߼��˵����ݽṹ
typedef struct _ADVANCED_DATA_
{
  uint8_t  startoption;				//����ѡ��
  uint8_t  logic;						//��������
  uint8_t  maxspeed;					//����ٶ�
  uint8_t  minspeed;					//��С�ٶ�
  uint8_t  esdtype;						//ESD����
  uint8_t  esdplace;					//ESD��λ
  uint8_t  alarm1;						//�����ź�1
  uint8_t  alarm2;						//�����ź�2
  uint8_t  alarm3;						//�����ź�3  
  uint8_t  alarm4;						//�����ź�4  
  uint8_t  alarm5;						//�����ź�5  
  uint8_t  alarm6;						//�����ź�6 
  uint8_t  alarmplace;					//������λ
  uint8_t  signaltype;					//�ź�����
  uint16_t addr;						//�豸��ַ
}AdvancedDataStr;
//�����˵�����
typedef struct _FACTORY_DATA_
{
  uint16_t  password;					//��������
  uint16_t  slowrange;					//���ٷ�Χ
  uint16_t  moment;						//����У׼
  uint16_t  momentunits;				//���ص�λ
  uint16_t  openmoment;				//������
  uint16_t  closemoment;				//������
  uint16_t  overmoment1;				//������ϵ��1
  uint16_t  overmoment2;				//������ϵ��2
  uint16_t  in4ma;						//����4maУ׼
  uint16_t  in20ma;						//����20maУ׼
  uint16_t  *number;					//��Ʒ��ŵ�ַ
  uint16_t  factor;						//ϵ��
  uint16_t  overdelay;					//��������ʱ
}FactoryDataStr;
//�����ṹ��
typedef struct _PARAM_STR_
{
	BasicDataStr Basic_data;			//�����˵�����
	AdvancedDataStr Advancd_data;		//�߼��˵�����
	FactoryDataStr Factory_data;		//�����˵�����
	uint16_t CRC;						//CRCУ������
	
}ParamStr;
//�궨��
#define DEFAULTBLOCK	Block_0			//�������ò�������Block��
#define PARAMBLOCK		Block_1			//�ϵ��ȡ��������Block��

//��������
extern ParamStr ParaData;						//�˵��������ݽṹ��

//��������
void Param_Init(void);



#endif//__FLASH_H