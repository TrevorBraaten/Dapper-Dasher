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

bool IsOnGround(AnimData data, int windowHeight)
{
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{

  // update running time
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime)
  {
    data.runningTime = 0.0;
    // update animation frame
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrame)
    {
      data.frame = 0;
    }
  }
  return data;
}








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
const int sizeOfNebulae{3};
const int distanceOfNebulae {500};

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

float finishLine{ nebulae[sizeOfNebulae - 1].pos.x };



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


   // Background Variable
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    // Midground Variable
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    // Foreground Variable
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    // Ends game when collision becomes true
     bool collision{};

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
        

        mgX -= 40 * dT;
        fgX -= 80 * dT;
        bgX -= 20 * dT;
        if (bgX <= -background.width*2)
        {
          bgX = 0.0;
        }

        if (mgX <= -midground.width*2)
        {
          mgX = 0.0;
        }

        if (fgX <= -foreground.width*2)
        {
          fgX = 0.0;
        }






      // draw the background
      Vector2 bg1Pos{bgX, 0.0};
      DrawTextureEx(background, bg1Pos, 0.0, 3.2, WHITE);
      Vector2 bg2Pos{bgX + background.width*2, 0.0};
      DrawTextureEx(background, bg2Pos, 0.0, 3.2, WHITE);
      // Draw the Midground



     Vector2 mg1Pos{mgX, 0.0};
     Vector2 mg2Pos{mgX + midground.width*2, 0.0};
      DrawTextureEx(midground, mg1Pos, 0.0, 3.2, WHITE);
      DrawTextureEx(midground, mg2Pos, 0.0, 3.2, WHITE);

      // Draw the Foreground
      Vector2 fg1Pos{fgX, 0.0};
      Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
      DrawTextureEx(foreground, fg1Pos, 0.0, 3.2, WHITE);
      DrawTextureEx(foreground, fg2Pos, 0.0, 3.2, WHITE);



      if (IsOnGround(scarfyData, windowDimensions[1]))
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

      // Update Finish Line
      finishLine += nebVel * dT;


        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

  // Update Scarfy's Animation Frame
        if (!IsInAir)
        {
           scarfyData = updateAnimData(scarfyData, dT, 5);
        }

      // Update Nebula Animation Frame
    
     for (int i = 0; i < sizeOfNebulae; i++)
     {

        nebulae[i] = updateAnimData(nebulae[i], dT, 7);

     }

      float pad{50};
      for (AnimData nebula : nebulae)
      {
        Rectangle nebRec{
          nebula.pos.x + pad,
          nebula.pos.y + pad,
          nebula.rec.width - 2*pad, 
          nebula.rec.height - 2*pad
        };
        Rectangle scarfyRec{
          scarfyData.pos.x,
          scarfyData.pos.y,
          scarfyData.rec.width,
          scarfyData.rec.height
        };

        if (CheckCollisionRecs(nebRec, scarfyRec))
        {
          collision = true;
        }
      }

      if (collision)
      {
        // Lose the Game
        DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 70, RED);
      }

     else if (scarfyData.pos.x >= finishLine)
     {
       // Win the game
       DrawText("You Win!", windowDimensions[0]/4, windowDimensions[1]/2, 70, RED);
     }
      

      else
      {

  for (int i = 0; i < sizeOfNebulae; i++)
      {
         // Draw Nebula
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
      }

      // Draww Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);


      }

        EndDrawing();
    }

    UnloadTexture(foreground);
    UnloadTexture(midground);
    UnloadTexture(background);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();



}