#pragma once
#include "Constants.h"
#include "Paddle.h"

class CpuPaddle: public Paddle
{
public:
    CpuPaddle();

    // automatic movement
    void UpdatePosition(int ballY);
};