#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "globals.hpp"


class Being
{

  public:
    
    Vector2 pos;

    bool forward;
    bool jumping;
    bool can_jump;

    Rectangle rep;

    float speed;
    int location_point;
    int target_point;
    int previous_point;

    Being() : pos{0,0} {};
    Being(Vector2 pos, bool forward,int location_point) 
    {
      this->pos = pos;
      this->forward = forward;
      this->location_point = location_point;
      previous_point = location_point;
      target_point = location_point+1;
      rep = {pos.x,pos.y,16,16};
      speed = 3.5;
      jumping = false;
      can_jump = false;
    }

    
    void MoveBeing(map<int, Vector2> &points_on_map,map<int, Vector2>& landing_points);
    void DrawBeing();


};



#endif


