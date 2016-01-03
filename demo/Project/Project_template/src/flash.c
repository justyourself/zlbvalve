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
#include "flash.h"


/******************************变量定义***********************************/
ParamStr ParaData;						//菜单保存数据结构体




/******************************函数定义***********************************/
/***************************************************************************/
//函数:	uint8_t GB21_SimuReadByte(void)
//说明:	GB21模拟SPI接收函数
//输入: 无
//输出: 接收字节数据
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
void Param_Init(void)
{
	uint8_t WriteBuffer[FLASH_BLOCK_SIZE] = "This is a Flash Data Memory write and read test...by-风驰 @2012-12-10";
	uint8_t ReadBuffer[FLASH_BLOCK_SIZE];
	//设置存储器编程时间是不固定模式,块擦除时为固定时间的一半,未擦除时为固定时间
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG);

    FLASH_EraseBlock(Block_0,FLASH_MEMTYPE_DATA);
	WriteMultiBlockByte(Block_0,FLASH_MEMTYPE_DATA,FLASH_PROGRAMMODE_STANDARD,WriteBuffer,1);
	
	ReadMultiBlockByte(Block_0,1,ReadBuffer);
//测试用程序
	//解锁对EEPROM操作
//	FLASH_Unlock(FLASH_MEMTYPE_DATA);
	// 等待 Data EEPROM area 解锁标志位置位
//  	while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);

//	FLASH_ProgramBlock(Block_1, FLASH_MEMTYPE_DATA, FLASH_PROGRAMMODE_STANDARD,WriteBuffer);
//	FLASH_ProgramByte(0x4040,0x88);
//	FLASH_Lock(FLASH_MEMTYPE_DATA);
	
	
}







