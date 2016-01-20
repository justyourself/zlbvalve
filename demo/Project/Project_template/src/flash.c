/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : flash.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2016-1-3
 * Version    : V1.0
 * Change     :
 * Description: �������溯��,����EEPROM�������б���
 */
/*************************************************************************/
#include <stdlib.h>
#include "flash.h"
#include "key.h"


/******************************��������***********************************/





/******************************��������***********************************/
/***************************************************************************/
//����:	void Param_Init(void)
//˵��:	������ʼ��
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.22
/***************************************************************************/
void Param_Init(void)
{
	uint8_t flag = 0;
	uint16_t crc = 0;
	ParamStr paratmp;	

	//���ô洢�����ʱ���ǲ��̶�ģʽ,�����ʱΪ�̶�ʱ���һ��,δ����ʱΪ�̶�ʱ��
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
	//��ȡĬ�����ݴ洢״̬��־
	ReadString(DEFAULTBLOCK, 1, &flag);
	if(flag)
	{
		ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&paratmp);
		crc = CRC_JY((uint8_t *)&paratmp, sizeof(ParamStr)-2);
		if(crc != paratmp.CRC)
		{
			//У��ʧ��,�ָ�Ĭ��ֵ
			Default_Data();
		}
	}
	else
	{
		//δ�洢Ĭ��ֵ,�ָ�Ĭ��ֵ
		Default_Data();
	}

	//��ȡ�˵�����
	ReadString(PARAMBLOCK, 1, &flag);
	if(flag)
	{
		ReadString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		crc = CRC_JY((uint8_t *)&ParaData, sizeof(ParamStr)-2);
		if(crc != ParaData.CRC)
		{
			//У��ʧ��,��Ĭ�����ݴ洢����ȡ����
			ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
			//���浽�˵����ݿ���
			WriteString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		}
	}
	else
	{
		//flag��ȡʧ��,��Ĭ�����ݴ洢����ȡ����
		ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		//���浽�˵����ݿ���
		WriteString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
	}
}
/***************************************************************************/
//����:	void Default_Data(void)
//˵��:	Ĭ����������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2016.1.6
/***************************************************************************/
void Default_Data(void)
{
	ParamStr *paratmp = NULL;

	paratmp = (ParamStr *)malloc(sizeof(ParamStr));
	//���ݴ��ڱ�־
	paratmp->flag = 1;							//������
	//�����˵�Ĭ������
	paratmp->Basic_data.language = 1;			//������ʾ
	paratmp->Basic_data.allopen = 920;			//ȫ��ֵ,��Ҫ����ʵ�ʽ��е�������
	paratmp->Basic_data.allclose = 100;			//ȫ��ֵ,��Ҫ����ʵ�ʽ��е�������
	paratmp->Basic_data.out4ma = 5;				//���4mAУ׼
	paratmp->Basic_data.out20ma = 5;			//���20mAУ׼	
	paratmp->Basic_data.deadzone = 3;			//��������ֵ
	paratmp->Basic_data.errtype = close;		//�������͹ر�,ȫ��,ȫ��,����,ָ��,
	paratmp->Basic_data.errplace = 50;			//����ʱ�ƶ���ָ��λ��
#ifdef G_TYPE
	paratmp->Basic_data.powerofftype = close;	//�ϵ�����,ͬ��������
	paratmp->Basic_data.poweroffplace = 50;		//�ϵ�ʱ�ƶ���ָ��λ��
	paratmp->Basic_data.poweroffdelay = 50;		//�ϵ�ʱ�ƶ���ָ��λ��	
	paratmp->Basic_data.rlstatus = local;		//���ػ�Զ��״̬(MTϵ��ΪӲ������)
#endif
	//�߼��˵�Ĭ������
	paratmp->Advancd_data.logic = 0;			//��������,0,������,1,������
#ifdef G_TYPE
	paratmp->Advancd_data.maxspeed = 2;			//����ٶ�
	paratmp->Advancd_data.minspeed = 1;			//��С�ٶ�
	paratmp->Advancd_data.esdtype = close;		//ESD����,ͬ��������
	paratmp->Advancd_data.esdplace = 50;		//ESDʱ�ƶ���ָ��λ��
	paratmp->Advancd_data.startoption = 1;		//����ѡ��,0,����,1,Զ��
#endif
	paratmp->Advancd_data.alarm1 = close;		//����1����:�ر�,ȫ��,ȫ��,�޸��ź�,�ع�����,��������,ָ��λ��,�ۺϱ���
	paratmp->Advancd_data.alarm2 = close;		//����2����	
#ifdef G_TYPE
	paratmp->Advancd_data.alarm3 = close;		//����3����	
	paratmp->Advancd_data.alarm4 = close;		//����4����	
	paratmp->Advancd_data.alarm5 = close;		//����5����
	paratmp->Advancd_data.alarm6 = close;		//����6����
#endif
	paratmp->Advancd_data.alarmplace = 50;		//ָ��λ�ñ����е�λ��
	paratmp->Advancd_data.signaltype = 0;		//0,4~20mA�ź�,1,0~20mA�ź�,2,0~10V�ź�
	paratmp->Advancd_data.addr = 3200;			//�豸��ַ,U16
	//�������ò˵�
	paratmp->Factory_data.password = 110;		//��������		
#ifdef G_TYPE
	paratmp->Factory_data.slowrange = 3;		//���ٷ�Χ
#endif
	paratmp->Factory_data.moment = 1;			//����У׼
	paratmp->Factory_data.momentunits = 0;		//���ص�λ 0,Nm;1,N
  	paratmp->Factory_data.openmoment = 5;		//������
  	paratmp->Factory_data.closemoment = 3;		//������
  	paratmp->Factory_data.overmoment1 = 1;		//������ϵ��1
  	paratmp->Factory_data.overmoment2 = 2;		//������ϵ��2
  	paratmp->Factory_data.in4ma = 2;			//����4maУ׼
  	paratmp->Factory_data.in20ma = 5;			//����20maУ׼
  	paratmp->Factory_data.number = "����֣��";	//��Ʒ��ŵ�ַ
  	paratmp->Factory_data.factor = 2;			//ϵ��
  	paratmp->Factory_data.overdelay = 30;		//��������ʱ
	//CRC���ݼ���
	paratmp->CRC = CRC_JY((uint8_t *)paratmp, sizeof(ParamStr)-2);
	//���������ݴ洢��
	WriteString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)paratmp);
	//�ͷ��ڴ�ռ�
	free(paratmp);
	
}
/***************************************************************************/
//����:	uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen)
//˵��:	16λCRCУ��
//����: puchMsg ��Ҫ����У������� usDataLen ��ҪУ������ݳ���
//���: 16λCRCУ��ֵ
//�༭: zlb
//ʱ��: 2016.1.4
/***************************************************************************/
uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t crc;
	uint8_t  i,j;
	uint8_t TT;

	crc=0xffff;
	for (j=0;j<usDataLen;j++)
	{
		crc=crc ^ *(puchMsg+j);
		for (i=0;i<8;i++)
		{
			TT=crc&1;
			crc=crc>>1;
			crc=crc&0x7fff;
			if (TT==1)
				crc=crc^0xa001;
			crc=crc&0xffff;
		}

	}
	return(crc);
}





