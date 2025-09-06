#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "CpuPaddle.h"
#include "Constants.h"
#include "Controls.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameState.h"

#include "raylib.h"

class Game 
{
private:
    GameState currentState;

    // game objects
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> player;
    std::unique_ptr<Paddle> cpu; // defined as Paddle for polymorphism

public:
    Game();

    void Initialize();
    void Run();
    void HandleInput();
    void Update();
    void Render();
};