/**
  ******************************************************************************
  * @file main.c
  * @brief Displaying variable voltage on a bar of LEDs Application example.
  * @author STMicroelectronics - MCD Application Team
  * @version 2.0.0
  * @date 15-MAR-2011
  ******************************************************************************
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"                // file needed only for registers mask 
#include "parameter.h"
/**
  * @addtogroup ADC1_Example1
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define ALL_LEDs ((u8)0x0F)				// LEDs mask 

/* Private macro -------------------------------------------------------------*/

#define switch_all_LEDs_on		{ GPIOB->ODR|= ALL_LEDs; }	//LEDs control : all on
#define switch_all_LEDs_off	  { GPIOB->ODR&=~ALL_LEDs; }    //LEDs control : all off

/* Private variables ---------------------------------------------------------*/
	u8  temp_AD_H;					   // temporary registers for reading ADC result (MSB)
	u8  temp_AD_L;             // temporary registers for reading ADC result (LSB)
	u8	ADInit;						     // flag for ADC initialized
	u8	ADSampRdy;				     // flag for filed of samples ready
	u8  AD_samp;						   // counter of stored samples
	u16 AD_sample[NUMB_SAMP];	 // store samples field 
	u16 AD_avg_value;				   // average of ADC result
	
	u8 peak_memo;					     // variables for peak level detector
	u8 peak_filt;					     // variables for peak level detector*/

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief Count average of samples stored in the u16 field
  * @par Parameters:
  *  *p: pointer to the begin of the field
  * smp: number of samples in the field
  * @retval Average u16 value
  */
u16 u16_average(u16 *p, u8 smp) { 
	u8 i;
	u16 sum;
	
	for(i=0, sum= 0; i < smp; ++i)
		sum+= *p++;		
	return sum / smp;
}
/* -------------------------------------------------------------------------- */
/**
  * @brief Prepare data for four LED bar of signal and peak indicator
  * @par Parameters:
  * val: Level of the mesured signal [0-4]
  * @retval 4 bits (low nibble) of the composite bar graph information
  */
u8 signal_and_peak_level(u8 val) {
	u8 signal;
	u8 peak;
	
	switch(val) {
		case 0: peak= 0; signal=  0; break;	//set peak and signal levels
		case 1: peak= 1; signal=  1; break;
		case 2: peak= 2; signal=  3; break;
		case 3: peak= 4; signal=  7; break;
		case 4: peak= 8; signal= 15; break;
		default: peak= signal= 15;
	};
	if(peak_filt == 0) {									// slow fall of peak level indicator 
		if(peak_memo) {
			peak_memo>>= 1;
			peak_filt= PEAK_FILTER;
		};
	}
	else
		--peak_filt;
	if(peak >= peak_memo) {				       // check the highest level value
		peak_memo= peak;					         // and copy it to peak indicator
		peak_filt= PEAK_FILTER;			       // with fall speed refresh
	};
	return (signal | peak_memo);		     // return bar graph information
}

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Validation firmware main entry point.
  * @par Parameters:
  * None
  * @retval void None
  */  
void main(void) {
	u8 leds;
// 								*** GPIO INIT ***
	GPIOB->ODR&=~ALL_LEDs; 				// LEDs - as push-pull outputs, all off
	GPIOB->DDR|= ALL_LEDs;				// 
	GPIOB->CR1|= ALL_LEDs;
	
	GPIOC->DDR|= 0x02;						// PC.1 as push-pull outputs
	GPIOC->CR1|= 0x02;
		
	GPIOE->CR1&=~0x40;					  // PE.6 as a floating input
	GPIOE->DDR&=~0x40;
	
// 								*** ADC INITIALIZATION ***
	TIM1->ARRH= (u8)(AUTORELOAD >> 8);		          // set autoreload register for trigger period
	TIM1->ARRL= (u8)(AUTORELOAD);				            // 
	TIM1->CCR1H= (u8)((AUTORELOAD-AD_STAB) >> 8);   // set compare register for trigger period
	TIM1->CCR1L= (u8)(AUTORELOAD-AD_STAB);
	TIM1->CR1|= TIM1_CR1_ARPE;					            // auto reload register is buferred
	
	TIM1->CR2= (4<<4) & TIM1_CR2_MMS;		            // CC1REF is used as TRGO
	TIM1->CCMR1= (6<<4) & TIM1_CCMR_OCM;	          // CC1REF in PWM 1 mode
	TIM1->IER|= TIM1_IER_CC1IE;				              // CC1 interrupt enable
	TIM1->CCER1|= TIM1_CCER1_CC1P;			            // CC1 negative polarity
	TIM1->CCER1|= TIM1_CCER1_CC1E;			            // CC1 output enable
	TIM1->BKR|= TIM1_BKR_MOE;												
	
	TIM1->SMCR|=  TIM1_SMCR_MSM;				            // synchronization of TRGO with ADC
	
	TIM1->CR1|= TIM1_CR1_CEN;					              // timer 1 enable
		
	ADC1->CSR= ADC1_CSR_EOCIE | (9 & ADC1_CSR_CH);  // ADC EOC interrupt enable, channel 9
	ADC1->CR1= 4<<4 & ADC1_CR1_SPSEL;			          // master clock/8, single conversion
	ADC1->CR2= ADC1_CR2_EXTTRIG;					          // external trigger on timer 1 TRGO, left alignment
	ADC1->TDRH= 2;									                // disable Schmitt trigger on AD input 9
	ADC1->TDRL= 0;                                  //

  // init ADC variables
	AD_samp= 0;						                          // number of stored samples 0
	ADInit= TRUE;                                   // ADC initialized 
	ADSampRdy= FALSE;                               // No sample 
	
	ADC1->CR1|= ADC1_CR1_ADON;					            // ADC on

	enableInterrupts();							                // enable all interrupts 
	
// 								*** MAIN LOOP ***	
	while (1) {
		if (ADSampRdy == TRUE) {				                     // field of ADC samples is ready?
			AD_avg_value= u16_average(&AD_sample[0], AD_samp); // average of samples
			
			AD_samp= 0;								                         // reinitalize ADC variables
			ADSampRdy= FALSE;
						
			leds= signal_and_peak_level((u8)((AD_avg_value + 128) / 256)); // setting LED status
			
			GPIOB->ODR&= leds | (~ALL_LEDs);	// LEDs settings in according to LED status
			GPIOB->ODR|= leds;
		};
	};
}
/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
