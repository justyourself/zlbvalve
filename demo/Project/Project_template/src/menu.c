/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : menu.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-18
 * Version    : V1.0
 * Change     :
 * Description: menu.c �˵��ṹ����
 */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "key.h"
#include "JLX12864G.h"
#include "GT21H16S2Y.h"
#include "flash.h"



/******************************��������***********************************/
MenuItem TopMenu[1];
MenuItem Level1_Fun[3];
MenuItem Advanced_Fun[14];
MenuItem Basic_Fun[12];
MenuItem Factory_Fun[13];
MenuItem Language_Fun[2];
MenuItem Fault_Fun[5];
MenuItem Local_Fun[2];
MenuItem Logic_Fun[2];
MenuItem ESD_Fun[5];
MenuItem Alarm_Fun[7];
MenuItem Signal_Fun[3];
MenuItem Unit_Fun[2];

uint8_t *const Level1_Chinese[];
uint8_t *const Level1_English[];
uint8_t *const Basic_Chinese[];
uint8_t *const Basic_English[];
uint8_t *const Advanced_Chinese[];
uint8_t *const Advanced_English[];
uint8_t *const Factory_Chinese[];
uint8_t *const Factory_English[];
uint8_t *const Language_Chinese[];
uint8_t *const Language_English[];
uint8_t *const Fault_Chinese[];
uint8_t *const Fault_English[];
uint8_t *const Local_Chinese[];
uint8_t *const Local_English[];
uint8_t *const ESD_Chinese[];
uint8_t *const ESD_English[];
uint8_t *const Alarm_Chinese[];
uint8_t *const Alarm_English[];
uint8_t *const Signal_Chinese[];
uint8_t *const Unit_Chinese[];
uint8_t *const alarm_string[];
uint8_t *const default_string[];
uint8_t *const fault_string[];
uint8_t *const status_string[];
uint8_t *const param_string[];
uint8_t *const param_english[];
uint8_t *const status_english[];
/******************************��������***********************************/
//�˵���ת��¼��������
uint8_t FatherIndex[Menu_Level];               //���˵�����λ��
uint8_t layer = 0;                             //��ǰ�˵����ڲ�
MenuItem *manyou = NULL;						//�����������������˵�
uint8_t  dofunflag = DISABLE;					//ִ�к���ִ�б�־
uint8_t  refresh = ENABLE;						//ˢ�²˵���־
uint8_t  keyup = 0;								//������ʾ���水��ֵ����
uint8_t  keydown = 0;
uint8_t  keyset = 0;

