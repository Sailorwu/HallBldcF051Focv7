#include "stm32f0xx.h"
#include "bldc_hall_adc.h"
#include "bldc_const.h"

void ADC1_Config(void)
{
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
   
  /* Configure ADC Channel 13 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC1 Configuration *******************************************************/
  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits*/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure);   


  ADC_ChannelConfig(ADC1, Speed_CH , ADC_SampleTime_7_5Cycles);  
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);

  /* Enable the auto delay feature */    
  ADC_WaitModeCmd(ADC1, ENABLE); 
  
  /* Enable the Auto power off mode */
  ADC_AutoPowerOffCmd(ADC1, ENABLE); 
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN));   
  

}



uint16_t R_Adc(uint8_t ADC_Channel)
{
//  uint32_t temp , i , result = 0 ,max,min;
//  
//  int time_out = 0;
//  
//    ADC1->CHSELR = ADC_Channel;
//    
//    for( i=0 ; i<10 ; i++ )
//    {
//        ADC1->CR |= (uint32_t)ADC_CR_ADSTART;
//        time_out = ADC_TIME_OUT;
//        while(!(ADC1->ISR & ADC_FLAG_EOC) && (--time_out != 0));
//        if(time_out == 0)
//        {
//          return 0;
//        }
//        temp = ADC1->DR;
//        result += temp;
//        if( i == 0 )          max = min = temp;
//        if( max < temp )      max = temp;
//        else if( min > temp ) min = temp;
//    }
//    
//    result -= ( max + min );
//    result = result >> 3;
//    result = (result * 2962)/0x3FF;               //电压是2.962V，AD分辨率为10位；
//    return (result);

  
}