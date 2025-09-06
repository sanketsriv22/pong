#pragma once
#include "GameState.h"
#include "Paddle.h"

class InputManager
{
public:
    void HandleInput(GameState &currentState, Paddle &player, Paddle &cpu) const;
};