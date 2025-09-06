#pragma once
#include "raylib.h"
#include "Constants.h"

class Paddle
{
protected: // visibility limited to this class and subclasses (cpuPaddle)
    void LimitMovement();
    
public:
    static const Vector2 size; // all paddles have same size
    Vector2 position;
    int speed;
    Color color;
    int score;

    Paddle();

    // virtual function makes abstract class, needs a virtual destructor?
    // other option is to create a nonabstract class, aka derived class from Paddle, so HumanPaddle class?
    virtual ~Paddle() = default; 

    void Draw();
    virtual void UpdatePosition(float ballY = 0.0f) = 0; // virtual because we expect CPU to override
    Vector2 GetPosition() const;
    int GetSpeed() const;
    const Vector2 GetSize() const;
    void AddScore();
    void ResetScore();

};