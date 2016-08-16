#ifndef _MYDEFINE_H_
#define _MYDEFINE_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#define LineDisable TIE_C0I=0; 
#define Linenable  TIE_C0I=1;
#define ROW        40                 //数字摄像头所采集的二维数组行数
#define COLUMN     80                //数字摄像头所采集的二维数组列数
#define ROW_START  10                 //数字摄像头二维数组行开始行值
#define ROW_MAX    220                //数字摄像头所采集的二维数组行最大值
#define THRESHOLD  155              //图像阈值，根据所采集图像亮度值大小的实际情况调整（OV7620所采集的亮度值大小为0--255）
#define oddField   PORTE_PE7
#define error1  5
#define error2  7
#define middle 20  //取第20行的中点 
#define farLine 11     //取第11行的点 

#endif