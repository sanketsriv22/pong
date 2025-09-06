#include "InputManager.h"
#include "raylib.h"

void InputManager::HandleInput(GameState &currentState, Paddle &player, Paddle &cpu) const
{
    switch (currentState)
    {
        case GameState::MAIN_MENU:
        {
            if (IsKeyPressed(KEY_ENTER)) currentState = GameState::PLAYING;
            break;
        }

        case GameState::LOSE:
        {
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
            if (IsKeyPressed(KEY_ENTER))
            {
                player.ResetScore();
                cpu.ResetScore();
                currentState = GameState::PLAYING;
            }
            break;
        }
        
        case GameState::PLAYING:
        {
            break;
        }   
    }
}