#include "being.hpp"



void Being::PopulateBeings(map<int, Vector2> &points_on_map)
{
    beings.push_back(Being{points_on_map[1], true,1,RED});
    beings.push_back(Being{points_on_map[3], true,3,DARKBLUE});
    beings.push_back(Being{points_on_map[5], true,5,YELLOW});
    beings.push_back(Being{points_on_map[6], true,6,DARKBLUE});
    beings.push_back(Being{points_on_map[11], true,11,RED});
    beings.push_back(Being{points_on_map[9], true,9,YELLOW});
}

void Being::MoveBeing(map<int, Vector2>& points_on_map, Vector2 landing_point)
{
    
    if (!jumping)
    {
        Vector2 target = points_on_map[target_point];

        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);

        if (Vector2Distance(pos, target) < 0.01f)
        {
            // ----------------------------------------------------------------We reached the target
            previous_point = location_point;
            location_point = target_point;

            // ----------------------------------------------------- Pick the next target
            if (forward)
            {
                target_point++;

                if (target_point > 12)
                    target_point = 1;
            }
            else
            {
                target_point--;

                if (target_point < 1)
                    target_point = 12;
            }
        }

    }
    else if (jumping)
    {
        Vector2 target = landing_point;
        pos = Vector2MoveTowards(pos,target,GetFrameTime() * speed);
        float distance = 1000.f;
        if (Vector2Distance(pos,target) < 0.01f)
        {
            
            for (int i =1; i < points_on_map.size(); i ++)
            {
                if (Vector2Distance(pos,points_on_map[i]) < distance)
                {
                    distance = Vector2Distance(pos,points_on_map[i]);
                    if (forward)
                    {
                        target_point = i+1;
                        location_point = i;
                    }
                    else
                    {
                        target_point = i;
                        location_point = i+1;
                    }
 
                }
                cout << " count is : " << i << endl;
            }
            cout << "target point is " << target_point << endl;
            cout << "location point is " << location_point << endl;
            jumping = false;
            can_jump = true;
        }
        
    }
    else 
    {
        pos = Vector2Zero();
    }

    rep.x = (pos.x-0.5) * 16;
    rep.y = (pos.y-0.5) * 16;
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
            being.rep.x, // X position on the screen
            being.rep.y, // Y position on the screen
            (float)frameWidth , // Width of the drawn framed)
            (float)frameHeight// Height of the drawn frame (scaled)
        };

        DrawTexturePro(being.sprite,src,dest,{0,0},0,being.color);
    }

}


void MergeTwoBeings(vector<Being>& beings, int i, int j)
{
    Being& b1 = beings[i];
    Being& b2 = beings[j];

    Color temp_color;

    if ((ColorIsEqual(b1.color, RED) && ColorIsEqual(b2.color, YELLOW)) ||
        (ColorIsEqual(b1.color, YELLOW) && ColorIsEqual(b2.color, RED))
        )
        {
            temp_color = ORANGE;
        }


 
    if ((ColorIsEqual(b1.color, DARKBLUE) && ColorIsEqual(b2.color, YELLOW)) ||
        (ColorIsEqual(b1.color, YELLOW) && ColorIsEqual(b2.color, DARKBLUE))
        )
        {
            temp_color = GREEN;
        }

    if ((ColorIsEqual(b1.color, RED) && ColorIsEqual(b2.color, DARKBLUE)) ||
        (ColorIsEqual(b1.color, DARKBLUE) && ColorIsEqual(b2.color, RED))
        )
        {
            temp_color = PURPLE;
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

    
    if (i > j)
        swap(i, j);

    beings.erase(beings.begin() + j);
    beings.erase(beings.begin() + i);

    
    beings.push_back(newBeing);
}