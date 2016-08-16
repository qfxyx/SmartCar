#ifndef _MOTOR_H_

#define _MOTOR_H_
#include <hidef.h>      
#include "derivative.h"
#include "PIDcontrol.h"
#include "motor_zhuansu_measure.h" 

extern unsigned char judge_line;
//extern unsigned int pwm; 
extern float ave_motor;
extern int iError, iIncpid;


void motor_driver(void);
//void speed(void);
//int Add_pid(int NextPoint);//ÔöÁ¿Ê½PID


#endif