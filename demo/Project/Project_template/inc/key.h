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
typedef enum {local, remote, set} StatusType;
// 宏定义
// 参数
#define LOWPOWER	420000u			//7*60*1000 7min背光时间
// KEY 定义
#define HR1			GPIO_PIN_5		//G5口 DOWN
#define HR2			GPIO_PIN_6		//G6口 ESC
#define HR3			GPIO_PIN_7		//G7口 SET
#define HR4			GPIO_PIN_4		//E4口 UP
// KEY键值定义
#define UP			0x10			//UP 按键键值
#define DOWN		0x20			//DOWN 按键键值
#define ESC			0x40			//ESC 按键键值
#define SET			0x80			//SET 按键键值
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
#define HEAT_PIN	GPIO_PIN_6		//E6口 9_5
#define HEAT_PORT	GPIOE			
#define UV_PIN		GPIO_PIN_1		//C1口 9_6
#define VW_PIN		GPIO_PIN_2		//C2口 9_7
#define WU_PIN		GPIO_PIN_3		//C3口 9_8
#define REMOTE		GPIO_PIN_7		//E7口 9_10
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
extern uint16_t Shift_ADC ;		//位移ADC值
extern uint16_t Current_ADC ;		//电流ADC值
extern uint16_t Shift_Step ;		//位移ADC偏移多少开始停止电机转动
extern uint8_t status;				//当前状态(远方或就地)
extern uint32_t light_flag;		//背光灯标志
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
















#endif//__KEY_H