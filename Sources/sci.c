#include "sci.h"
unsigned char data_receive=0;
unsigned char data_temp[4]=0;

/*************************************************************/
/*                       串口0初始化函数                     */
/*************************************************************/
void SCI_Init() 

{ 
          SCI0BD=48000000/16/115200;              //115200bps     Baud Rate=BusClock/(16*SCIBD) 
         //SCI0BD=261;              //19200bps     Baud Rate=BusClock/(16*SCIBD) 
         //SCI0BD=521;
         SCI0CR1=0;              //正常8 位模式，无奇偶校验 
         SCI0CR2=0X2C;           //发送允许  接受中断允许 
} 

void SCI_Init1()
{
  SCI1BD = 48000000/16/9600;   //设置SCI0波特率为9600
  SCI1CR1 = 0x00;        //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI1CR2 = 0x2c;        //允许接收和发送数据，允许接收中断功能
}

unsigned char SCI_receive(void) 
{
  while(!SCI1SR1_RDRF);          //等待发送数据寄存器满
  return(SCI1DRL);
}


/*************************************************************/
/*                        串口0发送函数                      */
/*************************************************************/
void SCI_Write(unsigned char SendChar) 
{ 
                                         
      while (!(SCI0SR1&0x80)); 
      SCI0DRH=0; 
      SCI0DRL=SendChar; 
} 

/*************************************************************/
/*                 向电脑串口发送所采集的图像                */
/*************************************************************/
void Process_Data(void) 
{ 
   unsigned char i,j; 
   
   for(i=0;i<ROW;i++) 
   { 
      for(j=0;j<COLUMN;j++) 
       { 
          if(Image_Data[i][j] == 0xFF) 
            SCI_Write(0xFE); 
          else
            SCI_Write(Image_Data[i][j]); 
      } 
      //SCI_Write(0x0D); 
      //SCI_Write(0X0A);    
   } 
   SCI_Write(0xFF);
} 

/*************************************************************/
/*                 向电脑串口发送所采集的图像                */
/*************************************************************/
void Process_Erzhi(void) 
{ 
   unsigned char i,j; 
   
   for(i=0;i<ROW;i++) 
   { 
      for(j=0;j<COLUMN;j++) 
       { 
            SCI_Write(ImageBuffer[i][j]) ; 
      } 
      //SCI_Write(0x0D); 
      //SCI_Write(0X0A);    
   } 
   SCI_Write(0xFF);
} 

/*************************************************************/
/*                 向电脑串口发送中心线数组                */
/*************************************************************/
//功能：将中心线数组发送到电脑上位机
void Process_zx(void) 
{ 
   unsigned char i;
   unsigned char temp;
   SCI_Write(0xff);  
   for(i=0;i<ROW;i++) 
   { 
      temp = (char)Image_Center[i];
      SCI_Write(temp);   
         
   } 
}   


/***************************************************************
                   向电脑发送各个参数
****************************************************************
功能：发送参数*/
void Process_canshu(void)
{ 
  SCI_Write(0xff);
  SCI_Write(big_curve_c);
  
  SCI_Write(0xaa);
  SCI_Write(judge_line);
  
  SCI_Write(0xbb);
  //SCI_Write(angle);
  
  SCI_Write(0xcc);
  //SCI_Write(left_turn[2]);
  
  SCI_Write(0xdd);
}

/*************************************************************/
/*                     串口中断接收函数                      */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void receivedata(void) 
{
    data_receive = SCI_receive();
    
    
    data_temp[3] = data_temp[2];
    data_temp[2] = data_temp[1];
    data_temp[1] = data_temp[0];
    data_temp[0] = data_receive;
    
    
    
   
    
}
#pragma CODE_SEG DEFAULT