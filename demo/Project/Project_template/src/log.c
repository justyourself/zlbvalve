/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : log.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-21
 * Version    : V1.0
 * Change     :
 * Description: log.c log图案
 */
/*************************************************************************/
#include "stm8s.h"
#include "menu.h"

// log文件
const uint8_t log[] = 
{
	/*--  调入了一幅图像：C:\Users\Administrator\Desktop\D+R商标（A）_副本.bmp  --*/
	/*--  取模方式:纵向取模,字节倒序， --*/
	/*--  宽度x高度=128x64  --*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x80,0xF0,0x38,0x0C,0x06,0xFE,0xFD,0x8D,0x8D,0x8D,0x8D,0x8D,0x8D,0xFB,
	0xFE,0x06,0x0C,0x38,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,
	0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0x60,0x70,0x70,0x70,0x70,0x30,0x30,0x38,0x38,
	0x38,0x38,0x38,0x98,0x98,0x98,0x98,0x98,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,
	0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x98,0x98,0x98,0x98,0x98,0x38,0x38,0x38,0x38,0x38,
	0x30,0x30,0x30,0x70,0x70,0x70,0x60,0x60,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0x80,0x80,
	0x80,0x00,0x07,0x1F,0x38,0x60,0xC0,0xFF,0xFF,0x81,0x01,0x01,0x03,0x07,0x9F,0xBD,
	0xF0,0xE0,0x60,0x38,0x1F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,
	0xC0,0xE0,0x70,0x70,0x38,0x38,0x9C,0x9C,0xCE,0xCE,0xE6,0xE7,0x63,0x73,0x73,0x79,
	0x79,0x79,0x79,0x7C,0x7C,0x7C,0x7C,0x7E,0x7E,0x7E,0x7E,0x7E,0x7F,0x7F,0x7F,0x7F,
	0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,
	0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,
	0x7F,0x7F,0x7F,0x7E,0x7E,0x7E,0x7E,0xFE,0xFC,0xFC,0xFC,0xFC,0xF9,0xF9,0xF9,0xF3,
	0xF3,0xF3,0xE7,0xE7,0xCE,0xCE,0x8C,0x9C,0x19,0x39,0x71,0x73,0xE3,0xC1,0xC1,0x81,
	0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0x78,0x3C,0x0E,0xC7,0xE3,0xF1,
	0xF9,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x0F,0x1F,0xFF,0xFF,0x80,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF9,0xF1,0xE3,
	0xC7,0x8E,0x1C,0x78,0xF0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0x01,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x3C,0xFF,0xFF,
	0x3C,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0xEF,0xEF,0xEF,0xEF,
	0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x18,0x18,0x18,0x3C,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x3E,0x78,0xE1,0xC7,0x8F,0x1F,0x3F,
	0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF8,0xFF,0x0F,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xFF,0x7F,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,
	0x8F,0xC7,0xE1,0xF0,0x7C,0x1F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x0E,
	0x1C,0x1C,0x39,0x31,0x73,0xE7,0xE7,0xCF,0xCF,0x9F,0x9F,0x9F,0x3B,0x3B,0x7B,0x7B,
	0x78,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xFB,0xFB,0xFB,0xFB,0xFB,
	0xFB,0xF8,0xF8,0xF8,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFB,0xFB,0xFB,0xF8,
	0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xFB,0xFB,0xFB,0xFF,0xFF,
	0xFF,0xFF,0xFC,0xFC,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF9,0xFD,0xFC,0x7E,0x7F,0x7F,
	0x3F,0x3F,0x3F,0x9F,0x9F,0xCF,0xCF,0xE7,0xE7,0x73,0x73,0x39,0x1C,0x1C,0x0E,0x07,
	0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x06,0x0E,
	0x0E,0x0E,0x0C,0x1C,0x1C,0x19,0x19,0x39,0x39,0x39,0x33,0x33,0x73,0x73,0x73,0x73,
	0x67,0x67,0x67,0x67,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,
	0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0x67,0x67,0x67,0x67,0x73,0x73,
	0x73,0x73,0x33,0x33,0x39,0x39,0x39,0x19,0x19,0x1C,0x1C,0x0C,0x0C,0x0E,0x0E,0x06,
	0x07,0x07,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
//字符串文件
const type_1332 specistring[] = 
{
"1",
/*--  文字:  1  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"2",
/*--  文字:  2  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x80,0xC0,0xC0,0x60,0x20,0x20,0x20,0x20,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,
0x07,0x07,0x07,0x06,0x00,0x00,0x80,0xE0,0xF8,0x7F,0x3F,0x0F,0x00,0x00,0x00,0xC0,
0xF0,0xB8,0x9C,0x8E,0x87,0x83,0x81,0x80,0xC0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"3",
/*--  文字:  3  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x80,0xC0,0xE0,0x60,0x20,0x20,0x20,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,
0x03,0x03,0x03,0x03,0x40,0x60,0x60,0x70,0xFF,0x9F,0x8F,0x02,0x00,0x00,0x00,0x70,
0xF8,0xF8,0xF0,0x80,0x00,0x00,0x80,0xE1,0xFF,0x7F,0x3F,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
"4",
/*--  文字:  4  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0xC0,0xE0,0x78,0x1E,0x0F,0x03,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x06,0x07,
0x07,0x05,0x04,0x84,0x84,0x84,0xFF,0xFF,0xFF,0x84,0x84,0x84,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"5",
/*--  文字:  5  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0xE0,0xE0,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x00,0x00,0x00,
0x00,0x7F,0x7F,0x70,0x30,0x10,0x10,0x30,0x70,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x78,
0xF8,0xF8,0x98,0x80,0x00,0x00,0x80,0xE0,0xFF,0x7F,0x3F,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
"6",
/*--  文字:  6  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0x00,0xC0,0xC0,0x60,0x20,0x20,0x20,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,
0xFE,0xFF,0xFF,0xE3,0x70,0x30,0x10,0x30,0x71,0xF1,0xE1,0xC0,0x00,0x00,0x00,0x1F,
0x7F,0xFF,0xF0,0xC0,0x80,0x00,0x80,0xC0,0xFF,0x7F,0x3F,0x0F,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
"7",
/*--  文字:  7  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x80,0xE0,0xE0,0x60,0x60,0x60,0x60,0x60,0x60,0xE0,0xE0,0x60,0x00,0x00,0x00,
0x03,0x03,0x01,0x00,0x00,0xC0,0xF0,0xFC,0x3F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0xFE,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"8",
/*--  文字:  8  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x80,0xC0,0xE0,0x60,0x20,0x20,0x20,0x20,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,
0x0F,0x9F,0xBF,0xF8,0x70,0x60,0xE0,0xE0,0xF0,0xBF,0x9F,0x0F,0x00,0x00,0x18,0x7F,
0xFF,0xF7,0x80,0x80,0x00,0x00,0x81,0xC3,0xFF,0x7F,0x3E,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
"9",
/*--  文字:  9  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x80,0xC0,0xE0,0xE0,0x20,0x20,0x20,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,0x1C,
0x7F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x80,0xE0,0xFF,0xFF,0xFF,0x70,0x00,0x00,0x40,
0xE0,0xE1,0xE1,0x81,0x01,0x81,0xE1,0xFC,0x7F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"0",
/*--  文字:  0  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0x80,0xC0,0xE0,0xE0,0x20,0x20,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,
0xFE,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x1F,
0x3F,0xFF,0xF8,0xC0,0x80,0x80,0xC0,0xF0,0xFF,0x7F,0x1F,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
".",
/*--  文字:  .  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0xC0,
0xE0,0xE0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"%",
/*--  文字:  %  --*/
/*--  @SimSun-ExtB22;  此字体下对应的点阵为：宽x高=15x29   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=15x32  --*/
0xC0,0xE0,0xE0,0x20,0xE0,0xE0,0x80,0x00,0x00,0xC0,0xE0,0x60,0x00,0x00,0x00,0x3F,
0x7F,0x78,0x40,0x7F,0xFF,0xFF,0xFC,0xBF,0xC7,0xC1,0xC0,0x80,0x00,0x00,0x00,0x00,
0xC0,0xF0,0x7C,0x1F,0x03,0x7F,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x01,
0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,
};


