#include "raylib.h"



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
Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
Vector2 nebPos{windowWidth, windowHeight -nebRec.height};

// nebula x velocity (pixels/second)
int nebVel{-600};



// Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
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


        // Update Scarfy Position
        scarfyPos.y += velocity * dT;

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


        // Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

      // Draww Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);



        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}