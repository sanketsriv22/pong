#include <format>
#include <iostream>
#include "raylib.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

enum class GameState
{
    PLAYING, 
    WIN,
    LOSE,
    MAIN_MENU
};

class Paddle
{
protected: // visibility limited to this class and subclasses (cpuPaddle)
    void LimitMovement()
    {
        // keep within vertical bounds
        if (position.y <= 0) position.y = 0;
        if (position.y >= (SCREEN_HEIGHT - size.y)) position.y = SCREEN_HEIGHT - size.y;
    }

public:
    Vector2 position;
    const Vector2 size;
    int speed;
    Color color;
    int score;

    Paddle() : position{0, 0}, size{25, 120}, speed{10}, color{WHITE}, score{0} {}

    void Draw()
    {
        DrawRectangle(position.x, position.y, size.x, size.y, color);
    }
    
    void UpdatePosition()
    {
        // move up and down
        if (IsKeyDown(KEY_W))
        {
            position.y -= speed;
        }
        if (IsKeyDown(KEY_S))
        {
            position.y += speed;
        }

        LimitMovement();
    }

    void AddScore()
    {
        score ++;
    }

    void ResetScore()
    {
        score = 0;
    }

};

class CpuPaddle: public Paddle
{
public:
    // automatic movement
    void UpdatePosition(int ballY) 
    {
        if (position.y + size.y/2 > ballY)
        {
            position.y -= speed;
        }
        if (position.y + size.y/2 < ballY)
        {
            position.y += speed;
        }

        LimitMovement();
    }
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
    int speedX, speedY;
    Ball() : position{SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, radius{20}, speedX{15}, speedY{15} {}
    
    void Draw()
    {
        DrawCircle(position.x, position.y, radius, WHITE);
    }

    void UpdatePosition()
    {
        position.x += speedX;
        position.y += speedY;

        // Bounce off top and bottom
        if (position.y + radius >= SCREEN_HEIGHT || position.y - radius <= 0)
            speedY = -speedY;
    }

    void ResetPosition()
    {
        position.x = SCREEN_WIDTH/2;
        position.y = SCREEN_HEIGHT/2;
    }

    void paddleCollision()
    {
        // reverse X direction if collision occurs
        speedX *= -1;
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
    DrawText("Game Over!", GetScreenWidth()/2 - 325, GetScreenHeight()/2 - 200, 100, RED);
    DrawText("Press Enter to Play Again", GetScreenWidth()/2 - 350, (GetScreenHeight()/2) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", GetScreenWidth()/2 - 250, (GetScreenHeight()/2) + 50 , 50, WHITE);
}

void DrawWinScreen()
{
    DrawText("You Win!", GetScreenWidth()/2 - 275, GetScreenHeight()/2 - 200, 100, BLUE);
    DrawText("Press Enter to Play Again", GetScreenWidth()/2 - 350, (GetScreenHeight()/2) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", GetScreenWidth()/2 - 250, (GetScreenHeight()/2) + 50 , 50, WHITE);
}

void DrawMainMenu()
{
    DrawText("Press Enter to Play", GetScreenWidth()/2 - 500, GetScreenHeight()/2 - 100, 100, WHITE);
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
    player.position.y = SCREEN_HEIGHT/2 - player.size.y/2;

    cpu.position.x = SCREEN_WIDTH - cpu.size.x;
    cpu.position.y = SCREEN_HEIGHT/2 - cpu.size.y/2;

    // initialize paddle colors
    player.color = BLUE;
    cpu.color = RED;

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
                if (CheckCollisionCircleRec(ball.position, ball.radius, Rectangle{player.position.x, player.position.y, player.size.x, player.size.y})
                    || CheckCollisionCircleRec(ball.position, ball.radius, Rectangle{cpu.position.x, cpu.position.y, cpu.size.x, cpu.size.y}))
                {
                    ball.paddleCollision();
                }

                // if someone scored, update their object instance score attribute
                if (Paddle* scorer = ball.WhoScored(&player, &cpu))
                {
                    scorer->AddScore();
                    if (scorer->score == 3) {
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