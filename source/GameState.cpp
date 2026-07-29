#include "GameState.hpp"





void UpdateMainMenu() // Draw and hanld Main Menu update
{

    if (IsKeyPressed(KEY_Z) && game_state == MENU)
    {
        game_state = PLAY;
    }
    else if (IsKeyPressed(KEY_Z) && (game_state == GAME_LOST || game_state == GAME_WON))
    {
        game_state = MENU;
    }

}


void DrawMenu()
{
    DrawTextEx(global_font,"bloorp",Vector2{45,160},48,4,{255, 127, 127, 255});
    DrawTextEx(global_font,"bloorp",Vector2{45,176},48,4,{255, 255, 158, 255});
    DrawTextEx(global_font,"bloorp",Vector2{45,190},48,4,{158, 207, 255, 255});
    DrawTextEx(global_font,"bloorp",Vector2{45,206},48,4,{207, 158, 255, 255});
    DrawTextEx(global_font,"bloorp",Vector2{45,222},48,4,{158, 255, 158, 255});
    DrawTextEx(global_font,"bloorp",Vector2{45,238},48,4,{255, 207, 158, 255});


    DrawTextEx(global_font,"z: change direction \n\t\t\t&& progress screens \nx: jump \nq: quit to menu"
    ,Vector2{45,320},8,4,WHITE);
    
}


void DrawWinGame()
{
    DrawTextEx(global_font,"WIN",Vector2{110,160},48,4,{255, 127, 127, 255});
    DrawTextEx(global_font,"WIN",Vector2{110,176},48,4,{255, 255, 158, 255});
    DrawTextEx(global_font,"WIN",Vector2{110,190},48,4,{158, 207, 255, 255});
    DrawTextEx(global_font,"WIN",Vector2{110,206},48,4,{207, 158, 255, 255});
    DrawTextEx(global_font,"WIN",Vector2{110,222},48,4,{158, 255, 158, 255});
    DrawTextEx(global_font,"WIN",Vector2{110,238},48,4,{255, 207, 158, 255});
}

void DrawLostGame()
{
    DrawTextEx(global_font,"LOSE",Vector2{90,160},48,4,{255, 127, 127, 255});
    DrawTextEx(global_font,"LOSE",Vector2{90,176},48,4,{255, 255, 158, 255});
    DrawTextEx(global_font,"LOSE",Vector2{90,190},48,4,{158, 207, 255, 255});
    DrawTextEx(global_font,"LOSE",Vector2{90,206},48,4,{207, 158, 255, 255});
    DrawTextEx(global_font,"LOSE",Vector2{90,222},48,4,{158, 255, 158, 255});
    DrawTextEx(global_font,"LOSE",Vector2{90,238},48,4,{255, 207, 158, 255});
}