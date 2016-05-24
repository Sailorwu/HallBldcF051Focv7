#include "stm32f0xx.h"

#include "bldc_pwm.h"

#include "bldc_hall_exti.h"

#include "bldc_hall_delay.h"

#include "bldc.h"

#include "bldc_global.h"


#define Relay_ON()      GPIO_SetBits(GPIOC,GPIO_Pin_13)

__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;

void init_AHB_clock()
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
}

extern inline void W_PwmDuty(uint16_t duty_value);


int main(void)
{
  
  uint16_t PwmDutyValue = STARTUP_DUTY ;
  static int32_t  temp2_speed = 0;

  
  RCC_ClocksTypeDef RCC_Clocks; 
 
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);//延时1us
  
  init_AHB_clock();
  
  init_three_phase();
  
//  init_uart1(); 
  
  init_pwm();
  
  //IOTEST();
  ADC1_Config();
  ADC_StartOfConversion(ADC1);  //第一次采集的数据不准，所以在这儿先采一次。
  
  init_HALL_EXTI();
 
  
  TIM2_config( );
  //TIM14_config( );


  dir_fg = Forward;

  restartup_fg = 1;
  
  Dis_GLOBAL_INT;
  
  while (1)
  {


  
    /* ADC1 regular Software Start Conv */ 
    ADC_StartOfConversion(ADC1);
     
    /* Get ADC1 converted data */
    ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
    
    /* Compute the voltage */
    ADC1ConvertedVoltage = (ADC1ConvertedValue * 3300)/0xFFF;
     
       //temp2_speed = R_Adc( Speed_CH ); 
    temp2_speed = ADC1ConvertedVoltage;
    
    if(temp2_speed < ADJ_RUN_TH)
    {
      restartup_fg = 1;
      DisAp;
      DisAn;
      DisBp;
      DisBn;
      DisCp;
      DisCn;
    }
    if( restartup_fg == 1 &&  temp2_speed > ADJ_RUN_TH)
    {
      error_fg = Startup( STARTUP_DUTY );
      restartup_fg = 0;
    }

     
     if( temp2_speed < ADJ_RUN_TH ) temp2_speed = 0;
     else temp2_speed = temp2_speed - ADJ_RUN_TH;
     PwmDutyValue = STARTUP_DUTY + ( ( ( PWM_MAX - STARTUP_DUTY ) * (uint32_t)temp2_speed ) / (3300 - ADJ_RUN_TH)  );
     if( PwmDutyValue > PWM_MAX )  PwmDutyValue = PWM_MAX ;

     Dis_GLOBAL_INT;
     if( PhaseTime > ( START_TIME - 500 ) && PwmDutyValue > PRO_DUTY ) PwmDutyValue = PRO_DUTY;
     En_GLOBAL_INT;
     
     
     //PwmDuty 逼近 PwmDutyValue
     if( PwmDuty < PwmDutyValue )
     {
        if( ( PwmDuty + PWM_ADD_NUM ) < PwmDutyValue ) PwmDuty += PWM_ADD_NUM;
        else PwmDuty += 1;
        W_PwmDuty(PwmDuty);
     }
     else if( PwmDuty > PwmDutyValue )
     {
        if( PwmDuty > ( PwmDutyValue + PWM_ADD_NUM ) ) PwmDuty -= PWM_ADD_NUM;
        else PwmDuty -= 1;
        W_PwmDuty(PwmDuty);
     }
      
       
  }
  
}






