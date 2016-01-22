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
MenuItem Advanced_Fun[ADVANCED_NUM];
MenuItem Basic_Fun[BASIC_NUM];
MenuItem Factory_Fun[FACTORY_NUM];
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
ParamStr ParaData;								//�˵��������ݽṹ��
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
MenuItem Basic_Fun[BASIC_NUM] =
{
	{BASIC_NUM,NULL,"B01",Display_Basic,NULL,Language_Fun,Level1_Fun},
	{BASIC_NUM,NULL,"B02",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B03",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B04",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B05",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B06",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B07",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{BASIC_NUM,NULL,"B08",Display_Basic,Display_Value,NULL,Level1_Fun},
#ifdef G_TYPE
	{BASIC_NUM,NULL,"B09",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{BASIC_NUM,NULL,"B10",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B11",Display_Basic,Display_Value,NULL,Level1_Fun},
	{BASIC_NUM,NULL,"B12",Display_Basic,NULL,Local_Fun,Level1_Fun},  
#endif
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
#ifdef G_TYPE
	{"�ϵ綯������"},
	{"�ϵ�ָ��λ��"},
	{"�ϵ綯����ʱ"},
	{"Զ���ֶ�����"},
#endif
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
#ifdef G_TYPE
	{"Power_off"},
	{"Power_pos"},
	{"Power_delay"},
	{"Set_local"},
#endif
};
//�߼��˵���ʾ
MenuItem Advanced_Fun[ADVANCED_NUM] = 
{
	{ADVANCED_NUM,NULL,"C01",Display_Basic,NULL,Logic_Fun,Level1_Fun},
#ifdef G_TYPE
	{ADVANCED_NUM,NULL,"C02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{ADVANCED_NUM,NULL,"C03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{ADVANCED_NUM,NULL,"C04",Display_Basic,NULL,ESD_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{ADVANCED_NUM,NULL,"C06",Display_Basic,Set_Value,NULL,Level1_Fun},
#endif
	{ADVANCED_NUM,NULL,"C07",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C08",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
#ifdef G_TYPE
	{ADVANCED_NUM,NULL,"C09",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C10",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C11",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C12",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
#endif
	{ADVANCED_NUM,NULL,"C13",Display_Basic,Display_Value,NULL,Level1_Fun},
	{ADVANCED_NUM,NULL,"C14",Display_Basic,NULL,Signal_Fun,Level1_Fun},
	{ADVANCED_NUM,NULL,"C15",Display_Basic,Set_Value,NULL,Level1_Fun},
	{ADVANCED_NUM,NULL,"C16",Display_Basic,Display_Warn,NULL,Level1_Fun},
};
//�߼��˵�����(����)
uint8_t *const Advanced_Chinese[] =
{
	{"��������"},
#ifdef G_TYPE
	{"����ٶ�"},
	{"��С�ٶ�"},
	{"ESD����"},
	{"ESD��λ"},
	{"����ѡ��"},
#endif
	{"����1����"},
	{"����2����"},
#ifdef G_TYPE
	{"����3����"},
	{"����4����"},
	{"����5����"},
	{"����6����"},
#endif
	{"������λ"},
	{"�ź�����"},
	{"�豸��ַ"},
	{"�����ָ�"},
};
//�߼��˵�����(Ӣ��)
uint8_t *const Advanced_English[] =
{
	{"Logic"},
#ifdef G_TYPE
	{"Max_Speed"},
	{"Min_Speed"},
	{"ESD_type"},
	{"ESD_pos"},
	{"Start_option"},
#endif
	{"Alarm_COM1"},
	{"Alarm_COM2"},
#ifdef G_TYPE
	{"Alarm_COM3"},
	{"Alarm_COM4"},
	{"Alarm_COM5"},
	{"Alarm_COM6"},
#endif
	{"Alarm_pos"},
	{"Sign_type"},
	{"Address"},
	{"Reset"},
};
//��������
MenuItem Factory_Fun[FACTORY_NUM] = 
{
	{FACTORY_NUM,NULL,"D01",Display_Basic,Set_Value,NULL,Level1_Fun},
#ifdef G_TYPE
	{FACTORY_NUM,NULL,"D02",Display_Basic,Set_Value,NULL,Level1_Fun},
#endif
	{FACTORY_NUM,NULL,"D03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D04",Display_Basic,NULL,Unit_Fun,Level1_Fun},
	{FACTORY_NUM,NULL,"D05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D07",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D09",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D12",Display_Basic,Set_Value,NULL,Level1_Fun},
	{FACTORY_NUM,NULL,"D13",Display_Basic,Set_Value,NULL,Level1_Fun},
};
//�����˵�����(����)
uint8_t *const Factory_Chinese[] =
{
	{"��������"},
#ifdef G_TYPE
	{"���ٷ�Χ"},
#endif
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
#ifdef G_TYPE
	{"Reduce"},
#endif
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
		for(i=0;i<ADVANCED_NUM;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_Chinese[i];
		}
		for(i=0;i<BASIC_NUM;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_Chinese[i];
		}
		for(i=0;i<FACTORY_NUM;i++)
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
		for(i=0;i<ADVANCED_NUM;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_English[i];
		}
		for(i=0;i<BASIC_NUM;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_English[i];
		}
		for(i=0;i<FACTORY_NUM;i++)
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
		Display_Statusbar(param_string[FatherIndex[0]],NORMAL);
	else
		Display_Statusbar(param_english[FatherIndex[0]],NORMAL);
	//�������
	switch(FatherIndex[0])
	{
		case 0:				//���㿪��ֵ
			rate = ParaData.Basic_data.allopen - ParaData.Basic_data.allclose;
			rate =(float) (ValidADC.shift - ParaData.Basic_data.allclose )*100 / rate;
			//rate = 45.1;
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
//����:	void Display_Statusbar(uint8_t *number, uint8_t colour)
//˵��:	��ʾ״̬������
//����: number Ҫ��ʾ�ı�� colour ����Ƿ���Ҫ����
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Display_Statusbar(uint8_t *number, uint8_t colour)
{
	uint8_t *string = NULL;
	//��ʾ��
	switch(flag.local)
	{
		case local:
		if(flag.set)
		{
			if(ParaData.Basic_data.language)
				string = status_string[2];
			else
				string = status_english[2];			
		}
		else
		{
			if(ParaData.Basic_data.language)
				string = status_string[0];
			else
				string = status_english[0];			
		}		
		break;
		case remote:
		if(ParaData.Basic_data.language)
			string = status_string[1];
		else
			string = status_english[1];		
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
	LCD_Display_String("        ",TYPE_16,4,50,NORMAL);
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
    //����״̬
	if(ParaData.Basic_data.language)
		LCD_Display_Mixure(status_string[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	else
		LCD_Display_Mixure(status_english[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
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
	rate = GetMenu_Data(FatherIndex[layer - 1], FatherIndex[layer]);
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
/***************************************************************************/
//����:	float GetMenu_Data(uint8_t father, uint8_t item)
//˵��:	��ȡ�˵����ݺ���
//����: father ���˵� item ��ǰ�˵�ѡ��
//���: ����ֵ
//�༭: zlb
//ʱ��: 2015.12.30
/***************************************************************************/
float GetMenu_Data(uint8_t father, uint8_t item)
{
	float outdata = 0;
	uint16_t tempdata;
	uint16_t *menudata1 = NULL;
	uint8_t *menudata2 = NULL;

	switch(father)
	{
		case 0:			//�����˵�
			//��ȡ�˵����ݵ�ַ
			menudata1 = (uint16_t *)&ParaData.Basic_data.language;
			//��Ҫ��ȡADCֵ,����Ĭ��ȫ����ȫ���ı�������ٷֱ�(ȫ��90%,ȫ��10%)
			if(item == 1|| item == 2)
			{
				tempdata = ValidADC.shift;
				outdata = ParaData.Basic_data.allopen - ParaData.Basic_data.allclose;
				outdata =(float) (tempdata - ParaData.Basic_data.allclose )*100 / outdata;
			}
			else
			{
				tempdata = menudata1[item];
				if(keyup)
				{
					keyup = 0;
					if(tempdata < 1000)
						tempdata++;
					else 
						tempdata = 0;
				}
				if(keydown)
				{
					keydown = 0;
					if(tempdata > 0)
						tempdata--;
					else
						tempdata = 0;
				}
				outdata = (float)tempdata / 10;
			}
			break;
		case 1:			//�߼��˵�
			//��ȡ�˵����ݵ�ַ
			menudata2 = (uint8_t *)&ParaData.Advancd_data.logic;
			tempdata = menudata2[item];
			if(keyup)
			{
				keyup = 0;
				if(tempdata < 1000)
					tempdata++;
				else 
					tempdata = 0;
			}
			if(keydown)
			{
				keydown = 0;
				if(tempdata > 0)
					tempdata--;
				else
					tempdata = 0;
			}
			outdata = (float)tempdata / 10;
		break;
		case 2:			//�����˵�
			//��ȡ�˵����ݵ�ַ
			menudata1 = (uint16_t *)&ParaData.Factory_data.password;
			tempdata = menudata1[item];			
		break;
		default:
			tempdata = 0;
		break;		
	}

	return outdata;
}

void Set_Value(void)
{
	//�ҳ��Լ���λ��
	uint8_t level = FatherIndex[layer-2];
	//ѡ��ǰ��Ԫ
	uint8_t item = FatherIndex[layer];
	uint8_t father = FatherIndex[layer - 1];
	uint16_t *menudata1 = NULL;
	uint8_t *menudata2 = NULL;
	
	switch(level)
	{
		case 0:
		menudata1 = (uint16_t *)&ParaData.Basic_data.language;
		menudata1[father] = item;
		break;
		case 1:
		menudata2 = (uint8_t *)&ParaData.Advancd_data.logic;
		menudata2[father] = item;
		break;
		case 2:
		menudata1 = (uint16_t *)&ParaData.Factory_data.password;
		menudata1[father] = item;
		default:
		break;
	}
}
void Display_Warn(void)
{
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

