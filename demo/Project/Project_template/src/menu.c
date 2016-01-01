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
#include "key.h"
#include "JLX12864G.h"
#include "GT21H16S2Y.h"



/******************************变量声明***********************************/
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
/******************************变量定义***********************************/
//菜单跳转记录参数定义
uint8_t FatherIndex[Menu_Level];               //父菜单所在位置
uint8_t layer = 0;                             //当前菜单所在层
MenuItem *manyou = NULL;						//变量用来漫游整个菜单
uint8_t  dofunflag = DISABLE;					//执行函数执行标志
uint8_t  refresh = ENABLE;						//刷新菜单标志
uint8_t  keyup = 0;								//数据显示界面按键值传递
uint8_t  keydown = 0;
uint8_t  keyset = 0;

//Top菜单显示(进入条件,需要在就地状态下,按下SET键)
MenuItem TopMenu[1] = 
{
	{1,NULL,NULL,NULL,Display_TopMenu,NULL,Level1_Fun,NULL},
};
//Level1菜单显示
MenuItem Level1_Fun[3] = 
{
	{3,"基本设置","Basi_set","A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,"高级设置","Adv_set","A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,"出厂设置","Fact_set","A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
//基本菜单显示
MenuItem Basic_Fun[12] =
{
	{12,"语言选择","Language","B01",Display_Basic,NULL,Language_Fun,Level1_Fun},
	{12,"全开设置","Open_pos","B02",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"全关设置","Close_pos","B03",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"给定4mA效验","In_4mA_adj","B04",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"给定20mA效验","In_20mA_adj","B05",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,"死区调整","Death_section","B06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"信号故障类型","Sign_err","B07",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,"故障指定位置","Sign_errpos","B08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"断电动作类型","Poweroff","B09",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,"断电指定位置","Power_pos","B10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"断电动作延时","Power_delay","B11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,"远控手动设置","Set_local","B12",Display_Basic,Set_Save,NULL,Level1_Fun},       
}; 
//高级菜单显示
MenuItem Advanced_Fun[14] = 
{
	{14,"正反作用","Logic","C01",Display_Basic,NULL,Logic_Fun,Level1_Fun},
	{14,"最大速度","Max_Speed","C02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,"最小速度","Min_Speed","C03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,"ESD类型","ESD_type","C04",Display_Basic,NULL,Level1_Fun},
	{14,"ESD定位","ESD_pos","C05",Display_Basic,NULL,Level1_Fun},
	{14,"报警1类型","Alarm_COM1","C06",Display_Basic,NULL,Level1_Fun},
	{14,"报警2类型","Alarm_COM2","C07",Display_Basic,NULL,Level1_Fun},
	{14,"报警3类型","Alarm_COM3","C08",Display_Basic,NULL,Level1_Fun},
	{14,"报警4类型","Alarm_COM4","C09",Display_Basic,NULL,Level1_Fun},
	{14,"报警5类型","Alarm_COM5","C10",Display_Basic,NULL,Level1_Fun},
	{14,"报警6类型","Alarm_COM6","C11",Display_Basic,NULL,Level1_Fun},
	{14,"报警定位","Alarm_pos","C12",Display_Basic,NULL,Level1_Fun},
	{14,"信号类型","Sign_type","C13",Display_Basic,NULL,Level1_Fun},
	{14,"设备地址","Address","C14",Display_Basic,NULL,Level1_Fun},
};
//出厂设置
MenuItem Factory_Fun[13] = 
{
	{13,"密码设置","Change_Key","D01",Display_Basic,NULL,Level1_Fun},
	{13,"减速范围","Reduce","D02",Display_Basic,NULL,Level1_Fun},
	{13,"力矩校准","Torque_adj","D03",Display_Basic,NULL,Level1_Fun},
	{13,"力矩单位","Touque_unit","D04",Display_Basic,NULL,Level1_Fun},
	{13,"开阀力矩","Open_touque","D05",Display_Basic,NULL,Level1_Fun},
	{13,"关阀力矩","Close_touque","D06",Display_Basic,NULL,Level1_Fun},
	{13,"过力矩系数一","Over_moment1","D07",Display_Basic,NULL,Level1_Fun},
	{13,"过力矩系数二","Over_moment2","D08",Display_Basic,NULL,Level1_Fun},
	{13,"输入4mA校准","Out_4mA_adj","D09",Display_Basic,NULL,Level1_Fun},
	{13,"输入20mA校准","Out_20mA_adj","D10",Display_Basic,NULL,Level1_Fun},
	{13,"产品编号","No.","D11",Display_Basic,NULL,Level1_Fun},
	{13,"系数","Factor","D12",Display_Basic,NULL,Level1_Fun},
	{13,"过力矩延时","Over_delay","D13",Display_Basic,NULL,Level1_Fun},
};
//语言设置
MenuItem Language_Fun[2] = 
{
	{2,"中文","CHINESE","E01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,"ENGLISH","ENGLISH","E02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//显示菜单
MenuItem Display_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Valve,NULL,NULL},
};
//错误菜单
MenuItem Fault_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Fault,NULL,NULL},
};
//正反作用菜单
MenuItem Logic_Fun[1] = 
{
	{1,NULL,NULL,NULL,Display_Fault,NULL,NULL},
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
//函数:	void Display(MenuItem *menu) 
//说明:	执行菜单显示函数
//输入: menu 要执行的菜单
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Display(MenuItem *menu) 
{ 
	(*(menu->Display))(menu); 
}
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
	dofunflag = ENABLE;
	(*(menu->Fun))(); 
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

	refresh = ENABLE;
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
	LCD_Display_Line(2,1);
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

	refresh = DISABLE;
	//切换状态
	LCD_Display_Chinese(status_string[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	//为屏蔽汉字多出的一个字节
    LCD_Display_String(" ",TYPE_12,STATUSBARLINE,STATUSBARCOLUMN2,NORMAL);
    //修改状态栏显示编号
    LCD_Display_String(Level1_Fun[FatherIndex[1]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6,REVERSE);
	//显示分割线
	LCD_Display_Line(2, 1);
	//清除主显示区
	LCD_Display_String("     ",TYPE_16,4,50,NORMAL);
    //清除进度条
    Clear_Progressbar();
    
    //显示当前菜单
    LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].DisplayString1, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //显示下级菜单
    for(i=0;i<2;i++)
    {
	   LCD_Display_String("            ",TYPE_12,CHILDL+2*i, CHILDC,NORMAL);
	   LCD_Display_Chinese(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString1, TYPE_12, CHILDL+2*i, CHILDC, NORMAL);
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
	MenuItem *parentms = manyou->Parentms;
	MenuItem *where = manyou;

	refresh = DISABLE;
    //修改状态栏显示 Level1_Fun[FatherIndex[1]].Childrenms[i]
    LCD_Display_String(where[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6, NORMAL);
    //显示分割线
	LCD_Display_Line(2, 1);
    //显示当前菜单为基本菜单(父菜单)
    LCD_Display_Chinese(parentms[FatherIndex[layer-1]].DisplayString1, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //显示本级菜单
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
//函数:	void Language_Set (void)
//说明:	语言设置,不需要切换显示界面，只需要保存选择即可
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.30
/***************************************************************************/
void Language_Set (void)
{
	refresh = DISABLE;
	//修改状态栏
	
	//设置语言选项

	//退回上级菜单
	layer --;
	manyou = (manyou+FatherIndex[layer])->Parentms;
}
/***************************************************************************/
//函数:	void Display_Valve(void)
//说明:	显示菜单数据,对没有菜单的数据进行显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.30
/***************************************************************************/
void Display_Value(void)
{
	MenuItem *where = manyou;
	float rate = 20.1;
	uint8_t datastr[5] = {0};

	//修改状态栏显示
	LCD_Display_String(where[FatherIndex[layer]].Status, TYPE_12,STATUSBARLINE, STATUSBARCOLUMN2+6, NORMAL);
    //显示分割线
	LCD_Display_Line(2, 1);
	//清除当前主显示区的数据
	LCD_CleanL2L(3,8);
	//显示当前所在选项
	LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString1, TYPE_12,MAINDISPLAYL, MAINDISPLAYC, NORMAL);
	//找出自己的位置

	//显示数据
	sprintf(datastr, "%.1f", rate);
	//主显示区
	LCD_Display_String(datastr,TYPE_16,VALUEL,VALUEC,REVERSE);
	
}
void Set_Value(void)
{
	//找出自己的位置
	
	
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

