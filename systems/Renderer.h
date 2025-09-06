#pragma once
#include "GameState.h"
#include "Ball.h"
#include "Paddle.h"

class Renderer
{
public:
    void Render(GameState state, Ball& ball, Paddle& player, Paddle& cpu) const;
private:
    void DrawMainMenu() const;
    void DrawLoseScreen() const;
    void DrawWinScreen() const;
};