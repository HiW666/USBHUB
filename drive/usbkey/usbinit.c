#include "stm32f10x.h"                  // Device header

void usbKey_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15| GPIO_Pin_13 |GPIO_Pin_14|GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_WriteBit(GPIOB,GPIO_Pin_13 |GPIO_Pin_14|GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7, Bit_SET);
  GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_RESET);
}