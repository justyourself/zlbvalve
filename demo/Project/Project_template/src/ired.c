/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : ired.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-23
 * Version    : V1.0
 * Change     :
 * Description: ired.c 红外传感器文件
 */
/*************************************************************************/
#include "ired.h"







/******************************函数定义***********************************/
/***************************************************************************/
//函数:	void Delay(uint8_t ms)
//说明:	延时时间ms
//输入: ms 延时时间
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
/*
void TIM3_Input_Capture(void)
{
	//捕获模式,TIM3通道1,下降沿捕获,CC1通道配置为输入,IC1映射在TI1FP1上,无预分频,采样频率fSAMPLING=fMASTER/32，N=8
	TIM3_ICInit( TIM3_CHANNEL_1, TIM3_ICPOLARITY_FALLING, TIM3_ICSELECTION_DIRECTTI , TIM3_ICPSC_DIV1, 0X0F);
	//使能更新中断与捕获中断
	TIM3_ITConfig(TIM3_IT_UPDATE|TIM3_IT_CC1,ENABLE);
	//使能输入捕获通道1
	TIM3_CCxCmd(TIM3_CHANNEL_1, ENABLE);
}
*/
void TIM3_Init(void)
{
	
}