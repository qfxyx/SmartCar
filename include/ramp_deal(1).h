#ifndef _RAMP_DEAL_H_
#define _RAMP_DEAL_H_

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
//#include "MC9S12XS128.h"


//INTCR_IRQEN=0;      //使能IRQ外部中端口，可以把该语句放入
                   //总的系统初始化函数中，没那么分散
                   

void Speed_less(void); 
                   
#endif