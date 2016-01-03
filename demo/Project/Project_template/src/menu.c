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
#include "flash.h"



/******************************变量声明***********************************/
MenuItem TopMenu[1];
MenuItem Level1_Fun[3];
MenuItem Advanced_Fun[14];
MenuItem Basic_Fun[12];
MenuItem Factory_Fun[13];
MenuItem Language_Fun[2];
MenuItem Fault_Fun[5];
MenuItem Local_Fun[2];
MenuItem Logic_Fun[2];
MenuItem ESD_Fun[5];
MenuItem Alarm_Fun[7];
MenuItem Signal_Fun[3];
MenuItem Unit_Fun[2];

uint8_t *const Level1_Chinese[];
uint8_t *const Level1_English[];
uint8_t *const Basic_Chinese[];
uint8_t *const Basic_English[];
uint8_t *const Advanced_Chinese[];
uint8_t *const Advanced_English[];
uint8_t *const Factory_Chinese[];
uint8_t *const Factory_English[];
uint8_t *const Language_Chinese[];
uint8_t *const Language_English[];
uint8_t *const Fault_Chinese[];
uint8_t *const Fault_English[];
uint8_t *const Local_Chinese[];
uint8_t *const Local_English[];
uint8_t *const ESD_Chinese[];
uint8_t *const ESD_English[];
uint8_t *const Alarm_Chinese[];
uint8_t *const Alarm_English[];
uint8_t *const Signal_Chinese[];
uint8_t *const Unit_Chinese[];
uint8_t *const alarm_string[];
uint8_t *const default_string[];
uint8_t *const fault_string[];
uint8_t *const status_string[];
uint8_t *const param_string[];
uint8_t *const param_english[];
uint8_t *const status_english[];
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
	{1,NULL,NULL,Display_TopMenu,NULL,Level1_Fun,NULL},
};
//Level1菜单显示
MenuItem Level1_Fun[3] = 
{
	{3,NULL,"A00",Display_Level1,NULL,Basic_Fun,TopMenu},
	{3,NULL,"A01",Display_Level1,NULL,Advanced_Fun,TopMenu},
	{3,NULL,"A02",Display_Level1,NULL,Factory_Fun,TopMenu},
};
//第一级菜单名称(中文)
uint8_t *const Level1_Chinese[] =
{
	{"基本设置"},
	{"高级设置"},
	{"出厂设置"},
};
//第一级菜单名称(英文)
uint8_t *const Level1_English[] =
{
	{"Basi_set"},
	{"Adva_set"},
	{"Fact_set"},
};
//基本菜单显示
MenuItem Basic_Fun[12] =
{
	{12,NULL,"B01",Display_Basic,NULL,Language_Fun,Level1_Fun},
	{12,NULL,"B02",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B03",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B04",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B05",Display_Basic,Display_Value,NULL,Level1_Fun},
	{12,NULL,"B06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B07",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,NULL,"B08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B09",Display_Basic,NULL,Fault_Fun,Level1_Fun},
	{12,NULL,"B10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{12,NULL,"B12",Display_Basic,NULL,Local_Fun,Level1_Fun},       
};
//基本菜单名称(中文)
uint8_t *const Basic_Chinese[] =
{
	{"语言选择"},
	{"全开设置"},
	{"全关设置"},
	{"给定4mA效验"},
	{"给定20mA效验"},
	{"死区调整"},
	{"信号故障类型"},
	{"故障指定位置"},
	{"断电动作类型"},
	{"断电指定位置"},
	{"断电动作延时"},
	{"远控手动设置"},
};
//基本菜单名称(英文)
uint8_t *const Basic_English[] =
{
	{"Language"},
	{"Open_pos"},
	{"Close_pos"},
	{"In_4mA_adj"},
	{"In_20mA_adj"},
	{"Death_section"},
	{"Sign_err"},
	{"Sign_err_pos"},
	{"Power_off"},
	{"Power_pos"},
	{"Power_delay"},
	{"Set_local"},
};
//高级菜单显示
MenuItem Advanced_Fun[14] = 
{
	{14,NULL,"C01",Display_Basic,NULL,Logic_Fun,Level1_Fun},
	{14,NULL,"C02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C04",Display_Basic,NULL,ESD_Fun,Level1_Fun},
	{14,NULL,"C05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C06",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C07",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C08",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C09",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C10",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C11",Display_Basic,NULL,Alarm_Fun,Level1_Fun},
	{14,NULL,"C12",Display_Basic,Set_Value,NULL,Level1_Fun},
	{14,NULL,"C13",Display_Basic,NULL,Signal_Fun,Level1_Fun},
	{14,NULL,"C14",Display_Basic,Set_Value,NULL,Level1_Fun},
};
//高级菜单名称(中文)
uint8_t *const Advanced_Chinese[] =
{
	{"正反作用"},
	{"最大速度"},
	{"最小速度"},
	{"ESD类型"},
	{"ESD定位"},
	{"报警1类型"},
	{"报警2类型"},
	{"报警3类型"},
	{"报警4类型"},
	{"报警5类型"},
	{"报警6类型"},
	{"报警定位"},
	{"信号类型"},
	{"设备地址"},
};
//高级菜单名称(英文)
uint8_t *const Advanced_English[] =
{
	{"Logic"},
	{"Max_Speed"},
	{"Min_Speed"},
	{"ESD_type"},
	{"ESD_pos"},
	{"Alarm_COM1"},
	{"Alarm_COM2"},
	{"Alarm_COM3"},
	{"Alarm_COM4"},
	{"Alarm_COM5"},
	{"Alarm_COM6"},
	{"Alarm_pos"},
	{"Sign_type"},
	{"Address"},
};
//出厂设置
MenuItem Factory_Fun[13] = 
{
	{13,NULL,"D01",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D02",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D03",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D04",Display_Basic,NULL,Unit_Fun,Level1_Fun},
	{13,NULL,"D05",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D06",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D07",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D08",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D09",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D10",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D11",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D12",Display_Basic,Set_Value,NULL,Level1_Fun},
	{13,NULL,"D13",Display_Basic,Set_Value,NULL,Level1_Fun},
};
//出厂菜单名称(中文)
uint8_t *const Factory_Chinese[] =
{
	{"密码设置"},
	{"减速范围"},
	{"力矩校准"},
	{"力矩单位"},
	{"开阀力矩"},
	{"关阀力矩"},
	{"过力矩系数一"},
	{"过力矩系数二"},
	{"输入4mA校准"},
	{"输入20mA校准"},
	{"产品编号"},
	{"系数"},
	{"过力矩延时"},
};
//出厂菜单名称(英文)
uint8_t *const Factory_English[] =
{
	{"Change_Key"},
	{"Reduce"},
	{"Torque_adj"},
	{"Touque_unit"},
	{"Open_touque"},
	{"Close_touque"},
	{"Over_moment1"},
	{"Over_moment2"},
	{"Out_4mA_adj"},
	{"Out_20mA_adj"},
	{"No."},
	{"Factor"},
	{"Over_delay"},
};
//语言设置
MenuItem Language_Fun[2] = 
{
	{2,NULL,"E01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,NULL,"E02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//语言菜单名称(中文)
uint8_t *const Language_Chinese[] =
{
	{"中文"},
	{"ENGLISH"},
};
//语言菜单名称(英文)
uint8_t *const Language_English[] =
{
	{"CHINESE"},
	{"ENGLISH"},
};
//故障菜单
MenuItem Fault_Fun[5] = 
{
	{5,NULL,"F01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F02",Display_Basic,Set_Value,NULL,Basic_Fun},	
	{5,NULL,"F03",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F04",Display_Basic,Set_Value,NULL,Basic_Fun},
	{5,NULL,"F05",Display_Basic,Set_Value,NULL,Basic_Fun},
};
//故障菜单名称(中文)
uint8_t *const Fault_Chinese[] =
{
	{"关闭"},
	{"全关"},
	{"全开"},
	{"保持"},
	{"指定"},
};
//故障菜单名称(英文)
uint8_t *const Fault_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"Keep"},
	{"Set_pos"},
};
//远方就地设置
MenuItem Local_Fun[2] = 
{
	{2,NULL,"H01",Display_Basic,Set_Value,NULL,Basic_Fun},
	{2,NULL,"H02",Display_Basic,Set_Value,NULL,Basic_Fun},		
};
//远方就地菜单名称(中文)
uint8_t *const Local_Chinese[] =
{
	{"就地"},
	{"远程"},
};
//远方就地菜单名称(英文)
uint8_t *const Local_English[] =
{
	{"Local"},
	{"Remote"},
};
//正反作用菜单
MenuItem Logic_Fun[2] = 
{
	{2,NULL,"F01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{2,NULL,"F02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
};
//正反作用菜单名称(中文)
uint8_t *const Logic_Chinese[] =
{
	{"正作用"},
	{"反作用"},
};
//正反作用菜单名称(英文)
uint8_t *const Logic_English[] =
{
	{"Positive"},
	{"Negative"},
};
//ESD菜单
MenuItem ESD_Fun[5] = 
{
	{5,NULL,"G01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
	{5,NULL,"G03",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G04",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{5,NULL,"G05",Display_Basic,Set_Value,NULL,Advanced_Fun},
};
//ESD菜单名称(中文)
uint8_t *const ESD_Chinese[] =
{
	{"关闭"},
	{"全关"},
	{"全开"},
	{"保持"},
	{"指定"},
};
//ESD菜单名称(英文)
uint8_t *const ESD_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"Keep"},
	{"Set_pos"},
};
//Alarm菜单
MenuItem Alarm_Fun[7] = 
{
	{7,NULL,"H01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
	{7,NULL,"H03",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H04",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H05",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H06",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{7,NULL,"H07",Display_Basic,Set_Value,NULL,Advanced_Fun},
};
//ESD菜单名称(中文)
uint8_t *const Alarm_Chinese[] =
{
	{"关闭报警"},
	{"全开报警"},
	{"全关报警"},
	{"无给信号"},
	{"关过力矩"},
	{"开过力矩"},
	{"指定位置"},
	{"综合报警"},
};
//ESD菜单名称(英文)
uint8_t *const Alarm_English[] =
{
	{"Close"},
	{"Open_pos"},
	{"Close_pos"},
	{"No_signal"},
	{"Ex_cl_to"},
	{"Ex_op_to"},
	{"Set_pos"},
	{"Unit"},
};
//信号类型菜单
MenuItem Signal_Fun[3] = 
{
	{3,NULL,"I01",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{3,NULL,"I02",Display_Basic,Set_Value,NULL,Advanced_Fun},
	{3,NULL,"I02",Display_Basic,Set_Value,NULL,Advanced_Fun},	
};
//信号类型菜单名称(中文)
uint8_t *const Signal_Chinese[] =
{
	{"4-20mA"},
	{"0-20mA"},
	{"0-10V"},	
};
//单位类型菜单
MenuItem Unit_Fun[2] = 
{
	{2,NULL,"J01",Display_Basic,Set_Value,NULL,Factory_Fun},
	{2,NULL,"J02",Display_Basic,Set_Value,NULL,Factory_Fun},	
};
//正反作用菜单名称(中文)
uint8_t *const Unit_Chinese[] =
{
	{"Nm"},
	{"N"},
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
//状态栏显示参数
uint8_t *const status_string[] =
{
	{"就地"},
	{"远程"},
	{"设置"},
};
uint8_t *const status_english[] =
{
	{"Local "},
	{"Remote"},
	{"Set   "},
};
uint8_t *const param_string[] =
{
	{"开度"},
	{"温度"},
	{"电流"},
};
uint8_t *const param_english[] =
{
	{"Open"},
	{"Temp"},
	{"Curr"},
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
//函数:	void Init_Menu(void) 
//说明:	配置菜单显示方式
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Init_Menu(void) 
{ 
	uint8_t i;
	//读取EEPROM数据
	//临时定义,显示中文菜单
	ParaData.Basic_data.language = 1;
	//根据配置信息配置菜单对应中英文选项 language = 1,为中文 0,为英文
	if(ParaData.Basic_data.language)
	{
		for(i=0;i<3;i++)
		{
			Level1_Fun[i].DisplayString = (uint8_t *)Level1_Chinese[i];
		}
		for(i=0;i<14;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_Chinese[i];
		}
		for(i=0;i<12;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_Chinese[i];
		}
		for(i=0;i<13;i++)
		{
			Factory_Fun[i].DisplayString = (uint8_t *)Factory_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Language_Fun[i].DisplayString = (uint8_t *)Language_Chinese[i];
		}
		for(i=0;i<5;i++)
		{
			Fault_Fun[i].DisplayString = (uint8_t *)Fault_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Local_Fun[i].DisplayString = (uint8_t *)Local_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Logic_Fun[i].DisplayString = (uint8_t *)Logic_Chinese[i];
		}
		for(i=0;i<5;i++)
		{
			ESD_Fun[i].DisplayString = (uint8_t *)ESD_Chinese[i];
		}
		for(i=0;i<7;i++)
		{
			Alarm_Fun[i].DisplayString = (uint8_t *)Alarm_Chinese[i];
		}
		for(i=0;i<3;i++)
		{
			Signal_Fun[i].DisplayString = (uint8_t *)Signal_Chinese[i];
		}
		for(i=0;i<2;i++)
		{
			Unit_Fun[i].DisplayString = (uint8_t *)Unit_Chinese[i];
		}	
	}
	else
	{
		for(i=0;i<3;i++)
		{
			Level1_Fun[i].DisplayString = (uint8_t *)Level1_English[i];
		}
		for(i=0;i<14;i++)
		{
			Advanced_Fun[i].DisplayString = (uint8_t *)Advanced_English[i];
		}
		for(i=0;i<12;i++)
		{
			Basic_Fun[i].DisplayString = (uint8_t *)Basic_English[i];
		}
		for(i=0;i<13;i++)
		{
			Factory_Fun[i].DisplayString = (uint8_t *)Factory_English[i];
		}
		for(i=0;i<2;i++)
		{
			Language_Fun[i].DisplayString = (uint8_t *)Language_English[i];
		}
		for(i=0;i<5;i++)
		{
			Fault_Fun[i].DisplayString = (uint8_t *)Fault_English[i];
		}
		for(i=0;i<2;i++)
		{
			Local_Fun[i].DisplayString = (uint8_t *)Local_English[i];
		}
		for(i=0;i<5;i++)
		{
			ESD_Fun[i].DisplayString = (uint8_t *)ESD_English[i];
		}
		for(i=0;i<7;i++)
		{
			Alarm_Fun[i].DisplayString = (uint8_t *)Alarm_English[i];
		}		
	}
	
	
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
	if(ParaData.Basic_data.language)
		Display_Statusbar(status, param_string[FatherIndex[0]],NORMAL);
	else
		Display_Statusbar(status, param_english[FatherIndex[0]],NORMAL);
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
	sprintf((char *)datastr, "%.1f%%", rate);
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
		if(ParaData.Basic_data.language)
			string = status_string[0];
		else
			string = status_english[0];
		break;
		case remote:
		if(ParaData.Basic_data.language)
			string = status_string[1];
		else
			string = status_english[1];
		break;
		case set:
		if(ParaData.Basic_data.language)
			string = status_string[2];
		else
			string = status_english[2];
		break;
		default:
		if(ParaData.Basic_data.language)
			string = status_string[1];
		else
			string = status_english[1];
		break;
	}
	LCD_Display_Mixure(string, TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
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
	if(ParaData.Basic_data.language)
		LCD_Display_Mixure(status_string[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
	else
		LCD_Display_Mixure(status_english[2], TYPE_12, STATUSBARLINE, STATUSBARCOLUMN, NORMAL);
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
    LCD_Display_Mixure(Level1_Fun[FatherIndex[1]].DisplayString, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //显示下级菜单
    for(i=0;i<2;i++)
    {
	   LCD_Display_String("            ",TYPE_12,CHILDL+2*i, CHILDC,NORMAL);
	   LCD_Display_Mixure(Level1_Fun[FatherIndex[1]].Childrenms[i].DisplayString, TYPE_12, CHILDL+2*i, CHILDC, NORMAL);
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
    LCD_CleanL2L(3,4);
    LCD_Display_Mixure(parentms[FatherIndex[layer-1]].DisplayString, TYPE_12, MAINDISPLAYL, MAINDISPLAYC, NORMAL);
    //显示本级菜单
    if(FatherIndex[layer] == 0)
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[0].DisplayString, TYPE_12,CHILDL, CHILDC, REVERSE);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[1].DisplayString, TYPE_12,CHILDL+2, CHILDC, NORMAL);
	}
	else
	{
		LCD_Display_String("            ",TYPE_12,CHILDL, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]-1].DisplayString, TYPE_12,CHILDL, CHILDC, NORMAL);
		LCD_Display_String("            ",TYPE_12,CHILDL+2, CHILDC,NORMAL);
		LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString, TYPE_12,CHILDL+2, CHILDC, REVERSE);
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
	LCD_Display_Mixure(where[FatherIndex[layer]].DisplayString, TYPE_12,MAINDISPLAYL, MAINDISPLAYC, NORMAL);
	//找出自己的位置
	
	//显示数据
	sprintf((char *)datastr, "%.1f", rate);
	//主显示区
	LCD_Display_String(datastr,TYPE_16,VALUEL,VALUEC,REVERSE);
	//数据保存
	if(keyset)
	{
		keyset --;
		//按下SET按键,将数据保存(先转换后保存)
		
	}
	
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

