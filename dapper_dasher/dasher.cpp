#include "raylib.h"

int main()
{

    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};

    int nebVel{-200}; // nebula x velocity (pixels/second)
    int nebFrame{};
    const float nebUpdateTime(1.0 / 12.0);
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime(1.0 / 60.0);
    float neb2RunningTime{};

    // scarfy variable
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos; // position of scarfy
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // acceleartion due to gravity (pixels/frame)/frame)
    const int gravity{1'000};

    // rectangle in the air
    bool isInAir{false};

    // jump velocity (pixels/second)
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);

    int frame{};

    float updateTime(1.0 / 12.0); // amount of time before update the animation frame

    float runningTime{};

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        float dT = GetFrameTime();

        // perform a ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebPos.x += nebVel * dT;

        // update second nebula position
        neb2Pos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        // update scarfy animation frame
        if (!isInAir)
        {
            runningTime += dT;

            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                // updtae animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula animation frame
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

        // update nebula animation frame
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

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}