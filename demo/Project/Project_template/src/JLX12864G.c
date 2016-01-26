/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : JLX12864G-102-stm8.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: JLX12864G-102 STM8����
 */
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "JLX12864G.h"
#include "GT21H16S2Y.h"

// ��������
static void delay(__IO uint32_t nCount);
static void LCD_SPISendByte(uint8_t DataToSend);
static void LCD_SimuSendByte(uint8_t DataToSend);

// ���ݻ��涨��
#ifdef DISPLAYBUFF
uint8_t Display_Buff[8][128] = {0};		//LCD��ʾ����
#endif
/***************************************************************************/
//����:	static void delay(__IO uint32_t nCount)
//˵��:	��ʱ����(�ڲ�ʹ�ú���,��ʱnCount��ʱ�ӽ���)
//����: nCount ��ʱ������
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
static void delay(__IO uint32_t nCount)
{
  // Decrement nCount value
  while (nCount != 0)
  {
    nCount--;
  }
}
/***************************************************************************/
//����:	void JLX_LCD_Init(void)
//˵��:	LCD��ʼ����������ʼ��SPI GPIO ������LCD_Init()��ʼ������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void JLX_LCD_Init(void)
{
	// Enable SPI clock
	CLK_PeripheralClockConfig(LCD_SPI_CLK, ENABLE);
	// Configure SPI pins: SCK MOSI MISO Pull Up
	//GPIO_ExternalPullUpConfig(LCD_SPI_GPIO_PORT, (GPIO_Pin_TypeDef)(LCD_SPI_SCK_PIN | LCD_SPI_MOSI_PIN | \
	//						LCD_SPI_MISO_PIN), ENABLE);
	GPIO_Init(LCD_SPI_GPIO_PORT, (GPIO_Pin_TypeDef)(LCD_SPI_SCK_PIN | LCD_SPI_MOSI_PIN) , GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LCD_SPI_GPIO_PORT, LCD_SPI_MISO_PIN, GPIO_MODE_IN_PU_NO_IT);
	// Initialize SPI  //Disable SPI config,simulation SPI sequence
	//SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, 
	//	   SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, 
	//	   SPI_NSS_SOFT, 0x07);
	// Enable SPI	   
	//SPI_Cmd(ENABLE);
	
	// Configure LCD ChipSelect pin (CS) in Output push-pull mode 
	GPIO_Init(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	// Set default CS is high level
	LCD_NCS_HIGH();
	// LCD RS PIN in Output push-pull mode
	GPIO_Init(LCD_SPI_RS_PORT, LCD_SPI_RS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

	// Configure LCD backlight pin in Output push-pull low level (backlight off)
	GPIO_Init(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	// Disable backlight
	LCD_BacklightCmd(DISABLE);
		
	// LCD_Init,Send CMD
	LCD_Init();
    // Enable backlight
    LCD_BacklightCmd(ENABLE);
}
/***************************************************************************/
//����:	void LCD_Init(void)
//˵��:	LCD��ʾ��ʼ����������ʼ����ʾ������Աȶ�
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Init(void)
{
	//JLX12864G-102 ��ʼ������
	LCD_SendByte(COMMAND_TYPE,SOFT_REST);           //soft reset
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_UP1);				//up power one 
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_UP2);				//up power two 
	delay(0x4000);  
	LCD_SendByte(COMMAND_TYPE,SET_UP3);				//up power three
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_THICK_CONTRAST);	//�ֵ��Աȶȣ�������(0x20~0x27)
	LCD_SendByte(COMMAND_TYPE,SET_THIN_CONTRAST);	//΢���Աȶ�
	LCD_SendByte(COMMAND_TYPE,0x1A);				//΢���Աȶ�ֵ�������÷�Χ(0x00~0x3f)
	LCD_SendByte(COMMAND_TYPE,0XA2);				//1/9ƫѹ��
	LCD_SendByte(COMMAND_TYPE,SET_LINE);			//��ɨ��˳�򣺴��ϵ���
	LCD_SendByte(COMMAND_TYPE,SET_ROW);				//��ɨ��˳�򣺴�����
	LCD_SendByte(COMMAND_TYPE,START_LINE);			//��ʼ�У���һ�п�ʼ
	LCD_SendByte(COMMAND_TYPE,OPEN_DISPLAY);		//����ʾ ����ʾ������������,����������������,һֱû�д���ɲ�����ʾ
}
/***************************************************************************/
//����:	void LCD_SendByte(uint8_t DataType, uint8_t DataToSend)
//˵��:	LCD���ݷ��ͺ���
//����: DataType �������� ���ݻ�����;DataToSend ��������
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_SendByte(uint8_t DataType, uint8_t DataToSend)
{
	// Enable access to LCD 
	LCD_NCS_LOW();

	// Set RS Pin 
	if(DataType == COMMAND_TYPE)
	{
		//��������Ϊ����
		LCD_RS_LOW();
	}
	else
	{	//��������Ϊ����
		LCD_RS_HIGH();
	}

	// Send byte SPI mode
	//LCD_SPISendByte(DataToSend);
	// Simulation SPI mode
	LCD_SimuSendByte(DataToSend);

	// Disable access to LCD 
	LCD_NCS_HIGH();
}
/***************************************************************************/
//����:	void LCD_BacklightCmd(FunctionalState NewState)
//˵��:	������Ƿ�ʹ��
//����: NewState �����ʹ��״̬
//���: ��
//�༭: zlb
//ʱ��: 2015.12.16
/***************************************************************************/
void LCD_BacklightCmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    GPIO_WriteLow(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
  }
  else
  {
    GPIO_WriteHigh(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
  }
}
/***************************************************************************/
//����:	static void LCD_SPISendByte(uint8_t DataToSend)
//˵��:	LCD SPI���ݷ��ͺ���
//����: DataToSend ��������
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
static void LCD_SPISendByte(uint8_t DataToSend)
{
	// Send byte through the SPI peripheral
	LCD_SPI->DR = DataToSend;

	while ((LCD_SPI->SR & SPI_SR_TXE) == 0)
	{
	/* Wait while the byte is transmitted */
	}
}
/***************************************************************************/
//����:	static void LCD_SimuSendByte(uint8_t DataToSend)
//˵��:	LCD ģ��SPI���ݷ��ͺ���
//����: DataToSend ��������
//���: ��
//�༭: zlb
//ʱ��: 2015.12.22
/***************************************************************************/
static void LCD_SimuSendByte(uint8_t DataToSend)
{
	uint8_t i;
	
	//ģ��SPIʱ��������
	for(i=0;i<8;i++)
	{
		// Set SCLK low
		LCD_SCLK_LOW();
		if(DataToSend & 0x80)
			LCD_MOSI_HIGH();
		else
			LCD_MOSI_LOW();
		// Set SCLK high
		LCD_SCLK_HIGH();
		DataToSend <<= 1;
	}
}
/***************************************************************************/
//����:	void LCD_Clear(void)
//˵��:	LCD�������� �����Ļ��ʾ
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Clear(void)
{
	uint8_t i,j;

	for(i=0;i<8;i++)
	{
		// ��λ��ʾλ��
		LCD_SetCursorPos(1+i,1);
		for(j=0;j<128;j++)
		{
			// �����ʾ����
			LCD_SendByte(DATA_TYPE,0x00);
			#ifdef DISPLAYBUFF
			Display_Buff[i][j] = 0x00;
			#endif
		}
	}
}
/***************************************************************************/
//����:	void LCD_CleanL2L(uint8_t begin, uint8_t end)
//˵��:	LCD���ָ��ҳ��ҳ֮�������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_CleanL2L(uint8_t begin, uint8_t end)
{
	uint8_t i,j;

	if(begin > end)
		return;
	
	for(i=begin;i<=end;i++)
	{
		// ��λ��ʾλ��
		LCD_SetCursorPos(i,1);
		for(j=0;j<128;j++)
		{
			// �����ʾ����
			LCD_SendByte(DATA_TYPE,0x00);
			#ifdef DISPLAYBUFF
			Display_Buff[i-1][j] = 0x00;
			#endif
		}
	}
}
/***************************************************************************/
//����:	void LCD_SetCursorPos(uint8_t Line, uint8_t Column)
//˵��:	LCD������ʾ���꺯��
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128�� 
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_SetCursorPos(uint8_t Line, uint8_t Column)
{
	// ҳ���0��ʼ,��˵�1ҳΪ��ҳ
	Line = Line - 1;
	// ����ҳ��ַ
	LCD_SendByte(COMMAND_TYPE,0xb0+Line);
	// �����е�ַ��4λ
	LCD_SendByte(COMMAND_TYPE,((Column>>4)&0x0f)+0x10);
	// �����е�ַ��4λ
	LCD_SendByte(COMMAND_TYPE,Column&0x0f);	
}
/***************************************************************************/
//����:	void LCD_Display_6x12(uint8_t Line, uint8_t Column, uint8_t *text)
//˵��:	LCD��ʾ6*12���ַ�
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128��; text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_6x12(uint8_t Line, uint8_t Column, uint8_t *text)
{
	uint8_t i,j;

	for(j=0;j<2;j++)
	{
		LCD_SetCursorPos(Line+j,Column);
		for (i=0;i<6;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[Line+j-1][Column+i-1] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_12x12(uint8_t Line, uint8_t Column, uint8_t *text)
//˵��:	LCD��ʾ12*12�ĺ���
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128��; text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_12x12(uint8_t Line, uint8_t Column, uint8_t *text)
{
	uint8_t i,j;
	
	for(j=0;j<2;j++)
	{
		LCD_SetCursorPos(Line+j,Column);
		for (i=0;i<12;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[Line+j-1][Column+i-1] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_8x16(uint8_t Line, uint8_t Column, uint8_t *text)
//˵��:	LCD��ʾ8*16���ַ�
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128��; text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_8x16(uint8_t Line, uint8_t Column, uint8_t *text)
{
	uint8_t i,j;
	
	for(j=0;j<2;j++)
	{
		LCD_SetCursorPos(Line+j,Column);
		for (i=0;i<8;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[Line+j-1][Column+i-1] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_16x16(uint8_t Line, uint8_t Column, uint8_t *text)
//˵��:	LCD��ʾ16*16�ĺ���
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128��; text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_16x16(uint8_t Line, uint8_t Column, uint8_t *text)
{
	uint8_t i,j;
	
	for(j=0;j<2;j++)
	{
		LCD_SetCursorPos(Line+j,Column);
		for (i=0;i<16;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[Line+j-1][Column+i-1] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_15x32(uint8_t Line, uint8_t Column, uint8_t *text)
//˵��:	LCD��ʾ16*16�ĺ���
//����: Line ������(ҳ)��λ,64�ж���Ϊ8ҳ,Line����ҳ��; Column �����ж�λ,128��; text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_15x32(uint8_t Line, uint8_t Column, uint8_t *text)
{
	uint8_t i,j;
	
	for(j=0;j<4;j++)
	{
		LCD_SetCursorPos(Line+j,Column);
		for (i=0;i<15;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[Line+j-1][Column+i-1] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_128x64(uint8_t *text)
//˵��:	LCD��ʾ128*64ͼƬ
//����: text ����ʾ����ָ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void LCD_Display_128x64(uint8_t *text)
{
	uint8_t i,j;
	
	for(j=0;j<8;j++)
	{
		LCD_SetCursorPos(j+1,1);
		for (i=0;i<128;i++)
		{
			LCD_SendByte(DATA_TYPE,*text);
			#ifdef DISPLAYBUFF
			Display_Buff[j][i] = *text;
			#endif
			text++;
		}
	}	
}
/***************************************************************************/
//����:	void LCD_Display_String(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//˵��:	LCD��ʾ�ַ�������
//����: string ����ʾ�ַ�������ָ�� type��ʾ�ַ����� Line ������ʾ�� Column ������ʾ�� colour �Ƿ���
//���: ��
//�༭: zlb
//ʱ��: 2015.12.16
/***************************************************************************/
void LCD_Display_String(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(16);				//�����ַ�������Ҫ16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//����Ҫ��ʾ��ôС���ַ�
		break;
		case TYPE_12:							// 6*12 �ַ�
		for(i=0;i<len;i++)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 12, pbff, colour);
			LCD_Display_6x12(Line, Column, pbff);
			string++;
			Column += 6;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		case TYPE_16:							// 8*16 �ַ�
		for(i=0;i<len;i++)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 16, pbff, colour);
			LCD_Display_8x16(Line, Column, pbff);
			string++;
			Column += 8;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		case TYPE_1532:
		for(i=0;i<len;i++)
		{
			for(addr = 0; addr<12;addr++)
			{	
				if(string[0] == specistring[addr].Index[0])
					break;
			}
			pbff = (uint8_t *)specistring[addr].Matrix;
			LCD_Display_15x32(Line, Column, pbff);
			string++;
			Column +=15;
			if(Column >= 128)
			{
				Column = 1;
//				Line += 4;
			}
		}	
		break;
		default:
		for(i=0;i<len;i++)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 16, pbff, colour);
			LCD_Display_8x16(Line, Column, pbff);
			string++;
			Column += 8;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
	}
	// free buff
	free(pbff);
}
/***************************************************************************/
//����:	void LCD_Display_Chinese(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//˵��:	LCD��ʾ�����ַ�������
//����: string ����ʾ�����ַ�������ָ�� type��ʾ�ַ����� Line ������ʾ�� Column ������ʾ�� colour �Ƿ���
//���: ��
//�༭: zlb
//ʱ��: 2015.12.16
/***************************************************************************/
void LCD_Display_Chinese(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(32);				//�����ַ�������Ҫ2*16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//�ֿ���û����ôС�ĺ���
		break;
		case TYPE_12:							// 12*12 ����
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 24, pbff, colour);
			LCD_Display_12x12(Line, Column, pbff);
			string += 2;
			i += 2;
			Column += 12;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		case TYPE_16:							// 16*16 �ַ�
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 32, pbff, colour);
			LCD_Display_16x16(Line, Column, pbff);
			string += 2;
			i += 2;
			Column += 16;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		default:
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			GB21_ReadData(addr, 32, pbff, colour);
			LCD_Display_16x16(Line, Column, pbff);
			string += 2;
			i += 2;
			Column += 16;
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
	}
	// free buff
	free(pbff);
}
/***************************************************************************/
//����:	void LCD_Display_Mixure(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//˵��:	LCD�����ʾ����,�ܹ���ʾ�������ַ�
//����: string ����ʾ�����ַ�������ָ�� type��ʾ�ַ����� Line ������ʾ�� Column ������ʾ�� colour �Ƿ���
//���: ��
//�༭: zlb
//ʱ��: 2015.12.16
/***************************************************************************/
void LCD_Display_Mixure(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(32);				//�����ַ�������Ҫ2*16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//�ֿ���û����ôС�ĺ���
		break;
		case TYPE_12:							// 12*12 ���� 6*12 �ַ�
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			if(*string < 0x80)					//ascii�ַ��뺺���������������128���ֽ磬���ڽ��ߵ�Ϊ������
			{
				GB21_ReadData(addr, 12, pbff, colour);
				LCD_Display_6x12(Line, Column, pbff);
				string++;
				i++;
				Column += 6;
			}
			else
			{
				GB21_ReadData(addr, 24, pbff, colour);
				LCD_Display_12x12(Line, Column, pbff);
				string += 2;
				i += 2;
				Column += 12;
			}
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		case TYPE_16:							// 16*16 �ַ�
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			if(*string < 0x80)
			{
				GB21_ReadData(addr, 16, pbff, colour);
				LCD_Display_8x16(Line, Column, pbff);
				string++;
				i++;
				Column += 8;
			}
			else
			{
				GB21_ReadData(addr, 32, pbff, colour);
				LCD_Display_16x16(Line, Column, pbff);
				string += 2;
				i += 2;
				Column += 16;
			}
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
		default:
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			if(*string < 0x80)
			{
				GB21_ReadData(addr, 16, pbff, colour);
				LCD_Display_8x16(Line, Column, pbff);
				string++;
				i++;
				Column += 8;
			}
			else
			{
				GB21_ReadData(addr, 32, pbff, colour);
				LCD_Display_16x16(Line, Column, pbff);
				string += 2;
				i += 2;
				Column += 16;
			}
			if(Column >= 128)
			{
				Column = 1;
				Line += 2;
			}
		}
		break;
	}
	// free buff
	free(pbff);
}
/***************************************************************************/
//����:	void LCD_Display_Line(uint8_t Line, uint8_t Column)
//˵��:	LCD��ʾֱ��,ֻ����ʼλ��,�յ�����Ļ����
//����: Line ������ʾ�� Column ������ʾ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.16
/***************************************************************************/
void LCD_Display_Line(uint8_t Line, uint8_t Column)
{
	uint8_t i;
	
	LCD_SetCursorPos(Line,Column);
	for(i=0;i<128;i++)
	{
		//��0x20����ʾҪ��ʾֱ�ߵ�λ��,��ɨ���Ǵӵ͵���(����ҵ���),���ϵ���	
		//�����Ǵӵ�λ����λ��ʾ,��֤�����ĸ�������������ʾ,��Ҫ������λ����,����λ����
		Display_Buff[Line-1][i] &= 0x0f;		
		Display_Buff[Line-1][i] |= 0x20;
		LCD_SendByte(DATA_TYPE, Display_Buff[1][i]);		
	}
}


