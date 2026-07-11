#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "globals.hpp"

class Portal;

class Being
{

  public:
    
    vector<Being> beings;
    Vector2 pos;
    // Vector2 landing_point;
    Vector2 sprite_pos;

    bool forward;
    bool jumping;
    bool can_jump;
    bool is_merged;
    bool is_active;

    

    float speed;
    int location_point;
    int being_landing_point;
    int target_point;
    int previous_point;
    int direction;
    Texture2D sprite;
    Rectangle rep;
    Color color;

    Being() : pos{0,0} {};
    Being(Vector2 pos, bool forward, int location_point, Color color) 
    {
      this->pos = pos;
      this->sprite_pos = pos;

      this->forward = forward;
      this->location_point = location_point;
      this->color = color;

      previous_point = location_point;
      target_point = location_point + 1;

      rep = {pos.x * 16, pos.y * 16, 9, 10};

      speed = 3.5;
      jumping = false;
      can_jump = false;
      being_landing_point =1;

      is_merged = false;
      is_active = true;

      direction = 0;

      sprite = red_blob;
    }

    void PopulateBeings(map<int, Vector2> &points_on_map);
    void MoveBeing(map<int, Vector2> &points_on_map, map<int,Portal>& portals);
  
    void DrawBeing();
    


};


void MergeTwoBeings(vector<Being> &beings, int i, int j);
void SplitTwoBeings(map<int, Vector2> &points_on_map,vector<Being> &beings,int merged_index);
void MoveOrthogonal(Vector2 &pos,const Vector2 &target, float step, int &direction);
void DeleteBeing(vector<Being> &beings);


#endif


