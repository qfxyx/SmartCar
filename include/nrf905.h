#ifndef _NRF905_H_

#define _NRF905_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"
//#include "camera_deal.h"

extern unsigned char angle;        //转的角度
extern unsigned char judge_line;     //判断直道还是弯道，1为直道
extern unsigned char big_curve_c;    //大弯道标志 
extern unsigned int square;
extern unsigned int base;              //基准
extern unsigned char slow_speed_flag;  //减速标志
extern unsigned char left_flag;       //左转标志
extern unsigned char right_flag;      //右转标志
extern unsigned char turn_flag;       //转弯标志
extern unsigned char far_temp;
extern unsigned char mid_temp;
extern unsigned char big_curve_turn_flag;
extern unsigned int Image_Center[ROW];
extern unsigned int average;
extern char di,gao;

void NrfDelay(unsigned char n); 	//延时 
unsigned char SpiRead(void);	//Spi读 
void SpiWrite(unsigned char send);		//Spi写 
void nRF905Init(void);	//905初始化 
void Config905(void);   //配置寄存器
void TxPacket(unsigned char *TxBuf); //发送数据包 
void SetTxMode(void); 	//设置发送状态 
void canshu(unsigned char *TxBufTemp);
void Send_data(void);
void zhongxian(unsigned char *TxZxTemp);
void Send_zhongxian(void);
void zhongxian2(unsigned char *TxZTemp);

#endif