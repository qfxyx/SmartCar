/***************************************************************************
作者：jnu_bin
时间：2014/8/15
内容：图像处理子程序
****************************************************************************/ 


#include "ccd.h"

#define  noise_min 5
#define  noise_max 50

unsigned char Image_Data[ROW][COLUMN]={0};       //所采集的图像二维数组
unsigned char ImageBuffer[ROW][COLUMN]={0};     //图像缓冲数组
unsigned int Image_Center[ROW]={0};        //所采集的图像中心线
 
unsigned char SampleFlag=0;       //奇偶场标记

unsigned int  m=0;                 //换行变量
 
unsigned int  Line;               //行中断计数变量
unsigned int  hang;               

 
unsigned int  Get_Image[]={   
                         17,19,21,23,25,28,31,34,37,40,43,46,49,53,57, 
                         61,65,69,73,77,81,85,89,94,99,105,111,117,123,
                         129,135,141,147,153,159,166,173,180,187,189
                         
                         };     //定每场采哪几行。 
                        

/*************************************************************/
/*                      行场中断初始化函数                   */
/*************************************************************/
void CCD_Init(void) 
{ 
        TIOS=0x04;              //外部输入捕捉0,1通道 
        TCTL4=0x09;             //通道0 上升沿触发,通道1下降沿触发 
        TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
        TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
        TSCR1=0x80;             //使能 
        TSCR2 = 0x04;	    // 预分频系数pr2-pr0:100,16分频，时钟周期为1/3us,
        TIE=0x03;               //通道 0，1 中断使能 
        TFLG1=0xFF;             //清中断标志位 
        TFLG2 = 0xff;     // 清除自由定时器中断标志位
        PACTL = 0x50;   //初始化累加器
} 

 
//*****************************************************************************
//                           二值化
//*****************************************************************************
//功能：对图像数组进行二值化
//输入:整幅图像 
//输出；二值化后的图像数组 
//数据储存//二值化
//测试通过，2014/8/16晚 
void erzhiAll()  
{  
     unsigned char i,j;
     //unsigned char *p_Image; 
     //unsigned char *q_Image;
     
     //q_Image=&ImageBuffer[0][0];
     /*for ( i=0; i<ROW; i++)
      for(p_Image=&Image_Data[i][0],q_Image=&ImageBuffer[i][0];p_Image<=&Image_Data[i][COLUMN-1];p_Image++,q_Image++)  
       {
          if ((*p_Image >= THRESHOLD) && (*p_Image<256)) 
          {
            *q_Image = 1;
          } 
          else
          {
            *q_Image = 0;
          }
       }*/
       
      for(i=0; i<ROW; i++)
        for(j=0; j<COLUMN; j++)
          if (Image_Data[i][j] >= THRESHOLD && Image_Data[i][j] < 256) 
          {
            ImageBuffer[i][j] = 1;
          } 
          else 
          {
            ImageBuffer[i][j] = 0;
          }
} 

//*****************************************************************************
//                          去噪
//****************************************************************************** 
//功能：去除宽度较小或较大的噪点
//输入：整个图像数组
//输出：去噪后的图像数组 
void quzao()
{
	unsigned char i,j;
	char k;
	unsigned int white_dop;
	for(i=0;i<ROW;i++)
		for(j=0;j<COLUMN;j++) {
		  if(ImageBuffer[i][j]==1) 	//从第一个白电平开始计数 
			{
				white_dop++;
				if(ImageBuffer[i][j+1]==0)  //下一个为黑电平时停止计数 
					{
					if(white_dop < noise_min || white_dop > noise_max)  //滤除过宽、过窄的噪点 
						for(k=white_dop-1;k>=0;k--)
							ImageBuffer[i][j-k]=0;
					white_dop=0;
					}
						
			}
		}
			
}

//****************************************************************************
//                         去绝对值
//****************************************************************************
//功能：求绝对值 
unsigned int mid(unsigned int n1,unsigned int n2)//算绝对值
{
   unsigned int dif;
   if(n1>n2)
   dif=n1-n2;
   else
   dif=n2-n1;
   return dif;
}/**/


