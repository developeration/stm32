#ifndef __URTC_X_H
#define __URTC_X_H

#include "sys.h"

u8 RTC_Init(void);        //初始化RTC,返回0,失败;1,成功;

void SysTickEnableOrDisable(u8 status);
void RTC_NVIC_Config(void);





#endif


