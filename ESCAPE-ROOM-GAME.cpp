#include "raylib.h"
typedef enum { START, PLAYING, PAUSED, GAMEOVER } GameState;

int main()
{
    // Window settings
    const int screenWidth = 1000;
    const int screenHeight = 700;
    const int wallHeight = 400;

    InitWindow(screenWidth, screenHeight, "ESCAPE ROOM");
    SetTargetFPS(60);

    Texture2D floorTexture = LoadTexture("FLOOR.png");
    Texture2D wallTexture = LoadTexture("wall.png");
    Texture2D doorTexture = LoadTexture("DOOR.png");
    Texture2D clockTexture = LoadTexture("clockhehe.png");
    Texture2D windowTexture = LoadTexture("windowhehe.png");
    Texture2D shelfTexture = LoadTexture("SHELF.png");
    Texture2D computerTexture = LoadTexture("comp.png");
    Texture2D playerTexture = LoadTexture("player150.png");

    GameState state = START;
    Rectangle computer = { 0, 232, 145, 145 };//ZAINAB
    // PLAYER SETTINGS
    Rectangle player = { 700, 500, 200, 200 };//MARYAM

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
        else if (state == PLAYING) //ZAINAB
        {
            float speed = 350.0f;
            float ft = GetFrameTime();
            if (IsKeyDown(KEY_UP))
                player.y = player.y - (ft * speed);

            if (IsKeyDown(KEY_DOWN))
                player.y = player.y + (ft * speed);

            if (IsKeyDown(KEY_LEFT))
                player.x = player.x - (ft * speed);

            if (IsKeyDown(KEY_RIGHT))
                player.x = player.x + (ft * speed);

            if (player.x > screenWidth - player.width)
                player.x = screenWidth - player.width;
            if (player.y > screenHeight - player.height)
                player.y = screenHeight - player.height;
            if (player.x < 0)
                player.x = 0;
            if (player.y < wallHeight - player.height)
                player.y = wallHeight - player.height;
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
        else if (state == PLAYING || state == PAUSED)
        {
            ClearBackground(DARKGRAY);
            // ROOM

            //WALL
            DrawTexturePro(wallTexture,
                { 0, 0, (float)wallTexture.width, (float)wallTexture.height },
                { 0,0,(float)screenWidth, (float)wallHeight },
                { 0,0 }, 0.0f, WHITE);

            //FLOOR
            DrawTexturePro(floorTexture,
                { 0, 0,(float)floorTexture.width, (float)floorTexture.height },//original rectangle dim
                { 0,(float)wallHeight,(float)screenWidth, (float)(screenHeight - wallHeight) },//x,y,width,height
                { 0,0 }, 0.0f, WHITE);//color

            //CLOCK
            DrawTexture(clockTexture, 450, 50, WHITE);

            //SHELF
            DrawTexture(shelfTexture, 380, 189, WHITE);

            //WINDOW
            DrawTexture(windowTexture, 600, 150, WHITE);

            //DOOR
            //DrawRectangle(250, wallHeight-152, 80, 155, DARKPURPLE);//AS y(axis point)+235(doorheight)=wallHeight so..
            DrawTexturePro(doorTexture,
                { 0, 0, (float)doorTexture.width, (float)doorTexture.height },
                { 230, wallHeight - 235, (float)doorTexture.width, (float)doorTexture.height },
                { 0,0 }, 0.0f, WHITE);
            // Player 
            DrawTexture(playerTexture, player.x, player.y, WHITE);
            //COMPUTER
            DrawTexture(computerTexture, computer.x, computer.y, WHITE);
        }
        EndDrawing();
    }

    //UNLOADING TEXTURE
    UnloadTexture(floorTexture);
    UnloadTexture(wallTexture);
    UnloadTexture(doorTexture);
    UnloadTexture(clockTexture);
    UnloadTexture(windowTexture);
    UnloadTexture(shelfTexture);
    UnloadTexture(computerTexture);
    UnloadTexture(playerTexture);

    CloseWindow();
    return 0;
}