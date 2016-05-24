
#ifndef BLDC_HALL_H
#define	BLDC_HALL_H

//********************************���Ŷ���**********************************//


//HALL
#define  A_Hall_PIN     GPIO_Pin_6
#define  B_Hall_PIN     GPIO_Pin_7
#define  C_Hall_PIN     GPIO_Pin_8

#define  A_Hall_PORT    GPIOC
#define  B_Hall_PORT    GPIOC
#define  C_Hall_PORT    GPIOC




//PWM
#define  A_Hin_PIN              GPIO_Pin_8
#define  A_Hin_PIN_Source       8
#define  A_Lin_PIN              GPIO_Pin_13

#define  B_Hin_PIN              GPIO_Pin_9
#define  B_Hin_PIN_Source       9
#define  B_Lin_PIN              GPIO_Pin_14

#define  C_Hin_PIN              GPIO_Pin_10
#define  C_Hin_PIN_Source       10
#define  C_Lin_PIN              GPIO_Pin_15

#define  A_Hin_PORT     GPIOA 
#define  A_Lin_PORT     GPIOB
#define  B_Hin_PORT     GPIOA
#define  B_Lin_PORT     GPIOB
#define  C_Hin_PORT     GPIOA
#define  C_Lin_PORT     GPIOB

//X = 0,1,...15
#define GPIO_Pin(X)  GPIO_Pin_##X
//X = A,B,C,D,F
#define GPIO_Port(X) GPIO##X

#define Ap_Port GPIO_Port(A)
#define Ap_Pin  GPIO_Pin(8)
#define Ap_Pin_Source 8

#define An_Port GPIO_Port(B)
#define An_Pin  GPIO_Pin(13)
#define An_Pin_Source 13

#define Bp_Port  GPIO_Port(A)
#define Bp_Pin   GPIO_Pin(9)
#define Bp_Pin_Source 9

#define Bn_Port  GPIO_Port(B)
#define Bn_Pin   GPIO_Pin(14)
#define Bn_Pin_Source 14

#define Cp_Port  GPIO_Port(A)
#define Cp_Pin   GPIO_Pin(10)
#define Cp_Pin_Source 10

#define Cn_Port  GPIO_Port(B)
#define Cn_Pin   GPIO_Pin(15)
#define Cn_Pin_Source 15
     





#define  DirCtrl_PORT  GPIOA
#define  DirCtrl_PIN   GPIO_Pin_13


#define  DirCtrl       GPIO_ReadInputDataBit(DirCtrl_PORT,DirCtrl_PIN)



#define Bat_CH                   ADC_Channel_4
#define Cur_CH                   ADC_Channel_1
#define Speed_CH                 ADC_Channel_13
#define Ntc_CH                   ADC_Channel_5
//********************************end**************************************//

//********************************�궨��ֵ**********************************//

#define  Forward      0        //����ת
#define  Reverse      1        //����ת

//********************************end**************************************//

//********************************��������**********************************//

#define  PWM_MAX      800
#define  STARTUP_DUTY PWM_MAX/5
#define  PRO_DUTY     ( PWM_MAX * 3 ) / 10
#define  PWM_ADD_NUM  2
#define  START_TIME   12500    //8usΪʱ��

#define  LOW_BAT1_TH    1488      //�͵�ѹ���� 16.5V  ������ѹ�ж�
#define  LOW_BAT2_TH    1312      //�͵�ѹ���� 14.5V  ���е�ѹ�ж�

#define  MAX_CUR1_TH    160     //1���������� 25A     10     1A 50m 270
#define  MAX_CUR2_TH    222       //2���������� 50A     20
#define  MAX_CUR3_TH    888       //3���������� 80A     32
#define  C_CUR_TH       185        //�㶨����   15A     6

#define  HIGH_TEMP1_TH   647     //����   �����¶��ж�    50C   270
#define  LOW_TEMP1_TH    70     //����   �����¶��ж�    -10C   862
#define  HIGH_TEMP2_TH   1134   //����   �����¶��ж�    75C   130   
#define  LOW_TEMP2_TH    70     //����   �����¶��ж�    -10C   862

#define  ADJ_RUN_TH     300      //�ɵ����迪���������  0.1V  1004 

//#define  ADJ_RUN_TH     2820      //�ɵ����迪���������  0.1V  1004 

#define  Speed_Low      3000    //����ٶ�
#define  Speed_High     20000   //����ٶ�
#define  Pole_Pairs	2	//������

#define  Speed_Low_TH   (uint16_t)( (12500) / ( (Speed_Low / 100 ) * Pole_Pairs ) )
#define  Speed_High_TH  (uint16_t)( (12500) / ( (Speed_High / 100 ) * Pole_Pairs ) )



//********************************end**************************************//


#endif	/* BLDC_HALL_H */

