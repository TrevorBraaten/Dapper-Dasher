#include "raylib.h"
#include <cmath>


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

      // Window Dimensions Array
      int windowDimensions[2];
      windowDimensions[0] = 800;
      windowDimensions[1] = 600;

    // Initializes Window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

  // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

// Nebula Variables
Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

// AnimData for Nebula
AnimData nebData {
   {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
{windowDimensions[0], windowDimensions[1] - nebula.height/8}, // Vector2 pos
0,  // int frame
{1.0/12.0}, // float updateTime
 0 // float running time
 };

AnimData neb2Data {
  {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
  {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8},
  0, // int frame
  1.0/16.0, // float running time 
  0.0
};

// Size of Nebula integer
const int sizeOfNebulae{10};
const int distanceOfNebulae {300};

AnimData nebulae[sizeOfNebulae]{};

for (int i = 0; i < sizeOfNebulae; i++)
{
  nebulae[i].rec.x = 0.0;
  nebulae[i].rec.y = 0.0;
  nebulae[i].rec.width = nebula.width/8;
  nebulae[i].rec.height = nebula.height/8;
  nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
  nebulae[i].frame = 0;
  nebulae[i].runningTime = 0.0;
  nebulae[i].updateTime = 0.0;
  nebulae[i].pos.x = windowDimensions[0] + distanceOfNebulae * i;   
}


// nebula x velocity (pixels/second)
int nebVel{-300};


// Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


  


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

      if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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



    for (int i = 0; i < sizeOfNebulae; i++)
    {
             // Update Nebula Position
      nebulae[i].pos.x += nebVel * dT;

    }

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

  // Update Scarfy's Animation Frame
        if (!IsInAir)
        {
            // Update the running time
          scarfyData.runningTime += dT;

          if (scarfyData.runningTime >= scarfyData.updateTime)
          {
            scarfyData.runningTime = 0;

              //Update Animation Frame
          scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
          scarfyData.frame++;
          if (scarfyData.frame > 5)
          {
            scarfyData.frame = 0;
          }
          }
        }

      // Update Nebula Animation Frame
      for (int i = 0; i < sizeOfNebulae; i++)
      {
      
         nebulae[i].runningTime += dT;
      if (nebulae[i].runningTime >= nebulae[i].updateTime)
      {
        nebulae[i].runningTime = 0.0;
        nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
        nebulae[i].frame++;
        if (nebulae[i].frame > 7)
        {
          nebulae[i].frame = 0;
        }
      }
      }
    
      for (int i = 0; i < sizeOfNebulae; i++)
      {
         // Draw Nebula
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
      }

      // Draww Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}