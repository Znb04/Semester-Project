#include "raylib.h"
typedef enum { START, PLAYING, PAUSED, GAMEOVER, BOOKRIDDLE } GameState;

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
    Texture2D livesTexture = LoadTexture("LIVES.png");

    GameState state = START;
    Rectangle computer = { 0, 232, 145, 145 };//ZAINAB
    // PLAYER SETTINGS
    Rectangle player = { 700, 500, 200, 200 };//MARYAM
    //MARYAM
    int lives = 3;
    int bookSolved = 0;      // 0 = not solved, 1 = solved
    char answer[20] = "";    // what the player types
    int letterCount = 0;     // how many letters typed
    bool submitted = false;  // has the player pressed ENTER yet?
    int result = 0;

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
            if (IsKeyPressed(KEY_P))
            {
                state = PAUSED;
            }

        }
        else if (state == PAUSED)// ZAINAB
        {
            if (IsKeyPressed(KEY_C))
            {
                state = PLAYING;
            }
            if (IsKeyPressed(KEY_S))
            {
                player.x = 700;
                player.y = 500;
                state = PLAYING;
            }
            if (IsKeyPressed(KEY_G))
            {
                state = GAMEOVER;
            }
        }
        else if (state == GAMEOVER)//ZAINAB
        {
            if (IsKeyPressed(KEY_S))
            {
                player.x = 700;
                player.y = 500;

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
        else if (state == PLAYING || state == PAUSED || state == BOOKRIDDLE)//MARYAM
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

            //LIVE 
            DrawText(TextFormat("%d LIVES", lives), 20, 20, 30, BLACK);

            //WINDOW
            DrawTexture(windowTexture, 600, 150, WHITE);
            //LIVES
            DrawTexture(livesTexture, 150, 15, WHITE);

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

            if (state == PAUSED)//ZAINAB
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("PAUSED", (screenWidth - MeasureText("PAUSED", 60)) / 2, 150, 60, WHITE);
                DrawText("C : CONTINUE", (screenWidth - MeasureText("C : CONTINUE", 36)) / 2, 260, 36, WHITE);
                DrawText("S : RESTART", (screenWidth - MeasureText("S : RESTART", 36)) / 2, 330, 36, WHITE);
                DrawText("G : END GAME", (screenWidth - MeasureText("G : END GAME", 36)) / 2, 400, 36, WHITE);
            }
            else if (state == BOOKRIDDLE)// MARYAM
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("BOOK RIDDLE", (screenWidth - MeasureText("BOOK RIDDLE", 60)) / 2, 120, 50, WHITE);
                if (bookSolved == 1 && result == 0)
                {
                    //IF OPEN AGAINAFTER SOLVED
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS R TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS R TO RETURN TO THE GAME.", 24)) / 2, 620, 24, LIGHTGRAY);
                }
                else
                {
                    DrawText("WHAT HAS A KEY BUT DOESN'T UNLOCK ANYTHING?", (screenWidth - MeasureText("WHAT HAS A KEY BUT DOESN'T UNLOCK ANYTHING?", 30)) / 2, 220, 30, WHITE);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(answer, 310, 310, 30, BLACK);//TYPED TEXT
                    if (!submitted)
                    {
                        DrawText("TYPE YOUR ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE YOUR ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, LIGHTGRAY);
                    }
                    else
                    {
                        if (result == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 420, 36, GREEN);
                        }
                        else if (result == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText("WRONG ANSWER! %d LIVES LEFT:(", lives), 36) / 2, 420, 36, RED);
                            DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 620, 24, LIGHTGRAY);
                        }
                    }
                }

            }
        }
        else if (state == GAMEOVER)//ZAINAB
        {
            ClearBackground(BLACK);
            DrawText("GAME OVER", (screenWidth - MeasureText("GAME OVER", 70)) / 2, 250, 70, RED);
            DrawText("PRESS S TO RESTART!", (screenWidth - MeasureText("PRESS S TO RESTART", 30)) / 2, 380, 30, WHITE);
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
    UnloadTexture(livesTexture);
    UnloadTexture(computerTexture);

    CloseWindow();
    return 0;
}