//****************************************************************************
//                           中心线提取
//****************************************************************************
//功能:提取中心线
//输入：整个图像数组（去噪后）
//输出：中心线数组
void center()
{
	unsigned int left,right,before,after;
	unsigned int j,i;	
	for(i=0;i<ROW;i++) 
      {
        if(ImageBuffer[i][0] == 0)     //判断第一个点是否为黑点 
  	  	{
  		     for(j=0; j<COLUMN; j++)
		       {
 	            if(ImageBuffer[i][j] == 1)   //取左边沿 
  		        {
  		          left = j;
  		          break;
  		        }
    	     }
   		     for(j=left; j<COLUMN; j++)
   	        {
     	         if(ImageBuffer[i][j] == 0)	//取右边沿 
       	   	   {
       	  	     right = j;
       	  	     break;
       	  	   } 
       	  	   else
       	  	   {
       	  	      if(ImageBuffer[i][78]==1 && ImageBuffer[i][79]==1)
       	  	        right = 79;
       	  	   }
  	        }
 		     Image_Center[i]=(left+right)/2;		//中心线数组 
  		   } 
  	   	else
  	   	  if (ImageBuffer[i][1] == 1 && ImageBuffer[i][2] == 1)
 		      {
  	  	   for(j=0;j<120;j++)
  		      {
  	          if(ImageBuffer[i][j] == 0)		//取右边沿 
              {
              right = j;
              break;
              } 
		        }
		        
	         Image_Center[i] = right/2;				//中心线数组 
  	  	  }
      }
   //处理、优化中心线 //需添加下限：即除去为零的中心数组的值。
   if(!(Image_Center[39] == 0&&Image_Center[38] == 0))
   {
    
   for(i=ROW-2;i>0;i--)
     if(Image_Center[i]==0) Image_Center[i]=Image_Center[i+1];
   for(i=ROW-3;i>0;i--)
     {
        after=mid(Image_Center[i],Image_Center[i-1]);
        before=mid(Image_Center[i-1],Image_Center[i+1]);
        if (before>error1)
        {
         if (after > error2) 
		         Image_Center[i]=Image_Center[i+1];
         else
            Image_Center[i]=(Image_Center[i-1]+Image_Center[i+1])/2;
        } 
        
     }
   before=mid(Image_Center[0],Image_Center[1]);
   if(before>error1)
     Image_Center[0]=Image_Center[1];
   }
} /* */

/*************************************************************
                       搜索中线
**************************************************************
功能：找出中线数组
内容：调用前面的函数*/
void SeachCenter(void) 
{
  erzhiAll(); //图像二值化
  quzao();    //图像去噪
  center();   //中线提取
}

