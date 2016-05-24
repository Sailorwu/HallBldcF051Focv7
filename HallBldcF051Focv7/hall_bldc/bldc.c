#include "stm32f0xx.h"
#include "bldc_global.h"




//初始化
void init_three_phase()
{
//init it output no pull up or pull down
    GPIO_InitTypeDef phaseInit; 

    phaseInit.GPIO_Mode = GPIO_Mode_OUT;
    phaseInit.GPIO_OType = GPIO_OType_PP;
    phaseInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    phaseInit.GPIO_Speed = GPIO_Speed_50MHz;
      
    phaseInit.GPIO_Pin = Ap_Pin;
    GPIO_Init(Ap_Port, &phaseInit);
    
    phaseInit.GPIO_Pin = An_Pin;
    GPIO_Init(An_Port, &phaseInit);

    phaseInit.GPIO_Pin = Bp_Pin;
    GPIO_Init(Bp_Port, &phaseInit);
    
    phaseInit.GPIO_Pin = Bn_Pin;
    GPIO_Init(Bn_Port, &phaseInit);
    
    phaseInit.GPIO_Pin = Cp_Pin;
    GPIO_Init(Cp_Port, &phaseInit);
    
    phaseInit.GPIO_Pin = Cn_Pin;
    GPIO_Init(Cn_Port, &phaseInit);
}




