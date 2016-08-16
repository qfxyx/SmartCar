 #include "ramp_deal(1).h"

  /*////////////////////////////////////////////////////////////
  //红外检测距离20cm左右，高2cm以上，最好在上面遮一块挡板，防室外光
  ,红外模块三条线分别接地，接5v电压，外部中断口PT2   */
  //////////////////////////////////////////////////////////////
  ////////////////////////////////////////
  //camera-deal.c中修改一点，使能PT2
  //用该口作为中断口
  
  
void Speed_less(void) 
{
      PWMDTY45 = 300;
      PWMDTY01 = 48;    //数值先随便设置一个
      
}//调用减速函数，由华生那边提供,具体要减多少，要实测

#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt VectorNumber_Vtimch2  PT2_Interrupt()
{
 
   PIFJ_PIFJ0 = 1;  //清楚中断标志位
   Speed_less(); 
   
}

//#pragma CODE_SEG DEFAULT