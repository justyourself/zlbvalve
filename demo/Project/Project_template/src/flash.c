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
 * Description: �������溯��,����EEPROM�������б���
 */
/*************************************************************************/
#include "flash.h"


/******************************��������***********************************/
ParamStr ParaData;						//�˵��������ݽṹ��




/******************************��������***********************************/
/***************************************************************************/
//����:	uint8_t GB21_SimuReadByte(void)
//˵��:	GB21ģ��SPI���պ���
//����: ��
//���: �����ֽ�����
//�༭: zlb
//ʱ��: 2015.12.22
/***************************************************************************/
void Param_Init(void)
{
	uint8_t WriteBuffer[FLASH_BLOCK_SIZE] = "This is a Flash Data Memory write and read test...by-��� @2012-12-10";
	uint8_t ReadBuffer[FLASH_BLOCK_SIZE];
	//���ô洢�����ʱ���ǲ��̶�ģʽ,�����ʱΪ�̶�ʱ���һ��,δ����ʱΪ�̶�ʱ��
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG);

    FLASH_EraseBlock(Block_0,FLASH_MEMTYPE_DATA);
	WriteMultiBlockByte(Block_0,FLASH_MEMTYPE_DATA,FLASH_PROGRAMMODE_STANDARD,WriteBuffer,1);
	
	ReadMultiBlockByte(Block_0,1,ReadBuffer);
//�����ó���
	//������EEPROM����
//	FLASH_Unlock(FLASH_MEMTYPE_DATA);
	// �ȴ� Data EEPROM area ������־λ��λ
//  	while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);

//	FLASH_ProgramBlock(Block_1, FLASH_MEMTYPE_DATA, FLASH_PROGRAMMODE_STANDARD,WriteBuffer);
//	FLASH_ProgramByte(0x4040,0x88);
//	FLASH_Lock(FLASH_MEMTYPE_DATA);
	
	
}







