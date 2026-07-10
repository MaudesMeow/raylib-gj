#ifndef CHICKEN_HEADER
#define CHICKEN_HEADER

#include "globals.hpp"

class Chicken
{

  public:
    
    vector<Chicken> chickens;
    Vector2 pos;
    Vector2 landing_point;
    Vector2 sprite_pos;



    bool flying_in;
    bool flying_out;
    bool active;

    float speed;
    int location_point;
    int target_point;
    int previous_point;

    Texture2D sprite;
    Rectangle rep;
    Color color;

    Chicken() : pos{0,0} {};
    Chicken(Vector2 pos, int location_point, Color color) 
    {
        this->pos = pos;
        sprite_pos = pos;
     
        this->location_point = location_point;
        this->color = color;
        previous_point = location_point;
        target_point = location_point+1;
        rep = {pos.x,pos.y,9,10};
        speed = 3.5;

        landing_point = Vector2Zero();
        active = true;
        flying_in = true;
        flying_out = false;
    
      
    }

    void PopulateChickens(map<int, Vector2> &points_on_map);
    void MoveChickens(map<int, Vector2> &points_on_map, Vector2 landing_point);
    void DrawChickens();


};



#endif