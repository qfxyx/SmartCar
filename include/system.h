#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
void PLL_Init(void);
void CCD_Init(void);
//void ECT_Init(void);
void IO_Init(void);
void PWM_Init(void);
void delays(unsigned int m);
void Rampinterrupt_init(void);
//void PID_init(void);  // PID参数初始化
/*
//-----PID参数结构体-----//
typedef struct {
  //int SetPWMDTY;    //设定的PWM占空比  
  //int CurrentError; //当前误差Error[0]
  int LastError;      //上一误差Error[-1]
  int PrevError;      //前一误差Error[-2]
  int LastUk;         //上一控制量
  int Proportion;     //比例常数Proportion Const
  int Integral;       //积分常数Integral Const
  int Derivative;     //微分常数Derivative Const
}PID;

static PID sPID;
static PID *pid = &sPID;
*/
 

#endif

