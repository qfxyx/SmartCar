#include "PIDcontrol.h" 
int iError, iIncpid;
typedef struct PID
{
int SetPoint; //设定目标 Desired Value
//long SumError; //误差累计
float Proportion; //比例常数 Proportional Const
float Integral; //积分常数 Integral Const
float Derivative; //微分常数 Derivative Const
int LastError; //Error[-1]
int PrevError; //Error[-2]
} PID;
static PID sPID;
static PID *sptr = &sPID;

//PID参数初始化
/*void PIDInit(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0; //比例常数 Proportional Const
sptr->Integral = 0; //积分常数Integral Const
sptr->Derivative = 0; //微分常数 Derivative Const
sptr->SetPoint = 2000;   //目标速度
}  */

//直道初始化PID参数
void PID_Line(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0.0055; //比例常数 Proportional Const
sptr->Integral = 0.005; //积分常数Integral Const
sptr->Derivative =0; //微分常数 Derivative Const
sptr->SetPoint = 1300;   //目标速度为6.2m/s,对应空载PWM大概为384，
}

//弯道初始化PID参数
void PID_Curve(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0.003; //比例常数 Proportional Const
sptr->Integral = 0.003; //积分常数Integral Const
sptr->Derivative = 0; //微分常数 Derivative Const
sptr->SetPoint = 1371;   //目标速度为5m/s,对应空载PWM大概为336
}


//nextpoint 实际速度
void Add_pid(int NextPoint)
{

//当前误差
iError = sptr->SetPoint - NextPoint;
//增量计算
iIncpid = (int)(sptr->Proportion * iError //E[k]项
- sptr->Integral * sptr->LastError //E[k－1]项
+ sptr->Derivative * sptr->PrevError); //E[k－2]项
//存储误差，用于下次计算
sptr->PrevError = sptr->LastError;
sptr->LastError = iError;
//返回增量值

}


