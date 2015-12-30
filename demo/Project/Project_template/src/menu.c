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
 * Description: menu.c 菜单结构函数
 */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "JLX12864G.h"
#include "GT21H16S2Y.h"



/******************************变量声明***********************************/
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

/******************************变量定义***********************************/
//菜单跳转记录参数定义
uint8_t FatherIndex[Menu_Level];               //父菜单所在位置
uint8_t layer = 0;                                 //当前菜单所在层

//Top菜单显示(进入条件,需要在就地状态下,按下SET键)
MenuItem TopMenu[1] = 
{
	{1,NULL,NULL,Display_TopMenu,Level1_Fun,NULL},
};
//Level1菜单显示
MenuItem Level1_Fun[3] = 
{
	{3,"基本设置","A00",Display_Level1,Basic_Fun,TopMenu},
	{3,"高级设置","A01",Display_Level1,Advanced_Fun,TopMenu},
	{3,"出厂设置","A02",Display_Level1,Factory_Fun,TopMenu},
};
//基本菜单显示
MenuItem Basic_Fun[12] =
{
	{12,"语言选择","B01",Display_Basic,NULL,Level1_Fun},
	{12,"全开设置","B02",Display_Basic,NULL,Level1_Fun},
	{12,"全关设置","B03",Display_Basic,NULL,Level1_Fun},
	{12,"给定4mA效验","B04",Display_Basic,NULL,Level1_Fun},
	{12,"给定20mA效验","B05",Display_Basic,NULL,Level1_Fun},
	{12,"死区调整","B06",Display_Basic,NULL,Level1_Fun},
	{12,"信号故障","B07",Display_Basic,NULL,Level1_Fun},
	{12,"故障指定位置","B08",Display_Basic,NULL,Level1_Fun},
	{12,"断电动作类型","B09",Display_Basic,NULL,Level1_Fun},
	{12,"断电指定位置","B10",Display_Basic,NULL,Level1_Fun},
	{12,"断电动作延时","B11",Display_Basic,NULL,Level1_Fun},
	{12,"远控手动设置","B12",Display_Basic,NULL,Level1_Fun},       
}; 
//高级菜单显示
MenuItem Advanced_Fun[14] = 
{
	{14,"正反作用","C01",Set_Alarm,NULL,Level1_Fun},
	{14,"最大速度","C02",Set_Alarm,NULL,Level1_Fun},
	{14,"最小速度","C03",Set_Default,NULL,Level1_Fun},
	{14,"ESD类型","C04",Display_Reserve,NULL,Level1_Fun},
	{14,"ESD定位","C05",Display_Reserve,NULL,Level1_Fun},
	{14,"报警1类型","C06",Display_Reserve,NULL,Level1_Fun},
	{14,"报警2类型","C07",Display_Reserve,NULL,Level1_Fun},
	{14,"报警3类型","C08",Display_Reserve,NULL,Level1_Fun},
	{14,"报警4类型","C09",Display_Reserve,NULL,Level1_Fun},
	{14,"报警5类型","C10",Display_Reserve,NULL,Level1_Fun},
	{14,"报警6类型","C11",Display_Reserve,NULL,Level1_Fun},
	{14,"报警定位","C12",Display_Reserve,NULL,Level1_Fun},
	{14,"信号类型","C13",Display_Reserve,NULL,Level1_Fun},
	{14,"设备地址","C14",Display_Reserve,NULL,Level1_Fun},
};
//出厂设置
MenuItem Factory_Fun[13] = 
{
	{13,"密码设置","D01",Password_Verify,NULL,Level1_Fun},
	{13,"减速范围","D02",Password_Change,NULL,Level1_Fun},
	{13,"力矩校准","D03",Input_Signal,NULL,Level1_Fun},
	{13,"力矩单位","D04",Input_Signal,NULL,Level1_Fun},
	{13,"开阀力矩","D05",Output_Signal,NULL,Level1_Fun},
	{13,"关阀力矩","D06",Output_Signal,NULL,Level1_Fun},
	{13,"过力矩系数一","D07",Display_DeadZone,NULL,Level1_Fun},
	{13,"过力矩系数二","D08",Display_Fault,NULL,Level1_Fun},
	{13,"输入4mA校准","D09",Display_Location,NULL,Level1_Fun},
	{13,"输入20mA校准","D10",Display_Valve,NULL,Level1_Fun},
	{13,"产品编号","D11",Display_Valve,NULL,Level1_Fun},
	{13,"系数","D12",Display_Valve,NULL,Level1_Fun},
	{13,"过力矩延时","D13",Display_Param,NULL,Level1_Fun},
};
//报警菜单
uint8_t *const alarm_string[] =
{
	{"全开"},
	{"全关"},
	{"给定报警"},
	{"关过力矩"},
	{"开过力矩"},
	{"指定位置"},
	{"综合"},
};
//恢复设置菜单
uint8_t *const default_string[] =
{
	{"取消"},
	{"恢复默认"},
};
//信号故障菜单
uint8_t *const fault_string[] =
{
	{"全开"},
	{"全关"},
	{"保持"},
	{"指定位置"},
};
//状态栏显示参数
uint8_t *const status_string[] =
{
	{"就地"},
	{"远程"},
	{"设置"},
};
uint8_t *const param_string[] =
{
	{"开度"},
	{"温度"},
	{"电流"},
};


