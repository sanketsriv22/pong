#include <memory>
#include <Ball.h>
#include <Constants.h>
#include <Paddle.h>

const float Ball::radius = BALL_RADIUS;
Vector2 position;
Vector2 speed;
Ball::Ball() : position{BALL_INITIAL_POSITION}, speed{BALL_SPEED} {}
    
void Ball::Draw()
{
    DrawCircle(position.x, position.y, radius, WHITE);
}


void Ball::UpdatePosition()
{
    position.x += speed.x;
    position.y += speed.y;
    
    // Bounce off top and bottom
    if (position.y + radius >= SCREEN_HEIGHT || position.y - radius <= 0)
    speed.y = -speed.y;
}

void Ball::ResetPosition()
{
    position = BALL_INITIAL_POSITION;
}

void Ball::paddleCollision()
{
    // reverse X direction if collision occurs
    speed.x *= -1;
}

Vector2 Ball::GetPosition() const
{
    return position;
}

Vector2 Ball::GetSpeed() const
{
    return speed;
}

const float Ball::GetRadius() const
{
    return radius;
}

Paddle* Ball::WhoScored(Paddle* player, Paddle* cpu)
{
    if (position.x + radius >= SCREEN_WIDTH) // player got a point
        return player;
    else if (position.x - radius <= 0)            // cpu got a point
        return cpu;
    else
        return nullptr;
}
