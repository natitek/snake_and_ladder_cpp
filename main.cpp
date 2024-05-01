#include "raylib.h"
#include "iostream"
#include "vector"
#include <math.h>
#include <string>
#include <algorithm>
#include <fstream>





struct player
{
    std::string name;
    int wins;
    int losses;
    int points;
    int position;
};

void turn(player player, int roll){
    player.position += roll;
}
struct player player1;
struct player player2;
struct player player3;
struct player player4;

// randomly generate from 1-6
int roll()
{
    int num = rand() % 6 + 1;
    return num;
}


int generated = 0;
float boxsize = 70;
float initialpositionx = 260;
float initialpositiony = 666;
float temp;
int initial;

bool player1turn = true;
bool player2turn = false;
bool player3turn = false;
bool player4turn = false;

bool player1turnb = true;
bool player2turnb = false;
bool player3turnb = false;
bool player4turnb = false;


std::vector <Vector2> coordinates;


void inbetween(int initialsent , int destination){
    initial = initialsent;
        for(int initial; initial < destination; initial++){
            if(GetTime() >= 1.00){
        player1.position = initial;}
    }
}

void checkwin(player theplayer){
    if(theplayer.position == 100){
        
    }
}

    void generatecoordinates()
{
      coordinates.push_back({initialpositionx, initialpositiony});
      for (int counter = 1; counter <= 100; counter++)
      {
            // if second digit even

            if (((counter / 10) % 2) == 0)
            {

                  if ((counter -1)  % 10 == 0 && (counter-1)!=0)
                  {
                        coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                                    std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                        continue;
                  }
                  else  if(counter%10==0){
                    coordinates.push_back({coordinates[counter - 1].x - boxsize, coordinates[counter - 1].y});
                    std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                    continue;
                  }  
                  coordinates.push_back({coordinates[counter - 1].x + boxsize, coordinates[counter - 1].y});
            }
            // if second digit odd
            else if (((counter / 10) % 2) != 0)
            {
                  // move one space up if last digit 0
                  if ((counter -1) % 10 == 0&& (counter-1)!=0)
                  {
                        coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                        std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                        continue;
                  }
                else  if(counter%10==0){
                    coordinates.push_back({coordinates[counter - 1].x + boxsize, coordinates[counter - 1].y});
                    std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                    continue;
                  }                 
                 
                    coordinates.push_back({coordinates[counter - 1].x - boxsize, coordinates[counter - 1].y});
            }
            // Print out the output of the above code
            std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
      }
}

