#pragma once

#include <memory>
#include <Constants.h>
#include <Paddle.h>
#include <raylib.h>

class Ball 
{
private:
public:
    static const float radius; // this type of ball should never change size 
    Vector2 position;
    Vector2 speed;

    Ball();
    
    void Draw();
    void UpdatePosition();
    void ResetPosition();
    void paddleCollision();
    Vector2 GetPosition() const;
    Vector2 GetSpeed() const;
    const float GetRadius() const;

    Paddle* WhoScored(Paddle *player, Paddle *cpu);
};