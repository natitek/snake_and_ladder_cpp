#include "raylib.h"
#include "raygui.h"
#include "iostream"
#include "vector"
#include <math.h>
#include <string>
#include <algorithm>
#include <fstream>


#define MAX_NAME_CHAR 10


struct player
{
    std::string name;
    int wins;
    int losses;
    int points;
    int position;
};

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

bool menu_state1;
bool menu_state2;
bool menu_state3;
bool menu_state4;
bool menu_state5;
bool menu_state6;
bool menu_state7;

bool player1in = false;
bool player2in = false;
bool player3in = false;
bool player4in = false;

bool player1turn = false;
bool player2turn = false;
bool player3turn = false;
bool player4turn = false;

char player1_name[MAX_NAME_CHAR + 1] = "\0";
char player2_name[MAX_NAME_CHAR + 1] = "\0";
char player3_name[MAX_NAME_CHAR + 1] = "\0";
char player4_name[MAX_NAME_CHAR + 1] = "\0";

int letterCounter = 0;
 

std::vector <Vector2> coordinates;


void inbetween(int initialsent , int destination){
    initial = initialsent;
        for(int initial; initial < destination; initial++){
            if(GetTime() >= 1.00){
        player1.position = initial;}
    }
}


// void checkwin(player theplayer){
//     if(theplayer.position == 100){
        
//     }
// }

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

Texture2D snakeimage = LoadTexture("src/img/snl.png");  // board image
Texture2D blue_sprite = LoadTexture("src/sprite/blue.png"); // player piece 
Texture2D bg_squares = LoadTexture("src/img/bg_check.png"); // cyan backgroun
Texture2D menu_title = LoadTexture("src/img/snl_title.png"); // title of game
Texture2D play_button = LoadTexture("src/img/play.png"); // play button
Texture2D setting_button = LoadTexture("src/img/gear.png"); //settings button

Texture2D single_player = LoadTexture("src/img/single_player.png");

Texture2D multi_player = LoadTexture("src/img/multi_player.png");

Texture2D option_bg = LoadTexture("src/img/option_bg.png");

Texture2D submit_button = LoadTexture("src/img/submit.png");

Texture2D main_menu_bg = LoadTexture("src/img/main_menu_bg.png");



//     // Sounds

Sound backgroundsound = LoadSound("src/audio/royalty_free_bg_sound.mp3");
Sound dice = LoadSound("src/audio/dice.mp3");

    SetTargetFPS(30); // Set our game to run at 60 frames-per-second



// PlaySound(backgroundsound);

//      //generate coordinates before game starts
      generatecoordinates();



std::vector<int> snakehead = {32, 36, 48, 62, 88, 95, 97};
std::vector<int> snaketail = {10, 6, 26, 18, 24, 56, 78};
std::vector<int> laddertop = {14, 30, 38, 42, 67, 76, 92, 99};
std::vector<int> ladderbottom = {4, 8, 1, 21, 50, 28, 71, 80};

Color trans = {0,0,0,0};

Rectangle player1_name_box = {400,100,225,50};
Rectangle player2_name_box = {400,200,225,50};
Rectangle player3_name_box = {400,300,225,50};
Rectangle player4_name_box = {400,400,225,50};


bool mouseOnText1 = false;
bool mouseOnText2 = false;
bool mouseOnText3 = false;
bool mouseOnText4 = false;

int framesCounter = 0;

// menu states

menu_state1 = true;



