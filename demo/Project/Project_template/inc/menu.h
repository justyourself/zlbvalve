/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : menu.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: menu.h �˵��ṹͷ�ļ�
 */
/*************************************************************************/
#ifndef __MENU_H
#define __MENU_H
#include "stm8s_gpio.h"
#include "key.h"

// �궨��
//�˵��ͺ�ѡ��
#define MT_TYPE					1				//MT��
//#define G_TYPE					1				//G��
//#define CLEAN_EEPROM			1				//���EEPROM

//�����˵������
#if MT_TYPE
#define BASIC_NUM				8				//�����˵�
#define ADVANCED_NUM			7				//�߼��˵�
#define FACTORY_NUM			12				//�������ò˵�
#else if G_TYPE
#define BASIC_NUM				12				//�����˵�
#define ADVANCED_NUM			16				//�߼��˵�
#define FACTORY_NUM			13				//�������ò˵�
#endif
//��ʾλ��
#define STATUSBARLINE			1				//״̬����ʼ��
#define STATUSBARCOLUMN		2				//״̬����ʼ��
#define STATUSBARCOLUMN2		100				//״̬���ڶ���ʼ��
#define MAINDISPLAYL           3               //����ʾ����ʼ��
#define MAINDISPLAYC           2               //����ʾ����ʼ��
#define CHILDL					5               //�Ӳ˵���ʾ��ʼ��
#define CHILDC                 32              //�Ӳ˵���ʾ��ʼ��
#define VALUEL					6				//������ʾ��ʼ��
#define VALUEC					50				//������ʾ��ʼ��

#define Menu_Level             4               //���֧��4���˵�

// �ṹ�嶨��
//�˵��ṹ�嶨��
typedef struct _MENUITEM_
{
	uint8_t MenuCount;							//�ṹ�������Ԫ�ظ���(�˵�����)
	uint8_t *DisplayString;					//�˵���ʾ��Ϣ
	uint8_t *Status;							//״̬����ʾ״̬��Ϣ
	void (*Display)();							//��ʾ������ָ��
	void (*Fun)();						//ִ�к�����ָ��
	struct _MENUITEM_ *Childrenms;			    //ָ���ӽڵ��ָ��
	struct _MENUITEM_ *Parentms;			    //ָ�򸸽ڵ��ָ��
}MenuItem;
//�˵����ݴ洢�ṹ��
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
#ifdef G_TYPE
  uint16_t  powerofftype;				//�ϵ綯������
  uint16_t  poweroffplace;				//�ϵ����λ��
  uint16_t  poweroffdelay;				//�ϵ綯����ʱ
  uint16_t  rlstatus;					//Զ���͵�״̬	
#endif
}BasicDataStr;
//�߼��˵����ݽṹ
typedef struct _ADVANCED_DATA_
{
  uint8_t  logic;						//��������
#ifdef G_TYPE
  uint8_t  maxspeed;					//����ٶ�
  uint8_t  minspeed;					//��С�ٶ�
  uint8_t  esdtype;						//ESD����
  uint8_t  esdplace;					//ESD��λ
  uint8_t  startoption;				//����ѡ��
#endif
  uint8_t  alarm1;						//�����ź�1
  uint8_t  alarm2;						//�����ź�2
#ifdef G_TYPE
  uint8_t  alarm3;						//�����ź�3  
  uint8_t  alarm4;						//�����ź�4  
  uint8_t  alarm5;						//�����ź�5  
  uint8_t  alarm6;						//�����ź�6 
#endif
  uint8_t  alarmplace;					//������λ
  uint8_t  signaltype;					//�ź�����
  uint16_t addr;						//�豸��ַ
}AdvancedDataStr;
//�����˵�����
typedef struct _FACTORY_DATA_
{
  uint16_t  password;					//��������
#ifdef G_TYPE
  uint16_t  slowrange;					//���ٷ�Χ
#endif
  uint16_t  moment;						//����У׼
  uint16_t  momentunits;				//���ص�λ
  uint16_t  openmoment;				//������
  uint16_t  closemoment;				//������
  uint16_t  overmoment1;				//������ϵ��1
  uint16_t  overmoment2;				//������ϵ��2
  uint16_t  in4ma;						//����4maУ׼
  uint16_t  in20ma;						//����20maУ׼
  uint8_t  *number;						//��Ʒ��ŵ�ַ
  uint16_t  factor;						//ϵ��
  uint16_t  overdelay;					//��������ʱ
}FactoryDataStr;
//�����ṹ��
typedef struct _PARAM_STR_
{
	uint8_t flag;						//�Ƿ�������ݱ�־
	BasicDataStr Basic_data;			//�����˵�����
	AdvancedDataStr Advancd_data;		//�߼��˵�����
	FactoryDataStr Factory_data;		//�����˵�����
	uint16_t CRC;						//CRCУ������
	
}ParamStr;
//�����ṹ��
typedef struct _TYPE_1332_
{
	uint8_t Index[2];					//����������
	uint8_t Matrix[60];			        //��ģ����
}type_1332;
//��������
extern uint8_t keyset;
extern uint8_t keyup;								   //������ʾ���水��ֵ����
extern uint8_t keydown;
extern uint8_t refresh;
extern uint8_t  dofunflag;						       //ִ�к���ִ�б�־
extern uint8_t FatherIndex[Menu_Level];               //���˵�����λ��
extern uint8_t layer; 
extern MenuItem *manyou;								//����������������˵�//��ǰ�˵����ڲ�
extern MenuItem TopMenu[1];
extern ParamStr ParaData;								//�˵��������ݽṹ��
extern const type_1332 specistring[];					//13*32�ַ�
//��������
void Init_Menu(void);
void Display(MenuItem *menu); 
void Run(MenuItem *menu);
void Display_TopMenu(void);
void Display_Statusbar(uint8_t *number, uint8_t colour);
void Display_Progressbar(uint8_t rate);
void Clear_Progressbar(void);
void Display_Level1(void);
void Display_Basic(void);
float GetMenu_Data(uint8_t father, uint8_t item);
void Default_Fun (void);
void Display_Advanced(void);
void Display_Factory(void);
void Set_Close(void);
void Set_Open(void);
void Set_Display(void);
void Display_Reserve(void);
void Set_Alarm(void);
void Set_Default(void);
void Password_Verify(void);
void Password_Change(void);
void Input_Signal(void);
void Output_Signal(void);
void Display_DeadZone(void);
void Display_Fault(void);
void Display_Location(void);
void Display_Valve(void);
void Display_Param(void);
void Set_Value(void);
void Display_Value(void);
void Display_Warn(void);
void Save_Value (float rate);
void Display_Save(uint8_t Line, uint8_t Column);

#endif//__MENU_H