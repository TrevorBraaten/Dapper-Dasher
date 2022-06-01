#include "raylib.h"




int main()
{

    // Window Variables
   const int windowWidth{2000};
   const int windowHeight{1200};

    // Initializes Window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};
    const int jumpVel{-22};
    bool IsInAir = false;


    // Rectangle Dimensions
    const int width{50};
    const int height{80};

    // Rectangle position
    int pos_y{windowHeight - height};
    int pos_x{1100};
    int velocity{0};
 
    // Sets Target FPS
    SetTargetFPS(60);

    // Game While Loop
    while (!WindowShouldClose())
    {
        // Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

      DrawRectangle(pos_x, pos_y, width, height, BLUE);


      if (pos_y >= windowHeight - height )
      {
        // Rectangle is on the ground
        velocity = 0;
        IsInAir = false;
      }
      else
      {
        // Rectangle is in the air
        velocity += gravity;
        IsInAir = true;
      }



      // Check For Jumping
      if (IsKeyPressed(KEY_SPACE) && !IsInAir)
      {
        velocity += jumpVel;
      }
        // Update Position
        pos_y += velocity;

        EndDrawing();

    }
    CloseWindow();
}