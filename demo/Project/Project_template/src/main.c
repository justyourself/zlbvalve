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
#include "flash.h"
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
	// 初始化输入输出
	InOut_Init();
	// 初始化LCD
	JLX_LCD_Init();
	// 初始化字库芯片
	GT21H16S2Y_GPIO_Init();
	LCD_Clear();
	// 初始化菜单参数
    Param_Init();
	// 初始化GPIO
	Key_Init();
	// 初始化LED
	LED_Init();
	// 初始化ADC
	ADC2_Shift_Init(ADC2_CHANNEL_4, ADC2_SCHMITTTRIG_CHANNEL7);
	// 初始化定时器4 1ms定时器 ADC采集专用
	TIM4_Init();
	//使能中断
	enableInterrupts();

	//开机显示LOGO
	LCD_Display_128x64((uint8_t *)log);
	//设置菜单
	Init_Menu();
	//延时
	Delay(50000);
    //清除界面log
    LCD_Clear();
	//显示默认界面
	manyou = TopMenu;
	Display(manyou);
	while (1)
	{
		//判断是否存在故障与故障提示
		
		key = Key_Read();
		// 页面是否需要按键值
		if(dofunflag == ENABLE)
		{
			key = Analysis_key(key);
		}
		// 无组合键功能
		switch(key)
		{
			case DOWN:
				FatherIndex[layer]++;
				if(FatherIndex[layer] > (manyou->MenuCount -1))
					FatherIndex[layer] = 0;
				Display(manyou + FatherIndex[layer]);
				break;
			case UP:
				if(FatherIndex[layer] == 0)
					FatherIndex[layer] = (manyou->MenuCount -1);
				else
					FatherIndex[layer]--;
				Display(manyou + FatherIndex[layer]);
				break;
			case SET:
				//远方状态不允许操作菜单//调试屏蔽
				if(flag.local == remote)
					break;
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
				if(((manyou + FatherIndex[layer])->Parentms != NULL)&&(dofunflag == DISABLE))
				{
					manyou = (manyou+FatherIndex[layer])->Parentms;
					FatherIndex[layer] = 0;
					layer --;
					if(layer == 0)
						LCD_Clear();	
					Display(manyou + FatherIndex[layer]);
				}
				else if(dofunflag == ENABLE)
				{
					dofunflag	= DISABLE;
					flag.fresh = DISABLE;
					LCD_Clear();
					Display(manyou + FatherIndex[layer]);
				}
				else
				{
					manyou = TopMenu;		
					Display(manyou);
				}
					
				break;
			default:
				if(refresh == ENABLE)
				{
					//刷新页面
					if(dofunflag == ENABLE)
					{
						flag.fresh = ENABLE;
						Run(manyou + FatherIndex[layer]);	
					}
					else
						Display(manyou);
				}
				break;
		}	
	}
}
#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)
{ 
	while (1)
	{
	}
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
