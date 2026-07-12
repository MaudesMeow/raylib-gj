#include "GameState.hpp"





void UpdateMainMenu() // Draw and hanld Main Menu update
{
    if (IsKeyPressed(KEY_Z))
    {
        game_state = PLAY;
    }
}


void DrawMenu()
{
    DrawText("TEST GAME", 16,16,48,WHITE);
}