#include "stm32f0xx.h"

#include "bldc_global.h"


void SetTiming( uint32_t time ) 
{
  TIM1->CR1 &= (~TIM_CR1_CEN);
  if( time == 0 ) time = 1;
  TIM1->SR = (uint16_t)~TIM_IT_Update;
  TIM1->ARR = time ; 
  TIM1->CNT = 0;
  TIM1->CR1 |= TIM_CR1_CEN;
}

void TIM1_config( )
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  
  /* Time Configuration in Timing mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing ;
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 95;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //計數方式
  TIM_TimeBaseStructure.TIM_Period = 1 ;     //設定周期
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Repetitive);
  
  TIM_ARRPreloadConfig(TIM1, DISABLE);
  
  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  
  TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);
  
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM1 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* TIM1 counter enable */
  //TIM_Cmd(TIM1, ENABLE);
}







void StartTime() 
{ 
  TIM_ITConfig(TIM2, TIM_IT_Update,DISABLE);
  
  TIM2->CNT &= 0X00;
  
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  
  TimeCnt = 0;
  
  TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
}



 /************* 設定周期  2MS *****************/
void TIM2_config( )
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  
  /* Time Configuration in Timing mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing ;
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 383;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //計數方式
  TIM_TimeBaseStructure.TIM_Period = 255;     //設定周期  2MS
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
  
  TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Repetitive);
  
  TIM_ARRPreloadConfig(TIM2, DISABLE);
  
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  
//  TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
  
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* TIM2 counter enable */
  TIM_Cmd(TIM2, ENABLE);
}

void TIM14_config( )
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14 , ENABLE);
  
  /* Time Configuration in Timing mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing ;
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 47;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //計數方式
  TIM_TimeBaseStructure.TIM_Period = 100;     //設定周期  1MS
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure); 
  
  TIM_SelectOnePulseMode(TIM14, TIM_OPMode_Repetitive);
  
  TIM_ARRPreloadConfig(TIM14, DISABLE);
  
  TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
  
  TIM_ITConfig(TIM14, TIM_IT_Update,ENABLE);
  
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM14 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* TIM14 counter enable */
  TIM_Cmd(TIM14, ENABLE);
}


