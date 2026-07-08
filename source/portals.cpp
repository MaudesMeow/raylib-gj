#include "portals.hpp"


void Portal_Handler::PopulateLandingPoints()
{
    landing_points =
    {
        {1,{9,6}},
        {2,{9,14}},
        {3,{19,10}}

    };
}

void Portal_Handler::DrawLandingPoints()
{
    for (auto& point : landing_points)
    {
        DrawCircle(point.second.x*16,point.second.y*(16),3,GREEN);
    }
}

void Portal_Handler::PopulatePortals()
{
    portal_points =
    {
        {1,{Rectangle{12,9,32,26}}},
        {2,{Rectangle{8,17,32,26}}},
        {3,{Rectangle{21,5,32,26}}}
    };
}

void Portal_Handler::DrawPortals()
{
    for (int i =1; i <= portal_points.size(); i++)
    {
        // portal_points[i].x = portal_points[i].x * 16;
        // portal_points[i].y = portal_points[i].y * 16;
        DrawRectangleLines(portal_points[i].x*16,portal_points[i].y*16,32,26,WHITE);
    }

}