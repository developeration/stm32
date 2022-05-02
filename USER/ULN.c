#include "ULN.h"

void ULN_GPIO_Config(void)
{		
		/*????GPIO_InitTypeDef??????*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*???????GPIO????*/
		RCC_APB2PeriphClockCmd( IN1_GPIO_CLK | IN2_GPIO_CLK | IN3_GPIO_CLK | IN4_GPIO_CLK , ENABLE);
		
	 /*??????GPIO??*/
		GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;	
		/*?????????????*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*???????50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*?????,???GPIO*/
		GPIO_Init(IN1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*??????GPIO??*/
		GPIO_InitStructure.GPIO_Pin = IN2_GPIO_PIN;
		/*?????,???GPIO*/
		GPIO_Init(IN2_GPIO_PORT, &GPIO_InitStructure);
		
		/*??????GPIO??*/
		GPIO_InitStructure.GPIO_Pin = IN3_GPIO_PIN;
		/*?????,???GPIOF*/
		GPIO_Init(IN3_GPIO_PORT, &GPIO_InitStructure);
		
		/*??????GPIO??*/
		GPIO_InitStructure.GPIO_Pin = IN4_GPIO_PIN;
		/*?????,???GPIOF*/
		GPIO_Init(IN4_GPIO_PORT, &GPIO_InitStructure);
		
		//???????????
    IN1_LOW;
    IN2_LOW;
    IN3_LOW;
    IN4_LOW;		
}

/*
ULN_GPIO_Config();
	u16 DelayTime = 3;
	while(1){
		
		 
		IN1_HIGH;
		Delay_Ms(DelayTime);
		IN1_LOW;
		IN2_HIGH;
		Delay_Ms(DelayTime);
		IN2_LOW;
		IN3_HIGH;
		Delay_Ms(DelayTime);
		IN3_LOW;
		IN4_HIGH;
		Delay_Ms(DelayTime);
		IN4_LOW; 
	}
*/