/******************************函数定义***********************************/
/***************************************************************************/
//函数:	void Run(struct MenuItem *menu) 
//说明:	执行菜单显示函数
//输入: menu 要执行的菜单
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Run(MenuItem *menu) 
{ 
	(*(menu->Fun))(menu); 
}
/***************************************************************************/
//函数:	void TopMenu(void)
//说明:	首页菜单显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_TopMenu(void)
{
	float rate;
	uint8_t datastr[6] = {"45.1%"};
	//显示状态栏
	Display_Statusbar(status, param_string[FatherIndex[0]],NORMAL);
	//计算进度
	switch(FatherIndex[0])
	{
		case 0:				//计算开度值
			//rate =(float) Shift_ADC *10 / distance;
			rate = 45.1;
			break;
		case 1:				//计算温度值
			//rate = ;
			break;
		case 2:				//计算电流值
			// rate = ;
			break;
	}
	sprintf(datastr, "%.1f%%", rate);
	//主显示区
	LCD_Display_String(datastr,TYPE_16,4,50,NORMAL);
	
	//显示进度条
	Display_Progressbar((uint8_t)rate);
	
}
/***************************************************************************/
//函数:	void Display_Statusbar(StatusType status, uint8_t *number, uint8_t colour)
//说明:	显示状态栏函数
//输入: status 要显示的状态 number 要显示的编号 colour 编号是否需要反显
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_Statusbar(StatusType status, uint8_t *number, uint8_t colour)
{
	uint8_t i;
	uint8_t *string = NULL;
	//显示字
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
	//如果显示编号,需要根据colour决定是否反显
	LCD_Display_Mixure(number, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN2, colour);
	//显示线
	//确定显示位置
	LCD_SetCursorPos(2,1);
	for(i=0;i<128;i++)
	{
		Display_Buff[1][i] |= 0x20;			//与0x20相或表示要显示直线的位置,列扫描是从低到高(或从右到左),从上到下	
		LCD_SendByte(DATA_TYPE, Display_Buff[1][i]);		
	}
}
/***************************************************************************/
//函数:	void Display_Progressbar(uint8_t rate)
//说明:	进度条显示函数
//输入: rate 要显示的进度条百分比
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_Progressbar(uint8_t rate)
{
	uint8_t i;
	uint8_t len = 128*rate/100;
	
	memset(Display_Buff[7],0xff,len);
	memset(&Display_Buff[7][len],0x81,127-len);
	//进度条结束位置
	Display_Buff[7][127] = 0xff;
	//确定显示位置
	LCD_SetCursorPos(8,1);
	for(i=0;i<128;i++)
	{
		LCD_SendByte(DATA_TYPE, Display_Buff[7][i]);
	}
}
/***************************************************************************/
//函数:	void Clear_Progressbar(void)
//说明:	清除进度条显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Clear_Progressbar(void)
{
	uint8_t i;
	
	//清除进度条缓存
	memset(Display_Buff[7],0x00,128);
	//确定显示位置
	LCD_SetCursorPos(8,1);
	for(i=0;i<128;i++)
	{
		LCD_SendByte(DATA_TYPE, Display_Buff[7][i]);
	}
}
/***************************************************************************/
//函数:	void Display_Level1(void)
//说明:	level1菜单显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_Level1(void)
{
	uint8_t i;
	
    //修改状态栏显示编号
    LCD_Display_String(Level1_Fun[FatherIndex[1]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2,REVERSE);
    //为屏蔽汉字多出的一个字节
    LCD_Display_String(" ",TYPE_12,STATUSBARLINE,STATUSBARCOLUMN2+18,NORMAL);
    //清除进度条
    Clear_Progressbar();
    
    //显示当前菜单
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_16, MAINDISPLAYL, MAINDISPLAYL, NORMAL);
    //显示下级菜单
    for(i=0;i<2;i++)
    {
       LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString, TYPE_16, CHILDL+2*i, CHILDC, NORMAL);
    }	
}
/***************************************************************************/
//函数:	void Display_Basic(void)
//说明:	基本菜单显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_Basic(void)
{
	uint8_t i;
	
    //修改状态栏显示
    LCD_Display_String(Basic_Fun[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2, NORMAL);
    
    //显示当前菜单为基本菜单(父菜单)
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_16, MAINDISPLAYL, MAINDISPLAYL, NORMAL);
    //显示本级菜单
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

