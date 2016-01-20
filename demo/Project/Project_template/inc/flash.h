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
 * Description: �������溯��,����EEPROM�������б���
 */
/*************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "menu.h"
#include "flash_eeprom.h"

//�Զ���ṹ��

//��������
typedef enum {close, allopen, allclose, keep, assign} ErrType;

//�궨��
#define DEFAULTBLOCK	Block_0			//�������ò�������Block��
#define PARAMBLOCK		Block_1			//�ϵ��ȡ��������Block��


//��������
void Param_Init(void);
void Default_Data(void);
uint16_t CRC_JY(uint8_t *puchMsg, uint16_t usDataLen);


#endif//__FLASH_H