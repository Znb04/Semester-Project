ESCAPE ROOM
A horror themed escape room game (in C++ with raylib)
Course: Programming Fundamentals (PF) – 1st Semester
Team:
Name: Zainab Fatima                    Rollno:26L-0817
Name: Maryam Fatima                    Rollno:26L-0695

1.	About the Game
Escape Room is a 2D game in which player is trapped in a haunted room. The player has 300s(5mins) and 3 lives to find clues and solve the riddles in the room before the time runs out. Every correct answer earns 20 points. Once all riddles are solved the player gets the key and can unlock the door to escape the room before the reaper arrives.

2.	How To Play
The goal is to solve all riddles and collect 120 points, then walk to the door and press U to unlock it. To interact with an object walk up to it and press E to open the riddle. Type the answer and press Enter. Wrong answer will cost one life. If you lose all 3 lives or the time runs out, the game is over.

Important things to know: 
•	You must try interacting with every object in the room. 
•	A riddle may or may not lead to another riddle.
•	 A riddle may or may not give you a clue. 
•	Some clues can be seen only once. Once you close them you might not be able to see them again.
•	Be careful with your answers. Every wrong answer costs a life.

3.	    Controls 
Key	        |           Action
S	        |Start the game from main menu
Arrow keys	|Move the Player
E	        |Interact with an object
Type + Enter	|Type and submit an answer in riddle 
Backspace	|Delete the last types character
TAB	        |Leave a riddle/clue and return to room
U	        |Unlock the door (after collecting all points)
P	        |Pause the game
C/R/G	        |While paused: Continues/Restart/End game 
M	        |On game over and win screen: Return to main menu


4.	Requirements

•	A C++ compiler and IDE (Visual Studio)
•	Raylib library, version 6.2.0 
•	The image and sound files listed below, placed in the same as program file.

5.	Installation and Setup
•	Clone or download the repository: git clone https://github.com/Znb04/Semester-Project/tree/main
•	Open the project folder and double-click the .sln file to open it in Visual Studio.
•	raylib is installed through NuGet and is restored automatically when you build. If it is not, right-click the solution in Solution Explorer and choose Restore NuGet Packages.
•	At the top, set the configuration to Debug or Release and the platform to x64.
•	Go to Project > Properties, set Configuration to All Configurations, then open Debugging and set Working Directory to $(ProjectDir). This lets the game find the assets folder.
•	Press Ctrl + F5 to build and run.

6.	Project Files 
Source File	Main.cpp containing game
Images(.png)	chainsR.png, COFFINS.png, COUCH.png, DOOR.png, LIVES.png, reapshehe.png, skull.png, windowhehe.png, chitss.png, COIN.png, cracks.png, FINAL WIN.png, GIRLPLAYER.png, TIMESKELETON.png, clockhehe.png, comp.png, DISPLAYCHIT.png, FLOOR.png, HOLE.png, SHELF.png, wall.png
Music (.mp3)	Eternal Terminal.mp3, riddle2.mp3, winmusic.mp3, gameovermusic.mp3






