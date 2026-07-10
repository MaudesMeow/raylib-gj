#include "being.hpp"

static const Color colors[7] = {
    {255, 127, 127, 255}, // light red 0
    {255, 255, 158, 255}, // light yellow 1
    {158, 207, 255, 255}, // light blue 2
    {207, 158, 255, 255}, // ;light purple 3
    {158, 255, 158, 255}, // light green 4
    {255, 207, 158, 255}, // light orange 5
    {0, 158, 115, 255}
};

void Being::PopulateBeings(map<int, Vector2> &points_on_map)
{
    beings.push_back(Being{points_on_map[1], true,1,colors[0]});
    beings.push_back(Being{points_on_map[3], true,3,colors[2]});
    beings.push_back(Being{points_on_map[5], true,5,colors[1]});
    beings.push_back(Being{points_on_map[6], true,6,colors[2]});
    beings.push_back(Being{points_on_map[11], true,11,colors[0]});
    beings.push_back(Being{points_on_map[9], true,9,colors[1]});
}

void Being::MoveBeing(map<int, Vector2>& points_on_map, Vector2 landing_point)
{
    if (!jumping)
    {
        Vector2 target = points_on_map[target_point];

        MoveOrthogonal(pos,target, GetFrameTime() * speed,direction);

        if (Vector2Distance(pos, target) < 0.01f)
        {
            // We reached the target
            previous_point = location_point;
            location_point = target_point;

            if (location_point == 13 && is_merged)
            {
                
                is_active = false;
                
            }
            else if(location_point == 13 && !is_merged)
            {
                target_point = 10;
            }


            // Pick the next target
            if (forward)
            {
                if (is_merged && location_point == 9)
                {
                    target_point = 13;
                }
                else
                {
                    target_point++;

                    if (target_point > 12)
                        target_point = 1;
                }
            }
            else
            {
                if (is_merged && location_point == 10)
                {
                    target_point = 13;
                }
                target_point--;

                if (target_point < 1)
                    target_point = 12;
            }
        }
    }
    else
    {
        // Moving after jump
        pos = Vector2MoveTowards(pos, landing_point, GetFrameTime() * speed);

        if (Vector2Distance(pos, landing_point) < 0.01f)
        {
            // Find the closest point on the map
            float distance = 1000.f;
            int closest_point = location_point;

            for (int i = 1; i < points_on_map.size(); i++)
            {
                float current_distance = Vector2Distance(pos, points_on_map[i]);

                if (current_distance < distance)
                {
                    distance = current_distance;
                    closest_point = i;
                }
            }

            previous_point = location_point;
            location_point = closest_point;

            // Pick the next target based on direction
            if (forward)
            {
                target_point = location_point + 1;

                if (target_point > 12)
                    target_point = 1;
            }
            else
            {
                target_point = location_point - 1;

                if (target_point < 1)
                    target_point = 12;
            }



            jumping = false;
            can_jump = true;
        }
    }


    rep.x = (pos.x - 0.3f) * 16;
    rep.y = (pos.y - 0.5f) * 16;
    sprite_pos.x = (pos.x - 0.5f) * 16;
    sprite_pos.y = (pos.y - 0.75f) * 16;
}
void Being::DrawBeing()
{
    for (auto& being : beings)
    {
        // DrawTextureEx(being.sprite,Vector2{being.rep.x,being.rep.y},0,1,being.color);
        // DrawRectangleRec(being.rep,being.color);
    
    

        int numFrames = 2;
        int frameWidth = being.sprite.width / numFrames; // Width of a single frame
        int frameHeight = being.sprite.height; // Assuming all frames have the same height
        float frameTime = 0.3f; // Time per frame in seconds 
        int currentFrame = static_cast<int>(GetTime() / frameTime) % numFrames;

        Rectangle src = 
        {
            (float)(frameWidth * currentFrame), // X position of the current frame
            0, // Y position of the current frame (assuming a single row of frames)
            (float)frameWidth, // Width of the current frame
            (float)frameHeight // Height of the current frame  
        } ;

        Rectangle dest = 
        {
            being.sprite_pos.x, // X position on the screen
            being.sprite_pos.y, // Y position on the screen
            (float)frameWidth , // Width of the drawn framed)
            (float)frameHeight// Height of the drawn frame (scaled)
        };

        DrawTexturePro(being.sprite,src,dest,{0,0},0,being.color);
        
       
    }

}
void DeleteBeing(vector<Being> &beings)
{
    

    for (int i = beings.size() - 1; i >= 0; i--)
    {
        

        if (!beings[i].is_active)
        {
            
            beings.erase(beings.begin() + i);
        }
    }
}


