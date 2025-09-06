#include "Renderer.h"
#include "Constants.h"
#include "Raylib.h"

void Renderer::Render(GameState currentState, Ball &ball, Paddle &player, Paddle &cpu) const
{
    BeginDrawing();
    ClearBackground(BLACK);
    switch (currentState)
    {
        case GameState::MAIN_MENU:
        {
            DrawMainMenu();
            break;
        }

        case GameState::LOSE:
        {
            DrawLoseScreen();
            break;
        }
        case GameState::WIN:
        {
            DrawWinScreen();
            break;
        }
        
        case GameState::PLAYING:
        {
            // Render all objects
            ball.Draw();
            player.Draw();
            cpu.Draw();
            DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, MIDLINE_COLOR); 

            // Scoring
            char playerScoreBuffer[2] = { scores[player.score], '\0'};
            char cpuScoreBuffer[2] = { scores[cpu.score], '\0'};
            DrawText(playerScoreBuffer, SCREEN_WIDTH/2 - 40, 20, 40, YELLOW);
            DrawText(cpuScoreBuffer, SCREEN_WIDTH/2 + 25, 20, 40, YELLOW);
            break;
        }
    }
    EndDrawing();
}

void Renderer::DrawLoseScreen() const
{
    DrawText("Game Over!", SCREEN_WIDTH/2 - 325, SCREEN_HEIGHT/2 - 200, 100, RED);
    DrawText("Press Enter to Play Again", SCREEN_WIDTH/2 - 350, (SCREEN_HEIGHT/2) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", SCREEN_WIDTH/2 - 250, (SCREEN_HEIGHT/2) + 50 , 50, WHITE);
}

void Renderer::DrawWinScreen() const
{
    DrawText("You Win!", SCREEN_WIDTH/2 - 275, SCREEN_HEIGHT/2 - 200, 100, BLUE);
    DrawText("Press Enter to Play Again", SCREEN_WIDTH/2 - 350, (SCREEN_HEIGHT) - 100 , 50, WHITE);
    DrawText("Press ESC to Quit", SCREEN_WIDTH/2 - 250, (SCREEN_HEIGHT/2) + 50 , 50, WHITE);
}

void Renderer::DrawMainMenu() const
{
    DrawText("Press Enter to Play", SCREEN_WIDTH/2 - 500, SCREEN_HEIGHT/2 - 100, 100, WHITE);
}
