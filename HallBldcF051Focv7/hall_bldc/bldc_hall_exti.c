/**
  ******************************************************************************
  * @file    EXTI.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include "bldc_global.h"



extern inline uint8_t  R_Hall_F(void);
extern inline void MotorStep_F(uint8_t step);
extern inline uint8_t  R_Hall_R(void);
extern inline void MotorStep_R(uint8_t step);


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Configure PA0 in interrupt mode
  * @param  None
  * @retval None
  */
void init_HALL_EXTI(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  
    /* Enable GPIOC clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  
  /* Configure PC6_7_8 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
 
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Connect EXTI4_15 Line to PC6 PC7 PC8 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource7);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);

  /* Enable and set EXTI0-1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

void EXTIx_Config(uint32_t EXTI_Linex,uint16_t EXTI_Trigger_x)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  
  /* Configure EXTIx line */
  EXTI_InitStructure.EXTI_Line = EXTI_Linex ;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_x;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Generate software interrupt: simulate a falling edge applied on EXTIx line */
  //EXTI_GenerateSWInterrupt(EXTI_Linex);
}


void HALL_EXTI_dis_intrrupt()   //ENABLE  DISABLE
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line6 | EXTI_Line7 | EXTI_Line8 ;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 4-9-10 interrupt request.
  * @param  None
  * @retval None
  */

 inline void HALL_EXTI_IRQHandler(void)
{
        uint16_t Num;
        uint8_t  Hall_Ok_Fg = 0;
        

          
        if( error_fg == 0 && brake_fg == 0 )
        {
             if( dir_fg == Reverse )
             {
                 step = R_Hall_R();
             }
             else
             {
                 step = R_Hall_F();
             }

             if( laststep == 5 )
             {
                if( step != 0 )
                {
                    Ck_Hall_Cnt += 1;
                }
                else 
                  Hall_Ok_Fg = 1;
             }
             else
             {
                if( ( step - laststep ) != 1 )
                {
                    Ck_Hall_Cnt += 1;
                }
                else 
                  Hall_Ok_Fg = 1;
             }
             laststep = step;

             if( Hall_Ok_Fg == 1 )
             {
                if( dir_fg == Reverse )
                {
                    MotorStep_R( step );
                }
                else
                {
                    MotorStep_F( step );
                }
//                Num = TimeCnt ;
//                Num = Num <<8 ;
//                Num += (uint8_t)TIM_GetCounter(TIM2);
//                TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//                PhaseTime = (PhaseTime + Num) >> 1;
//                if( PhaseTime > START_TIME ) PhaseTime = START_TIME;
//                //SetTiming( (PhaseTime >> 1) + 1);
//                //comm_fg = 1;
//                StartTime(); 
             }
         }
    
//    if( Ck_Hall_Cnt >= 4 || error_fg == 1 || brake_fg == 1 )
//    {
//         Ck_Hall_Cnt = 0;
//         Close_All_INT();
//         error_fg = 1;
//    }
    



}
void EXTI4_15_IRQHandler(void)
{
  Dis_GLOBAL_INT;
  //Delay(1);
  HALL_EXTI_IRQHandler();
  EXTI_ClearITPendingBit(EXTI_Line6);
  EXTI_ClearITPendingBit(EXTI_Line7);
  EXTI_ClearITPendingBit(EXTI_Line8);
  En_GLOBAL_INT;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
