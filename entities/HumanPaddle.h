#pragma once

#include "Paddle.h"
#include "Constants.h"
#include "raylib.h"

class HumanPaddle : public Paddle
{
public:
    HumanPaddle();
    void UpdatePosition(float ballY) override; // virtual because we expect CPU to override
};