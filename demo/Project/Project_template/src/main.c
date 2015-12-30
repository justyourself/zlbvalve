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
 * Description: menu.c �˵��ṹ����
 */
/*************************************************************************/
#include "string.h"
#include "stm8s.h"
#include "stm8s_clk.h"
#include "key.h"
#include "menu.h"
#include "GT21H16S2Y.h"
#include "JLX12864G.h"

/******************************��������***********************************/
// LOG ͼ��
extern const uint8_t log[];
/******************************��������***********************************/
/***************************************************************************/
//����:	void Init_Clock(void)
//˵��:	��ʼ��ʱ��Ϊ�ڲ�ʱ��
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void Init_Clock(void)
{
	/* Select fCPU = 16MHz */
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	/* For test purpose output Fcpu on MCO pin */
	CLK_CCOConfig(CLK_OUTPUT_CPU);
}
/***************************************************************************/
//����:	void main(void)
//˵��:	������
//����: ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
void main(void)
{
	uint8_t key;
	// ��ʼ��ʱ��
	Init_Clock();
	// ��ʼ��LCD
	JLX_LCD_Init();
	// ��ʼ���ֿ�оƬ
	GT21H16S2Y_GPIO_Init();
	LCD_Clear();
	// ��ʼ��GPIO
	Key_Init();
        // ��ʼ���������
	InOut_Init();
	// ��ʼ��LED
	LED_Init();
	// ��ʼ��ADC
	ADC2_Shift_Init(ADC2_CHANNEL_7, ADC2_SCHMITTTRIG_CHANNEL7);
	// ��ʼ����ʱ��4 1ms��ʱ�� ADC�ɼ�ר��
	TIM4_Init();
	//ʹ���ж�
	enableInterrupts();

	//������ʾLOGO
	LCD_Display_128x64(log);
	//��ʱ
	Delay(10000);
	//��ʾĬ�Ͻ���
	manyou = TopMenu;
	Display(manyou);
	while (1)
	{
		key = Key_Read();
		// ����ϼ�����
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
				//ˢ��ҳ��
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
