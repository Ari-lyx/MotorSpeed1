#include "encoder.h"
#include "tim.h"

float Encoder_Get_RPM(void)
{
    uint16_t count = 0;
    float rpm = 0.0f;

    // 1. 读取 100ms 内产生的脉冲个数
    count = __HAL_TIM_GET_COUNTER(&htim1);
    __HAL_TIM_SET_COUNTER(&htim1, 0); // 清零

    // 2. 计算 RPM
    // 因为没有 A/B 相，所以没有 4 倍频，1 个脉冲就是 1 个槽位经过
    // 公式：(脉冲数 / 槽位数) * (60s / 0.1s采样周期)
    rpm = ((float)count / DISK_SLOTS / GEAR_RATIO) * 600.0f;

    return rpm;
}