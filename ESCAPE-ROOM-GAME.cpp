#include "raylib.h"
#include<string>
#include<cctype>
using namespace std;
typedef enum { START, PLAYING, PAUSED, RESTART, GAMEOVER, BOOKRIDDLE, COFFIN, COMPPASSWORD, HOLE, CHIT, SOFA, WINDOW, WIN } GameState;/////// ADDED A STATE ////////

//BACKSPACE FUNCTION
auto backspace = [](string& s)
    {
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !s.empty())
            s.pop_back();
    };


int main()
{
    // Window settings
    const int screenWidth = 1000;
    const int screenHeight = 700;
    const int wallHeight = 400;
    float timeLeft = 300.0f;
    bool gameStart = true;
    int points = 0;
    //
    Rectangle bookArea = { 340,300,240,40 }, compArea = { 0,200,240,150 }, sofaArea = { 500,510,150,234 }, coffinArea = { 780, 300, 220, 50 }, holeArea = { 840, 560, 220, 160 }, chitArea = { 25,500,100,100 }, windowArea = { 600,150,200,200 }, doorArea = { 230,150,270,300 };

    InitWindow(screenWidth, screenHeight, "ESCAPE ROOM");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D floorTexture = LoadTexture("FLOOR.png");
    Texture2D wallTexture = LoadTexture("wall.png");
    Texture2D doorTexture = LoadTexture("DOOR.png");
    Texture2D clockTexture = LoadTexture("clockhehe.png");
    Texture2D windowTexture = LoadTexture("windowhehe.png");
    Texture2D shelfTexture = LoadTexture("SHELF.png");
    Texture2D computerTexture = LoadTexture("comp.png");
    Texture2D playerTexture = LoadTexture("GIRLPLAYER.png");
    Texture2D livesTexture = LoadTexture("LIVES.png");
    Texture2D sofaTexture = LoadTexture("COUCH.png");
    Texture2D skeletonTexture = LoadTexture("TIMESKELETON.png");
    Texture2D coffinTexture = LoadTexture("COFFINS.png");
    Texture2D skullsTexture = LoadTexture("skull.png");
    Texture2D chitTexture = LoadTexture("chitss.png");
    Texture2D cracksTexture = LoadTexture("cracks.png");
    Texture2D holeTexture = LoadTexture("HOLE.png");
    Texture2D chainsTexture = LoadTexture("chainsR.png");
    Texture2D gameoverTexture = LoadTexture("reapshehe.png");/////////////////
    Texture2D menudisplayTexture = LoadTexture("excaperoomdisplay.png");////////////////////
    Texture2D handscareTexture = LoadTexture("no escape msg jump.png");
    Texture2D displaychitTexture = LoadTexture("DISPLAYCHIT.png");
    Texture2D winTexture = LoadTexture("FINAL WIN.png");
    Texture2D coinTexture = LoadTexture("COIN.png");
    
    //sound
    Music mainmusic = LoadMusicStream("Eternal Terminal.mp3");
    Music riddlemusic = LoadMusicStream("riddle2.mp3");
    Music startmusic = LoadMusicStream("menumusic.mp3");
    Music gameovermusic = LoadMusicStream("gameovermusic.mp3");
    Music winmusic = LoadMusicStream("winmusic.mp3");
    mainmusic.looping = true;
    riddlemusic.looping = true;
    startmusic.looping = true;
    gameovermusic.looping = true;
    winmusic.looping = true;
    SetMusicVolume(mainmusic, 0.2f);
    SetMusicVolume(riddlemusic, 0.5f);
    SetMusicVolume(startmusic, 0.5f);
    SetMusicVolume(gameovermusic, 0.5f);
    SetMusicVolume(winmusic, 0.5f);
    PlayMusicStream(mainmusic);

    Music* currentMusic = &mainmusic;   // points to the track that is playing
    PlayMusicStream(*currentMusic);

    GameState state = START;
    Rectangle computer = { 0, 232, (float)computerTexture.width, (float)computerTexture.height };//ZAINAB
    Rectangle sofa = { 280,516,(float)sofaTexture.width,(float)sofaTexture.height };
    Rectangle collisionArea = { 0,0,0,0 };
    // PLAYER SETTINGS
    Rectangle player = { 700, 500,(float)playerTexture.width, (float)playerTexture.height };//MARYAM
    //BOOK
    int lives = 3;
    int bookSolved = 0;      // 0 = not solved, 1 = solved
    string word = ""; // what the player types
    bool submittedR = false;  // has the player pressed ENTER yet?
    int resultR = 0;
    // SOFA RIDDLE
    int sofaSolved = 0;
    string answerSofa = "";
    bool submittedSofa = false;
    int resultSofa = 0;
    //COMP PASSWORD
    int passSolved = 0;
    int  resultCp = 0;//RESULT CP DEALS WITH BEGIN DRAWING AND PASS SOLVE DEALS WITH BAGIN DRAWING
    string answerCp = "";
    bool submittedCp = false;
    //STRICK
    int holeSolved = 0;
    string answerHole = "";
    bool submittedHole = false;
    int resultHole = 0;
    //COFFIN
    int coffinsolved1 = 0;// RIDDLE IN COMP
    string answerC1 = "";
    bool submittedC1 = false;
    int resultC1 = 0, resultChit = 0;
    //WINDOW
    int windowSolved = 0;      // 0 = not solved, 1 = solved
    string answerW = ""; // what the player types
    bool submittedWindow = false;  // has the player pressed ENTER yet?
    int resultW = 0;
    // we gotta make detection
    bool nearBook = false, nearComp = false, nearCoffin = false, nearHole = false, nearChit = false, nearSofa = false, nearWindow = false, nearDoor = false;
    // MAIN GAME LOOP

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*currentMusic);

        if (state == PLAYING || state == BOOKRIDDLE || state == COFFIN || state == COMPPASSWORD || state == HOLE)
        {

            timeLeft = timeLeft - GetFrameTime();
        }
        gameStart = true;
        if (timeLeft <= 0.0f)
        {
            timeLeft = 300.0f;
            state = GAMEOVER;
        }
        //START STATE   
        if (state == START)//ZAINAB
        {
            if (IsKeyPressed(KEY_S))
            {
                lives = 3;
                timeLeft = 300.0f;
                player.x = 700;
                player.y = 500;
                points = 0;
                bookSolved = 0, passSolved = 0, coffinsolved1 = 0, holeSolved = 0, sofaSolved = 0, word = "", answerC1 = "", answerCp = "", answerHole = "", answerSofa = "", submittedR = false, submittedC1 = false, submittedCp = false, submittedHole = false, submittedSofa = false, resultR = 0, resultC1 = 0, resultCp = 0, resultHole = 0, resultSofa = 0, submittedWindow = false, resultW = 0, answerW = "", windowSolved = 0;

                state = PLAYING;
            }
        }
        else if (state == PLAYING) //ZAINAB
        {


            //START STATE
            nearBook = CheckCollisionRecs(player, bookArea);
            nearComp = CheckCollisionRecs(player, compArea);
            nearCoffin = CheckCollisionRecs(player, coffinArea);
            nearHole = CheckCollisionRecs(player, holeArea);
            nearChit = CheckCollisionRecs(player, chitArea);
            nearSofa = CheckCollisionRecs(player, sofaArea);
            nearWindow = CheckCollisionRecs(player, windowArea);
            nearDoor = CheckCollisionRecs(player, doorArea);

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
            if (player.y < wallHeight - player.height + 20)
                player.y = wallHeight - player.height + 20;

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
            //COLLISION SOFA
            if (CheckCollisionRecs(player, sofa))
            {
                collisionArea = GetCollisionRec(player, sofa);

                if (collisionArea.width > collisionArea.height) {//vertical collision
                    if (player.y < sofa.y)//collison from bottom
                        player.y = player.y - collisionArea.height;
                    else//collison from toph
                        player.y = player.y + collisionArea.height;
                }
                if (collisionArea.height > collisionArea.width) {//horizontal collision
                    if (player.x < sofa.x)//collison from left
                        player.x = player.x - collisionArea.width;
                    else//collison from right
                        player.x = player.x + collisionArea.width;
                }
            }

            //INTERACTIONS
            if (IsKeyPressed(KEY_E))
            {
                if (nearBook) // ZAINAB
                {
                    state = BOOKRIDDLE;//MARYAM

                    word = "";
                    submittedR = false;
                    resultR = 0;
                    while (GetCharPressed() > 0) {}   // throws away the "e" you just pressed

                }
                else if (nearComp)
                {
                    state = COMPPASSWORD;
                    answerCp = "";
                    submittedCp = false;
                    resultCp = 0;
                    while (GetCharPressed() > 0) {}

                }
                else if (nearCoffin)
                {
                    state = COFFIN;//zainab 
                    answerC1 = "";
                    submittedC1 = false;
                    resultC1 = 0;
                    while (GetCharPressed() > 0) {}   // throws away the "e" you just pressed
                }
                else if (nearHole) // ZAINAB
                {
                    state = HOLE;
                    answerHole = "";
                    submittedHole = false;
                    resultHole = 0;
                    while (GetCharPressed() > 0) {}   // throws away the "e" you just pressed

                }
                else if (nearChit && !resultChit)
                {
                    state = CHIT;
                }
                else if (nearSofa)
                {
                    state = SOFA;
                    sofaSolved = 0;
                    answerSofa = "";
                    submittedSofa = false;
                    resultSofa = 0;
                    while (GetCharPressed() > 0) {}
                }
                else if (nearWindow)
                {
                    state = WINDOW;
                    answerW = "";
                    submittedWindow = false;
                    resultW = 0;
                    while (GetCharPressed() > 0) {}
                }

            }
            else if (nearDoor && points == 120 && IsKeyPressed(KEY_U))
            {
                state = WIN;
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
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0)
                    {
                        if (key >= 32 && key <= 125)   // printable characters, including spaces
                            word += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(word);

                    // 2) Enter: a separate check, outside the typing part
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        submittedR = true;
                        if (word == "silence")
                        {
                            bookSolved = 1;
                            points += 20;
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

            }

            if (IsKeyPressed(KEY_TAB) && (submittedR || bookSolved == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == COFFIN)// comp riddle
        {//WORKING
            if (coffinsolved1 == 0 && !submittedC1) {
                int key = GetCharPressed();
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0)
                    {
                        answerC1 += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(answerC1);

                    if (IsKeyPressed(KEY_ENTER)) {
                        submittedC1 = true;
                        if (answerC1 == "hurry up") {
                            coffinsolved1 = 1;
                            points += 20;
                            resultC1 = 1;
                        }
                        else
                        {
                            lives--;
                            if (lives == 0) {
                                timeLeft = 300.0f;
                                lives = 3;
                                state = GAMEOVER;
                            }
                            resultC1 = 2;// wrong answer
                        }
                    }
                }
            }
            if (IsKeyPressed(KEY_TAB) && (submittedC1 || coffinsolved1 == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == COMPPASSWORD)
        {
            if (passSolved == 0 && !submittedCp)
            {
                int key = GetCharPressed();
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0)
                    {
                        answerCp += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(answerCp);

                    if (IsKeyPressed(KEY_ENTER))
                    {
                        submittedCp = true;
                        if (answerCp == "9251")
                        {
                            passSolved = 1;
                            points += 20;
                            resultCp = 1;//RIGHT ANSWER CONDITION

                        }
                        else
                        {
                            lives--;
                            if (lives == 0)
                            {
                                timeLeft = 300.0f;
                                lives = 3;
                                state = GAMEOVER;
                            }
                            resultCp = 2;//WRONG ANSWER CONDITION
                        }
                    }
                }
            }
            if (IsKeyPressed(KEY_TAB) && (submittedCp || passSolved == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == HOLE)// comp riddle
        {//WORKING
            if (holeSolved == 0 && !submittedHole) {
                int key = GetCharPressed();
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0) {
                        answerHole += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(answerHole);

                    if (IsKeyPressed(KEY_ENTER)) {
                        submittedHole = true;
                        if (answerHole == "coffin") {
                            holeSolved = 1;
                            points += 20;
                            resultHole = 1;
                        }
                        else
                        {
                            lives--;
                            if (lives == 0) {
                                timeLeft = 300.0f;
                                lives = 3;
                                state = GAMEOVER;
                            }
                            resultHole = 2;// wrong answer
                        }
                    }
                }
            }
            if (IsKeyPressed(KEY_TAB) && (submittedHole || holeSolved == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == CHIT)
        {
            resultChit = 1;
            if (IsKeyPressed(KEY_TAB))
            {
                state = PLAYING;
            }
        }
        else if (state == SOFA)
        {
            if (sofaSolved == 0 && !submittedSofa)
            {
                int key = GetCharPressed();
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0)
                    {
                        if (key >= 32 && key <= 125)   // printable characters, including spaces
                            answerSofa += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(answerSofa);

                    // 2) Enter: a separate check, outside the typing part
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        submittedSofa = true;
                        if (answerSofa == "n")
                        {
                            sofaSolved = 1;
                            points += 20;
                            resultSofa = 1;
                        }
                        else
                        {
                            lives--;
                            if (lives == 0)
                            {
                                timeLeft = 300.0f;
                                lives = 3;
                                state = GAMEOVER;
                            }
                            resultSofa = 2;
                        }
                    }
                }
            }
            if (IsKeyPressed(KEY_TAB) && (submittedSofa || sofaSolved == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == WINDOW)
        {
            if (windowSolved == 0 && !submittedWindow)
            {
                int key = GetCharPressed();
                if (IsKeyPressed(KEY_TAB))
                {
                    state = PLAYING;
                }
                else
                {
                    while (key > 0)
                    {
                        if (key >= 32 && key <= 125)
                            answerW += tolower((char)key);
                        key = GetCharPressed();
                    }

                    backspace(answerW);

                    if (IsKeyPressed(KEY_ENTER))
                    {
                        submittedWindow = true;
                        if (answerW == "footsteps")
                        {
                            windowSolved = 1;
                            points += 20;
                            resultW = 1;
                        }
                        else
                        {
                            lives--;
                            if (lives == 0)
                            {
                                timeLeft = 300.0f;
                                lives = 3;
                                state = GAMEOVER;
                            }
                            resultW = 2;
                        }
                    }
                }

            }

            if (IsKeyPressed(KEY_TAB) && (submittedWindow || windowSolved == 1))
            {
                state = PLAYING;
            }
        }
        else if (state == WIN)
        {
            if (IsKeyPressed(KEY_M))
            {
                state = START;///////////////////////////////////////////
            }
            }
        else if (state == PAUSED)// ZAINAB
        {
            if (IsKeyPressed(KEY_C))
            {
                state = PLAYING;
            }
            if (IsKeyPressed(KEY_R))
            {
                /*player.x = 700;
                player.y = 500;
                state = PLAYING;*/
                state = RESTART;///////////////////////////////////////////
            }
            if (IsKeyPressed(KEY_G))
            {
                state = GAMEOVER;
            }
        }
        else if (state == RESTART)/////////// ADDED A RESTART STATE ///////////
        {
            lives = 3;
            timeLeft = 300.0f;
            player.x = 700;
            player.y = 500;
            points = 0;
            bookSolved = 0, passSolved = 0, coffinsolved1 = 0, holeSolved = 0, sofaSolved = 0, word = "", answerC1 = "", answerCp = "", answerHole = "", answerSofa = "", submittedR = false, submittedC1 = false, submittedCp = false, submittedHole = false, submittedSofa = false, resultR = 0, resultC1 = 0, resultCp = 0, resultHole = 0, resultSofa = 0, submittedWindow = false, resultW = 0, answerW = "", windowSolved = 0;

            state = PLAYING;
        }
        else if (state == GAMEOVER)//ZAINAB
        {
            if (IsKeyPressed(KEY_M))
            {
                lives = 3;
                timeLeft = 300.0f;
                player.x = 700;
                player.y = 500;
                bookSolved = 0, passSolved = 0, coffinsolved1 = 0, holeSolved = 0, sofaSolved = 0, word = "", answerC1 = "", answerCp = "", answerHole = "", answerSofa = "", submittedR = false, submittedC1 = false, submittedCp = false, submittedHole = false, submittedSofa = false, resultR = 0, resultC1 = 0, resultCp = 0, resultHole = 0, resultSofa = 0, submittedWindow = false, resultW = 0, answerW = "", windowSolved=0;

                points = 0;
                state = START;
            }
        }
        

        // choose which music the current state wants
        Music* wantedMusic = currentMusic;   // default: keep playing (PAUSED, RESTART)

        if (state == PAUSED || state == PLAYING)
        {
            wantedMusic = &mainmusic;
        }
        else if (state == BOOKRIDDLE || state == COFFIN || state == COMPPASSWORD || state == HOLE || state == CHIT || state == SOFA || state==WINDOW)
        {
            wantedMusic = &riddlemusic;      // same track for every riddle
        }
        else if (state == START)
        {
            wantedMusic = &startmusic;
        }
        else if (state == WIN)
        {
            wantedMusic = &winmusic;
        }
        else if (state == GAMEOVER)
        {
            wantedMusic = &gameovermusic;
        }


        // only switch if it is a different track
        if (wantedMusic != currentMusic)
        {
            StopMusicStream(*currentMusic);
            currentMusic = wantedMusic;
            PlayMusicStream(*currentMusic);
        }
        // DRAW EVERYTHING

        BeginDrawing();
        if (state == START)// ZAINAB
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));///////////////////
            DrawTexture(menudisplayTexture, 00, 00, WHITE);/////////////////////
            /*ClearBackground(BLACK);
            DrawText("ESCAPE ROOM", (screenWidth - MeasureText("ESCAPE ROOM", 60)) / 2, 90, 60, WHITE);
            DrawText("USE ARROW KEYS FOR PLAYER MOVEMENT. ", (screenWidth - MeasureText("USE ARROW KEYS FOR PLAYER MOVEMENT. ", 28)) / 2, 210, 28, LIGHTGRAY);
            DrawText("PRESS E TO INTERACT WITH THE OBJECTS. ", (screenWidth - MeasureText("PRESS E TO INTERACT WITH THE OBJECTS. ", 24)) / 2, 255, 24, LIGHTGRAY);
            DrawText("DESCRIPTION: YOU HAVE 5 MINS AND 3 LIVES TO ESCAPE THE ROOM  ", (screenWidth - MeasureText("DESCRIPTION: YOU HAVE 5 MINS AND 3 LIVES TO ESCAPE THE ROOM  ", 22)) / 2, 340, 22, LIGHTGRAY);
            DrawText("BY FINDING CLUES AND SOLVING THE RIDDLES BEFORE THE REAPER", (screenWidth - MeasureText("BY FINDING CLUES AND SOLVING THE RIDDLES BEFORE THE REAPER", 22)) / 2, 375, 22, LIGHTGRAY);
            DrawText("COMES IN AND KILLS YOU", (screenWidth - MeasureText("COMES IN AND KILLS YOU", 22)) / 2, 410, 22, LIGHTGRAY);
            DrawText("PRESS S TO START!", (screenWidth - MeasureText("PRESS S TO START!", 36)) / 2, 520, 36, YELLOW);*/

        }
        else if (state == PLAYING || state == PAUSED || state == BOOKRIDDLE || state == COFFIN || state == COMPPASSWORD || state == HOLE || state == CHIT || state == SOFA || state == WINDOW)//MARYAM
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
            DrawTexture(sofaTexture, 280, 516, WHITE);

            //CRACKS
            DrawTexture(cracksTexture, 485, 520, WHITE);

            //CLOCK
            DrawTexture(clockTexture, 450, 50, WHITE);

            //SHELF
            DrawTexture(shelfTexture, 380, 189, WHITE);


            //TIME
            DrawText(TextFormat("Time: %d", (int)timeLeft), 20, 60, 30, BLACK);

            //TIME SKELETON 
            DrawTexture(skeletonTexture, 150, 55, WHITE);

            //CHIT
            DrawTexture(chitTexture, 25, 600, WHITE);

            //LIVE 
            DrawText(TextFormat("%d LIVES", lives), 20, 20, 30, BLACK);

            //HEARTS
            DrawTexture(livesTexture, 150, 15, WHITE);

            //POINTS
            DrawText(TextFormat("Points: %d", points), 795, 20, 30, BLACK);
            //COIN
            DrawTexture(coinTexture, 942, 15, WHITE);

            //WINDOW
            DrawTexture(windowTexture, 600, 150, WHITE);

            //DOOR
            //DrawRectangle(250, wallHeight-152, 80, 155, DARKPURPLE);//AS y(axis point)+235(doorheight)=wallHeight so..
            DrawTexturePro(doorTexture,
                { 0, 0, (float)doorTexture.width, (float)doorTexture.height },
                { 230, wallHeight - 235, (float)doorTexture.width, (float)doorTexture.height },
                { 0,0 }, 0.0f, WHITE);

            //COFFIN
            DrawTexture(coffinTexture, 851, 190, WHITE);

            //SKULLS
            DrawTexture(skullsTexture, 750, 320, WHITE);

            //HOLE
            DrawTexture(holeTexture, 840, 538, WHITE);

            //chain
            DrawTexture(chainsTexture, 875, 599, WHITE);

            // Player 
            DrawTexture(playerTexture, player.x, player.y, WHITE);

            //COMPUTER
            DrawTexture(computerTexture, computer.x, computer.y, WHITE);

            // draw interaction 
           /* if (state == PLAYING && (nearBook || nearComp || nearCoffin || nearHole))
            {
                DrawText("press e to interact", (screenWidth - MeasureText("press e to interact", 30)) / 2, 600, 30, WHITE);
            }*/


            if (points == 120)
            {
                DrawText("YOU GOT THE KEY, GO TO DOOR PRESS U TO UNLOCK", (screenWidth - MeasureText("YOU GOT THE KEY, GO TO DOOR PRESS U TO UNLOCK", 30)) / 2, 560, 30, WHITE);
            }
            if (state == PAUSED)//ZAINAB
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("PAUSED", (screenWidth - MeasureText("PAUSED", 60)) / 2, 150, 60, WHITE);
                DrawText("C : CONTINUE", (screenWidth - MeasureText("C : CONTINUE", 36)) / 2, 260, 36, WHITE);
                DrawText("R : RESTART", (screenWidth - MeasureText("S : RESTART", 36)) / 2, 330, 36, WHITE);
                DrawText("G : END GAME AND RETURN TO MAIN MENU", (screenWidth - MeasureText("G : END GAME AND RETURN TO MAIN MENU", 36)) / 2, 400, 36, WHITE);////////////////////////////////
            }
            else if (state == CHIT)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawTexture(displaychitTexture, 04, 04, WHITE);
            }
            else if (state == BOOKRIDDLE)// MARYAM
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("BOOK RIDDLE", (screenWidth - MeasureText("BOOK RIDDLE", 50)) / 2, 120, 50, WHITE);
                if (bookSolved == 1 && resultR == 0)
                {
                    //IF OPEN AGAINAFTER SOLVED
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
                }
                else
                {
                    DrawText("WHAT DISAPPEARS AS SOON AS YOU SAY ITS NAME?", (screenWidth - MeasureText("WHAT DISAPPEARS AS SOON AS YOU SAY ITS NAME ?", 30)) / 2, 220, 30, WHITE);
                    DrawText("PRESS TAB TO GO BACK.", (screenWidth - MeasureText("PRESS TAB TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
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

                        }
                        else if (resultR == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 420, 36, RED);

                        }
                    }
                }

            }
            else if (state == COFFIN)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("COFFIN RIDDLE", (screenWidth - MeasureText("COFFIN RIDDLE", 50)) / 2, 120, 50, WHITE);
                if (coffinsolved1 == 1 && resultC1 == 0)
                {
                    //if open again after solving
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);

                }
                else
                {
                    DrawText("SOLVE THE SEQUENCE!", (screenWidth - MeasureText("SOLVE THE SEQUENCE!", 30)) / 2, 220, 30, WHITE);
                    DrawText("IVSSZ VQ (HINT:+1 OR -1)", (screenWidth - MeasureText("IVSSZ VQ (HINT:+1 OR -1)", 30)) / 2, 260, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(answerC1.c_str(), 310, 310, 30, BLACK);
                    if (!submittedC1)
                    {
                        DrawText("TYPE ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, WHITE);
                    }
                    else
                    {
                        if (resultC1 == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 420, 36, GREEN);

                            DrawText("CLUE: METAL RINGS!", (screenWidth - MeasureText("CLUE: METAL RINGS!", 22)) / 2, 480, 22, YELLOW);
                        }
                        else if (resultC1 == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 420, 36, RED);

                        }
                    }
                }
            }
            else if (state == HOLE)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("HOLE RIDDLE", (screenWidth - MeasureText("HOLE RIDDLE", 50)) / 2, 120, 50, WHITE);
                if (holeSolved == 1 && resultHole == 0)
                {
                    //if open again after solving
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);

                }
                else
                {
                    DrawText("SOLVE THE RIDDLE!", (screenWidth - MeasureText("SOLVE THE RIDDLE!", 30)) / 2, 220, 30, WHITE);
                    DrawText("A SILENT BED TO SET YOU FREE", (screenWidth - MeasureText("A SILENT BED TO SET YOU FREE", 30)) / 2, 260, 30, WHITE);
                    DrawText("OR HOLD YOUR CORPSE ETERNALLY!", (screenWidth - MeasureText("OR HOLD YOUR CORPSE ETERNALLY!", 30)) / 2, 300, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 580, 24, LIGHTGRAY);
                    DrawRectangle(300, 400, 400, 50, WHITE);//INPUT BOX
                    DrawText(answerHole.c_str(), 310, 410, 30, BLACK);
                    if (!submittedHole)
                    {
                        DrawText("TYPE ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, WHITE);
                    }
                    else
                    {
                        if (resultHole == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 460, 36, GREEN);

                        }
                        else if (resultHole == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 460, 36, RED);

                        }
                    }
                }
            }
            else if (state == COMPPASSWORD)
            {
                if (passSolved == 1 && resultCp == 0)
                {

                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

                    DrawText("YOU HAVE ALREADY UNLOCKED IT.", (screenWidth - MeasureText("YOU HAVE ALREADY UNLOCKED IT.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);

                }
                else {
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                    DrawText("ENTER PASSWORD", (screenWidth - MeasureText("ENTER PASSWORD", 50)) / 2, 120, 50, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
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
                            DrawText("CLUE: METAL RINGS", (screenWidth - MeasureText("CLUE: METAL RINGS!", 22)) / 2, 480, 22, YELLOW);
                            //DrawText("PRESS.", (screenWidth - MeasureText("PRESS R TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
                        }
                        else if (resultCp == 2)
                        {
                            DrawText(TextFormat("INCORRECT PASSWORD!% d LIVES LEFT : (", lives), (screenWidth - MeasureText(TextFormat("INCORRECT PASSWORD!% d LIVES LEFT  : (", lives), 36)) / 2, 420, 36, RED);

                        }

                    }
                }
            }
            else if (state == SOFA)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("SOFA RIDDLE", (screenWidth - MeasureText("SOFA RIDDLE", 60)) / 2, 120, 50, WHITE);
                if (sofaSolved == 1 && resultSofa == 0)
                {
                    //if open again after solving
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
                }
                else
                {
                    DrawText("IF YOU THROW OUT THE WINDOW, YOU'LL LEAVE A GREIVING WIFE. BUT DROP ME", (screenWidth - MeasureText("IF YOU THROW OUT THE WINDOW, YOU'LL LEAVE AGREIVING WIFE. BUT DROP ME", 22)) / 2, 220, 22, WHITE);
                    DrawText("IN THE MIDDLE OF THE DOOR, YOU WILL SAVE A LIFE", (screenWidth - MeasureText("IN THE MIDDLE OF THE DOOR, YOU WILL SAVE A LIFE", 22)) / 2, 260, 22, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 560, 24, LIGHTGRAY);
                    DrawText("HINT: ONE LETTER ANSWER", (screenWidth - MeasureText("HINT: ONE LETTER ANSWER", 24)) / 2, 420, 24, YELLOW);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(answerSofa.c_str(), 310, 310, 30, BLACK);
                    if (!submittedSofa)
                    {
                        DrawText("TYPE ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, WHITE);
                    }
                    else
                    {
                        if (resultSofa == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 370, 36, GREEN);

                            DrawText("CLUE: MY SPINE STIFF MY BODY PALE,", (screenWidth - MeasureText("CLUE: MY SPINE STIFF MY BODY PALE,", 22)) / 2, 460, 22, YELLOW);
                            DrawText("I'M ALWAYS READY TO TELL YOU A TALE", (screenWidth - MeasureText("I'M ALWAYS READY TO TELL YOU A TALE", 22)) / 2, 500, 22, YELLOW);
                        }
                        else if (resultSofa == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 460, 36, RED);

                        }
                    }
                }
            }
            else if (state == WINDOW)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                DrawText("WINDOW RIDDLE", (screenWidth - MeasureText("WINDOW RIDDLE", 50)) / 2, 120, 50, WHITE);
                if (windowSolved == 1 && resultW == 0)
                {
                    //IF OPEN AGAINAFTER SOLVED
                    DrawText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", (screenWidth - MeasureText("YOU HAVE ALREADY SOLVED THIS RIDDLE.", 30)) / 2, 280, 30, WHITE);
                    DrawText("PRESS TAB TO RETURN TO THE GAME.", (screenWidth - MeasureText("PRESS TAB TO RETURN TO THE GAME.", 24)) / 2, 520, 24, LIGHTGRAY);
                }
                else
                {
                    DrawText("THE MORE YOU TAKE, THE MORE YOU LEAVE BEHIND.WHATS IT?", (screenWidth - MeasureText("THE MORE YOU TAKE, THE MORE YOU LEAVE BEHIND.WHATS IT?", 23)) / 2, 220, 23, WHITE);
                    DrawText("PRESS TAB TO GO BACK.", (screenWidth - MeasureText("PRESS TAB TO GO BACK.", 24)) / 2, 520, 24, LIGHTGRAY);
                    DrawRectangle(300, 300, 400, 50, WHITE);//INPUT BOX
                    DrawText(answerW.c_str(), 310, 310, 30, BLACK);//TYPED TEXT
                    if (!submittedWindow)
                    {
                        DrawText("TYPE YOUR ANSWER AND PRESS ENTER!", (screenWidth - MeasureText("TYPE YOUR ANSWER AND PRESS ENTER!", 22)) / 2, 370, 22, LIGHTGRAY);
                    }
                    else
                    {
                        if (resultW == 1)
                        {
                            DrawText("YOU ARE CORRECT!", (screenWidth - MeasureText("YOU ARE CORRECT!", 36)) / 2, 420, 36, GREEN);
                            

                        }
                        else if (resultW == 2)
                        {
                            DrawText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), (screenWidth - MeasureText(TextFormat("WRONG ANSWER! %d LIVES LEFT:(", lives), 36)) / 2, 420, 36, RED);

                        }
                    }
                }
            }
        }
        else if (state == GAMEOVER)//ZAINAB
        {
            /*
            ClearBackground(BLACK);
            DrawText("GAME OVER", (screenWidth - MeasureText("GAME OVER", 70)) / 2, 250, 70, RED);
            DrawText("PRESS M TO RETURN TO MAIN MENU!", (screenWidth - MeasureText("PRESS M TO RETURN TO MAIN MENU!", 30)) / 2, 380, 30, WHITE);////////CHNAGES THE TEXT///////////////////////////////////////
            */
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));///////////////////
            DrawTexture(gameoverTexture, 00, 00, WHITE);/////////////////////

        }
        else if (state == WIN)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
            DrawTexture(winTexture, 00, 00, WHITE);
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
    UnloadTexture(holeTexture);
    UnloadTexture(chainsTexture);
    UnloadTexture(cracksTexture);
    UnloadTexture(gameoverTexture);////////////////
    UnloadTexture(menudisplayTexture);//////////////////////
    UnloadTexture(chitTexture);
    UnloadTexture(displaychitTexture);
    UnloadTexture(winTexture);
    UnloadTexture(coinTexture);
   
    //MUSIC
    UnloadMusicStream(mainmusic);
    UnloadMusicStream(riddlemusic);
    UnloadMusicStream(gameovermusic);
    UnloadMusicStream(winmusic);
    CloseWindow();
    CloseAudioDevice();
    return 0;
}