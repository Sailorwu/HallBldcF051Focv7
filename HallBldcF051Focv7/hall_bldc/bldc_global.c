#include "stm32f0xx.h"


uint8_t TimeCnt=0 ; 
uint8_t dir_fg=0;
uint8_t step=0; 
uint8_t Ck_Hall_Cnt=0; 
uint8_t laststep=0; 
uint8_t DirCnt=0; 
uint8_t Resatrt_Cnt=0;
uint8_t Ck_Ok_Cnt=0;

uint16_t PwmDuty=0;
uint16_t PhaseTime=0;


uint8_t error_fg=0;
uint8_t restartup_fg=0; 
uint8_t brake_fg=0; 
uint8_t comm_fg=0;
uint8_t delay_1ms=0;