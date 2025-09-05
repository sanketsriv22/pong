#include <format>
#include <iostream>
#include "raylib.h"
#include "Constants.h"
#include "Paddle.h"
#include "CpuPaddle.h"

enum class GameState
{
    PLAYING, 
    WIN,
    LOSE,
    MAIN_MENU
};

struct Line 
{
    Vector2 start;
    Vector2 end;
    Color color;
};

class Ball 
{
public:
    Vector2 position;
    const float radius;
    Vector2 speed;
    Ball() : position{BALL_INITIAL_POSITION}, radius{BALL_RADIUS}, speed{BALL_SPEED} {}
    
    void Draw()
    {
        DrawCircle(position.x, position.y, radius, WHITE);
    }

    void UpdatePosition()
    {
        position.x += speed.x;
        position.y += speed.y;

        // Bounce off top and bottom
        if (position.y + radius >= SCREEN_HEIGHT || position.y - radius <= 0)
            speed.y = -speed.y;
    }

    void ResetPosition()
    {
        position = BALL_INITIAL_POSITION;
    }

    void paddleCollision()
    {
        // reverse X direction if collision occurs
        speed.x *= -1;
    }

    Paddle* WhoScored(Paddle *player, Paddle *cpu)
    {
        if (position.x + radius >= SCREEN_WIDTH) // player got a point
            return player;
        else if (position.x - radius <= 0)            // cpu got a point
            return cpu;
        else
            return nullptr;
    }
};


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

int main()
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game");
    SetTargetFPS(60);
    
    std::cout << "Game Started" << std::endl;
    GameState currentState = GameState::MAIN_MENU;

    // instantiate environment objects
    Ball ball;
    Paddle player;
    CpuPaddle cpu;
    Line midLine { Vector2{ SCREEN_WIDTH/2, 0 }, Vector2{ SCREEN_WIDTH/2, SCREEN_HEIGHT }, GRAY };

    // initial paddle locations
    // player.position.y = SCREEN_HEIGHT/2 - PADDLE_SIZE.y/2;

    // cpu.position.x = SCREEN_WIDTH - PADDLE_SIZE.x;
    // cpu.position.y = SCREEN_HEIGHT/2 - PADDLE_SIZE.y/2;

    // initialize paddle colors
    // player.color = BLUE;
    // cpu.color = RED;

    // scoreboard text
    const char scores[5] {'0', '1', '2', '3', '\0'};

    // GAME LOOP
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK); // clear each frame to replace previous drawings
        char playerScoreBuffer[2] = { scores[player.score], '\0'};
        char cpuScoreBuffer[2] = { scores[cpu.score], '\0'};

        switch (currentState)
        {
            case GameState::PLAYING:
            {
                // Draw all objects
                ball.Draw();
                player.Draw();
                cpu.Draw();
                DrawLine(midLine.start.x, midLine.start.y, midLine.end.x, midLine.end.y, midLine.color); 
                
                DrawText(playerScoreBuffer, midLine.start.x - 40, 20, 40, YELLOW);
                DrawText(cpuScoreBuffer, midLine.start.x + 25, 20, 40, YELLOW);

                // Update all dynamic object positions
                ball.UpdatePosition();
                player.UpdatePosition();
                cpu.UpdatePosition(ball.position.y);

                // Check for paddle collision
                if (CheckCollisionCircleRec(ball.position, ball.radius, Rectangle{player.position.x, player.position.y, PADDLE_SIZE.x, PADDLE_SIZE.y})
                    || CheckCollisionCircleRec(ball.position, ball.radius, Rectangle{cpu.position.x, cpu.position.y, PADDLE_SIZE.x, PADDLE_SIZE.y}))
                {
                    ball.paddleCollision();
                }

                // if someone scored, update their object instance score attribute
                if (Paddle* scorer = ball.WhoScored(&player, &cpu))
                {
                    scorer->AddScore();
                    if (scorer->score == POINTS_TO_WIN) {
                        if (scorer == &player) {
                            currentState = GameState::WIN;
                        } else {
                            currentState = GameState::LOSE;
                        }
                    }
                            
                    ball.ResetPosition();
                }

                break;
            }
            case GameState::LOSE:
            {
                DrawLoseScreen();
                if (IsKeyPressed(KEY_ENTER))
                {
                    player.ResetScore();
                    cpu.ResetScore();
                    currentState = GameState::PLAYING;
                }
                break;
            }
            case GameState::WIN:
            {
                DrawWinScreen();
                if (IsKeyPressed(KEY_ENTER))
                {
                    player.ResetScore();
                    cpu.ResetScore();
                    currentState = GameState::PLAYING;
                }
                break;
            }
            case GameState::MAIN_MENU:
            {
                DrawMainMenu();
                if (IsKeyPressed(KEY_ENTER)) currentState = GameState::PLAYING;
                break;
            }   
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}