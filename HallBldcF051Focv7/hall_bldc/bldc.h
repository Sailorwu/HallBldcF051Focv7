#include "stm32f0xx.h"

#define Driver_High_High

#define set_pin(port,pin) (port)->BSRR = (pin);
#define clr_pin(port,pin) (port)->BRR = (pin);



#define set_Ap() set_pin(Ap_Port,Ap_Pin)
#define clr_Ap() clr_pin(Ap_Port,Ap_Pin)

#define set_An() set_pin(An_Port,An_Pin)
#define clr_An() clr_pin(An_Port,An_Pin)




#define set_Bp() set_pin(Bp_Port,Bp_Pin)
#define clr_Bp() clr_pin(Bp_Port,Bp_Pin)

#define set_Bn() set_pin(Bn_Port,Bn_Pin)
#define clr_Bn() clr_pin(Bn_Port,Bn_Pin)



#define set_Cp() set_pin(Cp_Port,Cp_Pin)
#define clr_Cp() clr_pin(Cp_Port,Cp_Pin)

#define set_Cn() set_pin(Cn_Port,Cn_Pin)
#define clr_Cn() clr_pin(Cn_Port,Cn_Pin)


#define EnAp_PWM    { A_Hin_PORT->MODER =((A_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(A_Hin_PIN_Source * 2))))\
                      | (GPIO_Mode_AF << (A_Hin_PIN_Source * 2))); }    //CH1

#define EnAp_IO     { set_Ap();\
                      A_Hin_PORT->MODER =((A_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(A_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (A_Hin_PIN_Source * 2))); }
#define DisAp       { clr_Ap(); \
                      A_Hin_PORT->MODER =((A_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(A_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (A_Hin_PIN_Source * 2))); }

#ifdef Driver_High_High
#define EnAn_IO     { set_An(); }
#define DisAn       { clr_An(); }
#else
#define EnAn_IO     { clr_An(); }
#define DisAn       { set_An(); }
#endif

#define EnBp_PWM    { B_Hin_PORT->MODER =((B_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(B_Hin_PIN_Source * 2))))\
                      | (GPIO_Mode_AF << (B_Hin_PIN_Source * 2))); }    //CH2

#define EnBp_IO     { set_Bp();\
                      B_Hin_PORT->MODER =((B_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(B_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (B_Hin_PIN_Source * 2))); }
#define DisBp       { clr_Bp();\
                      B_Hin_PORT->MODER =((B_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(B_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (B_Hin_PIN_Source * 2))); }
#ifdef Driver_High_High
#define EnBn_IO     { set_Bn(); }
#define DisBn       { clr_Bn(); }
#else
#define EnBn_IO     { clr_Bn(); }
#define DisBn       { set_Bn(); }
#endif

#define EnCp_PWM    { C_Hin_PORT->MODER =((C_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(C_Hin_PIN_Source * 2))))\
                      | (GPIO_Mode_AF << (C_Hin_PIN_Source * 2))); }    //CH4

#define EnCp_IO     { set_Cp(); \
                      C_Hin_PORT->MODER =((C_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(C_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (C_Hin_PIN_Source * 2))); }
#define DisCp       { clr_Cp();  \
                      C_Hin_PORT->MODER =((C_Hin_PORT->MODER&(~(GPIO_MODER_MODER0<<(C_Hin_PIN_Source * 2))))\
                      |(GPIO_Mode_OUT << (C_Hin_PIN_Source * 2))); }
#ifdef Driver_High_High
#define EnCn_IO     { set_Cn(); }
#define DisCn       { clr_Cn(); }
#else
#define EnCn_IO     { clr_Cn();}
#define DisCn       { set_Cn(); }
#endif

#define Dis_All_Phase  { DisAp; DisBp; DisCp; DisAn; DisBn; DisCn; DisAn; }

#define En_All_Down    { EnAn_IO; EnBn_IO; EnCn_IO; }

#define Dis_All_Down   { DisAn; DisBn; DisCn; }

#define En_All_Up      { EnAp_IO; EnBp_IO; EnCp_IO; }

#define En_Brake       { Dis_All_Phase; En_All_Down;   }//  En_All_Down;


#define En_GLOBAL_INT   __enable_irq();
#define Dis_GLOBAL_INT  __disable_irq();


#define StopTiming()     TIM1->CR1 &= (~TIM_CR1_CEN);
#define RunTiming()      TIM1->CR1 |= TIM_CR1_CEN;


#define DIS_Time2_interrupt()      TIM_ITConfig(TIM2, TIM_IT_Update,DISABLE);
#define EN_Time2_interrupt()       TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);



extern void init_three_phase();
extern uint8_t Startup( uint16_t duty );



