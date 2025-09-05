#pragma once
#include "raylib.h"
#include "Constants.h"

class Paddle
{
protected: // visibility limited to this class and subclasses (cpuPaddle)
    void LimitMovement();
    static const Vector2 size; // all paddles have same size

public:
    Vector2 position;
    int speed;
    Color color;
    int score;

    Paddle();

    void Draw();
    void UpdatePosition();
    void AddScore();
    void ResetScore();

};