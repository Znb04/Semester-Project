#include "raylib.h"
#include<string>
#include<cctype>
using namespace std;
typedef enum { START, PLAYING, PAUSED, GAMEOVER, BOOKRIDDLE,COFFIN, COMPPASSWORD } GameState;

int main()
{
    // Window settings
    const int screenWidth = 1000;
    const int screenHeight = 700;
    const int wallHeight = 400;
    const int bookrangex1 = 340, bookrangex2 = 600, bookrangey = 300, comprangex1 = 0, comprangex2 = 180, comprangey = 400;
    float timeLeft = 120.0f;
    bool gameStart = true;

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
    Texture2D sofaTexture = LoadTexture("COUCH.png");
    Texture2D skeletonTexture = LoadTexture("TIMESKELETON.png");
    Texture2D coffinTexture = LoadTexture("COFFINS.png");
    Texture2D skullsTexture = LoadTexture("skull.png");
    Texture2D handsTexture = LoadTexture("HANDS.png");
    Texture2D cracksTexture = LoadTexture("cracks.png");
    

    GameState state = START;
    Rectangle computer = { 0, 232, 145, 145 };//ZAINAB
    Rectangle collisionArea = { 0,0,0,0 };
    // PLAYER SETTINGS
    Rectangle player = { 700, 500, 200, 200 };//MARYAM
    //MARYAM
    int lives = 3;
    int bookSolved = 0;      // 0 = not solved, 1 = solved
    string word = ""; // what the player types
    int letterCount = 0;     // how many letters typed
    bool submittedR = false;  // has the player pressed ENTER yet?
    int resultR = 0;
    //COMP PASSWORD
    int passSolved=0, resultCp=0;//RESULT CP DEALS WITH BEGIN DRAWING AND PASS SOLVE DEALS WITH BAGIN DRAWING
    string answerCp="";
    bool submittedCp=false;

    //zainab
    //int coffinsolved1 = 0;// RIDDLE IN COMP
    //string answerC1 = "";
    //bool submittedC1 = false;
    //int resultC1 = 0;
    // MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        if (state == PLAYING || state == BOOKRIDDLE || state == COFFIN || state==COMPPASSWORD)
        {
            timeLeft = timeLeft - GetFrameTime();
        }
        gameStart = true;
        if (timeLeft <= 0.0f)
        {
            timeLeft = 120.0f;
            state = GAMEOVER;
        }
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
            //START STATE
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

            //COLLISION DETECTION
            if (CheckCollisionRecs(player, computer))
            {
                collisionArea = GetCollisionRec(player, computer);

                if (collisionArea.width > collisionArea.height) {//vertical collision
                    if (player.y < computer.y)//collison from bottom
                        player.y = player.y - collisionArea.height;
                    else//collison from toph
                        player.y = player.y + collisionArea.height;
                }
                if (collisionArea.height > collisionArea.width) {//horizontal collision
                    if (player.x < computer.x)//collison from left
                        player.x = player.x - collisionArea.width;
                    else//collison from right
                        player.x = player.x + collisionArea.width;
                }
            }

            //INTERACTIONS
            if (IsKeyPressed(KEY_E) && (player.x > bookrangex1 && player.x < bookrangex2) && (player.y < bookrangey)) // ZAINAB
            {
                state = BOOKRIDDLE;//MARYAM
                letterCount = 0;
                word = "";
                submittedR = false;
                resultR = 0;
                while (GetCharPressed() > 0) {}   // throws away the "e" you just pressed

            }
            if (IsKeyPressed(KEY_E) && (player.x > comprangex1 && player.x < comprangex2) && (player.y < comprangey))
            {
                //state = COMP;//zainab 
                //answerC1 = "";
                //submittedC1 = false;
                //resultC1 = 0;
                //while (GetCharPressed() > 0) {}   // throws away the "e" you just pressed
                state = COMPPASSWORD;
                answerCp = "";
                submittedCp = false;
                resultCp = 0;
                while (GetCharPressed() > 0) {}

            }
            if (IsKeyPressed(KEY_P))
            {
                state = PAUSED;
            }

        }
        else if (state == BOOKRIDDLE)// MARYAM
        {
            if (bookSolved == 0 && !submittedR)
            {
                int key = GetCharPressed();
                while (key > 0)
                {
                    if (key >= 32 && key <= 125)   // printable characters, including spaces
                        word += tolower((char)key);
                    key = GetCharPressed();
                }

                // 2) Enter: a separate check, outside the typing part
                if (IsKeyPressed(KEY_ENTER))
                {
                    submittedR = true;
                    if (word == "keyboard")
                    {
                        bookSolved = 1;
                        resultR = 1;
                    }
                    else
                    {
                        lives--;
                        if (lives == 0)
                        {
                            timeLeft = 120.0f;
                            lives = 3;
                            state = GAMEOVER;
                        }
                        resultR = 2;
                    }
                }

            }

            if (IsKeyPressed(KEY_R) && (submittedR || bookSolved == 1))
            {
                state = PLAYING;
            }
        }
        //else if (state == COFFIN)// comp riddle
        //{//WORKING
        //    if (coffinsolved1 == 0 && !submittedC1) {
        //        int key = GetCharPressed();
        //        while (key > 0) {
        //            answerC1 += tolower((char)key);
        //            key = GetCharPressed();
        //        }
        //        if (IsKeyPressed(KEY_ENTER)) {
        //            submittedC1 = true;
        //            if (answerC1 == "hurry up") {
        //                coffinsolved1 = 1;
        //                resultC1 = 1;
        //            }
        //            else
        //            {
        //                lives--;
        //                if (lives == 0) {
        //                    timeLeft = 120.0f;
        //                    lives = 3;
        //                    state = GAMEOVER;
        //                }
        //                resultC1 = 2;// wrong answer
        //            }
        //        }
        //    }
        //    if (IsKeyPressed(KEY_R) && (submittedC1 || coffinsolved1 == 1))
        //    {
        //        state = PLAYING;
        //    }
        //}
        else if (state == COMPPASSWORD)
        {
            if (passSolved == 0 && !submittedCp)
            {
                int key = GetCharPressed();
                while (key > 0)
                {
                    answerCp += tolower((char)key);
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_ENTER))
                {
                    submittedCp = true;
                    if (answerCp == "2007")
                    {
                        passSolved = 1;
                        resultCp = 1;//RIGHT ANSWER CONDITION
                       
                    }
                    else
                    {
                        lives--;
                        if (lives == 0)
                        {
                            timeLeft = 120.0f;
                            lives = 3;
                            state = GAMEOVER;
                        }
                        resultCp = 2;//WRONG ANSWER CONDITION
                    }
                }
            }
            if (IsKeyPressed(KEY_R) && (submittedCp || passSolved == 1))
            {
               state = PLAYING;
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
                timeLeft = 120.0f;
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
        else if (state == PLAYING || state == PAUSED || state == BOOKRIDDLE || state == COFFIN || state == COMPPASSWORD)//MARYAM
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


            //SOFA
            DrawTexture(sofaTexture, 235, 450, WHITE);
            //CRACKS
            DrawTexture(cracksTexture, 485, 498, WHITE);

            //CLOCK
            DrawTexture(clockTexture, 450, 50, WHITE);

            //SHELF
            DrawTexture(shelfTexture, 380, 189, WHITE);
            if ((player.x > bookrangex1 && player.x < bookrangex2) && (player.y < bookrangey))
            {
                DrawText("press e to interact", (screenWidth - MeasureText("press e to interact", 30)) / 2, 600, 30, WHITE);
            }

            //TIME
            DrawText(TextFormat("Time: %d", (int)timeLeft), 20, 60, 30, BLACK);
            //TIME SKELETON 
            DrawTexture(skeletonTexture, 150, 55, WHITE);


            //HANDS
            DrawTexture(handsTexture, 30, 520, WHITE);

            //LIVE 
            DrawText(TextFormat("%d LIVES", lives), 20, 20, 30, BLACK);
            //HEARTS
            DrawTexture(livesTexture, 150, 15, WHITE);

            //WINDOW
            DrawTexture(windowTexture, 600, 150, WHITE);

            //DOOR
            //DrawRectangle(250, wallHeight-152, 80, 155, DARKPURPLE);//AS y(axis point)+235(doorheight)=wallHeight so..
            DrawTexturePro(doorTexture,
                { 0, 0, (float)doorTexture.width, (float)doorTexture.height },
                { 230, wallHeight - 235, (float)doorTexture.width, (float)doorTexture.height },
                { 0,0 }, 0.0f, WHITE);

            //COFFIN
           /* DrawTexturePro(coffinTexture,
                { 0, 0, (float)coffinTexture.width, (float)coffinTexture.height },
                { 851, wallHeight - 210, (float)coffinTexture.width, (float)coffinTexture.height },
                { 0,0 }, 0.0f, WHITE);*/
            DrawTexture(coffinTexture, 851, 190, WHITE);

            //SKULLS
            DrawTexture(skullsTexture, 750, 320, WHITE);


            // Player 
            DrawTexture(playerTexture, player.x, player.y, WHITE);
            //COMPUTER
            DrawTexture(computerTexture, computer.x, computer.y, WHITE);
            if ((player.x > comprangex1 + 20 && player.x < comprangex2 + 20) && (player.y < comprangey + 20)) {
                DrawText("press e to interact", (screenWidth - MeasureText("press e to interact", 30)) / 2, 600, 30, WHITE);
            }

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
                if (bookSolved == 1 && resultR == 0)
                {
                    //IF OPEN AGAINAFTER SOLVED
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS R TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS R TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
                }
                else
                {
                    DrawText("WHAT HAS A KEY BUT DOESN'T UNLOCK ANYTHING?", (screenWidth - MeasureText("WHAT HAS A KEY BUT DOESN'T UNLOCK ANYTHING?", 30)) / 2, 220, 30, WHITE);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(word.c_str(), 310, 310, 30, BLACK);//TYPED TEXT
                    if (!submittedR)
                    {
                        DrawText("TYPE YOUR ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE YOUR ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, LIGHTGRAY);
                    }
                    else
                    {
                        if (resultR == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 420, 36, GREEN);
                            DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
                        }
                        else if (resultR == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 420, 36, RED);
                            DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
                        }
                    }
                }

            }
            //else if (state == COFFIN)
            //{
            //    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
            //    DrawText("COMPUTER RIDDLE", (screenWidth - MeasureText("COMPUTER RIDDLE", 60)) / 2, 120, 50, WHITE);
            //    if (coffinsolved1 == 1 && resultC1 == 0)
            //    {
            //        //if open again after solving
            //        DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
            //        DrawText("PRESS R TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS R TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);

            //    }
            //    else
            //    {
            //        DrawText("SOLVE THE SEQUENCE!", (screenWidth - MeasureText("SOLVE THE SEQUENCE!", 30)) / 2, 220, 30, WHITE);
            //        DrawText("IVSSZ VQ (HINT:+1 OR -1)", (screenWidth - MeasureText("IVSSZ VQ (HINT:+1 OR -1)", 30)) / 2, 260, 30, WHITE);
            //        DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
            //        DrawText(answerC1.c_str(), 310, 310, 30, BLACK);
            //        if (!submittedC1)
            //        {
            //            DrawText("TYPE ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, WHITE);
            //        }
            //        else
            //        {
            //            if (resultC1 == 1)
            //            {
            //                DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 420, 36, GREEN);
            //                DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
            //            }
            //            else if (resultC1 == 2)
            //            {
            //                DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 420, 36, RED);
            //                DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
            //            }
            //        }
            //    }
            //}
            else if (state == COMPPASSWORD)
            {
                if (passSolved == 1 && resultCp == 0)
                {
                    
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                    DrawText("UNLOCK COMPUTER", (screenWidth - MeasureText("UNLOCK COMPUTER", 60)) / 2, 120, 50, WHITE);
                    //if open again after solving
                    DrawText("YOU HAVE ALREADY UNLOCKED IT.", (screenWidth - MeasureText("YOU HAVE ALREADY UNLOCKED IT.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS R TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS R TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);

                }
                else {
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                    DrawText("ENTER PASSWORD", (screenWidth - MeasureText("ENTER PASSWORD", 60)) / 2, 120, 50, WHITE);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(answerCp.c_str(), 310, 310, 30, BLACK);
                    if (!submittedCp)
                    {
                        DrawText("TYPE PASSWORD AND PRESS ENTER!", (screenWidth - MeasureText("TYPE PASSWORD AND PRESS ENTER!", 22)) / 2, 370, 22, WHITE);
                    }
                    else
                    {
                        if (resultCp == 1)
                        {
                            DrawText("COMPUTER UNLOCKED!", (screenWidth - MeasureText("COMPUTER UNLOCKED!", 36)) / 2, 420, 36, GREEN);
                            DrawText("A SILENT BED TO SET YOU FREE OR HOLD YOUR CORPSE ETERNALLY!", (screenWidth - MeasureText("A SILENT BED TO SET YOU FREE OR HOLD YOUR CORPSE ETERNALLY!", 22)) / 2, 480, 22, RED);
                            //DrawText("PRESS.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
                        }
                        else if (resultCp == 2)
                        {
                            DrawText(TextFormat("INCORRECT PASSWORD!% d LIVES LEFT : (", lives), (screenWidth - MeasureText(TextFormat("INCORRECT PASSWORD!% d LIVES LEFT  : (", lives), 36)) / 2, 420, 36, RED);
                            DrawText("PRESS R TO GO BACK.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
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
    UnloadTexture(sofaTexture);
    UnloadTexture(skeletonTexture);
    UnloadTexture(coffinTexture);
    UnloadTexture(skullsTexture);
    UnloadTexture(handsTexture);
    UnloadTexture(cracksTexture);

    CloseWindow();
    return 0;
}