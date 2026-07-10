#include "chicken.hpp"


void Chicken::PopulateChickens(map<int, Vector2> &points_on_map)
{
    chickens.push_back(Chicken{Vector2{points_on_map[1].x,points_on_map[1].y-20},1,WHITE});

}


void Chicken::MoveChickens(map<int, Vector2> &points_on_map, Vector2 landing_point)
{
    if (flying_in)
    {
        Vector2 target = points_on_map[location_point];
        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
        if (Vector2Distance(target,pos) < 0.01f)
        {
            flying_in = false;
        }
    }
    else if (!flying_in && !flying_out)
    {
        Vector2 target = points_on_map[target_point];
        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
       if (Vector2Distance(target,pos) < 0.01f)
        {
            flying_out = true;
        }
    }
    else if (!flying_in && flying_out)
    {
        Vector2 target = Vector2{points_on_map[target_point].x + 30,points_on_map[target_point].y};
        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
        if (Vector2Distance(target,pos) < 0.01f)
        {
            active = false;
        }
    }



    rep.x = (pos.x-0.3) * 16;
    rep.y = (pos.y-0.5) * 16;
    sprite_pos.x = (pos.x-0.5) * 16;
    sprite_pos.y = (pos.y-0.75) * 16;
}

void Chicken::DrawChickens()
{
    for (auto& chicken : chickens)
    {
        // DrawTextureEx(being.sprite,Vector2{being.rep.x,being.rep.y},0,1,being.color);
        // DrawRectangleRec(being.rep,being.color);
    
    

        int numFrames = 3;
        int frameWidth = chicken.sprite.width / numFrames; // Width of a single frame
        int frameHeight = chicken.sprite.height; // Assuming all frames have the same height
        float frameTime = 0.3f; // Time per frame in seconds 
        int currentFrame = static_cast<int>(GetTime() / frameTime) % numFrames;

        Rectangle src = 
        {
            (float)(frameWidth * currentFrame), // X position of the current frame
            0, // Y position of the current frame (assuming a single row of frames)
            (float)-frameWidth, // Width of the current frame
            (float)frameHeight // Height of the current frame  
        } ;

        Rectangle dest = 
        {
            chicken.sprite_pos.x, // X position on the screen
            chicken.sprite_pos.y, // Y position on the screen
            (float)frameWidth , // Width of the drawn framed)
            (float)frameHeight// Height of the drawn frame (scaled)
        };

        if (chicken.flying_in || chicken.flying_out)
        {
            chicken.sprite = flying_chicken_sprite;
        }
        else
        {
            chicken.sprite = chicken_sprite;
            
        }
        DrawTexturePro(chicken.sprite,src,dest,{0,0},0,chicken.color);
       
        
       
    }
}