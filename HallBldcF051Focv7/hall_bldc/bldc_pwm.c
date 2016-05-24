#include "stm32f0xx.h"
#include "bldc_global.h"


void init_pwm()
{
  GPIO_InitTypeDef GPIO_InitStructure;
   //配置为pwm输出功能
  GPIO_InitStructure.GPIO_Pin = A_Hin_PIN | B_Hin_PIN |C_Hin_PIN ;  //PA8PA9 PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(A_Hin_PORT, &GPIO_InitStructure);
  

  
  GPIO_PinAFConfig(A_Hin_PORT, A_Hin_PIN_Source, GPIO_AF_2);
  GPIO_PinAFConfig(B_Hin_PORT, B_Hin_PIN_Source, GPIO_AF_2);
  GPIO_PinAFConfig(C_Hin_PORT, C_Hin_PIN_Source, GPIO_AF_2);


    /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  
    //配置TIM1为PWM 工作模式
  
  /* TIM1 clock enable */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  
 
 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
 int32_t  TimerPeriod = (SystemCoreClock / 16000 ) - 1;
  
   /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;   //計數方式
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;     //設定周期
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    
   
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
}