/*************************************************************/
/*                        行中断处理函数                     */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt 8  PT0_Interrupt(){
 
   TFLG1_C0F=1;    //行中断标志位清除，以便于下次行中断进行

   Line++;         //行中断计数变量
   
   if ( Line<ROW_START || Line>ROW_MAX ){ 
      return;     //不是要采集图像的有效行，返回                               
    } 
    
  if( Line==Get_Image[hang]){
   
    delays(23);//如果图像不在中间请修改这里
   
          
        Image_Data[m][0]=PORTA;_asm();_asm();Image_Data[m][1]=PORTA;_asm();_asm();Image_Data[m][2]=PORTA;_asm();_asm();Image_Data[m][3]=PORTA;_asm();_asm();Image_Data[m][4]=PORTA;_asm();_asm();
        Image_Data[m][5]=PORTA;_asm();_asm();Image_Data[m][6]=PORTA;_asm();_asm();Image_Data[m][7]=PORTA;_asm();_asm();Image_Data[m][8]=PORTA;_asm();_asm();Image_Data[m][9]=PORTA;_asm();_asm();
        Image_Data[m][10]=PORTA;_asm();_asm();Image_Data[m][11]=PORTA;_asm();_asm();Image_Data[m][12]=PORTA;_asm();_asm();Image_Data[m][13]=PORTA;_asm();_asm();Image_Data[m][14]=PORTA;_asm();_asm();
        Image_Data[m][15]=PORTA;_asm();_asm();Image_Data[m][16]=PORTA;_asm();_asm();Image_Data[m][17]=PORTA;_asm();_asm();Image_Data[m][18]=PORTA;_asm();_asm();Image_Data[m][19]=PORTA;_asm();_asm();
        Image_Data[m][20]=PORTA;_asm();_asm();Image_Data[m][21]=PORTA;_asm();_asm();Image_Data[m][22]=PORTA;_asm();_asm();Image_Data[m][23]=PORTA;_asm();_asm();Image_Data[m][24]=PORTA;_asm();_asm();
        Image_Data[m][25]=PORTA;_asm();_asm();Image_Data[m][26]=PORTA;_asm();_asm();Image_Data[m][27]=PORTA;_asm();_asm();Image_Data[m][28]=PORTA;_asm();_asm();Image_Data[m][29]=PORTA;_asm();_asm();
        Image_Data[m][30]=PORTA;_asm();_asm();Image_Data[m][31]=PORTA;_asm();_asm();Image_Data[m][32]=PORTA;_asm();_asm();Image_Data[m][33]=PORTA;_asm();_asm();Image_Data[m][34]=PORTA;_asm();_asm();
        Image_Data[m][35]=PORTA;_asm();_asm();Image_Data[m][36]=PORTA;_asm();_asm();Image_Data[m][37]=PORTA;_asm();_asm();Image_Data[m][38]=PORTA;_asm();_asm();Image_Data[m][39]=PORTA;_asm();_asm();
        Image_Data[m][40]=PORTA;_asm();_asm();Image_Data[m][41]=PORTA;_asm();_asm();Image_Data[m][42]=PORTA;_asm();_asm();Image_Data[m][43]=PORTA;_asm();_asm();Image_Data[m][44]=PORTA;_asm();_asm();
        Image_Data[m][45]=PORTA;_asm();_asm();Image_Data[m][46]=PORTA;_asm();_asm();Image_Data[m][47]=PORTA;_asm();_asm();Image_Data[m][48]=PORTA;_asm();_asm();Image_Data[m][49]=PORTA;_asm();_asm();
        Image_Data[m][50]=PORTA;_asm();_asm();Image_Data[m][51]=PORTA;_asm();_asm();Image_Data[m][52]=PORTA;_asm();_asm();Image_Data[m][53]=PORTA;_asm();_asm();Image_Data[m][54]=PORTA;_asm();_asm();
        Image_Data[m][55]=PORTA;_asm();_asm();Image_Data[m][56]=PORTA;_asm();_asm();Image_Data[m][57]=PORTA;_asm();_asm();Image_Data[m][58]=PORTA;_asm();_asm();Image_Data[m][59]=PORTA;_asm();_asm();
        Image_Data[m][60]=PORTA;_asm();_asm();Image_Data[m][61]=PORTA;_asm();_asm();Image_Data[m][62]=PORTA;_asm();_asm();Image_Data[m][63]=PORTA;_asm();_asm();Image_Data[m][64]=PORTA;_asm();_asm();
        Image_Data[m][65]=PORTA;_asm();_asm();Image_Data[m][66]=PORTA;_asm();_asm();Image_Data[m][67]=PORTA;_asm();_asm();Image_Data[m][68]=PORTA;_asm();_asm();Image_Data[m][69]=PORTA;_asm();_asm();
        Image_Data[m][70]=PORTA;_asm();_asm();Image_Data[m][71]=PORTA;_asm();_asm();Image_Data[m][72]=PORTA;_asm();_asm();Image_Data[m][73]=PORTA;_asm();_asm();Image_Data[m][74]=PORTA;_asm();_asm();
        Image_Data[m][75]=PORTA;_asm();_asm();Image_Data[m][76]=PORTA;_asm();_asm();Image_Data[m][77]=PORTA;_asm();_asm();Image_Data[m][78]=PORTA;_asm();_asm();Image_Data[m][79]=PORTA;_asm();_asm();
        Image_Data[m][80]=PORTA;_asm();
  
       hang++;               
       m++; 
   }
   //erzhi(m);

} 

/*************************************************************/
/*                        场中断处理函数                     */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 9 PT1_Interrupt() 

{ 
             TFLG1_C1F=1;              //场中断清楚，以便于下次的场中断的正常进行
             TFLG1_C0F=1;              //行中断清除，以便于开始采集图像数据
             m=0;                      //行中间变量清零，以便于开始从把采集的图像放到数组的第一行
             Line=0;                   //行中断临时变量清零
             hang=0;                   //行临时变量清除
             if (oddField == 0) 
             {
               LineDisable;    //关行中断
               SampleFlag=0;   //场标记记为0，不采集图像
             }
             else 
             {
                SampleFlag=1;
                Linenable;      //使能行中断
              }             
}




