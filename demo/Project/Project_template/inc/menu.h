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
//#define CLEAN_EEPROM			1				//清除EEPROM

//各级菜单项个数
#if MT_TYPE
#define BASIC_NUM				8				//基本菜单
#define ADVANCED_NUM			7				//高级菜单
#define FACTORY_NUM			12				//出厂设置菜单
#else if G_TYPE
#define BASIC_NUM				12				//基本菜单
#define ADVANCED_NUM			16				//高级菜单
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
//菜单数据存储结构体
//基本菜单数据结构,全部采用16位数据是为后面方便操作数据
//内存空间比较大,不存在存储不够的问题
typedef struct _BASIC_DATA_
{
  uint16_t  language;					//语言选择
  uint16_t  allopen;					//全开
  uint16_t  allclose;					//全关
  uint16_t  out4ma;						//输出4mA校准
  uint16_t  out20ma;					//输出20mA校准
  uint16_t  deadzone;					//死区
  uint16_t  errtype;					//信号故障类型
  uint16_t  errplace;					//信号故障位置
#ifdef G_TYPE
  uint16_t  powerofftype;				//断电动作类型
  uint16_t  poweroffplace;				//断电故障位置
  uint16_t  poweroffdelay;				//断电动作延时
  uint16_t  rlstatus;					//远方就地状态	
#endif
}BasicDataStr;
//高级菜单数据结构
typedef struct _ADVANCED_DATA_
{
  uint8_t  logic;						//正反作用
#ifdef G_TYPE
  uint8_t  maxspeed;					//最大速度
  uint8_t  minspeed;					//最小速度
  uint8_t  esdtype;						//ESD类型
  uint8_t  esdplace;					//ESD定位
  uint8_t  startoption;				//开机选项
#endif
  uint8_t  alarm1;						//报警信号1
  uint8_t  alarm2;						//报警信号2
#ifdef G_TYPE
  uint8_t  alarm3;						//报警信号3  
  uint8_t  alarm4;						//报警信号4  
  uint8_t  alarm5;						//报警信号5  
  uint8_t  alarm6;						//报警信号6 
#endif
  uint8_t  alarmplace;					//报警定位
  uint8_t  signaltype;					//信号类型
  uint16_t addr;						//设备地址
}AdvancedDataStr;
//出厂菜单设置
typedef struct _FACTORY_DATA_
{
  uint16_t  password;					//密码设置
#ifdef G_TYPE
  uint16_t  slowrange;					//减速范围
#endif
  uint16_t  moment;						//力矩校准
  uint16_t  momentunits;				//力矩单位
  uint16_t  openmoment;				//开力矩
  uint16_t  closemoment;				//关力矩
  uint16_t  overmoment1;				//过力矩系数1
  uint16_t  overmoment2;				//过力矩系数2
  uint16_t  in4ma;						//输入4ma校准
  uint16_t  in20ma;						//输入20ma校准
  uint8_t  *number;						//产品编号地址
  uint16_t  factor;						//系数
  uint16_t  overdelay;					//过力矩延时
}FactoryDataStr;
//参数结构体
typedef struct _PARAM_STR_
{
	uint8_t flag;						//是否具有数据标志
	BasicDataStr Basic_data;			//基本菜单数据
	AdvancedDataStr Advancd_data;		//高级菜单数据
	FactoryDataStr Factory_data;		//出厂菜单数据
	uint16_t CRC;						//CRC校验数据
	
}ParamStr;
//字摸结构体
typedef struct _TYPE_1332_
{
	uint8_t Index[2];					//索引机器码
	uint8_t Matrix[60];			        //字模数据
}type_1332;
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
extern ParamStr ParaData;								//菜单保存数据结构体
extern const type_1332 specistring[];					//13*32字符
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
void Set_Value(void);
void Display_Value(void);
void Display_Warn(void);
void Save_Value (float rate);
void Display_Save(uint8_t Line, uint8_t Column);

#endif//__MENU_H