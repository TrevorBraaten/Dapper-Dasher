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

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0; 
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;


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
        // Update Position
        scarfyPos.y += velocity * dT;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);



        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
}