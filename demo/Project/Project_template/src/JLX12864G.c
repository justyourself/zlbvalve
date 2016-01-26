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
 * Description: JLX12864G-102 STM8驱动
 */
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "JLX12864G.h"
#include "GT21H16S2Y.h"

// 函数声明
static void delay(__IO uint32_t nCount);
static void LCD_SPISendByte(uint8_t DataToSend);
static void LCD_SimuSendByte(uint8_t DataToSend);

// 数据缓存定义
#ifdef DISPLAYBUFF
uint8_t Display_Buff[8][128] = {0};		//LCD显示缓存
#endif
/***************************************************************************/
//函数:	static void delay(__IO uint32_t nCount)
//说明:	延时函数(内部使用函数,延时nCount个时钟节拍)
//输入: nCount 延时节拍数
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void JLX_LCD_Init(void)
//说明:	LCD初始化函数，初始化SPI GPIO 并调用LCD_Init()初始化命令
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Init(void)
//说明:	LCD显示初始化函数，初始化显示界面与对比度
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LCD_Init(void)
{
	//JLX12864G-102 初始化命令
	LCD_SendByte(COMMAND_TYPE,SOFT_REST);           //soft reset
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_UP1);				//up power one 
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_UP2);				//up power two 
	delay(0x4000);  
	LCD_SendByte(COMMAND_TYPE,SET_UP3);				//up power three
	delay(0x4000);
	LCD_SendByte(COMMAND_TYPE,SET_THICK_CONTRAST);	//粗调对比度，可设置(0x20~0x27)
	LCD_SendByte(COMMAND_TYPE,SET_THIN_CONTRAST);	//微调对比度
	LCD_SendByte(COMMAND_TYPE,0x1A);				//微调对比度值，可设置范围(0x00~0x3f)
	LCD_SendByte(COMMAND_TYPE,0XA2);				//1/9偏压比
	LCD_SendByte(COMMAND_TYPE,SET_LINE);			//行扫描顺序：从上到下
	LCD_SendByte(COMMAND_TYPE,SET_ROW);				//列扫描顺序：从左到右
	LCD_SendByte(COMMAND_TYPE,START_LINE);			//起始行，第一行开始
	LCD_SendByte(COMMAND_TYPE,OPEN_DISPLAY);		//开显示 打开显示才能正常工作,在这里碰到过问题,一直没有打开造成不能显示
}
/***************************************************************************/
//函数:	void LCD_SendByte(uint8_t DataType, uint8_t DataToSend)
//说明:	LCD数据发送函数
//输入: DataType 发送类型 数据或命令;DataToSend 发送数据
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LCD_SendByte(uint8_t DataType, uint8_t DataToSend)
{
	// Enable access to LCD 
	LCD_NCS_LOW();

	// Set RS Pin 
	if(DataType == COMMAND_TYPE)
	{
		//发送类型为命令
		LCD_RS_LOW();
	}
	else
	{	//发送类型为数据
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
//函数:	void LCD_BacklightCmd(FunctionalState NewState)
//说明:	背光灯是否使能
//输入: NewState 背光灯使能状态
//输出: 无
//编辑: zlb
//时间: 2015.12.16
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
//函数:	static void LCD_SPISendByte(uint8_t DataToSend)
//说明:	LCD SPI数据发送函数
//输入: DataToSend 发送数据
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	static void LCD_SimuSendByte(uint8_t DataToSend)
//说明:	LCD 模拟SPI数据发送函数
//输入: DataToSend 发送数据
//输出: 无
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
static void LCD_SimuSendByte(uint8_t DataToSend)
{
	uint8_t i;
	
	//模拟SPI时序发送数据
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
//函数:	void LCD_Clear(void)
//说明:	LCD清屏函数 清除屏幕显示
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LCD_Clear(void)
{
	uint8_t i,j;

	for(i=0;i<8;i++)
	{
		// 定位显示位置
		LCD_SetCursorPos(1+i,1);
		for(j=0;j<128;j++)
		{
			// 清除显示数据
			LCD_SendByte(DATA_TYPE,0x00);
			#ifdef DISPLAYBUFF
			Display_Buff[i][j] = 0x00;
			#endif
		}
	}
}
/***************************************************************************/
//函数:	void LCD_CleanL2L(uint8_t begin, uint8_t end)
//说明:	LCD清除指定页与页之间的数据
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LCD_CleanL2L(uint8_t begin, uint8_t end)
{
	uint8_t i,j;

	if(begin > end)
		return;
	
	for(i=begin;i<=end;i++)
	{
		// 定位显示位置
		LCD_SetCursorPos(i,1);
		for(j=0;j<128;j++)
		{
			// 清除显示数据
			LCD_SendByte(DATA_TYPE,0x00);
			#ifdef DISPLAYBUFF
			Display_Buff[i-1][j] = 0x00;
			#endif
		}
	}
}
/***************************************************************************/
//函数:	void LCD_SetCursorPos(uint8_t Line, uint8_t Column)
//说明:	LCD设置显示坐标函数
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列 
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LCD_SetCursorPos(uint8_t Line, uint8_t Column)
{
	// 页码从0开始,因此第1页为首页
	Line = Line - 1;
	// 设置页地址
	LCD_SendByte(COMMAND_TYPE,0xb0+Line);
	// 设置列地址高4位
	LCD_SendByte(COMMAND_TYPE,((Column>>4)&0x0f)+0x10);
	// 设置列地址低4位
	LCD_SendByte(COMMAND_TYPE,Column&0x0f);	
}
/***************************************************************************/
//函数:	void LCD_Display_6x12(uint8_t Line, uint8_t Column, uint8_t *text)
//说明:	LCD显示6*12的字符
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列; text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_12x12(uint8_t Line, uint8_t Column, uint8_t *text)
//说明:	LCD显示12*12的汉字
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列; text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_8x16(uint8_t Line, uint8_t Column, uint8_t *text)
//说明:	LCD显示8*16的字符
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列; text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_16x16(uint8_t Line, uint8_t Column, uint8_t *text)
//说明:	LCD显示16*16的汉字
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列; text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_15x32(uint8_t Line, uint8_t Column, uint8_t *text)
//说明:	LCD显示16*16的汉字
//输入: Line 设置行(页)定位,64行定义为8页,Line代表页码; Column 设置列定位,128列; text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_128x64(uint8_t *text)
//说明:	LCD显示128*64图片
//输入: text 待显示数据指针
//输出: 无
//编辑: zlb
//时间: 2015.12.13
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
//函数:	void LCD_Display_String(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//说明:	LCD显示字符串函数
//输入: string 待显示字符串数据指针 type显示字符类型 Line 设置显示行 Column 设置显示列 colour 是否反显
//输出: 无
//编辑: zlb
//时间: 2015.12.16
/***************************************************************************/
void LCD_Display_String(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(16);				//最大的字符类型需要16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//不需要显示这么小的字符
		break;
		case TYPE_12:							// 6*12 字符
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
		case TYPE_16:							// 8*16 字符
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
//函数:	void LCD_Display_Chinese(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//说明:	LCD显示汉字字符串函数
//输入: string 待显示汉字字符串数据指针 type显示字符类型 Line 设置显示行 Column 设置显示列 colour 是否反显
//输出: 无
//编辑: zlb
//时间: 2015.12.16
/***************************************************************************/
void LCD_Display_Chinese(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(32);				//最大的字符类型需要2*16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//字库中没有这么小的汉字
		break;
		case TYPE_12:							// 12*12 汉字
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
		case TYPE_16:							// 16*16 字符
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
//函数:	void LCD_Display_Mixure(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
//说明:	LCD混合显示函数,能够显示汉字与字符
//输入: string 待显示汉字字符串数据指针 type显示字符类型 Line 设置显示行 Column 设置显示列 colour 是否反显
//输出: 无
//编辑: zlb
//时间: 2015.12.16
/***************************************************************************/
void LCD_Display_Mixure(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour)
{
	uint8_t len = strlen((char *)string);
	uint32_t addr = 0;
	uint8_t *pbff = NULL;
	uint8_t i;
	
	// Get space for display buff
	pbff = (uint8_t *)malloc(32);				//最大的字符类型需要2*16byte
	if(pbff == NULL)
		return ;

	// Display	
	switch(type)
	{
		case TYPE_8:							//字库中没有这么小的汉字
		break;
		case TYPE_12:							// 12*12 汉字 6*12 字符
		for(i=0;i<len;)
		{
			addr = GB2312_Addr(string, type);
			if(*string < 0x80)					//ascii字符与汉字内码的区别在于128做分界，大于界线的为汉字码
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
		case TYPE_16:							// 16*16 字符
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
//函数:	void LCD_Display_Line(uint8_t Line, uint8_t Column)
//说明:	LCD显示直线,只有起始位置,终点是屏幕结束
//输入: Line 设置显示行 Column 设置显示列
//输出: 无
//编辑: zlb
//时间: 2015.12.16
/***************************************************************************/
void LCD_Display_Line(uint8_t Line, uint8_t Column)
{
	uint8_t i;
	
	LCD_SetCursorPos(Line,Column);
	for(i=0;i<128;i++)
	{
		//与0x20相或表示要显示直线的位置,列扫描是从低到高(或从右到左),从上到下	
		//由于是从低位到高位显示,保证上面四个点阵能正常显示,需要将低四位保护,高四位清零
		Display_Buff[Line-1][i] &= 0x0f;		
		Display_Buff[Line-1][i] |= 0x20;
		LCD_SendByte(DATA_TYPE, Display_Buff[1][i]);		
	}
}