std::vector <player> players;
void loadPlayerData()
{
    std::ifstream inputFile("player_data.txt");
    if (inputFile.is_open())
    {
        players.clear(); // Clear the vector before loading data
        player playerr;
        while (inputFile >> playerr.name  >> playerr.wins >> playerr.losses >> playerr.points)
        {
            players.push_back(playerr);
        }
        inputFile.close(); 
    }
    else
    {
       std:: cout << "Unable to open file for reading." << std::endl;
    }
}
void savePlayerData(int n)
{
    std::ofstream outputFile("player_data.txt");
    if (outputFile.is_open())
    {
        for (player &playerr : players)
        {
            playerr.points = (playerr.wins * n);
            outputFile << playerr.name << " " << playerr.wins << " " << playerr.losses << " " << playerr.points<< "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}


void initializePlayer(player &newPlayer)
{
    std::cout << "Enter Name: ";
    getline(std::cin, newPlayer.name);
    newPlayer.wins = 0;
    newPlayer.losses = 0;
    newPlayer.points = 0;
    players.push_back(newPlayer);

}


int main(void)
{

//     // Lenovo thinkpad screen size(1366x768)

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();  

//     // Textures

Texture2D snakeimage = LoadTexture("src/img/snl.png");
Texture2D blue_sprite = LoadTexture("src/sprite/blue.png");
Texture2D bg_squares = LoadTexture("src/img/bg_check.png");
Texture2D menu_title = LoadTexture("src/img/snl_title.png");
Texture2D play_button = LoadTexture("src/img/play.png");
Texture2D setting_button = LoadTexture("src/img/gear.png");


//     // Sounds

Sound backgroundsound = LoadSound("src/audio/royalty_free_bg_sound.mp3");
Sound dice = LoadSound("src/audio/dice.mp3");

    SetTargetFPS(20); // Set our game to run at 60 frames-per-second



// PlaySound(backgroundsound);

//      //generate coordinates before game starts
      generatecoordinates();


    Rectangle btnBound;

std::vector<int> snakehead = {32, 36, 48, 62, 88, 95, 97};
std::vector<int> snaketail = {10, 6, 26, 18, 24, 56, 78};
std::vector<int> laddertop = {14, 30, 38, 42, 67, 76, 92, 99};
std::vector<int> ladderbottom = {4, 8, 1, 21, 50, 28, 71, 80};

Color trans = {0,0,0,0};

//     // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

       

        // Get the coordinates of the mouse by pressing SPACE
        Vector2 mousepositon = GetMousePosition();
        if (IsKeyReleased(KEY_SPACE))
        {
            
            std::cout << "x:" << mousepositon.x << "   y: " << mousepositon.y << std::endl;
        }

        // if(player1);


        else if (IsKeyReleased(KEY_A))
        {
            generated = roll();
            player1.position += generated;
            PlaySound(dice);
        }

        else if (IsKeyReleased(KEY_B))
        {
            generated = roll();
            player2.position += generated;
            PlaySound(dice);
        }


        else if (IsKeyReleased(KEY_C))
        {
            generated = roll();
            player3.position += generated;
            PlaySound(dice);
        }

 else if (IsKeyReleased(KEY_D))
        {
            generated = roll();
            player4.position += generated;
            PlaySound(dice);
        }


for (int i = 0; i <= 6; i++){
        if(player1.position == snakehead[i]){
          player1.position = snaketail[i];
        }
      }
      for (int i = 0; i <= 7; i++) {
        if (player1.position == ladderbottom[i]) {
          player1.position = laddertop[i];
        }
      }

//check if player lands on s or l
//  for (int n : snakehead)
//         {
//             if (player1.position == n)
//             {
//                 auto index = find(snakehead.begin(), snakehead.end(), n) - snakehead.begin();
//                 player1.position = snaketail[index];
//             }
//         }
// for (int n : ladderbottom)
//         {
//             if (player1.position == n)
//             {
//                 auto index = find(ladderbottom.begin(), laddertop.end(), n) - ladderbottom.begin();
//                 player1.position = laddertop[index];
//             }
//         }

//Mute button test
   


//         // Draw
//         //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle source = (Rectangle){0, 0, snakeimage.width, snakeimage.height};
        Rectangle Dest = (Rectangle){screenWidth / 2, screenHeight / 2, source.width * 1.5, source.height * 1.5};
        DrawTexturePro(snakeimage, source, Dest, (Vector2){Dest.width / 2, (Dest.height / 2)}, 0, WHITE);




        Rectangle bluesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle bluedestination = (Rectangle){coordinates[player1.position].x, coordinates[player1.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle greensource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle greendestination = (Rectangle){coordinates[player2.position].x+15, coordinates[player2.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle redsource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle reddestination = (Rectangle){coordinates[player3.position].x+5, coordinates[player3.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle orangesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle orangedestination = (Rectangle){coordinates[player4.position].x+10, coordinates[player4.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        //player 1
         DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);

          //player 2
         DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);

      
          //player 3
         DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
      
          //player 4
         DrawTexturePro(blue_sprite, orangesource, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, ORANGE);





        if(player1.position >= 100){
            DrawText("Player 1 Won", screenWidth/2, screenHeight/2, 80, GREEN);
        }

        DrawText("press R to roll", 100, 110, 20, GREEN);

        DrawText(TextFormat("%i", generated), 100, 120, 80, LIGHTGRAY);

        DrawText("player1 Positon : ", 100,180, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player1.position), 100, 220, 80, LIGHTGRAY);

        DrawText("players2 Positon : ", 100,280, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player2.position), 100, 320, 80, LIGHTGRAY);

        DrawText("players3 Positon : ", 100,380, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player3.position), 100, 420, 80, LIGHTGRAY);

         DrawText("players4 Positon : ", 100,480, 20, LIGHTGRAY);


         // MENU UI
       
       DrawTexture(bg_squares,0,0,RAYWHITE); //background
      
       DrawTextureEx(menu_title,(Vector2){(screenWidth/2)-((menu_title.width*0.2f)/2),80},0,0.2f,RAYWHITE);  //snl title
       DrawTextureEx(play_button,(Vector2){(screenWidth/2)-(0.2*(play_button.width)/2),(screenHeight/2)-(0.2*play_button.height/2)},0,0.2f,RAYWHITE); //play button
        DrawTextureEx(setting_button,{20,(screenHeight)-(setting_button.height*0.1f+30)},0,0.1f,RAYWHITE); //settings button

        
// std::cout << GetTime() << std::endl;
        EndDrawing();
        DrawText(TextFormat("%i", player4.position), 100, 520, 80, LIGHTGRAY);
    }
 UnloadSound(backgroundsound);  // Unload sound
 UnloadSound(dice);  
    CloseAudioDevice();     // Close audio device

 
    CloseWindow();
    return 0;
}