void MergeTwoBeings(vector<Being> &beings, int i, int j)
{
    Being& b1 = beings[i];
    Being& b2 = beings[j];

    Color temp_color;

    if ((ColorIsEqual(b1.color, colors[0]) && ColorIsEqual(b2.color, colors[1])) ||
        (ColorIsEqual(b1.color, colors[1]) && ColorIsEqual(b2.color, colors[0]))
        )
        {
            temp_color = colors[5];
        }


 
    if ((ColorIsEqual(b1.color, colors[2]) && ColorIsEqual(b2.color, colors[1])) ||
        (ColorIsEqual(b1.color, colors[1]) && ColorIsEqual(b2.color, colors[2]))
        )
        {
            temp_color = colors[4];
        }

    if ((ColorIsEqual(b1.color, colors[0]) && ColorIsEqual(b2.color, colors[2])) ||
        (ColorIsEqual(b1.color, colors[2]) && ColorIsEqual(b2.color, colors[0]))
        )
        {
            temp_color = colors[3];
        }       
    Being newBeing =
    {
        b1.pos,
        b1.forward,
        b1.location_point,
        temp_color
    };

    newBeing.pos.x = (b1.pos.x + b2.pos.x) / 2;
    newBeing.pos.y = (b1.pos.y + b2.pos.y) / 2;

    
    newBeing.target_point = b1.target_point;
    newBeing.speed = 3.5;
    newBeing.jumping = false;
    newBeing.can_jump = false;
    newBeing.can_jump = false;
    newBeing.landing_point = Vector2Zero();
    newBeing.is_merged = true;
    newBeing.sprite = red_blob;
    newBeing.rep = Rectangle{b1.pos.x*16,b1.pos.y*16,9,10};
    newBeing.sprite_pos.x = b1.rep.x;
    newBeing.sprite_pos.y = b1.rep.y;

    
    if (i > j)
        swap(i, j);

    beings.erase(beings.begin() + j);
    beings.erase(beings.begin() + i);

    
    beings.push_back(newBeing);
}

void SplitTwoBeings(vector<Being> &beings, Being &merged_being)
{

    

    Color temp_color_1 = RED;
    Color temp_color_2 = YELLOW;

    if (ColorIsEqual(merged_being.color,colors[5]))
    {
        temp_color_1 = colors[0];
        temp_color_2 = colors[1];
    } 
    else if (ColorIsEqual(merged_being.color,colors[4]))
    {
        temp_color_1 = colors[2];
        temp_color_2 = colors[1];
    } 
    else if (ColorIsEqual(merged_being.color,colors[3]))
    {
        temp_color_1 = colors[0];
        temp_color_2 = colors[2];
    } 



    merged_being.is_active = false;
     Being newBeing =
    {
        merged_being.pos,
        merged_being.forward,
        merged_being.location_point,
        temp_color_1
    };

    newBeing.pos.x = (merged_being.pos.x);
    newBeing.pos.y = (merged_being.pos.y);
    if (merged_being.target_point == 13 && merged_being.forward)
    {
        newBeing.target_point = 10;
    }
    else if (merged_being.target_point == 13 && !merged_being.forward)
    {
        newBeing.target_point = 9;
    }
    else
    {
        newBeing.target_point = 10;
    }
    
    
    newBeing.speed = 3.5;
    newBeing.jumping = false;
    newBeing.can_jump = false;

    newBeing.landing_point = Vector2Zero();
    newBeing.is_merged = false;
    newBeing.sprite = red_blob;
    newBeing.rep = Rectangle{newBeing.pos.x*16,newBeing.pos.y*16,9,10};
    newBeing.sprite_pos.x = newBeing.rep.x;
    newBeing.sprite_pos.y = newBeing.rep.y;   
    

    int temp_y =0;
    int temp_x = 0;

    if (merged_being.direction == 0)
    {
        temp_y = -3;
    }
    else if(merged_being.direction ==1)
    {
        temp_x = 3;
    }
    else if(merged_being.direction == 2)
    {
        temp_y = 3;
    }
    else
    {
        temp_x = -3;
    }
    Being newBeing2 =
    {
        merged_being.pos,
        merged_being.forward,
        merged_being.location_point,
        temp_color_2
    };

    newBeing2.pos.x = (merged_being.pos.x+temp_x);
    newBeing2.pos.y = (merged_being.pos.y+temp_y);

    if (merged_being.target_point == 13 && merged_being.forward)
    {
        newBeing2.target_point = 10;
    }
    else if (merged_being.target_point == 13 && !merged_being.forward)
    {
        newBeing2.target_point = 9;
    }
    else
    {
        newBeing2.target_point = 10;
    }

    newBeing2.speed = 3.5;
    newBeing2.jumping = false;
    newBeing2.can_jump = false;
    newBeing2.landing_point = Vector2Zero();
    newBeing2.is_merged = false;
    newBeing.is_active = true;
    newBeing2.sprite = red_blob;
    newBeing2.rep = Rectangle{newBeing2.pos.x*16,newBeing2.pos.y*16,9,10};
    newBeing2.sprite_pos.x = newBeing2.rep.x;
    newBeing2.sprite_pos.y = newBeing2.rep.y;

    beings.push_back(newBeing);
    beings.push_back(newBeing2);


}


void MoveOrthogonal(Vector2 &pos,const Vector2 &target, float step, int &direction)
{
    if (fabsf(pos.x - target.x) > 0.01f)
    {
        if (pos.x < target.x)
        {
            pos.x = min(pos.x + step, target.x);
            direction = 3;
        }

        else
        {
            pos.x = max(pos.x - step, target.x);
            direction = 1;
        }
            
        
        
    }
    else if (fabsf(pos.y - target.y) > 0.01f)
    {
        if (pos.y < target.y)
        {
            pos.y = min(pos.y + step, target.y);
            direction =2;
        }
            
        else
        {
            pos.y = max(pos.y - step, target.y);
            direction = 0;
        }
            
    }
}