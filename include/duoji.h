

#ifndef _DUOJI_H_

#define _DUOJI_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"

extern unsigned char angle;         //偏转角度
extern unsigned char turn_flag;   //判断左转和右转，一为左转
extern unsigned char judge_line;     //直道、弯道标志 1为直道，0为弯道
extern unsigned int Image_Center[ROW];        //所采集的图像中心线

void duoji_driver (void);  //dty为舵机的PWMDTY的值

#endif
