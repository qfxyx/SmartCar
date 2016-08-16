#include "system.h"
/*************************************************************/
/*                        初始化PLL函数                      */
/*************************************************************/
void PLL_Init(void) {

    CLKSEL=0X00;			                	//disengage PLL to system
    PLLCTL_PLLON=1;			                //turn on PLL
    SYNR =0xc0 | 0x05;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;                       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=96MHz;
    _asm(nop);                          //BUS CLOCK=48M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	          //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		                //engage PLL to system; 

}  

void Rampinterrupt_init(void) 
{
   PPSJ_PPSJ0 = 1 ;      //PJ0口触发方式，=1下拉，上升沿触发，=0上拉，下降沿触发
   PIEJ_PIEJ0 = 1 ;      //PJ0中断使能 ， =1可以中断， =0 不可以中断
}


 //--------PID参数初始化--------//
/*void PID_init(void) 
{
  //pid->SetPWMDTY = 0;  
  //pid->CurrentError = 0;  //Error[0]
  pid->LastError = 0;  //Error[-1]
  pid->PrevError = 0;  //Error[-2]
  pid->LastUk = 0;   //上一控制量
  //PID系数请修改下面三句的数值
  pid->Proportion = 0;   //比例常数Proportion Const
  pid->Integral = 0;     //积分常数Integral Const
  pid->Derivative = 0;   //微分常数Derivative Const
}   */


/*************************************************************/
/*                      IO口初始化函数                       */
/*************************************************************/

void IO_Init(void) 
{ 

         DDRA = 0X00;             //端口A配置成输入
         DDRB = 0XFF;             //
         DDRK = 0XB7;
         DDRE &= 0X63;          //E端口中，E7、E4、3、2为输入
         PORTB = 0X00;  
} 

void PWM_Init(void)    //PWM初始化，包括电机和舵机
{     
    //SB,B for ch2367
    //SA,A for ch0145         
    PWMCTL_CON45=1;  //4和5联合成16位PWM
    PWMCTL_CON01=1;  //01和45控制电机
    PWMCTL_CON23=1;  //2和3联合成16位PWM，控制舵机
   
    PWMCAE_CAE5=0; //选择输出模式为左对齐输出模式
    PWMCAE_CAE1=0;
    PWMCAE_CAE3=0; //选择输出模式为左对齐输出模式
    
    PWMCNT45=0;  //计数器清零
    PWMCNT01=0;
    PWMCNT23=0;  //计数器清零
    
    PWMPOL_PPOL5=1;
    PWMPOL_PPOL1=1; //先输出高电平，计数到DTY时，反转电平
    PWMPOL_PPOL3=1; //先输出高电平，计数到DTY时，反转电平
    
    PWMPRCLK=0X31; //clockA2分频,clockA=24MHz，clockB进行8分频,clockB=busclock/4=6MHz
    PWMSCLB=3; //对clock SB 进行2*3=6分频SB clock=clockB/6=1MHz;
    PWMCLK_PCLK1=0; //选择clock  A做时钟源
    
    PWMCLK_PCLK5=0;  //选择clock A做时钟源
    PWMCLK_PCLK3=1; //选择clock SB做时钟源
    
    PWMPER45=2000; //周期 25KHz
    PWMPER01=2000;
    PWMPER23=20000; //周期20ms； 50Hz
    
    PWMDTY01=48;
    PWMDTY45=48;  //设置初始电机速度为0
    PWMDTY23=1500;  //设置初始舵机角度为0
     
    PWME_PWME1=1; 
    PWME_PWME5=1;
    PWME_PWME3=1; 
    
    
    
} 


/*************************************************************/
/*                     延时函数                              */
/*************************************************************/

void delays(unsigned int m){

 while(m--);
 
 }
 
 