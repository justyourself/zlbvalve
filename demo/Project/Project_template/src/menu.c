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



/******************************��������***********************************/
MenuItem TopMenu[1];
MenuItem Level1_Fun[3];
MenuItem Advanced_Fun[14];
MenuItem Basic_Fun[12];
MenuItem Factory_Fun[13];
MenuItem Fault_Fun[1];
MenuItem Logic_Fun[1];
MenuItem Language_Fun[2];
uint8_t *const alarm_string[];
uint8_t *const default_string[];
uint8_t *const fault_string[];
uint8_t *const status_string[];
uint8_t *const param_string[];
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
	{1,NULL,NULL,NULL,Display_TopMenu,NULL,Level1_Fun,NULL},
};
//Level1�˵���ʾ
MenuItem Level1_Fun[3] = 
{
	{3,"��������","Basi_set","A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,"�߼�����","Adv_set","A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,"��������","Fact_set","A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
//�����˵���ʾ
MenuItem Basic_Fun[12] =
{
	{12,"����ѡ��","Language","B01",Display_Basic,NULL,Language_Fun,Level1_Fun},
	{12,"ȫ������","Open_pos","B02",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"ȫ������","Close_pos","B03",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"����4mAЧ��","In_4mA_adj","B04",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"����20mAЧ��","In_20mA_adj","B05",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"��������","Death_section","B06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"�źŹ�������","Sign_err","B07",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,"����ָ��λ��","Sign_errpos","B08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"�ϵ綯������","Poweroff","B09",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,"�ϵ�ָ��λ��","Power_pos","B10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"�ϵ綯����ʱ","Power_delay","B11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"Զ���ֶ�����","Set_local","B12",Display_Basic,Set_Save,NULL,Level1_Fun},       
}; 
//�߼��˵���ʾ
MenuItem Advanced_Fun[14] = 
{
	{14,"��������","Logic","C01",Display_Basic,NULL,Logic_Fun,Level1_Fun},
	{14,"����ٶ�","Max_Speed","C02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,"��С�ٶ�","Min_Speed","C03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,"ESD����","ESD_type","C04",Display_Basic,NULL,Level1_Fun},
	{14,"ESD��λ","ESD_pos","C05",Display_Basic,NULL,Level1_Fun},
	{14,"����1����","Alarm_COM1","C06",Display_Basic,NULL,Level1_Fun},
	{14,"����2����","Alarm_COM2","C07",Display_Basic,NULL,Level1_Fun},
	{14,"����3����","Alarm_COM3","C08",Display_Basic,NULL,Level1_Fun},
	{14,"����4����","Alarm_COM4","C09",Display_Basic,NULL,Level1_Fun},
	{14,"����5����","Alarm_COM5","C10",Display_Basic,NULL,Level1_Fun},
	{14,"����6����","Alarm_COM6","C11",Display_Basic,NULL,Level1_Fun},
	{14,"������λ","Alarm_pos","C12",Display_Basic,NULL,Level1_Fun},
	{14,"�ź�����","Sign_type","C13",Display_Basic,NULL,Level1_Fun},
	{14,"�豸��ַ","Address","C14",Display_Basic,NULL,Level1_Fun},
};
//��������
MenuItem Factory_Fun[13] = 
{
	{13,"��������","Change_Key","D01",Display_Basic,NULL,Level1_Fun},
	{13,"���ٷ�Χ","Reduce","D02",Display_Basic,NULL,Level1_Fun},
	{13,"����У׼","Torque_adj","D03",Display_Basic,NULL,Level1_Fun},
	{13,"���ص�λ","Touque_unit","D04",Display_Basic,NULL,Level1_Fun},
	{13,"��������","Open_touque","D05",Display_Basic,NULL,Level1_Fun},
	{13,"�ط�����","Close_touque","D06",Display_Basic,NULL,Level1_Fun},
	{13,"������ϵ��һ","Over_moment1","D07",Display_Basic,NULL,Level1_Fun},
	{13,"������ϵ����","Over_moment2","D08",Display_Basic,NULL,Level1_Fun},
	{13,"����4mAУ׼","Out_4mA_adj","D09",Display_Basic,NULL,Level1_Fun},
	{13,"����20mAУ׼","Out_20mA_adj","D10",Display_Basic,NULL,Level1_Fun},
	{13,"��Ʒ���","No.","D11",Display_Basic,NULL,Level1_Fun},
	{13,"ϵ��","Factor","D12",Display_Basic,NULL,Level1_Fun},
	{13,"��������ʱ","Over_delay","D13",Display_Basic,NULL,Level1_Fun},
};
//��������
MenuItem Language_Fun[2] = 
{
	{2,"����","CHINESE","E01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,"ENGLISH","ENGLISH","E02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//��ʾ�˵�
MenuItem Display_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Valve,NULL,NULL},
};
//����˵�
MenuItem Fault_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Fault,NULL,NULL},
};
//�������ò˵�
MenuItem Logic_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Fault,NULL,NULL},
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
	LCD_Display_Chinese(status_string[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
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
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString1, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //��ʾ�¼��˵�
    for(i=0;i<2;i++)
    {
	   LCD_Display_String("            ",TYPE_12,CHILDL+2*i, CHILDC,NORMAL);
	   LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString1, TYPE_12, CHILDL+2*i, CHILDC, NORMAL);
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
    LCD_Display_Chinese(parentms[FatherIndex[layer-1]].DisplayString1, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //��ʾ�����˵�
    if(FatherIndex[layer] == 0)
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[0].DisplayString1, TYPE_12,CHILDL, CHILDC, REVERSE);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[1].DisplayString1, TYPE_12,CHILDL+2, CHILDC, NORMAL);
	}
	else
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]-1].DisplayString1, TYPE_12,CHILDL, CHILDC, NORMAL);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString1, TYPE_12,CHILDL+2, CHILDC, REVERSE);
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
	LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString1, TYPE_12,MAINDISPLAYL, MAINDISPLAYC, NORMAL);
	//�ҳ��Լ���λ��

	//��ʾ����
	sprintf(datastr, "%.1f", rate);
	//����ʾ��
	LCD_Display_String(datastr,TYPE_16,VALUEL,VALUEC,REVERSE);
	
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

