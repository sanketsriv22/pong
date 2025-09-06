#include <memory>
#include <iostream>

#include "Ball.h"
#include "Paddle.h"
#include "HumanPaddle.h"
#include "CpuPaddle.h"
#include "Constants.h"
#include "Controls.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameState.h"
#include "Game.h"

#include "raylib.h"

void DrawLoseScreen()
{
    DrawText("Game Over!", SCREEN_WIDTH/2 - 325, SCREEN_HEIGHT/2 - 200, 100, RED);
    DrawText("Press Enter to Play Again", SCREEN_WIDTH/2 - 350, (SCREEN_HEIGHT/2) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", SCREEN_WIDTH/2 - 250, (SCREEN_HEIGHT/2) + 50 , 50, WHITE);
}

void DrawWinScreen()
{
    DrawText("You Win!", SCREEN_WIDTH/2 - 275, SCREEN_HEIGHT/2 - 200, 100, BLUE);
    DrawText("Press Enter to Play Again", SCREEN_WIDTH/2 - 350, (SCREEN_HEIGHT) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", SCREEN_WIDTH/2 - 250, (SCREEN_HEIGHT/2) + 50 , 50, WHITE);
}

void DrawMainMenu()
{
    DrawText("Press Enter to Play", SCREEN_WIDTH/2 - 500, SCREEN_HEIGHT/2 - 100, 100, WHITE);
}


Game::Game() : currentState {GameState::MAIN_MENU} {};

void Game::Initialize()
{ 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game");
    SetTargetFPS(60);
    std::cout << "Game Started" << std::endl;

    ball = std::make_unique<Ball>();
    player = std::make_unique<HumanPaddle>();
    cpu = std::make_unique<CpuPaddle>();
    Line midLine { Vector2{ SCREEN_WIDTH/2, 0 }, Vector2{ SCREEN_WIDTH/2, SCREEN_HEIGHT }, GRAY };
}

void Game::Run()
{
    // GAME LOOP
    while(!WindowShouldClose())
    {
        HandleInput();
        Update();
        Render();
    }
    CloseWindow();
}

void Game::HandleInput()
{
    InputManager iManager;
    // pass currentState here, catch the reference on other side in order to modify
    iManager.HandleInput(currentState, *player, *cpu); 
}

void Game::Update()
{
    // Update all dynamic object positions
    ball->UpdatePosition();
    player->UpdatePosition();
    cpu->UpdatePosition(ball->GetPosition().y);

    // Check for paddle collision
    if (CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), Rectangle{player->GetPosition().x, player->GetPosition().y, PADDLE_SIZE.x, PADDLE_SIZE.y})
        || CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), Rectangle{cpu->GetPosition().x, cpu->GetPosition().y, PADDLE_SIZE.x, PADDLE_SIZE.y}))
    {
        ball->paddleCollision();
    }

    // if someone scored, update their object instance score attribute
    if (Paddle* scorer = ball->WhoScored(player.get(), cpu.get()))
    {
        scorer->AddScore();
        if (scorer->score == POINTS_TO_WIN) {
            if (scorer == player.get()) {
                currentState = GameState::WIN;
            } else {
                currentState = GameState::LOSE;
            }
            return;
        }
        ball->ResetPosition();
    }
}

void Game::Render()
{
    Renderer render;
    render.Render(currentState, *ball, *player, *cpu); // dereferenced pointers -> references
}