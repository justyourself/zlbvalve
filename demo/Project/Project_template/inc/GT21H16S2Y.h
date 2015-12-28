/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : GT21H16S2Y.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: GT21H16S2Y字库芯片 STM8驱动头文件
 */
/*************************************************************************/
#ifndef __GT21H16S2Y_H
#define __GT21H16S2Y_H
#include "stm8s_gpio.h"

// Address macro
#define ASC0808D2HZ_ADDR	(0x66C0) 		//7*8 ascii code
#define ASC0812M2ZF_ADDR	(0x66D40) 		//6*12 ascii code
#define GBEX0816ZF_ADDR 	(0x3B7C0) 		//8*16 ascii code
#define ZF1112B2ZF_ADDR		(0x3CF80) 		//12*12 12 点字符
#define HZ1112B2HZ_ADDR 	(0x3CF80+376*24)        //12*12 12 点汉字
#define CUTS1516ZF_ADDR 	(0x00)			//16*16 16 点字符
#define JFLS1516HZ_ADDR		(0x69C0) 		//16*16 16 点汉字

// 要显示的汉字的类型
#define TYPE_8 				0 				//8 点字符
#define TYPE_12 			1 				//12 点汉字字符
#define TYPE_16 			2 				//16 点汉字字符

// GPIO Set
#define GT21_SPI_CLK         CLK_PERIPHERAL_SPI
#define GT21_SPI_CS_PORT     GPIOG
#define GT21_SPI_CS_PIN      GPIO_PIN_2
#define GT21_SPI_SCK_PIN     GPIO_PIN_5
#define GT21_SPI_MOSI_PIN    GPIO_PIN_6
#define GT21_SPI_MISO_PIN    GPIO_PIN_7
#define GT21_SPI_GPIO_PORT   GPIOC


// Set CS HIGH or LOW
#define GT21_SPI_CS_HIGH()  GPIO_WriteHigh(GT21_SPI_CS_PORT, GT21_SPI_CS_PIN)
#define GT21_SPI_CS_LOW()   GPIO_WriteLow(GT21_SPI_CS_PORT, GT21_SPI_CS_PIN)
// Simulation send data SCLK
#define GT21_SCLK_LOW()	  	GPIO_WriteLow(GT21_SPI_GPIO_PORT, GT21_SPI_SCK_PIN)
#define GT21_SCLK_HIGH()	GPIO_WriteHigh(GT21_SPI_GPIO_PORT, GT21_SPI_SCK_PIN)
// MOSI
#define GT21_MOSI_LOW()	  	GPIO_WriteLow(GT21_SPI_GPIO_PORT, GT21_SPI_MOSI_PIN)
#define GT21_MOSI_HIGH()	GPIO_WriteHigh(GT21_SPI_GPIO_PORT, GT21_SPI_MOSI_PIN)
// MISO
#define GB21_MISO()		  	GPIO_ReadInputPin(GT21_SPI_GPIO_PORT, GT21_SPI_MISO_PIN)


// 函数声明
void GT21H16S2Y_GPIO_Init(void);
void GT21H16S2Y_SPI_Init(void);
uint8_t GB21_SendByte(uint8_t byte);
uint8_t GB21_SimuReadByte(void);
void GB21_SimuSendByte(uint8_t DataToSend);
void GB21_ReadData(uint32_t addr,uint8_t length,uint8_t *pbuf, uint8_t colour);
uint32_t GB2312_Addr(uint8_t *gb21str,uint8_t type);


#endif //__GT21H16S2Y_H
