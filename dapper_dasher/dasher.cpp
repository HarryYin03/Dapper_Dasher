#include "raylib.h"

int main()
{

    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // player character size

    const int width{50};
    const int height{80};

    // acceleartion due to gravity (pixels/frame)/frame)
    const int gravity{1};

    // rectangle in the air
    bool isInAir{false};

    // jump velocity
    const int jumpVel{-22};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // perform a ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;
        }

        // update the velocity
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}