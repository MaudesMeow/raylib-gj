#ifndef PORTALS_HEADER
#define PORTALS_HEADER


#include "globals.hpp"


struct Portal
{
    Vector2 pos;
    Rectangle rep;
    Vector2 landing_point;
};


class Portal_Handler
{
    public:
        map<int,Portal> portals;
        

        Portal_Handler() {};

        
        void PopulatePortals();
        void DrawPortals();
        void DrawLandingPoints();

};




#endif