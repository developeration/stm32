/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rtc.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "string.h" 
#include "sim900a.h"
#include "led.h"
#include "rtc.h"

void parseGpsBuffer(void);
void printGpsBuffer(void);
void flashLed(int num);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
***/
int main(void)
{
	u8 res=1;
	
	delay_init();	    	 //延时函数初始化
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	LED_GPIO_Config();   // LED 指示灯
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{
		flashLed(1);
	}
	while(1)
	{
		int oo = 0;
		for(oo = 0;oo < 6 ; oo++){
			SysTickEnableOrDisable(DISABLE);      // 每1ms产生中断，可能导致Stop模式进入被忽略，从而进不去stop模式。
			RTC_ClearITPendingBit(RTC_IT_OW | RTC_IT_ALR);		//清闹钟中断
			//PWR_Regulator_ON  PWR_Regulator_LowPower
			PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);     // 进入stop模式
			/**************被唤醒后*******************/
			RCC_HSEConfig(RCC_HSE_ON);	//由于唤醒后，系统时钟源变成了HSI,导致了系统时间紊乱，其他外设不能正常工作，所以要配置HSE.==
			SysTickEnableOrDisable(ENABLE);   // 要用到delay_ms函数
			delay_init();	    	 //延时函数初始化
			LED_GPIO_Config();   // LED 指示灯
			flashLed(1);
		}
		
		
		USART2_Init(9600);	 //初始化串口2 SIM
		USART3_Init(9600);	//LOG信息		
		
		res=1;
		res = GSM_Dect();
		if(res){ flashLed(2); continue; }else {flashLed(1);}
		res = SIM900A_GET_LOCATION();
		if(res){ flashLed(4); continue; }else {flashLed(1);}
		res = SIM900A_CONNECT_SERVER_SEND_INFOR((u8*)"win-ad.eastus.cloudapp.azure.com",(u8*)"9000");	
		if(res){ flashLed(8); continue; }else {flashLed(1);} 
		SIM900A_GPRS_SEND_DATA(SIM_Location); 
		flashLed(1);
	 
	}
	
}
void flashLed(int num){
	int i = 0;
	for (i = 0 ; i < num ; i++)
	{
		LED(ON);
		delay_ms(20);
		LED(OFF);
		delay_ms(20);
	}
}

