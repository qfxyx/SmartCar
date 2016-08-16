#include"motor.h"
int PWM_value=0,PWM_value1;
int motor_n; //n 为转速

/**********************************************************************
                         电机驱动
**********************************************************************
功能：驱动电机：直道和弯道
输入：直道或弯道标志
输出：控制电机的PWMDTY*/

void motor_driver(void) 
{
  //unsigned int dty;    //dty指占空比寄存器5的值，声明必须在禁止中断之前，否则会出错 
   /*
    PID_Line();
    speed();  //测速模块
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value1 + iIncpid;  //速度PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 1500)
      PWM_value = 1500;
    
    PWMDTY01 = PWM_value;
    PWM_value1 = PWM_value;
    PWMDTY45 = 48; 
    */
    PWMDTY01 = 1000;
    PWMDTY45 = 48; 
  
   /*
  if (judge_line == 1) 
  {
    //PWMDTY01 = 400;
    //PWMDTY45 = 48; 
    
    PID_Line();
    speed();  //测速模块
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value + iIncpid;  //速度PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 700)
      PWM_value = 700;
    
    PWMDTY01 = PWM_value;
    PWMDTY45 = 48; 
     
  } 
  else 
  {
    //PWMDTY01 = 300;
    //PWMDTY45 = 48;
    
    PID_Curve();
    speed();  //测速模块
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value + iIncpid;  //速度PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 700)
      PWM_value = 700;
    PWMDTY01 = PWM_value;
    PWMDTY45 = 48;
  }
  */
  
  //dty = (int)(44.552603319 + 0.16739543382 * motor_n);  //取整数
    
  //PWMDTY45=dty; //高电平时间
  //PWMDTY01=48;  //占空比为5%
    
  //PWME_PWME5=1; //使能通道5      
  //PWME_PWME1=1;
}