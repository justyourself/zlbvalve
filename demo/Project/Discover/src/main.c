/**
  ******************************************************************************
  * @file main.c
  * @brief Adjustable LED blinking speed using STM8S-DISCOVERY touch sensing key
  * Application example.
  * @author STMicroelectronics - MCD Application Team
  * @version V2.0.0
  * @date 15-MAR-2011
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2008 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8_tsl_api.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MilliSec       1
#define Sec           10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void CLK_Configuration(void);
void GPIO_Configuration(void);
void ExtraCode_Init(void);
void ExtraCode_StateMachine(void);
void Delay(void action(void), int NumberofTIMCycles);
void Toggle(void);

/* Private functions ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
u8 BlinkSpeed = 6;
int NumberOfStart;
int CheckFlag = 1;

/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief Main function.
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void main(void)
{
  /* Configures clocks */
  CLK_Configuration();

  /* Configures GPIOs */
  GPIO_Configuration();

  /* Initialize Touch Sensing library */
  TSL_Init();
  
	/* Initialize all the Touch Sensing keys */
  ExtraCode_Init();

  /* Start the 100ms timebase Timer */
  TSL_Tick_Flags.b.User1_Start_100ms = 1;

  for (;;)
  {

    /* User code */
    ExtraCode_StateMachine();
   
	  /* Main function of the Touch Sensing library */
  
    TSL_Action();

  }

}


/**
  ******************************************************************************
  * @brief Initialize all the TS keys
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void ExtraCode_Init(void)
{

  u8 i;

  /* All keys are implemented and enabled */

  for (i = 0; i < NUMBER_OF_SINGLE_CHANNEL_KEYS; i++)
  {
    sSCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sSCKeyInfo[i].Setting.b.ENABLED = 1;
    sSCKeyInfo[i].DxSGroup = 0x01; /* Put 0x00 to disable the DES on these pins */
  }

#if NUMBER_OF_MULTI_CHANNEL_KEYS > 0
  for (i = 0; i < NUMBER_OF_MULTI_CHANNEL_KEYS; i++)
  {
    sMCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sMCKeyInfo[i].Setting.b.ENABLED = 1;
    sMCKeyInfo[i].DxSGroup = 0x01; /* Put 0x00 to disable the DES on these pins */
  }
#endif

  enableInterrupts();
}


/**
  ******************************************************************************
  * @brief Adjustable led blinking speed using touch sensing keys
  * KEY1: LED1 is blinking
  * KEY1: LED1 is blinking faster
  * KEY1: LED1 don't blink anymore
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void ExtraCode_StateMachine(void)
{
  if ((TSL_GlobalSetting.b.CHANGED) && (TSLState == TSL_IDLE_STATE))
  {
    TSL_GlobalSetting.b.CHANGED = 0;

    if (sSCKeyInfo[0].Setting.b.DETECTED) /* KEY 1 touched */
    {
      BlinkSpeed++;
      BlinkSpeed = BlinkSpeed % 3;
    }
  }

  switch (BlinkSpeed)
  {
    case 0 :
      GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
      break;

    case 1 :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 2*MilliSec);
      }
      break;

    case 2 :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 1*MilliSec);
      }
      break;

    default :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 1*Sec);
      }
  }
 
}

/**
  ******************************************************************************
  * @brief Configures clocks
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void CLK_Configuration(void)
{

  /* Fmaster = 16MHz */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

}

/**
  ******************************************************************************
  * @brief Configures GPIOs
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void GPIO_Configuration(void)
{
  /* GPIOD reset */
  GPIO_DeInit(GPIOD);

  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);

}


/**
  ******************************************************************************
  * @brief Delay before completing the action
  * @param[in] function action() to be performed once the delay past
 * @param[in]
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void Delay(void action(void), int NumberofTIMCycles)
{
  if ((CheckFlag) != 0)
    NumberOfStart = NumberofTIMCycles;
  if (NumberOfStart != 0)
  {
    TSL_Tick_Flags.b.User1_Start_100ms = 1;
    CheckFlag = 0;
  }
  if (TSL_Tick_Flags.b.User1_Flag_100ms)
  {
    TSL_Tick_Flags.b.User1_Flag_100ms = 0;
    NumberOfStart--;
  }
  if (NumberOfStart == 0)
  {
    action();
    CheckFlag = 1;
  }
}


/**
  ******************************************************************************
  * @brief Toggle PD0 (Led LD1)
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void Toggle(void)
{
  GPIO_WriteReverse(GPIOD, GPIO_PIN_0);
}
/****************** (c) 2008  STMicroelectronics ******************************/
