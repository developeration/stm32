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
#include "delay.h"
#include "usart2.h"
#include "string.h" 
#include "sim900a.h"
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
	USART2_Init(115200);	//初始化串口2 
	USART3_Init(9600);	//LOG信息
	UART3SendString("系统初始化完毕\r\n",strlen("系统初始化完毕\r\n"));
	res=1;
	while(res)
	{
		res=GSM_Dect();
		delay_ms(2000);
	}
  while (1)
  {
		delay_ms(2000);
		
		
		delay_ms(2000);
  }
}
 
