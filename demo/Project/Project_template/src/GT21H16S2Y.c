/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : GT21H16S2Y.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: GT21H16S2Y字库芯片 STM8驱动文件
 */
/*************************************************************************/
#include "stm8s_spi.h"
#include "GT21H16S2Y.h"


/***************************************************************************/
//函数:	void GT21H16S2Y_GPIO_Init(void)
//说明:	GT21H16S2Y GPIO初始化函数
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void GT21H16S2Y_GPIO_Init(void)
{
	// Enable SPI clock
//	CLK_PeripheralClockConfig(GT21_SPI_CLK, ENABLE);
	// Configure SPI pins: SCK MOSI MISO Pull Up
//	GPIO_ExternalPullUpConfig(GT21_SPI_GPIO_PORT, (GPIO_Pin_TypeDef)(GT21_SPI_SCK_PIN | GT21_SPI_MOSI_PIN | \
//                            GT21_SPI_MISO_PIN), ENABLE);
	
	// Configure GB21 ChipSelect pin (CS) in Output push-pull mode 
	GPIO_Init(GT21_SPI_CS_PORT, GT21_SPI_CS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
        // Set default CS as high level
        GT21_SPI_CS_HIGH();
}
/***************************************************************************/
//函数:	void GT21H16S2Y_SPI_Init(void)
//说明:	GT21H16S2Y SPI初始化函数
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void GT21H16S2Y_SPI_Init(void)
{
	// Enable SPI clock
	CLK_PeripheralClockConfig(GT21_SPI_CLK, ENABLE);
	// Initialize SPI
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, 
		   SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, 
		   SPI_NSS_SOFT, 0x07);
	// Enable SPI	   
	SPI_Cmd(ENABLE);
}
/***************************************************************************/
//函数:	uint8_t GB21_SendByte(uint8_t byte)
//说明:	GB21发送接收函数
//输入: byte 发送字节数据
//输出: 接收字节数据
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
uint8_t GB21_SendByte(uint8_t byte)
{
  // Loop while DR register in not emplty
  while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);

  // Send byte through the SPI1 peripheral
  SPI_SendData(byte);

  // Wait to receive a byte
  while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);

  // Return the byte read from the SPI bus
  return SPI_ReceiveData();	 
}
/***************************************************************************/
//函数:	uint8_t GB21_SimuReadByte(void)
//说明:	GB21模拟SPI接收函数
//输入: 无
//输出: 接收字节数据
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
uint8_t GB21_SimuReadByte(void)
{
	uint8_t i;
	uint8_t data;
	
	// Set SCLK High 
	GT21_SCLK_HIGH();
	for(i=0;i<8;i++)
	{
		//上升沿获取数据
		GT21_SCLK_LOW();
		data <<= 1;
		
		if(GB21_MISO())
			data |= 0x01;
		else
			data &= 0xfe;
		GT21_SCLK_HIGH();
	}
	return data;	
}
/***************************************************************************/
//函数:	void GB21_SimuSendByte(uint8_t DataToSend)
//说明:	GB21模拟SPI发送函数
//输入: DataToSend 发送字节数据
//输出: 无
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
void GB21_SimuSendByte(uint8_t DataToSend)
{
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		// 上升沿锁存发送数据
		GT21_SCLK_LOW();
		if(DataToSend & 0x80)
			GT21_MOSI_HIGH();
		else
			GT21_MOSI_LOW();
		GT21_SCLK_HIGH();
		
		DataToSend <<= 1;
	}
}
/***************************************************************************/
//函数:	void GB21_ReadData(uint32_t addr,uint8_t length,uint8_t *pbuf)
//说明:	GB21数据读取函数
//输入: addr 数据存放地址;length 数据读取长度;pbuf 数据存放缓存指针 colour 是否反显
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void GB21_ReadData(uint32_t addr,uint8_t length,uint8_t *pbuf, uint8_t colour)
{
  uint8_t i;
  // Enable CS
  GT21_SPI_CS_LOW();
  
  // Send byte high nibble 0x03 normal read speed 0x0B higher speed
  GB21_SimuSendByte(0x0B);					
  GB21_SimuSendByte((addr >> 16)&(uint8_t)0xFF);
  GB21_SimuSendByte((addr >> 8)&(uint8_t)0xFF);
  GB21_SimuSendByte(addr &(uint8_t)0xFF);
  // Higher speed need send a dummy byte
  GB21_SimuSendByte(0x00);

  // Receive data
  for(i=0;i<length;i++)
  {
    //pbuf[i] = GB21_SendByte(0xff) ^ colour;
	pbuf[i] = GB21_SimuReadByte() ^ colour;
  }
  // Disable CS
  GT21_SPI_CS_HIGH();  
}
/***************************************************************************/
//函数:	uint32_t GB2312_Addr(uint8_t *gb21str,uint8_t type)
//说明:	GB21地址计算函数
//输入: gb21str 获取地址数据的字符串指针;type 要获取的字符显示类型
//输出: 32位字库地址
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
uint32_t GB2312_Addr(uint8_t *gb21str,uint8_t type)
{
	uint32_t temp = 0;
	uint8_t c1,c2;
	
	// ascii 半角字符
	if(gb21str[0] < 0x80)
	{
		if(gb21str[0] < ' ')
			gb21str[0] = ' ';
		temp = gb21str[0] - ' ';
		if(type == TYPE_8)
			temp = temp*8 + ASC0808D2HZ_ADDR;
		else if(type == TYPE_12)
			temp = temp*12 + ASC0812M2ZF_ADDR;
		else if(type == TYPE_16)
			temp = temp*16 + GBEX0816ZF_ADDR;		
	}
	// 符号区
	else
	{
		c1 = gb21str[0];
		c2 = gb21str[1];
		if(c1>=0xA1 && c1 <= 0xAB && c2>=0xA1)
		{
			if( type == TYPE_12 )
			{
				if( c1>=0xA1 && c1 <= 0xA3 && c2>=0xA1 )
					temp = (c1 - 0xA1) * 94 + (c2 - 0xA1);
				if( c1 == 0xA9 && c2>=0xA1 )
					temp = 282 + ( c2 - 0xA1 );
				return( temp*24 + ZF1112B2ZF_ADDR);
			}
			else
			{
				if( c1>=0xA1 && c1 <= 0xA3 && c2>=0xA1 )
					temp = (c1 - 0xA1) * 94 + (c2 - 0xA1);
				if( c1 == 0xA9 && c2>=0xA1 )
					temp = 282 + ( c2 - 0xA1 );
				return(temp*32 + CUTS1516ZF_ADDR);
			}
		}
		//GBK 双字节2区6768
		else if(c1>=0xB0 && c1 <= 0xF7 && c2>=0xA1)
		{
			temp= (c1 - 0xB0) * 94 + (c2 - 0xA1);
			if( type == TYPE_12 )
			temp = temp*24 + HZ1112B2HZ_ADDR;
			else if( type == TYPE_16 )
			temp = temp*32 + JFLS1516HZ_ADDR;
		}
	}
	return temp;
}
