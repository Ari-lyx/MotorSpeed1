#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h" // 包含此头文件以使用 HAL 库和 CubeMX 生成的 Pin 定义

/* 电机方向控制宏定义，方便修改引脚 */
// #define MOTOR_IN1_PORT  GPIOC
// #define MOTOR_IN1_PIN   GPIO_PIN_1
// #define MOTOR_IN2_PORT  GPIOC
// #define MOTOR_IN2_PIN   GPIO_PIN_2

/* 函数原型声明 */
void Motor_Set_Speed(int16_t speed); // 设置电机速度和方向
void Motor_Stop(void);               // 紧急停止

#endif