#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 ;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_14);
	
	
}


void FlashLedOK(int num){
	int i = 0;
	for (i = 0 ; i < num ; i++)
	{
		LEDOK(ON);
		Delay_Ms(150);
		LEDOK(OFF);
		Delay_Ms(150);
	}
}

void FlashLedFail(int num){
	int i = 0;
	for (i = 0 ; i < num ; i++)
	{
		LEDFAIL(ON);
		Delay_Ms(150);
		LEDFAIL(OFF);
		Delay_Ms(150);
	}
}
