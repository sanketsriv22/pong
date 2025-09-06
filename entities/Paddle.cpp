#include "Paddle.h"
#include "Constants.h"
#include "Controls.h"
#include "raylib.h"

const Vector2 Paddle::size = PADDLE_SIZE; // construct the paddle size

Paddle::Paddle() : 
position{0, SCREEN_HEIGHT/2 - PADDLE_SIZE.y/2}, speed{PLAYER_SPEED}, color{PLAYER_COLOR}, score{0} {}

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

void Paddle::UpdatePosition(float ballY)
{
    
}

Vector2 Paddle::GetPosition() const
{
    return position;
}

int Paddle::GetSpeed() const
{
    return speed;
}

const Vector2 Paddle::GetSize() const
{
    return size;
}

void Paddle::AddScore()
{
    score ++;
}

void Paddle::ResetScore()
{
    score = 0;
}