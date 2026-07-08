#include "input.hpp"
#include "being.hpp"



void UserInput(Being &being_instance)
{
    if (IsKeyPressed(KEY_Z) and !being_instance.jumping)
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
}
