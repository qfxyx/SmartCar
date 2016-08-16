
#ifndef _CAMERA_DEAL_H
#define _CAMERA_DEAL_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mydefine.h"

extern unsigned int Image_Center[ROW];

unsigned int Abs(unsigned int a,unsigned int b); 
unsigned char angle_x1(unsigned int x); 
unsigned char angle_x2(unsigned int x);

void c_deal(void);
void big_curve(void);

#endif 