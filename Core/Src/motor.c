#include "motor.h"
#include "tim.h"  // 必须包含此头文件以访问 htim3

/**
 * @brief  设置电机速度和方向
 * @param  speed: 范围 -999 到 999 (对应 CubeMX 中设置的 ARR 值)
 * @retval 无
 */
void Motor_Set_Speed(int16_t speed)
{
    // 1. 限幅保护
    if (speed > 999)  speed = 999;
    if (speed < -999) speed = -999;

    // 2. 判断方向
    if (speed >= 0)
    {
        // 正转逻辑 (具体方向取决于你的接线)
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
        // 设置 PWM 占空比
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
    }
    else
    {
        // 反转逻辑
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_SET);
        // 设置 PWM 占空比 (取绝对值)
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, -speed);
    }
}

/**
 * @brief  电机紧急停止
 */
void Motor_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
}