/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : key.c
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: key.c 按键程序
 */
/*************************************************************************/
#include "stm8s_gpio.h"
#include "key.h"
#include "menu.h"

/******************************变量定义***********************************/
uint8_t ADC_Counter = 0;
uint8_t ADC_Channel = ADC2_CHANNEL_4;		//默认ADC为第四通道,位移采集
uint16_t Shift_ADC = 0;					//位移ADC值
uint16_t Current_ADC = 0;					//电流ADC值
uint8_t status;								//当前状态(远方或就地)


/******************************函数定义***********************************/
/***************************************************************************/
//函数:	void Delay(uint8_t ms)
//说明:	延时时间ms
//输入: ms 延时时间
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Delay(uint32_t ms)
{
	uint8_t i;
	while (ms != 0)
	{
		ms--;
		for(i=0;i<100;i++);
	}
}
/***************************************************************************/
//函数:	void Key_Init(void)
//说明:	初始化KEY
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void Key_Init(void)
{
	//设置按键1 2 3为上拉
	GPIO_Init(GPIOG,(GPIO_Pin_TypeDef)(HR1|HR2|HR3),GPIO_MODE_IN_PU_NO_IT);
	//设置按键4
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)HR4,GPIO_MODE_IN_PU_NO_IT);
}
/***************************************************************************/
//函数:	void LED_Init(void)
//说明:	初始化LED
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void LED_Init(void)
{
	//初始化LED IO为上拉
	GPIO_Init(LED_PORT,(GPIO_Pin_TypeDef)(ERRLED|GREENLED|BLUELED),GPIO_MODE_OUT_PP_HIGH_FAST);
        
	if(!GPIO_ReadInputPin(GPIOE,(GPIO_Pin_TypeDef)(REMOTE)))
	{
		LED_LightON(BLUELED);			//打开远方指示灯
		status = remote;
	}
	else
	{
		LED_LightON(GREENLED);			//打开就地指示灯
		status = local;
	}
        
}
/***************************************************************************/
//函数:	void InOut_Init(void)
//说明:	初始化输入输出接口 电机过热管脚为中断管脚
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void InOut_Init(void)
{
	//初始化输入OUT IO为快速推挽输出
	GPIO_Init(OUT_PORT,(GPIO_Pin_TypeDef)(ERR1|ERR2|OPEN|CLOSE),GPIO_MODE_OUT_PP_HIGH_FAST);
	//初始化输入IN IO为上拉输入C口 三相输入UV_PIN VW_PIN WU_PIN
	GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)(UV_PIN|VW_PIN|WU_PIN),GPIO_MODE_IN_PU_NO_IT);
	//初始化输入IN IO为浮点输入E口 远方就地REMOTE 中断模式
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(REMOTE),GPIO_MODE_IN_FL_IT);
	//初始化输入IN IO为浮点输入E口 电机过热输入HEAT_PIN 为中断输入
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(HEAT_PIN),GPIO_MODE_IN_FL_IT);

	
	//使能上升沿下降沿触发中断(远方就地为上升沿下降沿触发中断,电机过热中断为下降沿中断 )
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_RISE_FALL);
}
/***************************************************************************/
//函数:	uint8_t Key_Read(void)
//说明:	初始化LED
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
uint8_t Key_Read(void)
{
	uint8_t keydata = 0;
	static uint8_t keyup = 0;
	//读取按键值 按键顺序高四位分别代表HR1 HR2 HR3 HR4
	keydata = GPIO_ReadInputPin(GPIOG, (GPIO_Pin_TypeDef)(HR1|HR2|HR3));
	keydata |= GPIO_ReadInputPin(GPIOE, (GPIO_Pin_TypeDef)HR4);
	
	//去抖动
	if(keyup && (keydata ^ 0xf0))
	{
		keyup = 0;
		//延时10ms
		Delay(10);
		//读取按键值
		keydata = GPIO_ReadInputPin(GPIOG, (GPIO_Pin_TypeDef)(HR1|HR2|HR3));
		keydata |= GPIO_ReadInputPin(GPIOE, (GPIO_Pin_TypeDef)HR4);
		if(keydata ^ 0xf0)
		{
			return keydata;
		}	
	}
	else if(keydata ^ 0xf0)
	{
		keyup = 1;
		return 0;
	}
        
	return 0;
}
/***************************************************************************/
//函数:	void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel)
//说明:	通用ADC初始化函数
//输入: ADC2_Channel ADC2通道号,ADC2_SchmittTrigg_Channel ADC2斯密特触发通道号
//输出: 无
//编辑: zlb
//时间: 2015.12.22
/***************************************************************************/
void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel)
{
	// ADC恢复默认值
	ADC2_DeInit();
	//循环模式 
	ADC2_Init(ADC2_CONVERSIONMODE_SINGLE , ADC2_Channel, ADC2_PRESSEL_FCPU_D18,\
		ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SchmittTrigg_Channel, DISABLE);
	
	//使能ADC
	ADC2_Cmd(ENABLE);
	//使能中断
	ADC2_ITConfig(ENABLE);
}
/***************************************************************************/
//函数:	void ADC_Shift_Init(void)
//说明:	初始化位移传感器ADC(保留)
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void ADC_Shift_Init(void)
{
	// ADC恢复默认值
	ADC2_DeInit();
	//循环模式 
	ADC2_Init(ADC2_CONVERSIONMODE_CONTINUOUS , ADC2_CHANNEL_4, ADC2_PRESSEL_FCPU_D18,\
		ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SCHMITTTRIG_CHANNEL4,DISABLE);
	ADC2_ITConfig(DISABLE);
	
	//使能ADC
	ADC2_Cmd(ENABLE);
	//开始转换
	ADC2_StartConversion();
}
/***************************************************************************/
//函数:	void TIM4_Init(void)
//说明:	TIM4定时器中断初始化
//输入: 无
//输出: 无
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
void TIM4_Init(void)
{
	TIM4_DeInit();
	//初始化TIM4为内部时钟64分频 计数周期为1ms 0-249
	TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249);
	//配置TIM4更新中断
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	//使能TIM4
	TIM4_Cmd(ENABLE);
}
/***************************************************************************/
//函数:	uint8_t Analysis_key(uint8_t key)
//说明:	特殊菜单中按键处理函数
//输入: key 传入按键值
//输出: 根据需要传出修改后的按键值
//编辑: zlb
//时间: 2015.12.13
/***************************************************************************/
uint8_t Analysis_key(uint8_t key)
{
	switch(key)
	{
		case ESC:
			return key;
		case SET:
			keyset ++;
			break;
		case UP:
			keyup ++;
			break;
		case DOWN:
			keydown ++;
			break;
		default:
			return key;
			break;
	}
	return 0;
}
















