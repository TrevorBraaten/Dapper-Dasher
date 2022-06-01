#include "raylib.h"




int main()
{

    // Window Variables
   const int windowWidth{512};
   const int windowHeight{380};

    // Initializes Window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};


    // Rectangle Dimensions
    const int width{50};
    const int height{80};

    // Rectangle position
    int pos_y{windowHeight - height};
    int velocity{0};
 
    // Sets Target FPS
    SetTargetFPS(60);

    // Game While Loop
    while (!WindowShouldClose())
    {
        // Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

      DrawRectangle(windowWidth/2, pos_y, width, height, BLUE);
      
      if (pos_y >= windowHeight - height )
      {
        // Rectangle is on the ground
        velocity = 0;
      }
      else
      {
        // Rectangle is in the air
        velocity += gravity;
      }
      // Check For Jumping
      if (IsKeyPressed(KEY_SPACE))
      {
        velocity -= 10;
      }


        // Update Position
        pos_y += velocity;

        EndDrawing();

    }
    CloseWindow();
}