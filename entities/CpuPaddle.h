#pragma once
#include "Constants.h"
#include "Paddle.h"

class CpuPaddle: public Paddle
{
public:
    int targetY;
    CpuPaddle();

    // automatic movement
    void UpdatePosition(float ballY) override;
};