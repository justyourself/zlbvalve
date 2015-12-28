 void ADC_Init(void)
{

	ADC1_Cmd(ENABLE);

	ADC1_DeInit();

	/* Init ADC2 peripheral */
	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_5, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_ALL, DISABLE);

	ADC1_DataBufferCmd(DISABLE);

	ADC1_Cmd(ENABLE);

	/* Enable EOC interrupt */
	ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);
    
}

Ȼ�����������￪��

main
{
��������
    ADC_Init();
    TIM4_INIT();
    enableInterrupts();
    ADC1_StartConversion();

while��1��
{
��������
}

}

�����timer4�����ڶ�ADC����ͨ���л���
��������tiemer4�ĳ�ʼ����
    void TIM4_INIT(void)
    {
        TIM4_DeInit();
        
        TIM4_TimeBaseInit(TIM4_PRESCALER_1, 500);

        TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
        
        TIM4_Cmd(ENABLE);
       
    }

������timer4���жϴ�������
@far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM4_UPD_OVF_IRQHandler(void) interrupt 23
#endif /* _COSMIC_ */
{
    ADC1_Cmd(ENABLE);   
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
}


�������ͨ���л�ʱ��ADC1�жϺ�������еġ�

@far @interrupt void ADC1_IRQHandler(void)
#else /* _RAISONANCE_ */
void ADC1_IRQHandler(void) interrupt 22
#endif /* _COSMIC_ */
{

   
ADC1_Cmd(DISABLE);                //����ADC
ADC1_ClearFlag(ADC1_FLAG_EOC);    //������λ

channelcounter++;
if(channel=5)
Conversion_Val =  ADC1_GetConversionValue();
else
XL_CURRETNT    =  ADC1_GetConversionValue();    


if(channelcounter >= 10)
{
ADC1->CSR &= (uint8_t)(~ADC1_CSR_CH);
ADC1->CSR |= (uint8_t)(ADC1_CHANNEL_5);
channelcounter=0;
channel=5;
}
else
{

ADC1->CSR &= (uint8_t)(~ADC1_CSR_CH);
ADC1->CSR |= (uint8_t)(ADC1_CHANNEL_3);
channel=3;

}

ADC1_Cmd(ENABLE);

  return;

}