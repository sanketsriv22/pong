#include "CpuPaddle.h"
#include "Constants.h"

CpuPaddle::CpuPaddle()
{
    color = CPU_COLOR;
    speed = CPU_SPEED;
}

void CpuPaddle::UpdatePosition(int ballY)
    {
        if (position.y + size.y/2 > ballY)
        {
            position.y -= speed;
        }
        if (position.y + size.y/2 < ballY)
        {
            position.y += speed;
        }

        LimitMovement();
    }