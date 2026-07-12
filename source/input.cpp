#include "input.hpp"
#include "being.hpp"



void UserInput(Being &being_instance, bool &clear_game_state)
{

    // --------------------------------------- being handling during gameplay
    if (IsKeyPressed(KEY_Z) )
    {
        being_instance.forward = !being_instance.forward;
        int oldTarget = being_instance.target_point;
        being_instance.target_point = being_instance.location_point;
        being_instance.location_point = oldTarget;


    }

    if (IsKeyDown(KEY_X) && being_instance.can_jump)
    {
        being_instance.jumping = true;
    }

    if (IsKeyDown(KEY_S))
        being_instance.speed = 16.0f;
    else
        being_instance.speed = 3.5f;


    // -------------------------------------------- menu buttons and or game state

    if (IsKeyPressed(KEY_Q))
    {
        if (game_state == PLAY)
        {
            clear_game_state = true;
            game_state = MENU;
        }
    }
    
}
