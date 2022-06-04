#include "raylib.h"


struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;



};


int main()
{

    // Window Variables
   const int windowWidth{1600};
   const int windowHeight{1000};

    // Initializes Window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

// Nebula Variables
Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

// AnimData for Nebula
AnimData nebData {
   {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
{windowWidth, windowHeight - nebula.height/8}, // Vector2 pos
0,  // int frame
{1.0/12.0}, // float updateTime
 0 // float running time
 };

AnimData neb2Data {
  {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
  {windowWidth + 300, windowHeight - nebula.height/8},
  0, // int frame
  1.0/16.0, // float running time 
  0.0
};


Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};


// Nebula Animation Variables
int nebFrame{};
const float nebUpdateTime{1.0/12.0};
float nebRunningTime{0};

// Nebula 2 Variables
int neb2Frame{};
const float neb2UpdateTime{1.0/16.0};
float neb2RunningTime;


// nebula x velocity (pixels/second)
int nebVel{-300};


// Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0; 
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;


  // Animation Frame
  int frame{};
  // Update Scarfys Animationn 1
  const float updateTime {1.0/12.0};
  // Update Animation Frame 
  float runningTime{0};


    int velocity{0};
    // jump velocity (pixels/second)
    const int jumpVel{-600};
    bool IsInAir {false};

    // Sets Target FPS
    SetTargetFPS(60);

    // Game While Loop
    while (!WindowShouldClose())
    {
        // delta time (time since the last frame)
        const float dT{GetFrameTime()};

        // Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

      if (scarfyPos.y >= windowHeight - scarfyRec.height)
      {
        // Rectangle is on the ground
        velocity = 0;
        IsInAir = false;
      }
      else
      {
        // Rectangle is in the air
        velocity += gravity * dT;
        IsInAir = true;
      }
     
      // Check For Jumping
      if (IsKeyPressed(KEY_SPACE) && !IsInAir)
      {
        velocity += jumpVel;
      }

      // Update Nebula Position
      nebPos.x += nebVel * dT;

  // Update the Second Nebula's Position
    neb2Pos.x += nebVel * dT;




        // Update Scarfy Position
        scarfyPos.y += velocity * dT;

  // Update Scarfy's Animation Frame
        if (!IsInAir)
        {
            // Update the running time
          runningTime += dT;

          if (runningTime >= updateTime)
          {
            runningTime = 0;

              //Update Animation Frame
          scarfyRec.x = frame * scarfyRec.width;
          frame++;
          if (frame > 5)
          {
            frame = 0;
          }
          }
        }

      // Update Nebula Animation Frame
      nebRunningTime += dT;
      if (nebRunningTime >= nebUpdateTime)
      {
        nebRunningTime = 0.0;
        nebRec.x = nebFrame * nebRec.width;
        nebFrame++;
        if (nebFrame > 7)
        {
          nebFrame = 0;
        }
      }

      // Update Nebula 2 Animation Frame
      neb2RunningTime += dT;
      if (neb2RunningTime >= neb2UpdateTime)
      {
        neb2RunningTime = 0.0;
        neb2Rec.x = neb2Frame * neb2Rec.width;
        neb2Frame++;
        if (neb2Frame > 7)
        {
          neb2Frame = 0;
        }
      }
    

        // Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // Draw The Second Nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);


      // Draww Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);



        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}