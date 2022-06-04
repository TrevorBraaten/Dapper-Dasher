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

      if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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
      nebData.pos.x += nebVel * dT;

  // Update the Second Nebula's Position
    neb2Data.pos.x += nebVel * dT;




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
      nebData.runningTime += dT;
      if (nebData.runningTime >= nebData.updateTime)
      {
        nebData.runningTime = 0.0;
        nebData.rec.x = nebData.frame * nebData.rec.width;
        nebData.frame++;
        if (nebData.frame > 7)
        {
          nebData.frame = 0;
        }
      }

      // Update Nebula 2 Animation Frame
      neb2Data.runningTime += dT;
      if (neb2Data.runningTime >= neb2Data.updateTime)
      {
        neb2Data.runningTime = 0.0;
        neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
        neb2Data.frame++;
        if (neb2Data.frame > 7)
        {
          neb2Data.frame = 0;
        }
      }
    

        // Draw Nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);

        // Draw The Second Nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);


      // Draww Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);



        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}