/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : flash.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2016-1-3
 * Version    : V1.0
 * Change     :
 * Description: 参数保存函数,调用EEPROM函数进行保存
 */
/*************************************************************************/
#include <stdlib.h>
#include "flash.h"
#include "key.h"


/******************************变量定义***********************************/





/******************************函数定义***********************************/
/***************************************************************************/
//函数:	void Param_Init(void)
//说明:	参数初始化
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
void Param_Init(void)
{
	uint8_t flag = 0;
	uint16_t crc = 0;
	ParamStr paratmp;	

	//设置存储器编程时间是不固定模式,块擦除时为固定时间的一半,未擦除时为固定时间
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
	//读取默认数据存储状态标志
	ReadString(DEFAULTBLOCK, 1, &flag);
	if(flag)
	{
		ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&paratmp);
		crc = CRC_JY((uint8_t *)&paratmp, sizeof(ParamStr)-2);
		if(crc != paratmp.CRC)
		{
			//校验失败,恢复默认值
			Default_Data();
		}
	}
	else
	{
		//未存储默认值,恢复默认值
		Default_Data();
	}

	//读取菜单数据
	ReadString(PARAMBLOCK, 1, &flag);
	if(flag)
	{
		ReadString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		crc = CRC_JY((uint8_t *)&ParaData, sizeof(ParamStr)-2);
		if(crc != ParaData.CRC)
		{
			//校验失败,从默认数据存储区读取数据
			ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
			//保存到菜单数据块中
			WriteString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		}
	}
	else
	{
		//flag读取失败,从默认数据存储区读取数据
		ReadString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
		//保存到菜单数据块中
		WriteString(PARAMBLOCK, sizeof(ParamStr), (uint8_t *)&ParaData);
	}
}
/***************************************************************************/
//函数:	void Default_Data(void)
//说明:	默认数据设置
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2016.1.6
/***************************************************************************/
void Default_Data(void)
{
	ParamStr *paratmp = NULL;

	paratmp = (ParamStr *)malloc(sizeof(ParamStr));
	//数据存在标志
	paratmp->flag = 1;							//有数据
	//基本菜单默认设置
	paratmp->Basic_data.language = 1;			//中文显示
	paratmp->Basic_data.allopen = 920;			//全开值,需要根据实际进行调整设置
	paratmp->Basic_data.allclose = 100;			//全关值,需要根据实际进行调整设置
	paratmp->Basic_data.out4ma = 5;				//输出4mA校准
	paratmp->Basic_data.out20ma = 5;			//输出20mA校准	
	paratmp->Basic_data.deadzone = 3;			//死区调整值
	paratmp->Basic_data.errtype = close;		//故障类型关闭,全开,全关,保持,指定,
	paratmp->Basic_data.errplace = 50;			//故障时移动至指定位置
#ifdef G_TYPE
	paratmp->Basic_data.powerofftype = close;	//断电类型,同故障类型
	paratmp->Basic_data.poweroffplace = 50;		//断电时移动至指定位置
	paratmp->Basic_data.poweroffdelay = 50;		//断电时移动至指定位置	
	paratmp->Basic_data.rlstatus = local;		//本地或远方状态(MT系列为硬件控制)
#endif
	//高级菜单默认设置
	paratmp->Advancd_data.logic = 0;			//正反作用,0,正作用,1,反作用
#ifdef G_TYPE
	paratmp->Advancd_data.maxspeed = 2;			//最大速度
	paratmp->Advancd_data.minspeed = 1;			//最小速度
	paratmp->Advancd_data.esdtype = close;		//ESD类型,同故障类型
	paratmp->Advancd_data.esdplace = 50;		//ESD时移动至指定位置
	paratmp->Advancd_data.startoption = 1;		//开机选项,0,本地,1,远方
#endif
	paratmp->Advancd_data.alarm1 = close;		//报警1类型:关闭,全开,全关,无给信号,关过力矩,开过力矩,指定位置,综合报警
	paratmp->Advancd_data.alarm2 = close;		//报警2类型	
#ifdef G_TYPE
	paratmp->Advancd_data.alarm3 = close;		//报警3类型	
	paratmp->Advancd_data.alarm4 = close;		//报警4类型	
	paratmp->Advancd_data.alarm5 = close;		//报警5类型
	paratmp->Advancd_data.alarm6 = close;		//报警6类型
#endif
	paratmp->Advancd_data.alarmplace = 50;		//指定位置报警中的位置
	paratmp->Advancd_data.signaltype = 0;		//0,4~20mA信号,1,0~20mA信号,2,0~10V信号
	paratmp->Advancd_data.addr = 3200;			//设备地址,U16
	//出厂设置菜单
	paratmp->Factory_data.password = 110;		//密码设置		
#ifdef G_TYPE
	paratmp->Factory_data.slowrange = 3;		//减速范围
#endif
	paratmp->Factory_data.moment = 1;			//力矩校准
	paratmp->Factory_data.momentunits = 0;		//力矩单位 0,Nm;1,N
  	paratmp->Factory_data.openmoment = 5;		//开力矩
  	paratmp->Factory_data.closemoment = 3;		//关力矩
  	paratmp->Factory_data.overmoment1 = 1;		//过力矩系数1
  	paratmp->Factory_data.overmoment2 = 2;		//过力矩系数2
  	paratmp->Factory_data.in4ma = 2;			//输入4ma校准
  	paratmp->Factory_data.in20ma = 5;			//输入20ma校准
  	paratmp->Factory_data.number = "河南郑州";	//产品编号地址
  	paratmp->Factory_data.factor = 2;			//系数
  	paratmp->Factory_data.overdelay = 30;		//过力矩延时
	//CRC数据计算
	paratmp->CRC = CRC_JY((uint8_t *)paratmp, sizeof(ParamStr)-2);
	//保存至数据存储区
	WriteString(DEFAULTBLOCK, sizeof(ParamStr), (uint8_t *)paratmp);
	//释放内存空间
	free(paratmp);
	
}
/***************************************************************************/
//函数:	uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen)
//说明:	16位CRC校验
//输入: puchMsg 需要进行校验的数据 usDataLen 需要校验的数据长度
//输出: 16位CRC校验值
//编辑: zlb
//时间: 2016.1.4
/***************************************************************************/
uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t crc;
	uint8_t  i,j;
	uint8_t TT;

	crc=0xffff;
	for (j=0;j<usDataLen;j++)
	{
		crc=crc ^ *(puchMsg+j);
		for (i=0;i<8;i++)
		{
			TT=crc&1;
			crc=crc>>1;
			crc=crc&0x7fff;
			if (TT==1)
				crc=crc^0xa001;
			crc=crc&0xffff;
		}

	}
	return(crc);
}





