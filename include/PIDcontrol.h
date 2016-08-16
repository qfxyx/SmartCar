#ifndef _PIDcontrol_H_
#define _PIDcontrol_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "system.h"

//-----外部变量-----//


//-----函数声明-----//

//void timer_init(void);  // 定时器中断初始化
void Add_pid(int NextPoint);//增量式PID
//void PIDInit(void);
void PID_Curve(void);
void PID_Line(void);

#endif