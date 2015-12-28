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
 * Description: menu.h 菜单结构头文件
 */
/*************************************************************************/
#ifndef __MENU_H
#define __MENU_H
#include "stm8s_gpio.h"
#include "key.h"

// 宏定义
#define STATUSBARLINE		1				//状态栏起始行
#define STATUSBARCOLUMN		2				//状态栏起始列
#define STATUSBARCOLUMN2	100				//状态栏第二起始列
#define MAINDISPLAYL            3                               //主显示区起始行
#define MAINDISPLAYC            1                               //主显示区起始列
#define CHILDL                  5                               //子菜单显示起始行
#define CHILDC                  32                              //子菜单显示起始列

#define Menu_Level              4                               //最大支持4级菜单

// 结构体定义
//菜单结构体定义
typedef struct _MENUITEM_
{
	uint8_t MenuCount;					//结构体数组的元素个数(菜单个数)
	uint8_t *DisplayString;					//菜单显示信息
	uint8_t *Status;					//状态栏显示状态信息
	void (*Fun)();						//执行函数的指针
	struct _MENUITEM_ *Childrenms;			        //指向子节点的指针
	struct _MENUITEM_ *Parentms;			        //指向父节点的指针
}MenuItem;

//变量声明
uint8_t FatherIndex[Menu_Level];               //父菜单所在位置
uint8_t layer;                                 //当前菜单所在层


//函数声明
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