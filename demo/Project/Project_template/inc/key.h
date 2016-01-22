/*************************************************************************/
/*
 * Copyright (c) 2015, Think All rights reserved.
 *
 * file       : key.h
 * Design     : zlb
 * Email	  : longbiao831@qq.com
 * Data       : 2015-12-13
 * Version    : V1.0
 * Change     :
 * Description: key.h 按键程序头文件
 */
/*************************************************************************/
#ifndef __KEY_H
#define __KEY_H
#include "stm8s_gpio.h"
#include "stm8s_adc2.h"

// 结构体定义
//状态定义
typedef enum {local, remote} StatusType;
//状态结构体定义
typedef struct _STATUS_FLAG_
{
	uint8_t heat:1;					//电机过热与否标志,0,正常,1,过热
	uint8_t move:1;					//电机运动与否标志,0,未运动,1,运动中
	uint8_t overclose:1;			//电机关阀超行程标志,0,未超行程,1,超行程
	uint8_t overopen:1;			//电机开阀超行程标志,0,未超行程,1,超行程
	uint8_t local:1;				//电机远方就地状态标志,0,就地,1,远方
	uint8_t set:1;					//菜单设置状态标志,0,普通,1,设置
	uint8_t light:1;				//面板背光状态标志,0,背光亮,1,背光灭
	uint8_t reserve:1;				//预留
}FlagTypeStr;
//ADC采集值定义
typedef struct _ADC_VALUE_
{
	uint16_t shift;					//移位ADC值
	uint16_t current;				//电流ADC值
}ADCValueStr;
// 宏定义
// 参数
#define LOWPOWER	420000u			//7*60*1000 7min背光时间
// KEY 定义
#define HR1			GPIO_PIN_5		//G5口 DOWN
#define HR2			GPIO_PIN_6		//G6口 ESC
#define HR3			GPIO_PIN_7		//G7口 SET
#define HR4			GPIO_PIN_4		//E4口 UP
// KEY键值定义
#define UP			0xD0			//UP 按键键值
#define DOWN		0xE0			//DOWN 按键键值
#define ESC			0xB0			//ESC 按键键值
#define SET			0x70			//SET 按键键值
// LED 定义
#define ERRLED		GPIO_PIN_7		//D7口 红色故障灯
#define GREENLED	GPIO_PIN_5		//D5口 绿色就地状态指示灯
#define BLUELED		GPIO_PIN_6		//D6口 蓝色远方状态指示灯
#define LED_PORT	GPIOD 
// 开出定义 报警1 报警2 关停止 开停止
#define ERR1		GPIO_PIN_3		//B3口 9_1
#define ERR2		GPIO_PIN_2		//B2口 9_2
#define CLOSE		GPIO_PIN_1		//B1口 9_3
#define OPEN		GPIO_PIN_0		//B0口 9_4
#define OUT_PORT	GPIOB
// 输入定义 电机过热信号 U V W 三相线序信号 REMOTE 远方就地信号
#define REMOTE		GPIO_PIN_7		//E7口 9_10
#define HEAT_PIN	GPIO_PIN_6		//E6口 9_5
#define HEAT_PORT	GPIOE			
#define UV_PIN		GPIO_PIN_1		//C1口 9_6
#define VW_PIN		GPIO_PIN_2		//C2口 9_7
#define WU_PIN		GPIO_PIN_3		//C3口 9_8
// ADC输入 电流数据AD信号 传感器数据AD信号 行程输入AD信号
#define CURRENT		GPIO_PIN_7		//B7口 9_9 电流数据
#define SENSOR		GPIO_PIN_7		//F7口 SENSOR
#define R_RE		GPIO_PIN_4		//B4口 行程输入

//LED 控制
#define LED_LightON( LED )  GPIO_WriteLow(LED_PORT, LED)
#define LED_LightOFF( LED)	GPIO_WriteHigh(LED_PORT, LED)

//变量声明
extern uint8_t ADC_Counter ;		//ADC通道采集计数器
extern uint8_t ADC_Channel ;		//默认ADC为第四通道,位移采集
extern uint16_t Shift_Step ;		//位移ADC偏移多少开始停止电机转动
extern uint8_t status;				//当前状态(远方或就地)
extern uint32_t light_flag;		//背光灯标志
extern FlagTypeStr flag;			//状态标志
extern ADCValueStr ValidADC;		//有效ADC值
extern ADCValueStr RealADC;			//实时ADC值
extern ADCValueStr UnitADC;			//死区ADC值
//函数声明
void Delay(uint32_t ms);
void Key_Init(void);
void LED_Init(void);
uint8_t Key_Read(void);
void InOut_Init(void);
void ADC_Shift_Init(void);			//保留(未使用)
void TIM4_Init(void);
uint8_t Analysis_key(uint8_t key);
void Motor_Out(uint8_t action, FunctionalState statu);
void ADC2_Shift_Init(ADC2_Channel_TypeDef ADC2_Channel, ADC2_SchmittTrigg_TypeDef ADC2_SchmittTrigg_Channel);
void Shift_Protect(void);
void Current_Protect(void);















#endif//__KEY_H