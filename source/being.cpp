#include "being.hpp"




void Being::MoveBeing(map<int, Vector2>& points_on_map,map<int, Vector2>& landing_points)
{
    if (!jumping)
    {
        Vector2 target = points_on_map[target_point];

        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);

        if (Vector2Distance(pos, target) < 0.01f)
        {
            // ----------------------------------------------------------------We reached the target
            previous_point = location_point;
            location_point = target_point;

            // ----------------------------------------------------- Pick the next target
            if (forward)
            {
                target_point++;

                if (target_point > 12)
                    target_point = 1;
            }
            else
            {
                target_point--;

                if (target_point < 1)
                    target_point = 12;
            }
        }

    }
    else if (jumping)
    {
        Vector2 target = landing_points[1];
        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
        float distance = 1000.f;
        if (Vector2Distance(pos,target) < 0.01f)
        {
            
            for (int i =1; i < points_on_map.size(); i ++)
            {
                if (Vector2Distance(pos,points_on_map[i]) < distance)
                {
                    distance = Vector2Distance(pos,points_on_map[i]);
                    if (forward)
                    {
                        target_point = i+1;
                        location_point = i;
                    }
                    else
                    {
                        target_point = i;
                        location_point = i+1;
                    }
 
                }
                cout << " count is : " << i << endl;
            }
            cout << "target point is " << target_point << endl;
            cout << "location point is " << location_point << endl;
            jumping = false;
            can_jump = true;
        }
        
    }
    else 
    {
        pos = Vector2Zero();
    }

    rep.x = (pos.x-0.5) * 16;
    rep.y = (pos.y-0.5) * 16;
}
void Being::DrawBeing()
{

    DrawRectangleRec(rep,RED);
}