//     // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

       

        // Get the coordinates of the mouse by pressing SPACE
        Vector2 mouseposition = GetMousePosition();
        if (IsKeyReleased(KEY_SPACE))
        {
            
            std::cout << "x:" << mouseposition.x << "   y: " << mouseposition.y << std::endl;
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


//Text logic


//         // Draw
//         //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle source = (Rectangle){0, 0, snakeimage.width, snakeimage.height};
        Rectangle Dest = (Rectangle){screenWidth / 2, screenHeight / 2, source.width * 1.5, source.height * 1.5};

        Rectangle bluesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle bluedestination = (Rectangle){coordinates[player1.position].x, coordinates[player1.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle greensource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle greendestination = (Rectangle){coordinates[player2.position].x+15, coordinates[player2.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle redsource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle reddestination = (Rectangle){coordinates[player3.position].x+5, coordinates[player3.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle orangesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle orangedestination = (Rectangle){coordinates[player4.position].x+10, coordinates[player4.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        //player 1
        //  DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);

        //   //player 2
        //  DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);

      
        //   //player 3
        //  DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
      
        //   //player 4
        //  DrawTexturePro(blue_sprite, orangesource, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, ORANGE);





        if(player1.position >= 100){
            DrawText("Player 1 Won", screenWidth/2, screenHeight/2, 80, GREEN);
        }


         //--- MENU UI ---//
    
        

        Rectangle option_bg_src = {0,0,option_bg.width,option_bg.height};
        Rectangle option_bg_des = {0,0,option_bg.width,option_bg.height};

        

        Rectangle single_player_src = {0,0,single_player.width,single_player.height};
        Rectangle single_player_des = {150,150,single_player_src.width,single_player_src.height};

   

        Rectangle multi_player_src = {0,0,multi_player.width,multi_player.height};
        Rectangle multi_player_des = {single_player_des.x+single_player_des.width+50,single_player_des.y,multi_player_src.width,multi_player_src.height};

        Rectangle play_button_src = {0,0,play_button.width,play_button.height};
        Rectangle play_button_des = {screenWidth/2-40,screenHeight/2+60,100,100};

        Rectangle setting_button_src = {0,0,setting_button.width,setting_button.height};
        Rectangle setting_button_des = {50,600,100,100};

        Rectangle submit_button_src = {0,0,submit_button.width,submit_button.height};
        Rectangle submit_button_des = {screenWidth/2,screenHeight/2,submit_button.width*0.5,submit_button.height*0.5};

     


        //menu state 1  main menu
        if(menu_state1){
    menu_state2,menu_state3,menu_state4,menu_state5,menu_state6,menu_state7= false;
        DrawTexture(main_menu_bg,0,0,RAYWHITE); //background
        DrawTexturePro(play_button,play_button_src,play_button_des,{0,0},0,RAYWHITE); //playbutton
        DrawTexturePro(setting_button,setting_button_src,setting_button_des,{0,0},0,RAYWHITE); //setting_button
               
                // checks if play_button is clicked
        if (CheckCollisionPointRec(mouseposition, play_button_des)){
           if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))menu_state3 = true;}
              // checks if setting_button is clicked
        if (CheckCollisionPointRec(mouseposition,setting_button_des)){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))menu_state2 = true;
                    }
                }
              
    
 
         //menu state 2 settings menu
      if(menu_state2){
            menu_state1,menu_state3,menu_state4,menu_state5,menu_state6,menu_state7= false;
        DrawTextureEx(bg_squares,{0,0},0,1,RAYWHITE);
        DrawTextureEx(option_bg,{100,100},0,1.0f,RAYWHITE);
          // press backspace to return to the main menu
        if(IsKeyPressed(KEY_BACKSPACE) && menu_state2 == true){
             menu_state1 =true;
            menu_state2 = false;
           
        }
    }

         //menu state 3 choose b/n single player or multiplayer
        if(menu_state3){
    menu_state1 = false;
    menu_state2 = false;
    menu_state4 = false;
    menu_state5 = false;
    menu_state6 = false;
    menu_state7 = false;
    DrawTextureEx(bg_squares,{0,0},0,1,RAYWHITE);
    DrawTexturePro(single_player,single_player_src,single_player_des,{0,0},0,RAYWHITE);

    DrawTexturePro(multi_player,multi_player_src,multi_player_des,{0,0},0,RAYWHITE);


           if (CheckCollisionPointRec(mouseposition, single_player_des) && menu_state1 != true && menu_state2 != true && menu_state5 != true){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))menu_state4 = true;}

    if (CheckCollisionPointRec(mouseposition, multi_player_des) && menu_state1 != true && menu_state2 != true  && menu_state4 != true){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))menu_state5 = true;}

 if(IsKeyPressed(KEY_BACKSPACE) && menu_state3 == true){
             menu_state1 =true;
            menu_state3 = false;
           
        }
    }

         //menu state 4  single player options
        if(menu_state4){
    menu_state1 = false;
    menu_state2 = false;
    menu_state3 = false;
    menu_state5 = false;
    menu_state6 = false;
    menu_state7 = false;
   DrawTextureEx(bg_squares,{0,0},0,1,RAYWHITE);
   DrawTextureEx(option_bg,{100,100},0,1.0f,RAYWHITE);
    DrawText("Single player options", 400,100, 50, LIGHTGRAY);
//    DrawRectangleRec(player1_name_box,WHITE);
    DrawTexturePro(submit_button,submit_button_src,submit_button_des,{0,0},0,RAYWHITE);

    if (CheckCollisionPointRec(mouseposition, submit_button_des) && menu_state4 == true){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    }
}


 if(IsKeyPressed(KEY_BACKSPACE) && menu_state4 == true){
             menu_state3 =true;
            menu_state4 = false;
           
        }
    }

         //menu state 5 multiplayer option
        if(menu_state5){
    
    menu_state1 = false;
    menu_state2 = false;
    menu_state3 = false;
    menu_state4 = false;
    menu_state6 = false;
    menu_state7 = false;
    DrawTextureEx(bg_squares,{0,0},0,1,RAYWHITE);
    DrawText("multiplayer options", 400,100, 50, LIGHTGRAY);
    DrawTexturePro(submit_button,submit_button_src,submit_button_des,{0,0},0,RAYWHITE);
    if (CheckCollisionPointRec(mouseposition, submit_button_des)){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    }
}
 if(IsKeyPressed(KEY_BACKSPACE) && menu_state5 == true){
             menu_state3 =true;
            menu_state5 = false;
           
        }
    }

           //menu state 6 game screen
        if(menu_state6){
     menu_state1 = false;
    menu_state2 = false;
    menu_state3 = false;
    menu_state4 = false;
    menu_state5 = false;
    menu_state7 = false;
   

  DrawTexturePro(snakeimage, source, Dest, (Vector2){Dest.width / 2, (Dest.height / 2)}, 0, WHITE);

        DrawText("press R to roll", 100, 110, 20, GREEN);

        DrawText(TextFormat("%i", generated), 100, 120, 80, LIGHTGRAY);

        DrawText("player1 Positon : ", 100,180, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player1.position), 100, 220, 80, LIGHTGRAY);

        DrawText("players2 Positon : ", 100,280, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player2.position), 100, 320, 80, LIGHTGRAY);

        DrawText("players3 Positon : ", 100,380, 20, LIGHTGRAY);
       
        DrawText(TextFormat("%i", player3.position), 100, 420, 80, LIGHTGRAY);

         DrawText("players4 Positon : ", 100,480, 20, LIGHTGRAY);

    }

             //menu state 7 pause screen
        if(menu_state7){
    menu_state1 = false;
    menu_state2 = false;
    menu_state3 = false;
    menu_state4 = false;
    menu_state5 = false;
    menu_state6 = false;
   
    }



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