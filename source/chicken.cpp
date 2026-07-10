#include "chicken.hpp"


static const int starting_vals[7] = {
    1,
    3,
    5,
    7,
    9,
    10,
    11
};

void Chicken::PopulateChickens(map<int, Vector2>& points_on_map)
{
   
    
    for (int i = chickens.size() - 1; i >= 0; --i)
    {
        if (!chickens[i].active)
        {
            chickens.erase(chickens.begin() + i);
            
        }
    }

    if (chickens.size() > 4)
        return;

    int ran1  = GetRandomValue(0, 6);;
    bool exists;


    int temp_val = starting_vals[ran1];

    do
    {
        ran1 = GetRandomValue(0, 6);
        temp_val = starting_vals[ran1];
        exists = false;
        for (const auto& chicken : chickens)
        {
            if (chicken.location_point == temp_val)
            {
                exists = true;
                break;
            }
        }

    } while (exists);
    int temp_start_x_offset = 0;
    int temp_end_x_offset = 0;
    int temp_start_y_offset = 0;
    int temp_end_y_offset = 0;
    int temp_direction = 1;

    if (temp_val == 1 || temp_val == 5 || temp_val == 9)
    {
        temp_start_x_offset = -15;
        temp_end_x_offset = 10;
        temp_direction = -1;
    }
    else if (temp_val == 3 || temp_val == 7 || temp_val == 11)
    {
        temp_start_x_offset = 10;
        temp_end_x_offset = -10;
        temp_direction = 1;
    }
    else if (temp_val == 10)
    {
        temp_start_x_offset = 0;
        temp_end_x_offset = 0;
        temp_start_y_offset = 10;
        temp_end_y_offset = -10;
        temp_direction = 1;
    }

    Chicken temp_chicken = Chicken{
        Vector2{
            points_on_map[temp_val].x + temp_start_x_offset,
            points_on_map[temp_val].y + temp_start_y_offset,
        },
        temp_val,
        3
    };

    temp_chicken.sprite = chicken_sprite;
    temp_chicken.direction = temp_direction;
    temp_chicken.end_x_offset = temp_end_x_offset;
    temp_chicken.end_y_offset = temp_end_y_offset;

    temp_chicken.rep.x = (temp_chicken.pos.x - 0.3) * 16;
    temp_chicken.rep.y = (temp_chicken.pos.y - 0.3) * 16;
    temp_chicken.sprite_pos.x = (temp_chicken.pos.x - 0.5) * 16;
    temp_chicken.sprite_pos.y = (temp_chicken.pos.y - 0.75) * 16;

    chickens.push_back(temp_chicken);
}

void Chicken::MoveChickens(map<int, Vector2> &points_on_map, Vector2 landing_point)
{   
    timer -= GetFrameTime();
    
    if (timer <= 0)
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
            Vector2 target = Vector2{points_on_map[target_point].x+end_x_offset,points_on_map[target_point].y+end_y_offset};
            pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
            if (Vector2Distance(target,pos) < 0.01f)
            {
                active = false;
                timer=4;
            }
        }



        rep.x = (pos.x-0.3) * 16;
        rep.y = (pos.y-0.5) * 16;
        sprite_pos.x = (pos.x-0.5) * 16;
        sprite_pos.y = (pos.y-0.75) * 16;
    }

    

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
            (float)chicken.direction*frameWidth, // Width of the current frame
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
        if (chicken.active)
        {
            DrawTexturePro(chicken.sprite,src,dest,{0,0},0,WHITE);
        }
        
    //    DrawRectangleLinesEx(chicken.rep,1,RED);
        
       
    }
}

