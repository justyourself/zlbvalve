/**
  ******************************************************************************
  * @file main.c
  * @brief This file contains the main function for TIM2 PWM Output example.
  * @author STMicroelectronics - MCD Application Team
  * @version V2.0.0
  * @date 15-March-2011
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define CCR1_Val  ((u16)500) // Configure channel 1 Pulse Width
#define CCR2_Val  ((u16)250) // Configure channel 2 Pulse Width
#define CCR3_Val  ((u16)750) // Configure channel 3 Pulse Width
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief Example firmware main entry point.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
void main(void)
{

  /* TIM2 Peripheral Configuration */ 
  TIM2_DeInit();

  /* Set TIM2 Frequency to 2Mhz */ 
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 999);

  
	/* Channel 1 PWM configuration */ 
  TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,CCR1_Val, TIM2_OCPOLARITY_LOW ); 
  TIM2_OC1PreloadConfig(ENABLE);
  
	/* Channel 2 PWM configuration */
  TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,CCR2_Val, TIM2_OCPOLARITY_LOW );
  TIM2_OC2PreloadConfig(ENABLE);
	
	/* Channel 3 PWM configuration */
	TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,CCR3_Val, TIM2_OCPOLARITY_LOW );
  TIM2_OC3PreloadConfig(ENABLE);
  
	/* Enables TIM2 peripheral Preload register on ARR */
	TIM2_ARRPreloadConfig(ENABLE);
	
  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);

  
  while (1); 
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  * where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval 
  * None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
