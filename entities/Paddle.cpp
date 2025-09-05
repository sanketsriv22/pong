#include "Paddle.h"
#include "Constants.h"
#include "Controls.h"
#include "raylib.h"

const Vector2 Paddle::size = PADDLE_SIZE; // construct the paddle size

Paddle::Paddle() : position{0, 0}, speed{PLAYER_SPEED}, color{PLAYER_COLOR}, score{0} {}

void Paddle::LimitMovement()
{
    // keep within vertical bounds
    if (position.y <= 0) position.y = 0;
    if (position.y >= (SCREEN_HEIGHT - size.y)) position.y = SCREEN_HEIGHT - size.y;
}

void Paddle::Draw()
{
    DrawRectangle(position.x, position.y, size.x, size.y, color);
}

void Paddle::UpdatePosition()
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

void Paddle::AddScore()
{
    score ++;
}

void Paddle::ResetScore()
{
    score = 0;
}