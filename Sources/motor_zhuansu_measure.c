#include "motor_zhuansu_measure.h"

float motor_n1=0,motor_n2=0;
float ave_motor = 0; 
unsigned int pulsenum1,pulsenum2,a1,a3;
char di,gao;

/****************************************************/
/*                     测速函数                     */
/*                  信号接口为T7口                  */
/****************************************************/
void speed_measure1() 
{ 
  unsigned int data1,data2;
 
  unsigned int i;
  float n=457.1429;  //n的值随着时间的不同而改变,n=45714.29/累加脉冲的时间长度
  
  TFLG1_C2F = 1;  //清除该位
   
   TC2=TCNT+100;
   data1 = PACNT; //把脉冲累加计数器当前值赋给data1，对比之前的程序改了，因为data2默认初始化值为随机数

    for(i=0;i<3;i++)          //延时0.1ms
    {
        while(TFLG1_C2F == 0);  
        TFLG1_C2F = 1;  //清除该位
        TC2 =TCNT+100;    //TCNT为定时器计数寄存器  
    }
    
    data2 = PACNT;  //脉冲累加计数寄存器
    pulsenum1 = data2-data1;   //计算100us采集的上升沿的数量(float)
    motor_n1= n * pulsenum1;    //返回转速n
} 

void speed_measure2 () 
{ 
  unsigned int data1,data2;
 
  unsigned int i;
  float n=457.1429;  //n的值随着时间的不同而改变,n=45714.29/累加脉冲的时间长度
  //float n=10;
  TFLG1_C2F = 1;  //清除该位
   
   TC2=TCNT+100;
   data1 = PACNT; //把脉冲累加计数器当前值赋给data1，对比之前的程序改了，因为data2默认初始化值为随机数

    for(i=0;i<3;i++)          //延时0.1ms
    {
        while(TFLG1_C2F == 0);  
        TFLG1_C2F = 1;  //清除该位
        TC2 =TCNT+100;    //TCNT为定时器计数寄存器  
    }
    
    data2 = PACNT;  //脉冲累加计数寄存器
    pulsenum2 = data2-data1;   //计算100us采集的上升沿的数量(float)
    motor_n2= n * pulsenum2;    //返回转速n
} 

void speed(void)
{
  speed_measure1();
  speed_measure2();
  ave_motor = (motor_n1 + motor_n2) / 2;
  //pwm = (int)(93.5427 + 0.135269 *ave_motor);   //当前速度PWM
  a1 = (int)ave_motor;
  di = (char)a1;    //转速低8位
  a3 = a1 >> 8;     //右移8位
  gao = (char)a3;    //转速高8位
}



/*
总体思路是：
目的：求一个脉冲的周期T
我们设定一段时间t(100us)
T = t / 脉冲个数

而t值的设定要在单片机里体现就是先设定让计数器从0到计满的时间为 tt(时钟周期)，而我们需要的时间是t,那就要计满t/tt 次
就是上面设的时钟周期为1/3us,计满300次就是100us了，而计满300次就是3 * 100 次，所以for循环3次，
pulsenum就是脉冲数，后来计数器值 - 初始计数器值
*/

