#include "raylib.h"
typedef enum { START, PLAYING, PAUSED, GAMEOVER } GameState;

int main()
{
    // Window settings
    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "ESCAPE ROOM");
    SetTargetFPS(60);

    GameState state = START;

    // MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        //START STATE   
        if (state == START)//ZAINAB
        {
            if (IsKeyPressed(KEY_S))
            {
                state = PLAYING;
            }
        }


        // DRAW EVERYTHING

        BeginDrawing();
        if (state == START)// ZAINAB
        {
            ClearBackground(BLACK);
            DrawText("ESCAPE ROOM", (screenWidth - MeasureText("ESCAPE ROOM", 60)) / 2, 90, 60, WHITE);
            DrawText("USE ARROW KEYS FOR PLAYER MOVEMENT. ", (screenWidth - MeasureText("USE ARROW KEYS FOR PLAYER MOVEMENT. ", 28)) / 2, 210, 28, LIGHTGRAY);
            DrawText("PRESS E TO INTERACT WITH THE OBJECTS. ", (screenWidth - MeasureText("PRESS E TO INTERACT WITH THE OBJECTS. ", 24)) / 2, 255, 24, LIGHTGRAY);
            DrawText("DESCRIPTION: YOU HAVE 5 MINS AND 3 LIVES TO ESCAPE THE ROOM  ", (screenWidth - MeasureText("DESCRIPTION: YOU HAVE 5 MINS AND 3 LIVES TO ESCAPE THE ROOM  ", 22)) / 2, 340, 22, LIGHTGRAY);
            DrawText("BY FINDING CLUES AND SOLVING THE RIDDLES BEFORE THE REAPER", (screenWidth - MeasureText("BY FINDING CLUES AND SOLVING THE RIDDLES BEFORE THE REAPER", 22)) / 2, 375, 22, LIGHTGRAY);
            DrawText("COMES IN AND KILLS YOU", (screenWidth - MeasureText("COMES IN AND KILLS YOU", 22)) / 2, 410, 22, LIGHTGRAY);
            DrawText("PRESS S TO START!", (screenWidth - MeasureText("PRESS S TO START!", 36)) / 2, 520, 36, YELLOW);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}