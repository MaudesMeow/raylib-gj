#include "portals.hpp"




void Portal_Handler::PopulatePortals()
{


    portals =
    {
        {1,Portal{{12,9},{Rectangle{12*16,9*16,32,26}},{9,6}}},
        {2,Portal{{8,17},{Rectangle{8*16,17*16,32,26}},{9,14}}},
        {3,Portal{{21,5},{Rectangle{21*16,5*16,32,26}},{19,10}}}
    };
}

void Portal_Handler::DrawLandingPoints()
{
    for (auto& point : portals)
    {
        DrawCircle(point.second.landing_point.x*16,point.second.landing_point.y*16,3,GREEN);
    }
}

void Portal_Handler::DrawPortals()
{
    for (auto& point : portals)
    {
        DrawRectangleLinesEx(point.second.rep,3,RED);
    }

}