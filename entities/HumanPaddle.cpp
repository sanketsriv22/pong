#include "HumanPaddle.h"
#include "Constants.h"
#include "Controls.h"
#include "raylib.h"

HumanPaddle::HumanPaddle()
{
    position = {0, SCREEN_HEIGHT/2 - PADDLE_SIZE.y/2};
    color = PLAYER_COLOR;
    speed = PLAYER_SPEED;
}

void HumanPaddle::UpdatePosition(float ballY)
{
    // move up and down
    if (IsKeyDown(PLAYER_UP_KEY))
    {
        position.y -= speed;
    }
    if (IsKeyDown(PLAYER_DOWN_KEY))
    {
        position.y += speed;
    }

    LimitMovement();
}