#include <math.h>
#include <stdio.h>

#include "pid.h"

static int nearly_equal(float a, float b)
{
    return fabsf(a - b) < 0.001f;
}

static int test_output_is_clamped(void)
{
    PID_Controller pid;

    PID_Init(&pid, 10.0f, 0.0f, 0.0f, -999.0f, 999.0f, -200.0f, 200.0f);

    return nearly_equal(PID_Update(&pid, 200.0f, 0.0f), 999.0f);
}

static int test_integral_is_clamped(void)
{
    PID_Controller pid;

    PID_Init(&pid, 0.0f, 1.0f, 0.0f, -999.0f, 999.0f, -20.0f, 20.0f);

    (void)PID_Update(&pid, 100.0f, 0.0f);
    (void)PID_Update(&pid, 100.0f, 0.0f);

    return nearly_equal(PID_Update(&pid, 100.0f, 0.0f), 20.0f);
}

static int test_reset_clears_history(void)
{
    PID_Controller pid;

    PID_Init(&pid, 0.0f, 1.0f, 1.0f, -999.0f, 999.0f, -999.0f, 999.0f);

    (void)PID_Update(&pid, 50.0f, 0.0f);
    PID_Reset(&pid);

    return nearly_equal(PID_Update(&pid, 0.0f, 0.0f), 0.0f);
}

int main(void)
{
    int failures = 0;

    if (!test_output_is_clamped()) {
        printf("test_output_is_clamped failed\n");
        failures++;
    }

    if (!test_integral_is_clamped()) {
        printf("test_integral_is_clamped failed\n");
        failures++;
    }

    if (!test_reset_clears_history()) {
        printf("test_reset_clears_history failed\n");
        failures++;
    }

    return failures;
}
