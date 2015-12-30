/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : menu.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-18
 * Version    : V1.0
 * Change     :
 * Description: menu.c 菜单结构函数
 */
/*************************************************************************/
#include "string.h"
#include "stm8s.h"
#include "stm8s_clk.h"
#include "key.h"
#include "menu.h"
#include "GT21H16S2Y.h"
#include "JLX12864G.h"

/******************************变量声明***********************************/
// LOG 图标
extern const uint8_t log[];
/******************************函数定义***********************************/
/***************************************************************************/
//函数:	void Init_Clock(void)
//说明:	初始化时钟为内部时钟
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Init_Clock(void)
{
	/* Select fCPU = 16MHz */
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	/* For test purpose output Fcpu on MCO pin */
	CLK_CCOConfig(CLK_OUTPUT_CPU);
}
/***************************************************************************/
//函数:	void main(void)
//说明:	主函数
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void main(void)
{
	uint8_t key;
	// 初始化时钟
	Init_Clock();
	// 初始化LCD
	JLX_LCD_Init();
	// 初始化字库芯片
	GT21H16S2Y_GPIO_Init();
	LCD_Clear();
	// 初始化GPIO
	Key_Init();
        // 初始化输入输出
	InOut_Init();
	// 初始化LED
	LED_Init();
	// 初始化ADC
	ADC2_Shift_Init(ADC2_CHANNEL_7, ADC2_SCHMITTTRIG_CHANNEL7);
	// 初始化定时器4 1ms定时器 ADC采集专用
	TIM4_Init();
	//使能中断
	enableInterrupts();

	//开机显示LOGO
	LCD_Display_128x64(log);
	//延时
	Delay(10000);
	//显示默认界面
	manyou = TopMenu;
	Display(manyou);
	while (1)
	{
		key = Key_Read();
		// 无组合键功能
		switch(key)
		{
			case UP:
				FatherIndex[layer]++;
				if(FatherIndex[layer] > (manyou->MenuCount -1))
					FatherIndex[layer] = 0;
				Display(manyou + FatherIndex[layer]);
				break;
			case DOWN:
				if(FatherIndex[layer] == 0)
					FatherIndex[layer] = (manyou->MenuCount -1);
				else
					FatherIndex[layer]--;
				Display(manyou + FatherIndex[layer]);
				break;
			case SET:
				if((manyou + FatherIndex[layer])->Childrenms != NULL)
				{
					manyou = (manyou+FatherIndex[layer])->Childrenms;
					layer ++;
					FatherIndex[layer] = 0;
					Display(manyou + FatherIndex[layer]);
				}
				else
					Run(manyou + FatherIndex[layer]);
				break;
			case ESC:
				if((manyou + FatherIndex[layer])->Parentms != NULL)
				{
					manyou = (manyou+FatherIndex[layer])->Parentms;
					FatherIndex[layer] = 0;
					layer --;
					Display(manyou + FatherIndex[layer]);
				}
				else
				{
					manyou = TopMenu;		
					Display(manyou);
				}
					
				break;
			default:
				//刷新页面
				Display(manyou);
				break;
		}
	}
}
		
	/*
	key1 = key2 = key3 = 0;
	key1 = GPIO_ReadInputPin(GPIOC,UV_PIN);
	key2 = GPIO_ReadInputPin(GPIOC,VW_PIN);
	key3 = GPIO_ReadInputPin(GPIOC,WU_PIN);
	key = GPIO_ReadInputPin(GPIOE,REMOTE);
	adcvalue = ADC2_GetConversionValue();
	        if(adcvalue > 0x150 && adcvalue < 0x160)
	        {
	          GPIO_WriteLow(OUT_PORT,OPEN);
	          Delay(100000);
	          adcvalue = ADC2_GetConversionValue();
	          GPIO_WriteHigh(OUT_PORT,OPEN);
	          Delay(100000);
	          adcvalue = ADC2_GetConversionValue();
	          if(adcvalue > 0x160)
	          {
	            GPIO_WriteLow(OUT_PORT,OPEN);
	          }
	          else
	          {
	            key1++;
	          }
	         
	          
	        }
	        else if(adcvalue > 0x160)
	        {
	           GPIO_WriteLow(OUT_PORT,OPEN);
	        }
	        else if(adcvalue < 0x10)
	        {
	          GPIO_WriteLow(OUT_PORT,CLOSE);
	        }
			*/
#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)
{ 
	while (1)
	{
	}
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
