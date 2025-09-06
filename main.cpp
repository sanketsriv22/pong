#include <format>
#include <iostream>
#include "raylib.h"
#include "Constants.h"
#include "Paddle.h"
#include "CpuPaddle.h"
#include "Ball.h"
#include "GameState.h"
#include "Game.h"


int main()
{
    // initialize game instance
    Game game;
    game.Initialize();
    game.Run();

    return 0;
}