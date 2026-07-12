#include "portals.hpp"




void Portal_Handler::PopulatePortals()
{


    portals =
    {
        {1,Portal{{12,9},{Rectangle{12.5*16,9.35*16,16,16}},{13,6},1,2,1,portal_sprite,false}},
        {2,Portal{{8,17},{Rectangle{8.5*16,17.35*16,16,16}},{9,14},2,6,5,portal_sprite,false}},
        {3,Portal{{21,5},{Rectangle{21.5*16,5.35*16,16,16}},{19,6},3,3,1,portal_sprite,false}},
        {4,Portal{{21,17},{Rectangle{21.5*16,17.35*16,16,16}},{19,18},4,8,7,portal_sprite,false}},
        {5,Portal{{6,5},{Rectangle{6.5*16,5.35*16,16,16}},{7,2},5,12,11,portal_sprite,false}}

    };
}

void Portal_Handler::DrawLandingPoints()
{
    for (auto& point : portals)
    {
        DrawCircle(point.second.portal_landing_point.x*16,point.second.portal_landing_point.y*16,3,GREEN);
    }
}

void Portal_Handler::DrawPortals()
{
    int dummy_timer = 4;
    // for (auto& point : portals)
    // {
    //     DrawRectangleLinesEx(point.second.rep,3,RED);
    // }
    for (auto& point : portals)
    {

        // DrawTexturePro(point.second.sprite,src,dest,{0,0},0,WHITE);
        if (point.second.active)
        {
            if (dummy_timer-GetFrameTime() > 0)
            {
                point.second.active = false;
            }
            DrawCircleLinesV(Vector2{point.second.rep.x+8,point.second.rep.y+8},9,WHITE);
            // DrawCircleLinesV(Vector2{point.second.rep.x+16,point.second.rep.y+13},6,WHITE);
            // DrawCircleLinesV(Vector2{point.second.rep.x+16,point.second.rep.y+13},3,WHITE);
        }
        DrawRectangleLinesEx(point.second.rep,1,WHITE);
        string temp_int = to_string(point.first);
        DrawText(temp_int.c_str(),point.second.portal_landing_point.x*16,point.second.portal_landing_point.y*16,13,WHITE);
        DrawCircleLines(point.second.portal_landing_point.x*16,point.second.portal_landing_point.y*16,3,GREEN);

    }
}