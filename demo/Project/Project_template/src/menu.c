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
#include "JLX12864G.h"
#include "GT21H16S2Y.h"



/******************************��������***********************************/
MenuItem TopMenu[1];
MenuItem Level1_Fun[3];
MenuItem Basic_Fun[12];
MenuItem Advanced_Fun[5];
MenuItem Factory_Fun[17];
uint8_t *const alarm_string[];
uint8_t *const default_string[];
uint8_t *const fault_string[];
uint8_t *const status_string[];
uint8_t *const param_string[];

/******************************��������***********************************/
//�˵���ת��¼��������
uint8_t FatherIndex[Menu_Level];               //���˵�����λ��
uint8_t layer = 0;                                 //��ǰ�˵����ڲ�

//Top�˵���ʾ(��������,��Ҫ�ھ͵�״̬��,����SET��)
MenuItem TopMenu[1] = 
{
	{1,NULL,NULL,Display_TopMenu,Level1_Fun,NULL},
};
//Level1�˵���ʾ
MenuItem Level1_Fun[3] = 
{
	{3,"��������","A00",Display_Level1,Basic_Fun,TopMenu},
	{3,"�߼�����","A01",Display_Level1,Advanced_Fun,TopMenu},
	{3,"��������","A02",Display_Level1,Factory_Fun,TopMenu},
};
//�����˵���ʾ
MenuItem Basic_Fun[12] =
{
	{12,"����ѡ��","B01",Display_Basic,NULL,Level1_Fun},
	{12,"ȫ������","B02",Display_Basic,NULL,Level1_Fun},
	{12,"ȫ������","B03",Display_Basic,NULL,Level1_Fun},
	{12,"����4mAЧ��","B04",Display_Basic,NULL,Level1_Fun},
	{12,"����20mAЧ��","B05",Display_Basic,NULL,Level1_Fun},
	{12,"��������","B06",Display_Basic,NULL,Level1_Fun},
	{12,"�źŹ���","B07",Display_Basic,NULL,Level1_Fun},
	{12,"����ָ��λ��","B08",Display_Basic,NULL,Level1_Fun},
	{12,"�ϵ綯������","B09",Display_Basic,NULL,Level1_Fun},
	{12,"�ϵ�ָ��λ��","B10",Display_Basic,NULL,Level1_Fun},
	{12,"�ϵ綯����ʱ","B11",Display_Basic,NULL,Level1_Fun},
	{12,"Զ���ֶ�����","B12",Display_Basic,NULL,Level1_Fun},       
}; 
//�߼��˵���ʾ
MenuItem Advanced_Fun[14] = 
{
	{14,"��������","C01",Set_Alarm,NULL,Level1_Fun},
	{14,"����ٶ�","C02",Set_Alarm,NULL,Level1_Fun},
	{14,"��С�ٶ�","C03",Set_Default,NULL,Level1_Fun},
	{14,"ESD����","C04",Display_Reserve,NULL,Level1_Fun},
	{14,"ESD��λ","C05",Display_Reserve,NULL,Level1_Fun},
	{14,"����1����","C06",Display_Reserve,NULL,Level1_Fun},
	{14,"����2����","C07",Display_Reserve,NULL,Level1_Fun},
	{14,"����3����","C08",Display_Reserve,NULL,Level1_Fun},
	{14,"����4����","C09",Display_Reserve,NULL,Level1_Fun},
	{14,"����5����","C10",Display_Reserve,NULL,Level1_Fun},
	{14,"����6����","C11",Display_Reserve,NULL,Level1_Fun},
	{14,"������λ","C12",Display_Reserve,NULL,Level1_Fun},
	{14,"�ź�����","C13",Display_Reserve,NULL,Level1_Fun},
	{14,"�豸��ַ","C14",Display_Reserve,NULL,Level1_Fun},
};
//��������
MenuItem Factory_Fun[13] = 
{
	{13,"��������","D01",Password_Verify,NULL,Level1_Fun},
	{13,"���ٷ�Χ","D02",Password_Change,NULL,Level1_Fun},
	{13,"����У׼","D03",Input_Signal,NULL,Level1_Fun},
	{13,"���ص�λ","D04",Input_Signal,NULL,Level1_Fun},
	{13,"��������","D05",Output_Signal,NULL,Level1_Fun},
	{13,"�ط�����","D06",Output_Signal,NULL,Level1_Fun},
	{13,"������ϵ��һ","D07",Display_DeadZone,NULL,Level1_Fun},
	{13,"������ϵ����","D08",Display_Fault,NULL,Level1_Fun},
	{13,"����4mAУ׼","D09",Display_Location,NULL,Level1_Fun},
	{13,"����20mAУ׼","D10",Display_Valve,NULL,Level1_Fun},
	{13,"��Ʒ���","D11",Display_Valve,NULL,Level1_Fun},
	{13,"ϵ��","D12",Display_Valve,NULL,Level1_Fun},
	{13,"��������ʱ","D13",Display_Param,NULL,Level1_Fun},
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
//�źŹ��ϲ˵�
uint8_t *const fault_string[] =
{
	{"ȫ��"},
	{"ȫ��"},
	{"����"},
	{"ָ��λ��"},
};
//״̬����ʾ����
uint8_t *const status_string[] =
{
	{"�͵�"},
	{"Զ��"},
	{"����"},
};
uint8_t *const param_string[] =
{
	{"����"},
	{"�¶�"},
	{"����"},
};


/******************************��������***********************************/
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
	(*(menu->Fun))(menu); 
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
	//��ʾ״̬��
	Display_Statusbar(status, param_string[FatherIndex[0]],NORMAL);
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
	sprintf(datastr, "%.1f%%", rate);
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
	uint8_t i;
	uint8_t *string = NULL;
	//��ʾ��
	switch(status)
	{
		case local:
		string = status_string[0];
		break;
		case remote:
		string = status_string[1];
		break;
		case set:
		string = status_string[2];
		break;
		default:
		string = status_string[1];
		break;
	}
	LCD_Display_Chinese(string, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	//�����ʾ���,��Ҫ����colour�����Ƿ���
	LCD_Display_Mixure(number, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN2, colour);
	//��ʾ��
	//ȷ����ʾλ��
	LCD_SetCursorPos(2,1);
	for(i=0;i<128;i++)
	{
		Display_Buff[1][i] |= 0x20;			//��0x20����ʾҪ��ʾֱ�ߵ�λ��,��ɨ���Ǵӵ͵���(����ҵ���),���ϵ���	
		LCD_SendByte(DATA_TYPE, Display_Buff[1][i]);		
	}
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
	
    //�޸�״̬����ʾ���
    LCD_Display_String(Level1_Fun[FatherIndex[1]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2,REVERSE);
    //Ϊ���κ��ֶ����һ���ֽ�
    LCD_Display_String(" ",TYPE_12,STATUSBARLINE,STATUSBARCOLUMN2+18,NORMAL);
    //���������
    Clear_Progressbar();
    
    //��ʾ��ǰ�˵�
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_16, MAINDISPLAYL, MAINDISPLAYL, NORMAL);
    //��ʾ�¼��˵�
    for(i=0;i<2;i++)
    {
       LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString, TYPE_16, CHILDL+2*i, CHILDC, NORMAL);
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
	uint8_t i;
	
    //�޸�״̬����ʾ
    LCD_Display_String(Basic_Fun[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2, NORMAL);
    
    //��ʾ��ǰ�˵�Ϊ�����˵�(���˵�)
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_16, MAINDISPLAYL, MAINDISPLAYL, NORMAL);
    //��ʾ�����˵�
    if(FatherIndex[layer] == 0)
	{
		LCD_Display_Mixure(Basic_Fun[0].DisplayString, TYPE_16,CHILDL, CHILDC, REVERSE);
		LCD_Display_Mixure(Basic_Fun[1].DisplayString, TYPE_16,CHILDL+2, CHILDC, NORMAL);
	}
	else
	{
		LCD_Display_Mixure(Basic_Fun[FatherIndex[layer]-1].DisplayString, TYPE_16,CHILDL, CHILDC, NORMAL);
		LCD_Display_Mixure(Basic_Fun[FatherIndex[layer]].DisplayString, TYPE_16,CHILDL+2, CHILDC, REVERSE);	
	}
}
void Language_Fun(void)
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
void Display_Valve(void)
{
	
}
void Display_Param(void)
{
	
}

