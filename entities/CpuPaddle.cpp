#include "CpuPaddle.h"
#include "Constants.h"

CpuPaddle::CpuPaddle()
{
    position = {SCREEN_WIDTH - PADDLE_SIZE.x, SCREEN_HEIGHT/2 - PADDLE_SIZE.y/2};
    color = CPU_COLOR;
    speed = CPU_SPEED;
}

void CpuPaddle::UpdatePosition(float ballY)
{
    if (position.y + size.y/2 > ballY)
        position.y -= speed;
    if (position.y + size.y/2 < ballY)
        position.y += speed;

    LimitMovement();
}