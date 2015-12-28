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
MenuItem TopMenu[2];
MenuItem Level1_Fun[3];
MenuItem Basic_Fun[4];
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
uint8_t layer;                                 //当前菜单所在层

//Top菜单显示(进入条件,需要在就地状态下,按下SET键)
MenuItem TopMenu[4] = 
{
	{4,"基本设置","A00",Display_Basic,Basic_Fun,NULL},
	{4,"高级设置","A01",Display_Advanced,Advanced_Fun,NULL},
	{4,"出场设置","A02",Display_Factory,Factory_Fun,NULL},
	{4,"参数恢复","A03",Set_Default,Default_Fun,NULL},
};
//Level1菜单显示
MenuItem Level1_Fun[3] = 
{
	{3,"基本设置","A02",Display_Basic,Basic_Fun,TopMenu},
	{3,"高级设置","A03",Display_Advanced,Advanced_Fun,TopMenu},
	{3,"出厂设置","A04",Display_Factory,Factory_Fun,TopMenu},
};
//基本菜单显示
MenuItem Basic_Fun[12] =
{
	{12,"语言选择","B01",Set_Close,NULL,Level1_Fun},
	{12,"全开设置","B02",Set_Open,NULL,Level1_Fun},
	{12,"全关设置","B03",Set_Display,NULL,Level1_Fun},
	{12,"给定4mA效验","B04",Display_Reserve,NULL,Level1_Fun},
	{12,"给定20mA效验","B05",Display_Reserve,NULL,Level1_Fun},
	{12,"死区调整","B06",Display_Reserve,NULL,Level1_Fun},
	{12,"信号故障","B07",Display_Reserve,NULL,Level1_Fun},
	{12,"故障指定位置","B08",Display_Reserve,NULL,Level1_Fun},
	{12,"断电动作类型","B09",Display_Reserve,NULL,Level1_Fun},
	{12,"断电指定位置","B10",Display_Reserve,NULL,Level1_Fun},
	{12,"断电动作延时","B11",Display_Reserve,NULL,Level1_Fun},
	{12,"远控手动设置","B12",Display_Reserve,NULL,Level1_Fun},       
}; 
//高级菜单显示
MenuItem Advanced_Fun[5] = 
{
	{5,"报警COM1","A06",Set_Alarm,NULL,Level1_Fun},
	{5,"报警COM2","A07",Set_Alarm,NULL,Level1_Fun},
	{5,"恢复设置","A08",Set_Default,NULL,Level1_Fun},
	{5,"备用3","A09",Display_Reserve,NULL,Level1_Fun},
	{5,"备用4","A10",Display_Reserve,NULL,Level1_Fun},
};
//出厂设置
MenuItem Factory_Fun[17] = 
{
	{17,"输入密码","F11",Password_Verify,NULL,Level1_Fun},
	{17,"修改密码","F12",Password_Change,NULL,Level1_Fun},
	{17,"给定4mA效验","F13",Input_Signal,NULL,Level1_Fun},
	{17,"给定20mA效验","F14",Input_Signal,NULL,Level1_Fun},
	{17,"反馈4mA效验","F15",Output_Signal,NULL,Level1_Fun},
	{17,"反馈20mA效验","F16",Output_Signal,NULL,Level1_Fun},
	{17,"死区调整","F17",Display_DeadZone,NULL,Level1_Fun},
	{17,"信号故障","F18",Display_Fault,NULL,Level1_Fun},
	{17,"指定位置","F19",Display_Location,NULL,Level1_Fun},
	{17,"开阀力矩","F20",Display_Valve,NULL,Level1_Fun},
	{17,"关阀力矩","F21",Display_Valve,NULL,Level1_Fun},
	{17,"最大力矩","F22",Display_Valve,NULL,Level1_Fun},
	{17,"型号","F23",Display_Param,NULL,Level1_Fun},
	{17,"出厂编号","F24",Display_Param,NULL,Level1_Fun},
	{17,"产地","F25",Display_Param,NULL,Level1_Fun},
	{17,"备用5","F26",Display_Reserve,NULL,Level1_Fun},
	{17,"备用6","F27",Display_Reserve,NULL,Level1_Fun},
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
void Display_TopMenu(uint8_t *level)
{
	//uint16_t rate;
	//显示状态栏
	Display_Statusbar(status, param_string[level[0]],NORMAL);
	//计算进度
	//rate = Shift_ADC * 10 / distance;
	//主显示区
	LCD_Display_String("61%",TYPE_16,4,50,NORMAL);
	
	//显示进度条
	Display_Progressbar(45);
	
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
//函数:	void Clear_Progressbar(void)
//说明:	清除进度条显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display_Basic(void)
{
	uint8_t i;
	
        //修改状态栏显示
        LCD_Display_String(TopMenu[0].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2,REVERSE);
        //为屏蔽汉字多出的一个字节
        LCD_Display_6x12(STATUSBARLINE,STATUSBARCOLUMN2+18," ");
        //清除进度条
        Clear_Progressbar();
        
        //显示当前菜单
        LCD_Display_Chinese(TopMenu[0].DisplayString, TYPE_16, MAINDISPLAYL, MAINDISPLAYL, NORMAL);
        //显示下级菜单
        for(i=0;i<2;i++)
        {
           LCD_Display_Chinese(TopMenu[0].Childrenms[i].Childrenms, TYPE_16, CHILDL, CHILDC, NORMAL);
        }
}

void Language_Fun(void)
{
	
}
void Display_Level1(void)
{
	
}
void Display_Basic(void)
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

