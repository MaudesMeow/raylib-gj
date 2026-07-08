#include "globals.hpp"
#include "being.hpp"
#include "input.hpp"
#include "portals.hpp"

#define BASE_WIDTH 720
#define BASE_HEIGHT 720
#define PROJECT_NAME "Game"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
    #define GLSL_VERSION (100)
#else
    #define GLSL_VERSION (330)
#endif


// ------------------------------------------------------variables 


static int screen_width, screen_height, screen_scale;
static Texture2D level_1_map;
static Camera2D camera;
map<int, Vector2> points_on_map;

Being being_instance;
bool map_recs;


Portal_Handler portal_handler;


// -------------------------------------------------------functions 
void Init(void);
void Update(void);
void Draw(void);
void Unload(void);
void UpdateDrawFrame(void);

void DrawMapRecs()
{
        for (int i = 0; i < GetScreenHeight()/16; i++)
        {
            for (int j =0; j < GetScreenWidth()/16; j++)
            {
                DrawRectangleLines(i *16,j*16,16,16,LIGHTGRAY);
            }
        }
}



// ---------------------------------------------------------------------------MAIN FUNCTION
int main(void)
{
    Init();

#ifdef PLATFORM_WEB
    // (main loop function, fps, simulate infinite loop)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    while (!WindowShouldClose())
    {
        
        UpdateDrawFrame();
    }
#endif
    Unload();
    return 0;
}
// ---------------------------------------------------------------------------INIT FUNCTION
void Init(void)
{
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(BASE_WIDTH, BASE_HEIGHT, PROJECT_NAME);

    SetWindowMinSize(BASE_WIDTH, BASE_HEIGHT);
    SetTargetFPS(60);

    // ------------------------------------------------------- Load Textures
    level_1_map = LoadTexture("assets/level_1.png");

    // -------------------------------------------------------- Set Variables

    
    map_recs = false;
    camera = { 0 };
    camera.target = (Vector2){ 0,0 };
    camera.offset = (Vector2){ 0,0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.8;
    points_on_map = 
    {
        {1,{2,6}},
        {2,{19,6}},
        {3,{19,10}},
        {4,{2,10}},
        {5,{2,14}},
        {6,{19,14}},
        {7,{19,18}},
        {8,{2,18}},
        {9,{2,22}},
        {10,{22,22}},
        {11,{22,2}},
        {12,{2,2}}


    };

    portal_handler.PopulateLandingPoints();
    portal_handler.PopulatePortals();
    
    being_instance = Being{points_on_map[1], true,1};



}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{
    UserInput(being_instance);
    being_instance.MoveBeing(points_on_map,portal_handler.landing_points);
    
    for (int i =1; i <= portal_handler.portal_points.size(); i++)
    {
        if (CheckCollisionRecs(portal_handler.portal_points[i],being_instance.rep))
        {
            cout << "colliding! " << endl;
        }
    }

    if (IsKeyPressed(KEY_A))
    {
        map_recs = !map_recs;
    }


    
}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{

    
    ClearBackground(BLACK);
    BeginMode2D(camera);

        DrawTextureEx(level_1_map,Vector2{0,0},0,1,WHITE);
        for (auto& point : points_on_map)
        {
            DrawCircle(point.second.x*16,point.second.y*(16),3,RED);
        }
        portal_handler.DrawLandingPoints();
        portal_handler.DrawPortals();
        being_instance.DrawBeing();
        
        
        if (map_recs)
        {
            DrawMapRecs();
        }

    EndMode2D();

}
// ---------------------------------------------------------------------------UNLOAD FUNCTION
void Unload(void)
{

#ifdef PLATFORM_WEB
    emscripten_exit_with_live_runtime();
#endif
    CloseWindow();
}
// ---------------------------------------------------------------------------UPDATE AND DRAW FUNCTION
void UpdateDrawFrame(void)
{
    Update();

    BeginDrawing();
        Draw();
    EndDrawing();
}