void W_PwmDuty(uint16_t duty_value)
{
  uint16_t duty=0;
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  
  duty=(uint16_t)((uint32_t)(duty_value*1000)/1023);
  
  int32_t  TimerPeriod = (SystemCoreClock / 16000 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  int32_t Channel1Pulse = (uint16_t) (((uint32_t) duty * (TimerPeriod - 1)) / 1000);
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 */
  int32_t Channel2Pulse = (uint16_t) (((uint32_t) duty * (TimerPeriod - 1)) / 1000);
  /* Compute CCR3 value to generate a duty cycle at 12.5%  for channel 4 */
  int32_t Channel3Pulse = (uint16_t) (((uint32_t) duty * (TimerPeriod- 1)) / 1000);
  
  /* Channel 1, 2 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //CCER
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //CCER
  
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // OCx and OCxN  占空比相同
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //占空比相反
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);  
  
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}





uint8_t  R_Hall_F(void)  //正
{
    uint8_t dat;
    uint8_t step ;  //= 3;
      
    dat = (GPIO_ReadInputDataBit(A_Hall_PORT,A_Hall_PIN)<<0)|(GPIO_ReadInputDataBit(B_Hall_PORT,B_Hall_PIN)<<1)|(GPIO_ReadInputDataBit(C_Hall_PORT,C_Hall_PIN)<<2);
    
    switch( dat & 7 )
    {
       case 5: step = 0; break;
       case 1: step = 1; break;
       case 3: step = 2; break;
       case 2: step = 3; break;
       case 6: step = 4; break;
       case 4: step = 5; break;
       default : step = 0xff;
    }
    return step ;
}

void MotorStep_F(uint8_t step)    //正转
{
    switch( step )
    {
        case 0 :     //A+B-

        DisCp;
        EnAn_IO;
        Delay1us();Delay1us();
        DisAn;DisAn;
        Delay1us();
        EnBn_IO;
        EnAp_PWM;
        EXTIx_Config(EXTI_Line8,EXTI_Trigger_Falling);  // En_C_Rising; 

        break;

        case 1 :    //A+C-

        DisBn;
        EnAp_PWM;
        EnCn_IO;
        EXTIx_Config(EXTI_Line7,EXTI_Trigger_Rising);   //En_B_Falling;

        break;

        case 2 :   //B+C-

        DisAp;
        EnBn_IO;
        Delay1us();Delay1us();
        DisBn;DisBn;
        Delay1us();
        EnCn_IO;
        EnBp_PWM;
        EXTIx_Config(EXTI_Line6,EXTI_Trigger_Falling); //En_A_Rising;

        break;

        case 3 :    //B+A-

        DisCn;
        EnBp_PWM;
        EnAn_IO;
        EXTIx_Config(EXTI_Line8,EXTI_Trigger_Rising); //En_C_Falling;

        break;

        case 4 :   //C+A-

        DisBp; 
        EnCn_IO;
        Delay1us();Delay1us();
        DisCn;DisCn;
        Delay1us();
        EnAn_IO;
        EnCp_PWM;
        EXTIx_Config(EXTI_Line7,EXTI_Trigger_Falling); //En_B_Rising;

        break;

        case 5 :   //C+B-

        DisAn;
        EnCp_PWM;
        EnBn_IO;
        EXTIx_Config(EXTI_Line6,EXTI_Trigger_Rising); //En_A_Falling;

        break;

        default :

        Dis_All_Phase;

        break;


    }

}


uint8_t  R_Hall_R(void)   //反
{
    uint8_t dat;
    uint8_t step;// = 3;
    dat = (GPIO_ReadInputDataBit(A_Hall_PORT,A_Hall_PIN)<<0)|(GPIO_ReadInputDataBit(B_Hall_PORT,B_Hall_PIN)<<1)|(GPIO_ReadInputDataBit(C_Hall_PORT,C_Hall_PIN)<<2);
 //   dat >>= 5;
    switch( dat & 7 )
    {
        case 5: step = 0; break;
        case 4: step = 1; break;
        case 6: step = 2; break;
        case 2: step = 3; break;
        case 3: step = 4; break;
        case 1: step = 5; break;
        
        default : step = 0xff;
    }
    return step ;
}

void MotorStep_R(uint8_t step)    //反转
{
    switch( step )
    {
        case 0 :                         //B+A-      
        DisCp;
        EnBn_IO;
//        Delay1us();Delay1us();
        DisBn;DisBn; 
        Delay1us();
        EnAn_IO;
        EnBp_PWM;
        EXTIx_Config(EXTI_Line6,EXTI_Trigger_Falling); //En_A_Rising;

        break;

        case 1 :                            //BC

        DisAn;
        EnBp_PWM;
        EnCn_IO;
        EXTIx_Config(EXTI_Line7,EXTI_Trigger_Rising); //En_B_Falling;

        break;

        case 2 :                            //AC

        DisBp;
        EnAn_IO;
//        Delay1us();Delay1us();    
        DisAn;DisAn;
        Delay1us();
        EnCn_IO;
        EnAp_PWM;
        EXTIx_Config(EXTI_Line8,EXTI_Trigger_Falling); //En_C_Rising;

        break;

        case 3 :                             //AB

        DisCn;
        EnAp_PWM;
        EnBn_IO;
        EXTIx_Config(EXTI_Line6,EXTI_Trigger_Rising); //En_A_Falling;

        break;

        case 4 :                             //CB

        DisAp;
        EnCn_IO;
//        Delay1us();Delay1us();
        DisCn;DisCn;
        Delay1us();       
        EnBn_IO;
        EnCp_PWM;
        EXTIx_Config(EXTI_Line7,EXTI_Trigger_Falling); //En_B_Rising;

        break;

        case 5 :                             //CA

        DisBn;
        EnCp_PWM;
        EnAn_IO; 
        EXTIx_Config(EXTI_Line8,EXTI_Trigger_Rising); //En_C_Falling;

        break;

        default :

        Dis_All_Phase;
        
        break;
    }
}



uint8_t Startup( uint16_t duty )
{

     Dis_All_Phase;
     En_All_Down;
     Delay1us(); Delay1us();Delay1us(); Delay1us(); Delay1us(); Delay1us(); Delay1us();
     Dis_All_Phase;
     
     if( dir_fg == Reverse )
     {
         step = R_Hall_R() ;
         MotorStep_R(step);
     }
     else
     {
         step = R_Hall_F() ;
         MotorStep_F(step);
     }
    

     if( step == 0xff ) return 1;  //返回错误标志
     


     laststep = step;

     PwmDuty = duty;
     W_PwmDuty( PwmDuty );
   
     En_GLOBAL_INT;

     return 0;
}