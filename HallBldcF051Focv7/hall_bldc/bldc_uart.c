
void init_uart1()
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource14, GPIO_AF_1);
  
  //以上选择了输入输出值
  USART_InitTypeDef  USART_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  USART_InitStruct.USART_BaudRate = 115200; 
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_StopBits = 1;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  
  USART_Init(USART1,&USART_InitStruct);

  USART_Cmd(USART1, ENABLE);
  
}

void send_data32(uint32_t send)
{
      int i =4;
      send |= 0xf0000000;
      while(i != 0)
      {
        if(USART_GetFlagStatus(USART1,USART_FLAG_TC) == SET)
        {  
           i--;  
           USART_SendData(USART1,((send >> (i*8))&0xFF));
        }
      }
}

void send_data16(uint16_t send)
{
      int i =2;
      send |= 0xf000;
      while(i != 0)
      {
        if(USART_GetFlagStatus(USART1,USART_FLAG_TC) == SET)
        {  
           i--;  
           USART_SendData(USART1,((send >> (i*8))&0xFF));
        }
      }   
}

void UART1_Send_Str(const unsigned char *s)
{
   unsigned char c;                        
   c = *s;
   while(c != '\0')                                               
   {
       USART_SendData(USART1,*s); 
       s++;         
       c = *s;
       while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
   }
}