/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_MA_LED
#define __STM32F10x_MA_LED

#include "stm32f10x.h"

#define ON 0
#define OFF 1

#define LED(a) if(a) \
		GPIO_SetBits(GPIOB,GPIO_Pin_14); \
  else \
		GPIO_ResetBits(GPIOB,GPIO_Pin_14)

void LED_GPIO_Config(void);

#endif /* __STM32F10x_CONF_H */

