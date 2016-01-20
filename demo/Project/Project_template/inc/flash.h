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

#include "menu.h"
#include "flash_eeprom.h"

//自定义结构体

//故障类型
typedef enum {close, allopen, allclose, keep, assign} ErrType;

//宏定义
#define DEFAULTBLOCK	Block_0			//出厂设置参数保存Block块
#define PARAMBLOCK		Block_1			//上电读取参数保存Block块


//函数声明
void Param_Init(void);
void Default_Data(void);
uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen);


#endif//__FLASH_H