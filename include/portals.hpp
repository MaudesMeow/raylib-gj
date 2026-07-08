#ifndef PORTALS_HEADER
#define PORTALS_HEADER


#include "globals.hpp"


struct portal
{
    /* data */
};


class Portal_Handler
{
    public:
        Vector2 pos;
        map<int, Vector2> landing_points;
        map<int, Rectangle> portal_points;
        Rectangle rep;
        Texture2D sprite;
        

        Portal_Handler() {};

        void PopulateLandingPoints();
        void PopulatePortals();
        void DrawPortals();
        void DrawLandingPoints();

};




#endif