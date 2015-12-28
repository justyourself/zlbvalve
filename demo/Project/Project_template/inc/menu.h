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
#define STATUSBARLINE		1				//״̬����ʼ��
#define STATUSBARCOLUMN		2				//״̬����ʼ��
#define STATUSBARCOLUMN2	100				//״̬���ڶ���ʼ��
#define MAINDISPLAYL            3                               //����ʾ����ʼ��
#define MAINDISPLAYC            1                               //����ʾ����ʼ��
#define CHILDL                  5                               //�Ӳ˵���ʾ��ʼ��
#define CHILDC                  32                              //�Ӳ˵���ʾ��ʼ��

#define Menu_Level              4                               //���֧��4���˵�

// �ṹ�嶨��
//�˵��ṹ�嶨��
typedef struct _MENUITEM_
{
	uint8_t MenuCount;					//�ṹ�������Ԫ�ظ���(�˵�����)
	uint8_t *DisplayString;					//�˵���ʾ��Ϣ
	uint8_t *Status;					//״̬����ʾ״̬��Ϣ
	void (*Fun)();						//ִ�к�����ָ��
	struct _MENUITEM_ *Childrenms;			        //ָ���ӽڵ��ָ��
	struct _MENUITEM_ *Parentms;			        //ָ�򸸽ڵ��ָ��
}MenuItem;

//��������
uint8_t FatherIndex[Menu_Level];               //���˵�����λ��
uint8_t layer;                                 //��ǰ�˵����ڲ�


//��������
void Run(MenuItem *menu);
void Display_TopMenu(void);
void Display_Statusbar(StatusType status, uint8_t *number, uint8_t colour);
void Display_Progressbar(uint8_t rate);
void Clear_Progressbar(void);
void Language_Fun(void);
void Display_Level1(void);
void Display_Basic(void);
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



#endif//__MENU_H