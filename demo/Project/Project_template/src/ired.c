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
 * Description: ired.c ���⴫�����ļ�
 */
/*************************************************************************/
#include "ired.h"







/******************************��������***********************************/
/***************************************************************************/
//����:	void Delay(uint8_t ms)
//˵��:	��ʱʱ��ms
//����: ms ��ʱʱ��
//���: ��
//�༭: zlb
//ʱ��: 2015.12.13
/***************************************************************************/
/*
void TIM3_Input_Capture(void)
{
	//����ģʽ,TIM3ͨ��1,�½��ز���,CC1ͨ������Ϊ����,IC1ӳ����TI1FP1��,��Ԥ��Ƶ,����Ƶ��fSAMPLING=fMASTER/32��N=8
	TIM3_ICInit( TIM3_CHANNEL_1, TIM3_ICPOLARITY_FALLING, TIM3_ICSELECTION_DIRECTTI , TIM3_ICPSC_DIV1, 0X0F);
	//ʹ�ܸ����ж��벶���ж�
	TIM3_ITConfig(TIM3_IT_UPDATE|TIM3_IT_CC1,ENABLE);
	//ʹ�����벶��ͨ��1
	TIM3_CCxCmd(TIM3_CHANNEL_1, ENABLE);
}
*/
void TIM3_Init(void)
{
	
}