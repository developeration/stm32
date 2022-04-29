/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_MA_LED
#define __STM32F10x_MA_LED

#include "stm32f10x.h"
#include "delay.h"
#define ON 0
#define OFF 1

#define LEDOK(a) if(a) \
		GPIO_SetBits(GPIOB,GPIO_Pin_12); \
  else \
		GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define LEDFAIL(a) if(a) \
	GPIO_SetBits(GPIOB,GPIO_Pin_14); \
else \
	GPIO_ResetBits(GPIOB,GPIO_Pin_14)
void LED_GPIO_Config(void);


void FlashLedOK(int num);
void FlashLedFail(int num);
#endif /* __STM32F10x_CONF_H */