//Top�˵���ʾ(��������,��Ҫ�ھ͵�״̬��,����SET��)
MenuItem TopMenu[1] = 
{
	{1,NULL,NULL,Display_TopMenu,NULL,Level1_Fun,NULL},
};
//Level1�˵���ʾ
MenuItem Level1_Fun[3] = 
{
	{3,NULL,"A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,NULL,"A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,NULL,"A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
//��һ���˵�����(����)
uint8_t *const Level1_Chinese[] =
{
	{"��������"},
	{"�߼�����"},
	{"��������"},
};
//��һ���˵�����(Ӣ��)
uint8_t *const Level1_English[] =
{
	{"Basi_set"},
	{"Adva_set"},
	{"Fact_set"},
};
//�����˵���ʾ
MenuItem Basic_Fun[12] =
{
	{12,NULL,"B01",Display_Basic,NULL,Language_Fun,Level1_Fun},
	{12,NULL,"B02",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B03",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B04",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B05",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B07",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,NULL,"B08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B09",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,NULL,"B10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B12",Display_Basic,NULL,Local_Fun,Level1_Fun},       
};
//�����˵�����(����)
uint8_t *const Basic_Chinese[] =
{
	{"����ѡ��"},
	{"ȫ������"},
	{"ȫ������"},
	{"����4mAЧ��"},
	{"����20mAЧ��"},
	{"��������"},
	{"�źŹ�������"},
	{"����ָ��λ��"},
	{"�ϵ綯������"},
	{"�ϵ�ָ��λ��"},
	{"�ϵ綯����ʱ"},
	{"Զ���ֶ�����"},
};
//�����˵�����(Ӣ��)
uint8_t *const Basic_English[] =
{
	{"Language"},
	{"Open_pos"},
	{"Close_pos"},
	{"In_4mA_adj"},
	{"In_20mA_adj"},
	{"Death_section"},
	{"Sign_err"},
	{"Sign_err_pos"},
	{"Power_off"},
	{"Power_pos"},
	{"Power_delay"},
	{"Set_local"},
};
//�߼��˵���ʾ
MenuItem Advanced_Fun[14] = 
{
	{14,NULL,"C01",Display_Basic,NULL,Logic_Fun,Level1_Fun},
	{14,NULL,"C02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C04",Display_Basic,NULL,ESD_Fun,Level1_Fun},
	{14,NULL,"C05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C06",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C07",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C08",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C09",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C10",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C11",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C12",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C13",Display_Basic,NULL,Signal_Fun,Level1_Fun},
	{14,NULL,"C14",Display_Basic,Set_Value,NULL,Level1_Fun},
};
//�߼��˵�����(����)
uint8_t *const Advanced_Chinese[] =
{
	{"��������"},
	{"����ٶ�"},
	{"��С�ٶ�"},
	{"ESD����"},
	{"ESD��λ"},
	{"����1����"},
	{"����2����"},
	{"����3����"},
	{"����4����"},
	{"����5����"},
	{"����6����"},
	{"������λ"},
	{"�ź�����"},
	{"�豸��ַ"},
};
//�߼��˵�����(Ӣ��)
uint8_t *const Advanced_English[] =
{
	{"Logic"},
	{"Max_Speed"},
	{"Min_Speed"},
	{"ESD_type"},
	{"ESD_pos"},
	{"Alarm_COM1"},
	{"Alarm_COM2"},
	{"Alarm_COM3"},
	{"Alarm_COM4"},
	{"Alarm_COM5"},
	{"Alarm_COM6"},
	{"Alarm_pos"},
	{"Sign_type"},
	{"Address"},
};
//��������
MenuItem Factory_Fun[13] = 
{
	{13,NULL,"D01",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D04",Display_Basic,NULL,Unit_Fun,Level1_Fun},
	{13,NULL,"D05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D07",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D09",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D12",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D13",Display_Basic,Set_Value,NULL,Level1_Fun},
};
//�����˵�����(����)
uint8_t *const Factory_Chinese[] =
{
	{"��������"},
	{"���ٷ�Χ"},
	{"����У׼"},
	{"���ص�λ"},
	{"��������"},
	{"�ط�����"},
	{"������ϵ��һ"},
	{"������ϵ����"},
	{"����4mAУ׼"},
	{"����20mAУ׼"},
	{"��Ʒ���"},
	{"ϵ��"},
	{"��������ʱ"},
};
//�����˵�����(Ӣ��)
uint8_t *const Factory_English[] =
{
	{"Change_Key"},
	{"Reduce"},
	{"Torque_adj"},
	{"Touque_unit"},
	{"Open_touque"},
	{"Close_touque"},
	{"Over_moment1"},
	{"Over_moment2"},
	{"Out_4mA_adj"},
	{"Out_20mA_adj"},
	{"No."},
	{"Factor"},
	{"Over_delay"},
};
//��������
MenuItem Language_Fun[2] = 
{
	{2,NULL,"E01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,NULL,"E02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//���Բ˵�����(����)
uint8_t *const Language_Chinese[] =
{
	{"����"},
	{"ENGLISH"},
};
//���Բ˵�����(Ӣ��)
uint8_t *const Language_English[] =
{
	{"CHINESE"},
	{"ENGLISH"},
};
//���ϲ˵�
MenuItem Fault_Fun[5] = 
{
	{5,NULL,"F01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F02",Display_Basic,Set_Value,NULL,Basic_Fun},	
	{5,NULL,"F03",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F04",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F05",Display_Basic,Set_Value,NULL,Basic_Fun},
};
//���ϲ˵�����(����)
uint8_t *const Fault_Chinese[] =
{
	{"�ر�"},
	{"ȫ��"},
	{"ȫ��"},
	{"����"},
	{"ָ��"},
};
//���ϲ˵�����(Ӣ��)
uint8_t *const Fault_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"Keep"},
	{"Set_pos"},
};
//Զ���͵�����
MenuItem Local_Fun[2] = 
{
	{2,NULL,"H01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,NULL,"H02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//Զ���͵ز˵�����(����)
uint8_t *const Local_Chinese[] =
{
	{"�͵�"},
	{"Զ��"},
};
//Զ���͵ز˵�����(Ӣ��)
uint8_t *const Local_English[] =
{
	{"Local"},
	{"Remote"},
};
//�������ò˵�
MenuItem Logic_Fun[2] = 
{
	{2,NULL,"F01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{2,NULL,"F02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
};
//�������ò˵�����(����)
uint8_t *const Logic_Chinese[] =
{
	{"������"},
	{"������"},
};
//�������ò˵�����(Ӣ��)
uint8_t *const Logic_English[] =
{
	{"Positive"},
	{"Negative"},
};
//ESD�˵�
MenuItem ESD_Fun[5] = 
{
	{5,NULL,"G01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
	{5,NULL,"G03",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G04",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G05",Display_Basic,Set_Value,NULL,Advanced_Fun},
};
//ESD�˵�����(����)
uint8_t *const ESD_Chinese[] =
{
	{"�ر�"},
	{"ȫ��"},
	{"ȫ��"},
	{"����"},
	{"ָ��"},
};
//ESD�˵�����(Ӣ��)
uint8_t *const ESD_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"Keep"},
	{"Set_pos"},
};
//Alarm�˵�
MenuItem Alarm_Fun[7] = 
{
	{7,NULL,"H01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
	{7,NULL,"H03",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H04",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H05",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H06",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H07",Display_Basic,Set_Value,NULL,Advanced_Fun},
};
//ESD�˵�����(����)
uint8_t *const Alarm_Chinese[] =
{
	{"�رձ���"},
	{"ȫ������"},
	{"ȫ�ر���"},
	{"�޸��ź�"},
	{"�ع�����"},
	{"��������"},
	{"ָ��λ��"},
	{"�ۺϱ���"},
};
//ESD�˵�����(Ӣ��)
uint8_t *const Alarm_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"No_signal"},
	{"Ex_cl_to"},
	{"Ex_op_to"},
	{"Set_pos"},
	{"Unit"},
};
//�ź����Ͳ˵�
MenuItem Signal_Fun[3] = 
{
	{3,NULL,"I01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{3,NULL,"I02",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{3,NULL,"I02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
};
//�ź����Ͳ˵�����(����)
uint8_t *const Signal_Chinese[] =
{
	{"4-20mA"},
	{"0-20mA"},
	{"0-10V"},	
};
//��λ���Ͳ˵�
MenuItem Unit_Fun[2] = 
{
	{2,NULL,"J01",Display_Basic,Set_Value,NULL,Factory_Fun},
	{2,NULL,"J02",Display_Basic,Set_Value,NULL,Factory_Fun},	
};
//�������ò˵�����(����)
uint8_t *const Unit_Chinese[] =
{
	{"Nm"},
	{"N"},
};
//�����˵�
uint8_t *const alarm_string[] =
{
	{"ȫ��"},
	{"ȫ��"},
	{"��������"},
	{"�ع�����"},
	{"��������"},
	{"ָ��λ��"},
	{"�ۺ�"},
};
//�ָ����ò˵�
uint8_t *const default_string[] =
{
	{"ȡ��"},
	{"�ָ�Ĭ��"},
};
//״̬����ʾ����
uint8_t *const status_string[] =
{
	{"�͵�"},
	{"Զ��"},
	{"����"},
};
uint8_t *const status_english[] =
{
	{"Local "},
	{"Remote"},
	{"Set   "},
};
uint8_t *const param_string[] =
{
	{"����"},
	{"�¶�"},
	{"����"},
};
uint8_t *const param_english[] =
{
	{"Open"},
	{"Temp"},
	{"Curr"},
};
/******************************��������***********************************/
/***************************************************************************/
//����:	void Display(MenuItem *menu) 
//˵��:	ִ�в˵���ʾ����
//����: menu Ҫִ�еĲ˵�
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display(MenuItem *menu) 
{ 
	(*(menu->Display))(menu); 
}
/***************************************************************************/
//����:	void Run(struct MenuItem *menu) 
//˵��:	ִ�в˵���ʾ����
//����: menu Ҫִ�еĲ˵�
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Run(MenuItem *menu) 
{ 
	dofunflag = ENABLE;
	(*(menu->Fun))(); 
}
/***************************************************************************/
//����:	void Init_Menu(void) 
//˵��:	���ò˵���ʾ��ʽ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Init_Menu(void) 
{ 
	uint8_t i;
	//��ȡEEPROM����
	//��ʱ����,��ʾ���Ĳ˵�
	ParaData.Basic_data.language = 1;
	//����������Ϣ���ò˵���Ӧ��Ӣ��ѡ�� language = 1,Ϊ���� 0,ΪӢ��
	if(ParaData.Basic_data.language)
	{
		for(i=0;i<3;i++)
		{
			Level1_Fun[i].DisplayString = (uint8_t *)Level1_Chinese[i];
		}
		for(i=0;i<14;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_Chinese[i];
		}
		for(i=0;i<12;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_Chinese[i];
		}
		for(i=0;i<13;i++)
		{
			Factory_Fun[i].DisplayString = (uint8_t *)Factory_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Language_Fun[i].DisplayString = (uint8_t *)Language_Chinese[i];
		}
		for(i=0;i<5;i++)
		{
			Fault_Fun[i].DisplayString = (uint8_t *)Fault_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Local_Fun[i].DisplayString = (uint8_t *)Local_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Logic_Fun[i].DisplayString = (uint8_t *)Logic_Chinese[i];
		}
		for(i=0;i<5;i++)
		{
			ESD_Fun[i].DisplayString = (uint8_t *)ESD_Chinese[i];
		}
		for(i=0;i<7;i++)
		{
			Alarm_Fun[i].DisplayString = (uint8_t *)Alarm_Chinese[i];
		}
		for(i=0;i<3;i++)
		{
			Signal_Fun[i].DisplayString = (uint8_t *)Signal_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Unit_Fun[i].DisplayString = (uint8_t *)Unit_Chinese[i];
		}	
	}
	else
	{
		for(i=0;i<3;i++)
		{
			Level1_Fun[i].DisplayString = (uint8_t *)Level1_English[i];
		}
		for(i=0;i<14;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_English[i];
		}
		for(i=0;i<12;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_English[i];
		}
		for(i=0;i<13;i++)
		{
			Factory_Fun[i].DisplayString = (uint8_t *)Factory_English[i];
		}
		for(i=0;i<2;i++)
		{
			Language_Fun[i].DisplayString = (uint8_t *)Language_English[i];
		}
		for(i=0;i<5;i++)
		{
			Fault_Fun[i].DisplayString = (uint8_t *)Fault_English[i];
		}
		for(i=0;i<2;i++)
		{
			Local_Fun[i].DisplayString = (uint8_t *)Local_English[i];
		}
		for(i=0;i<5;i++)
		{
			ESD_Fun[i].DisplayString = (uint8_t *)ESD_English[i];
		}
		for(i=0;i<7;i++)
		{
			Alarm_Fun[i].DisplayString = (uint8_t *)Alarm_English[i];
		}		
	}
	
	
}
/***************************************************************************/
//����:	void TopMenu(void)
//˵��:	��ҳ�˵���ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_TopMenu(void)
{
	float rate;
	uint8_t datastr[6] = {"45.1%"};

	refresh = ENABLE;
	//��ʾ״̬��
	if(ParaData.Basic_data.language)
		Display_Statusbar(status, param_string[FatherIndex[0]],NORMAL);
	else
		Display_Statusbar(status, param_english[FatherIndex[0]],NORMAL);
	//�������
	switch(FatherIndex[0])
	{
		case 0:				//���㿪��ֵ
			//rate =(float) Shift_ADC *10 / distance;
			rate = 45.1;
			break;
		case 1:				//�����¶�ֵ
			//rate = ;
			break;
		case 2:				//�������ֵ
			// rate = ;
			break;
	}
	sprintf((char *)datastr, "%.1f%%", rate);
	//����ʾ��
	LCD_Display_String(datastr,TYPE_16,4,50,NORMAL);
	
	//��ʾ������
	Display_Progressbar((uint8_t)rate);
	
}
/***************************************************************************/
//����:	void Display_Statusbar(StatusType status, uint8_t *number, uint8_t colour)
//˵��:	��ʾ״̬������
//����: status Ҫ��ʾ��״̬ number Ҫ��ʾ�ı�� colour ����Ƿ���Ҫ����
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_Statusbar(StatusType status, uint8_t *number, uint8_t colour)
{
	uint8_t *string = NULL;
	//��ʾ��
	switch(status)
	{
		case local:
		if(ParaData.Basic_data.language)
			string = status_string[0];
		else
			string = status_english[0];
		break;
		case remote:
		if(ParaData.Basic_data.language)
			string = status_string[1];
		else
			string = status_english[1];
		break;
		case set:
		if(ParaData.Basic_data.language)
			string = status_string[2];
		else
			string = status_english[2];
		break;
		default:
		if(ParaData.Basic_data.language)
			string = status_string[1];
		else
			string = status_english[1];
		break;
	}
	LCD_Display_Mixure(string, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	//�����ʾ���,��Ҫ����colour�����Ƿ���
	LCD_Display_Mixure(number, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN2, colour);
	//��ʾ��
	//ȷ����ʾλ��
	LCD_Display_Line(2,1);
}
/***************************************************************************/
//����:	void Display_Progressbar(uint8_t rate)
//˵��:	��������ʾ����
//����: rate Ҫ��ʾ�Ľ������ٷֱ�
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_Progressbar(uint8_t rate)
{
	uint8_t i;
	uint8_t len = 128*rate/100;
	
	memset(Display_Buff[7],0xff,len);
	memset(&Display_Buff[7][len],0x81,127-len);
	//����������λ��
	Display_Buff[7][127] = 0xff;
	//ȷ����ʾλ��
	LCD_SetCursorPos(8,1);
	for(i=0;i<128;i++)
	{
		LCD_SendByte(DATA_TYPE, Display_Buff[7][i]);
	}
}
/***************************************************************************/
//����:	void Clear_Progressbar(void)
//˵��:	�����������ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Clear_Progressbar(void)
{
	uint8_t i;
	
	//�������������
	memset(Display_Buff[7],0x00,128);
	//ȷ����ʾλ��
	LCD_SetCursorPos(8,1);
	for(i=0;i<128;i++)
	{
		LCD_SendByte(DATA_TYPE, Display_Buff[7][i]);
	}
}
/***************************************************************************/
//����:	void Display_Level1(void)
//˵��:	level1�˵���ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_Level1(void)
{
	uint8_t i;

	refresh = DISABLE;
	//�л�״̬
	if(ParaData.Basic_data.language)
		LCD_Display_Mixure(status_string[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	else
		LCD_Display_Mixure(status_english[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	//Ϊ���κ��ֶ����һ���ֽ�
    LCD_Display_String(" ",TYPE_12,STATUSBARLINE,STATUSBARCOLUMN2,NORMAL);
    //�޸�״̬����ʾ���
    LCD_Display_String(Level1_Fun[FatherIndex[1]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6,REVERSE);
	//��ʾ�ָ���
	LCD_Display_Line(2, 1);
	//�������ʾ��
	LCD_Display_String("     ",TYPE_16,4,50,NORMAL);
    //���������
    Clear_Progressbar();
    
    //��ʾ��ǰ�˵�
    LCD_Display_Mixure(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //��ʾ�¼��˵�
    for(i=0;i<2;i++)
    {
	   LCD_Display_String("            ",TYPE_12,CHILDL+2*i, CHILDC,NORMAL);
	   LCD_Display_Mixure(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString, TYPE_12, CHILDL+2*i, CHILDC, NORMAL);
    }	
}
/***************************************************************************/
//����:	void Display_Basic(void)
//˵��:	�����˵���ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_Basic(void)
{
	MenuItem *parentms = manyou->Parentms;
	MenuItem *where = manyou;

	refresh = DISABLE;
    //�޸�״̬����ʾ Level1_Fun[FatherIndex[1]].Childrenms[i]
    LCD_Display_String(where[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6, NORMAL);
    //��ʾ�ָ���
	LCD_Display_Line(2, 1);
    //��ʾ��ǰ�˵�Ϊ�����˵�(���˵�)
    LCD_CleanL2L(3,4);
    LCD_Display_Mixure(parentms[FatherIndex[layer-1]].DisplayString, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //��ʾ�����˵�
    if(FatherIndex[layer] == 0)
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[0].DisplayString, TYPE_12,CHILDL, CHILDC, REVERSE);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[1].DisplayString, TYPE_12,CHILDL+2, CHILDC, NORMAL);
	}
	else
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]-1].DisplayString, TYPE_12,CHILDL, CHILDC, NORMAL);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString, TYPE_12,CHILDL+2, CHILDC, REVERSE);
	}
}
/***************************************************************************/
//����:	void Language_Set (void)
//˵��:	��������,����Ҫ�л���ʾ���棬ֻ��Ҫ����ѡ�񼴿�
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.30
/***************************************************************************/
void Language_Set (void)
{
	refresh = DISABLE;
	//�޸�״̬��
	
	//��������ѡ��

	//�˻��ϼ��˵�
	layer --;
	manyou = (manyou+FatherIndex[layer])->Parentms;
}
/***************************************************************************/
//����:	void Display_Valve(void)
//˵��:	��ʾ�˵�����,��û�в˵������ݽ�����ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.30
/***************************************************************************/
void Display_Value(void)
{
	MenuItem *where = manyou;
	float rate = 20.1;
	uint8_t datastr[5] = {0};

	//�޸�״̬����ʾ
	LCD_Display_String(where[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6, NORMAL);
    //��ʾ�ָ���
	LCD_Display_Line(2, 1);
	//�����ǰ����ʾ��������
	LCD_CleanL2L(3,8);
	//��ʾ��ǰ����ѡ��
	LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString, TYPE_12,MAINDISPLAYL, MAINDISPLAYC, NORMAL);
	//�ҳ��Լ���λ��
	
	//��ʾ����
	sprintf((char *)datastr, "%.1f", rate);
	//����ʾ��
	LCD_Display_String(datastr,TYPE_16,VALUEL,VALUEC,REVERSE);
	//���ݱ���
	if(keyset)
	{
		keyset --;
		//����SET����,�����ݱ���(��ת���󱣴�)
		
	}
	
}
void Set_Value(void)
{
	//�ҳ��Լ���λ��
	
	
}
void Set_Save (void)
{
	
}
void Default_Fun (void)
{
	
}
void Display_Advanced(void)
{
	
}
void Display_Factory(void)
{
	
}
void Set_Close(void)
{
	
}
void Set_Open(void)
{
	
}
void Set_Display(void)
{
	
}
void Display_Reserve(void)
{
	
}
void Set_Alarm(void)
{
	
}
void Set_Default(void)
{
	
}
void Password_Verify(void)
{
	
}
void Password_Change(void)
{
	
}
void Input_Signal(void)
{
	
}
void Output_Signal(void)
{
	
}
void Display_DeadZone(void)
{
	
}
void Display_Fault(void)
{
	
}
void Display_Location(void)
{
	
}
void Display_Param(void)
{
	
}

