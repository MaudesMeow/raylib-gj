#include "being.hpp"



void Being::MoveBeing(map<int, Vector2> &points_on_map, bool forward)
{
    switch (forward)
    {
    case true:
            if (pos == points_on_map[target_point])
            {
                
                target_point += 1;
                if (target_point > 12)
                {
                    target_point = 1;
                }
            }
        break;
    case false:
            if (pos == points_on_map[target_point])
            {
                
                target_point -= 1;
                if (target_point < 1)
                {
                    target_point = 12;
                }
            }
    default:
        break;
    }



    pos = Vector2MoveTowards(pos,points_on_map[target_point],GetFrameTime()*speed);
    

    rep.x = pos.x;
    rep.y = pos.y;
}

void Being::DrawBeing()
{
    rep.x = pos.x * 16;
    rep.y = pos.y * 16;
    DrawRectangleRec(rep,RED);
}