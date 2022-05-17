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



#define CAT4GPOWERON()	GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define CAT4GPOWEROFF()	GPIO_ResetBits(GPIOB,GPIO_Pin_8)
void SystemSleep(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
***/
int main(void)
{

	u8 res=1;
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	Delay_Init();	    	 //延时函数初始化
	LED_GPIO_Config();   // LED 指示灯
	
	while(RTC_Init()){FlashLedFail(1);Delay_Ms(2000);}		//RTC初始化	，一定要初始化成功

	
	while(1)
	{
		int oo = 0;
		CAT4G_POWER_Config();
		CAT4GPOWERON();
		USART2_Init(115200);	 //初始化串口2 SIM
		USART3_Init(9600);	//LOG信息	
		Delay_Ms(500);
		res=1;
		for(oo=0;oo < 5;oo++){
			res = GSM_Dect();
			if(res){ Delay_Ms(1000);} else{ break;}
		}
		
		if(res){ FlashLedFail(2); CAT4GPOWEROFF();SystemSleep();continue; }else {FlashLedOK(1);}
		res = SIM900A_GET_LOCATION();
		if(res){ FlashLedFail(4); Delay_Ms(2000);continue; }else {FlashLedOK(1);}
		res = SIM900A_CONNECT_SERVER_SEND_INFOR((u8*)"wix.eastus.cloudapp.azure.com",(u8*)"9000");	
		if(res){ FlashLedFail(8); Delay_Ms(2000);continue; }else {FlashLedOK(1);} 
		SIM900A_GPRS_SEND_DATA(SIM_Location); 
		FlashLedOK(1);
		CAT4GPOWEROFF();
		for(oo = 0;oo < 8 ; oo++){ 
			SystemSleep();
			FlashLedOK(1);
		}
	 
	}
	
}

void SystemSleep(void){
	SysTickEnableOrDisable(DISABLE);      // 每1ms产生中断，可能导致Stop模式进入被忽略，从而进不去stop模式。
	RTC_ClearITPendingBit(RTC_IT_OW | RTC_IT_ALR);		//清闹钟中断
	//PWR_Regulator_ON  PWR_Regulator_LowPower
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);     // 进入stop模式
	//**************被唤醒后*******************
	RCC_HSEConfig(RCC_HSE_ON);	//由于唤醒后，系统时钟源变成了HSI,导致了系统时间紊乱，其他外设不能正常工作，所以要配置HSE.==
	SystemInit();
	SysTickEnableOrDisable(ENABLE);   // 要用到delay_ms函数
	Delay_Init();	    	 //延时函数初始化
	LED_GPIO_Config();   // LED 指示灯 
}
