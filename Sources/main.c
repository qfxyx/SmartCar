/********************************************************************************/
/********************************************************************************
作者：jnu_fangze
时间：2014/8/18

                  
上位机设置
  波特率   115200
  图像宽度 80
  图像高度 40

接线：
      S0(单片机上的RXD)  -----> 串口模块TXD:绿
      S1(单片机上的TXD)  -----> 串口模块RXD：白
      GND(单片机上的地)  -----> 串口模块GND      //如果单片机和串口使用不同电源，也需要共地
      波特率115200
      
      A0-A7  -----------------> 摄像头模块 (数据)Y0 - Y7
      T0     -----------------> 摄像头模块 (行中断)HREF
      T1     -----------------> 摄像头模块 (场中断)VSYN
      PE7 -----------------------摄像头奇偶场信号
      
  舵机：
      P3------------------------白色线
  电机：
      P1------------------------第一路
      P5------------------------第二路 
  905：
      TXEN------PORTK_PK0;  TRX_CE------PORTK_PK1 ;  PWR ------PORTK_PK2;	
      MISO------PORTK_PK3;  MOSI------PORTK_PK4;    SCK ------PORTK_PK5;
      CSN ------PORTK_PK7;  AM  ------PORTE_PE2;    DR  ------PORTE_PE3;
      CD  ------PORTE_PE4;  AM,DR,MISO,CD 为输入，其余为输出           
*********************************************************************************
*********************************************************************************/
#include <hidef.h>          
#include "derivative.h"         
#include <mc9s12xs128.h>
#include "system.h" 
#include "sci.h"
#include "mydefine.h"
#include "ccd.h"
#include "duoji.h"
#include "motor.h"
#include "camera_deal.h"
#include "nrf905.h"
#include "motor_zhuansu_measure.h"
#include "PIDcontrol.h"

extern unsigned char SampleFlag;


/*************************************************************/
/*                          主函数                           */
/*************************************************************/
void main(void) 
{ 
  
 /* put your own code here */ 
   PLL_Init();  //初始化锁相环
   CCD_Init();  //初始化中断
   IO_Init();   //初始化IO口
   SCI_Init();  //初始化串口
   SCI_Init1();
   PWM_Init();  //初始化PWM   
   nRF905Init();//初始化NRF905
   Config905(); //配置NRF905
   //PIDInit();
   //Rampinterrupt_init();

  
 
  EnableInterrupts; 
  
  for(;;) 
  {
      if(data_temp[3]==0xA5 && data_temp[2]==0x5A&&data_temp[1]==0x49&&data_temp[0]==0xAA)
      {
       PWMDTY01 = 0;
       PWMDTY45 = 0; 
      }
      else
      {
          if(SampleFlag==0) 
            { 
              PORTB=0X00;
              Process_Data();           //向电脑串口发送所采集的图像
              
              SeachCenter();
              //Process_Erzhi();       //发送二值化后的图像数组
      		    //Process_zx();         //发送中线数组
              big_curve();
              //Process_canshu();   //发送参数
              
              //Send_data();
              
              //Send_zhongxian();
             
              //duoji_driver();
              
              motor_driver(); 
              
                                         
            } 
          else 
            {
            PORTB=0XFF;
            }
      }
   }   
 
           //   _FEED_COP(); /* feeds the dog */ 

          /* loop forever */ 
         /* please make sure that you never leave main */ 
} 

