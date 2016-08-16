
//******************author:tan**************************************************
//******************input:中心数组 *********************************************
//******************output:判断直道还是弯道；转的方向；转的角度*****************
#include "camera_deal.h"

#define square_c  50


unsigned char angle=0;        //转的角度
unsigned char judge_line;     //判断直道还是弯道，1为直道
unsigned char big_curve_c;    //大弯道标志 
unsigned int square=0;
unsigned int base;              //基准
unsigned char slow_speed_flag;  //减速标志
unsigned char left_flag;       //左转标志
unsigned char right_flag;      //右转标志
unsigned char turn_flag;       //转弯标志
unsigned char far_temp;
unsigned char mid_temp;
unsigned char big_curve_turn_flag;


//************作用：取绝对值****************************************************
//************输入：较远端的中心（a） ；较近端的中心（b）；第i 条线判断的方向***
//************输出： 第i 条线的斜率和方向*************************************** 
unsigned int Abs(unsigned int a,unsigned int b)//Absolute value
{
	unsigned int value;
	
	if(a<=b) 
	{
	    value=b-a;      //绝对值 
	    left_flag = 1;
	    right_flag = 0;
  }
	else 
	{
	    value=a-b;
	    right_flag = 1;
	    left_flag =0;
	}
	
	return(value);
}

/**************************************************************************
                            根据偏差求偏转角
***************************************************************************
功能：使用查表法，求偏转角*/
unsigned char angle_x1(unsigned int x) 
{
  const unsigned char angle_temp[6]={11,13,14,16,18,19};
  return (angle_temp[x-8]);
}

unsigned char angle_x2(unsigned int x) 
{
  const unsigned char angle_temp2[7]={19,21,24,28,33,37,42};
  return (angle_temp2[x]);
}

//***********图像处理程序*******************************************************
//***********输入：中线数组*****************************************************
//***********输出: 判断直道还是弯道；转的方向；转的角度*************************
void c_deal(void)
{
   unsigned int offset;
   unsigned char angle_tp;

   //若 两 条线的方向相同，则以近端的角度决定舵机转角：否则以近端点与远端点的连线角度决定舵机 
   offset = Abs(Image_Center[middle],base);
   angle_tp = angle_x1(offset);
   
   
   if (angle_tp <= 3)             
   {
      judge_line = 1;                         //straightaway直道 
      slow_speed_flag = 0;
   } 
   else
   {
      if (left_flag == 1)
        turn_flag = 1;                     //turn_flag=1  左转
      else 
      {
        if (right_flag == 1)
           turn_flag = 0;                  //turn_flag=0  右转
      }
      
      judge_line = 0;                         //curve
      
      angle = angle_tp;
   }
}

//****************************大弯道判断**************************************** 
void big_curve(void) 
{
    unsigned char i,j,k,edge,angle1,next_angle=0,big_angle;
    unsigned int x,average=0,sum=0,valve_temp0=0, valve_temp1=0,valve_temp2=0;
    unsigned int offset1,valve_temp3=0,base_temp;
    
    for (i=ROW-1; i>(ROW-6); i--)
	     sum += Image_Center[i];
	  base_temp = sum/5;                //以前五行的平均值为基准
	  
	  if (base_temp>=25 && base_temp<=55)
	     base = base_temp;
	  else
	     base = (40+base_temp)/2;
	  
	  for(x=0; x<ROW; x++)
	    {
	    average += Image_Center[x];
	    } 
    average = average/ROW;          //求平均值
    
    for(x=0; x<ROW; x++)
      {
      	square += ((average-Image_Center[x])*(average-Image_Center[x]));
      }  
    square = square/ROW;            //求均方差
    
    if(square > square_c)
    {
   	  big_curve_c = 1;      //判定为大弯道 ，减速
   	  judge_line = 0;
   	  slow_speed_flag = 1;
   	  
   	  for(k=1; k<ROW; k++)              //取远点中线
   	  {
   	    valve_temp3 = Abs(Image_Center[k],base);
   	    if (valve_temp3>=9 && valve_temp3<=12) 
   	    {
   	      edge = k;
   	      far_temp = edge;
   	      break;
   	    }
   	  }
   	  
   	  for(j=35; j>edge; j--)               //取中间中线
   	  {  
   	    valve_temp0 = Abs(Image_Center[j],base);
 
   	    if (valve_temp0 > 2)
   	    {
   	       mid_temp = j-1;
   	       break;
   	    } 
   	  } /*
   	  if (big_curve_turn_flag == 1) 
   	  {
   	     big_curve_turn_flag =0;
   	     angle = next_angle;
   	  }
   	  */
   	  
   	  
   	  if (far_temp>= 14 && far_temp<=18) 
   	  {
   	    offset1 = Abs(far_temp, mid_temp); 
   	    angle1 = angle_x2(offset1);
   	    judge_line = 0;
   	    big_curve_turn_flag =1;
   	    big_angle = angle1/2;
   	    next_angle = angle1/2;
   	    
   	    if (left_flag == 1)
           turn_flag = 1;                     //turn_flag=1  左转
        else 
        {
        if (right_flag == 1)
           turn_flag = 0;                  //turn_flag=0  右转
        }
        angle = big_angle;
   	  } 
   	  else
   	    if (far_temp < 14) 
   	    {
   	       judge_line = 1;
   	    }
    } 
    else
  	{
	     big_curve_c = 0; 
       c_deal(); 
    }
}



