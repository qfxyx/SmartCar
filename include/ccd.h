
#ifndef _CCD_H_
#define _CCD_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"
#include "system.h"

void CCD_Init(void); 
void erzhiAll(void);	//二值化
void quzao(void);	//去噪
unsigned int mid(unsigned int n1, unsigned int n2);		//取绝对值
void center();	//中心线提取
void SeachCenter(void);//搜索中线

#endif