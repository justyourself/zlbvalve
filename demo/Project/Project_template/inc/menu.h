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
//菜单型号选择
#define MT_TYPE					1				//MT型
//#define G_TYPE					1				//G型

//各级菜单项个数
#if MT_TYPE
#define BASIC_NUM				8				//基本菜单
#define ADVANCED_NUM			7				//高级菜单
#define FACTORY_NUM			12				//出厂设置菜单
#else if G_TYPE
#define BASIC_NUM				12				//基本菜单
#define ADVANCED_NUM			15				//高级菜单
#define FACTORY_NUM			13				//出厂设置菜单
#endif
//显示位置
#define STATUSBARLINE			1				//状态栏起始行
#define STATUSBARCOLUMN		2				//状态栏起始列
#define STATUSBARCOLUMN2		100				//状态栏第二起始列
#define MAINDISPLAYL           3               //主显示区起始行
#define MAINDISPLAYC           2               //主显示区起始列
#define CHILDL					5               //子菜单显示起始行
#define CHILDC                 32              //子菜单显示起始列
#define VALUEL					6				//数据显示起始行
#define VALUEC					50				//数据显示起始列

#define Menu_Level             4               //最大支持4级菜单

// 结构体定义
//菜单结构体定义
typedef struct _MENUITEM_
{
	uint8_t MenuCount;							//结构体数组的元素个数(菜单个数)
	uint8_t *DisplayString;					//菜单显示信息
	uint8_t *Status;							//状态栏显示状态信息
	void (*Display)();							//显示函数的指针
	void (*Fun)();						//执行函数的指针
	struct _MENUITEM_ *Childrenms;			    //指向子节点的指针
	struct _MENUITEM_ *Parentms;			    //指向父节点的指针
}MenuItem;

//变量声明
extern uint8_t keyset;
extern uint8_t keyup;								   //数据显示界面按键值传递
extern uint8_t keydown;
extern uint8_t refresh;
extern uint8_t  dofunflag;						       //执行函数执行标志
extern uint8_t FatherIndex[Menu_Level];               //父菜单所在位置
extern uint8_t layer; 
extern MenuItem *manyou;								//变量用来漫游真个菜单//当前菜单所在层
extern MenuItem TopMenu[1];
//函数声明
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
void Set_Save (void);
void Set_Value(void);
void Display_Value(void);
void Language_Set (void);
void Display_Warn(void);


#endif//__MENU_H