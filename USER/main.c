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
#include "usart1.h"
#include "usart2.h"
#include "string.h" 
#include "sim900a.h"
#include "led.h"

void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);
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
	//USART1_Init(115200);	//初始化串口1 GPS
	USART2_Init(9600);	 //初始化串口2 SIM
	USART3_Init(9600);	//LOG信息
	LED_GPIO_Config();   // LED 指示灯
	//clrGPSStruct();
	UART3SendString((u8 *)"System Init Finished\r\n",strlen("System Init Finished\r\n"));
	res=1;
	while(res)
	{
		LED(ON);
		delay_ms(100);
		LED(OFF);
		delay_ms(100);
		LED(ON);
		delay_ms(100);
		LED(OFF);
		res = GSM_Dect();
		delay_ms(2000);
	}
  
	//res = SIM900A_GET_LOCATION();
	//UART3SendString(SIM_Location,1024);
	//res = SIM900A_CONNECT_SERVER_SEND_INFOR((u8*)"win-ad.eastus.cloudapp.azure.com",(u8*)"9000");
	//SIM900A_CONNECT_SERVER_SEND_INFOR
  //SIM900A_GPRS_SEND_DATA	
	while(1)
	{
		LED(ON);
		//parseGpsBuffer();
		//printGpsBuffer();
		res = SIM900A_GET_LOCATION();
		if(res){
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			continue;
		}
		//UART3SendString(SIM_Location,1024);
		res = SIM900A_CONNECT_SERVER_SEND_INFOR((u8*)"win-ad.eastus.cloudapp.azure.com",(u8*)"9000");	
		if(res){
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			delay_ms(100);
			LED(ON);
			delay_ms(100);
			LED(OFF);
			continue;
		}
		UART3SendString(SIM_Location,1024);
		SIM900A_GPRS_SEND_DATA(SIM_Location);
		//UART3SendString(SIM_Location,1024);
		LED(OFF);
		
		delay_ms(5000);
		delay_ms(5000);
		delay_ms(5000);
		delay_ms(5000);
		delay_ms(5000);
		
	}
}
 

void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
		printf(Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//½âÎö´íÎó
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//»ñÈ¡UTCÊ±¼ä
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//»ñÈ¡UTCÊ±¼ä
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//»ñÈ¡Î³¶ÈÐÅÏ¢
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//»ñÈ¡N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//»ñÈ¡¾­¶ÈÐÅÏ¢
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//»ñÈ¡E/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//½âÎö´íÎó
				}
			}


		}
	}
}

void printGpsBuffer()
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
		printf("Save_Data.UTCTime = ");
		printf(Save_Data.UTCTime);
		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("Save_Data.latitude = ");
			printf(Save_Data.latitude);
			printf("\r\n");


			printf("Save_Data.N_S = ");
			printf(Save_Data.N_S);
			printf("\r\n");

			printf("Save_Data.longitude = ");
			printf(Save_Data.longitude);
			printf("\r\n");

			printf("Save_Data.E_W = ");
			printf(Save_Data.E_W);
			printf("\r\n");
		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}
