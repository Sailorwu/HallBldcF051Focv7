

#include "bldc_hall_delay.h"
#include "bldc_hall_exti.h"
#include "bldc_hall_adc.h"
#include "bldc_hall_timer.h"


#include "bldc.h"
#include "bldc_const.h"



extern uint8_t TimeCnt ; 
extern uint8_t dir_fg;
extern uint8_t Ck_Hall_Cnt; 
extern uint8_t error_fg;
extern uint8_t brake_fg; 
extern uint8_t restartup_fg;


extern uint8_t delay_1ms;
extern uint8_t Mode; 


extern uint8_t step; 
extern uint8_t laststep; 
extern uint8_t dir_fg;
extern uint8_t TimeCnt ; 
extern uint8_t error_fg;
extern uint8_t brake_fg; 
extern uint8_t Ck_Hall_Cnt; 


extern uint16_t PhaseTime;

extern uint16_t PwmDuty;