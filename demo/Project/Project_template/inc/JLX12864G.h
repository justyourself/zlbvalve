/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : JLX12864G-102-stm8.h
 * Design     : zlb
 * Email      : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: JLX12864G-102 STM8驱动头文件
 */
/*************************************************************************/
#ifndef __JLX12864G_H
#define __JLX12864G_H
#include "stm8s_gpio.h"
#include "stm8s_spi.h"

// macro define
#define DISPLAYBUFF	      1		 //定义显示缓存
// Common define
#define NORMAL                0x00	//普通显示
#define REVERSE               0xFF	//反色显示

// GPIO SET
#define LCD_SPI               SPI 
#define LCD_NCS_GPIO_PORT     GPIOE
#define LCD_NCS_PIN           GPIO_PIN_5
#define LCD_SPI_CLK           CLK_PERIPHERAL_SPI
#define LCD_BACKLIGHT_PORT    GPIOE
#define LCD_BACKLIGHT_PIN     GPIO_PIN_3
#define LCD_SPI_SCK_PIN       GPIO_PIN_5
#define LCD_SPI_MOSI_PIN      GPIO_PIN_6
#define LCD_SPI_MISO_PIN      GPIO_PIN_7
#define LCD_SPI_GPIO_PORT     GPIOC
#define LCD_SPI_RS_PORT       GPIOG
#define LCD_SPI_RS_PIN        GPIO_PIN_1

// LCD Commands
#define COMMAND_TYPE         ((uint8_t)0xF8)
#define DATA_TYPE            ((uint8_t)0xFA)
#define SOFT_REST	     ((uint8_t)0xE2)
#define SET_UP1		     ((uint8_t)0x2C)
#define SET_UP2		     ((uint8_t)0x2E)
#define SET_UP3	             ((uint8_t)0x2F)
#define SET_THICK_CONTRAST   ((uint8_t)0x24)
#define SET_THIN_CONTRAST    ((uint8_t)0x81)
#define SET_LINE             ((uint8_t)0xC8)  //set line scan sequence ,form up to down
#define SET_ROW              ((uint8_t)0xA0)  //set row scan sequence ,form left to right
#define START_LINE           ((uint8_t)0x60)  //set start line is first line
#define OPEN_DISPLAY         ((uint8_t)0xAF)  //open dispaly
#define CLOSE_DISPLAY 	     ((uint8_t)0xAE)  //close dispaly			
#define REVERSE_DISPLAY	     ((uint8_t)0xA7)  //反色显示
#define NORMAL_DISPLAY	     ((uint8_t)0xA6)  //普通显示

// Set CS macro
#define LCD_NCS_LOW()     GPIO_WriteLow(LCD_NCS_GPIO_PORT, LCD_NCS_PIN)
#define LCD_NCS_HIGH()    GPIO_WriteHigh(LCD_NCS_GPIO_PORT, LCD_NCS_PIN)
// Set RS macro
#define LCD_RS_LOW()      GPIO_WriteLow(LCD_SPI_RS_PORT, LCD_SPI_RS_PIN)
#define LCD_RS_HIGH()     GPIO_WriteHigh(LCD_SPI_RS_PORT, LCD_SPI_RS_PIN)
// Simulation send data
#define LCD_SCLK_LOW()	  GPIO_WriteLow(LCD_SPI_GPIO_PORT, LCD_SPI_SCK_PIN)
#define LCD_SCLK_HIGH()	  GPIO_WriteHigh(LCD_SPI_GPIO_PORT, LCD_SPI_SCK_PIN)
// MOSI
#define LCD_MOSI_LOW()	  GPIO_WriteLow(LCD_SPI_GPIO_PORT, LCD_SPI_MOSI_PIN)
#define LCD_MOSI_HIGH()	  GPIO_WriteHigh(LCD_SPI_GPIO_PORT, LCD_SPI_MOSI_PIN)

// 函数声明
void LCD_Init(void);
void LCD_Clear(void);
void JLX_LCD_Init(void);
void LCD_Display_128x64(uint8_t *text);
void LCD_BacklightCmd(FunctionalState NewState);
void LCD_SendByte(uint8_t DataType, uint8_t DataToSend);
void LCD_SetCursorPos(uint8_t Line, uint8_t Column);
void LCD_Display_6x12(uint8_t Line, uint8_t Column, uint8_t *text);
void LCD_Display_12x12(uint8_t Line, uint8_t Column, uint8_t *text);
void LCD_Display_8x16(uint8_t Line, uint8_t Column, uint8_t *text);
void LCD_Display_16x16(uint8_t Line, uint8_t Column, uint8_t *text);
void LCD_Display_String(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour);
void LCD_Display_Chinese(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour);
void LCD_Display_Mixure(uint8_t *string, uint8_t type, uint8_t Line, uint8_t Column, uint8_t colour);
void LCD_Display_Line(uint8_t Line, uint8_t Column);
void LCD_CleanL2L(uint8_t begin, uint8_t end);
// 变量声明
extern uint8_t Display_Buff[8][128];







#endif //__JLX12864G_H
