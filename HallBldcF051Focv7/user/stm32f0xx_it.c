#include "stm32f0xx.h"

#include "bldc_global.h"


extern void TimingDelay_Decrement(void);

void SysTick_Handler(void)
{
   TimingDelay_Decrement();
}


void Close_All_INT(void)
{
    Dis_All_Phase;
    HALL_EXTI_dis_intrrupt();  //Dis_GPIO_INT;
    DIS_Time2_interrupt();    //StopTime();
    StopTiming();
    restartup_fg = 0;
    EXTI_ClearITPendingBit(EXTI_Line0);
    EXTI_ClearITPendingBit(EXTI_Line1);
    EXTI_ClearITPendingBit(EXTI_Line2);
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
void TIM2_IRQHandler()
{
 if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
 {
  if( TimeCnt < 0x62 ) 
    TimeCnt += 1;
  else 
    error_fg = 1; 
//    Mode = 2;
//    restartup_fg=1;
  
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  
  if( Ck_Hall_Cnt >= 4 || error_fg == 1 || brake_fg == 1 )
    {
         Ck_Hall_Cnt = 0;
         Close_All_INT();
         error_fg = 1;
    } 
 }
}
