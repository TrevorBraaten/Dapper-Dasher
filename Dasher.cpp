#include "raylib.h"




int main()
{

    // Window Variables
   const int window_width{1200};
   const int window_height{800};

    // Initializes Window
    InitWindow(window_width, window_height, "Dapper Dasher!");

    // Rectangle Dimensions
    const int rec_width{200};
    const int rec_height{100};

    // Rectangle position
    int pos_y{600};
    int pos_x{250};
    int velocity{0};

    
    // Sets Target FPS
    SetTargetFPS(60);


    // Game While Loop
    while (!WindowShouldClose())
    {

        // Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

        pos_y += velocity;

      //  DrawRectangle(window_width/2, rec_pos_y, rec_width, rec_height, BLUE);
        DrawRectangle(pos_x, pos_y, rec_width, rec_height, BLUE);

        if (IsKeyPressed(KEY_SPACE))
        {

            velocity -= 10;

           // pos_y -= velocity;
          //  pos_x += velocity;
        }





        EndDrawing();

    }
    CloseWindow();
}