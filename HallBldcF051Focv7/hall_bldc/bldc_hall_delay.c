#include "stm32f0xx.h"






static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


void Delay1us()
{
  uint8_t num; 
  for(num=2;num>0;num--)
  {
    __NOP(); __NOP(); __NOP();
  }
}