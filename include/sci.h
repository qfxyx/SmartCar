
#ifndef _SCI_H_
#define _SCI_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mydefine.h"
extern unsigned char ImageBuffer[ROW][COLUMN];       //所采集的图像二维数组
extern unsigned char Image_Data[ROW][COLUMN];       //所采集的图像二维数组
extern unsigned int Image_Center[ROW];

extern unsigned char left_turn[3];   //判断左转和右转，一为左转
extern unsigned char angle;        //转的角度
extern unsigned char judge_line;     //判断直道还是弯道，1为直道
extern unsigned char big_curve_c;    //大弯道标志

extern unsigned char data_receive;
extern unsigned char data_temp[4];
void SCI_Init(void);
void SCI_Init1(void);
void SCI_Write(unsigned char SendChar);
void Process_Data(void);  //发送采集到的原始图像数组
void Process_Erzhi(void);//发送二值化后的数组或去噪后的数组
void Process_zx(void);   //发送中线数组
void Process_canshu(void);  //发送各个参数

#endif