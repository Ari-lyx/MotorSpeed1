#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

// 关键参数：你的码盘有多少个槽位？（通常是 20 或 13）
#define DISK_SLOTS      20.0f   
// 减速比（如果测速模块在电机轴上则为1.0，在轮子轴上则看减速比）
#define GEAR_RATIO      48.0f    

float Encoder_Get_RPM(void);

#endif