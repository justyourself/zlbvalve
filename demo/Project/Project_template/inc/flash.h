/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : flash.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2016-1-3
 * Version    : V1.0
 * Change     :
 * Description: 参数保存函数,调用EEPROM函数进行保存
 */
/*************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "flash_eeprom.h"

//自定义结构体

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
  uint16_t  powerofftype;				//断电动作类型
  uint16_t  poweroffplace;				//断电故障位置
  uint16_t  rlstatus;					//远方就地状态	
}BasicDataStr;
//高级菜单数据结构
typedef struct _ADVANCED_DATA_
{
  uint8_t  startoption;				//开机选项
  uint8_t  logic;						//正反作用
  uint8_t  maxspeed;					//最大速度
  uint8_t  minspeed;					//最小速度
  uint8_t  esdtype;						//ESD类型
  uint8_t  esdplace;					//ESD定位
  uint8_t  alarm1;						//报警信号1
  uint8_t  alarm2;						//报警信号2
  uint8_t  alarm3;						//报警信号3  
  uint8_t  alarm4;						//报警信号4  
  uint8_t  alarm5;						//报警信号5  
  uint8_t  alarm6;						//报警信号6 
  uint8_t  alarmplace;					//报警定位
  uint8_t  signaltype;					//信号类型
  uint16_t addr;						//设备地址
}AdvancedDataStr;
//出厂菜单设置
typedef struct _FACTORY_DATA_
{
  uint16_t  password;					//密码设置
  uint16_t  slowrange;					//减速范围
  uint16_t  moment;						//力矩校准
  uint16_t  momentunits;				//力矩单位
  uint16_t  openmoment;				//开力矩
  uint16_t  closemoment;				//关力矩
  uint16_t  overmoment1;				//过力矩系数1
  uint16_t  overmoment2;				//过力矩系数2
  uint16_t  in4ma;						//输入4ma校准
  uint16_t  in20ma;						//输入20ma校准
  uint16_t  *number;					//产品编号地址
  uint16_t  factor;						//系数
  uint16_t  overdelay;					//过力矩延时
}FactoryDataStr;
//参数结构体
typedef struct _PARAM_STR_
{
	BasicDataStr Basic_data;			//基本菜单数据
	AdvancedDataStr Advancd_data;		//高级菜单数据
	FactoryDataStr Factory_data;		//出厂菜单数据
	uint16_t CRC;						//CRC校验数据
	
}ParamStr;
//宏定义
#define DEFAULTBLOCK	Block_0			//出厂设置参数保存Block块
#define PARAMBLOCK		Block_1			//上电读取参数保存Block块

//变量声明
extern ParamStr ParaData;						//菜单保存数据结构体

//函数声明
void Param_Init(void);



#endif//__FLASH_H