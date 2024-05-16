#include "raylib.h"
#include "iostream"
#include "vector"
#include <math.h>
#include <string>
#include <algorithm>
#include <fstream>

#define MAX_VOLUME 10
#define MIN_VOLUME 0
#define MAX_NAME_CHAR 10

  //     // Lenovo thinkpad screen size(1366x768)

    const int screenWidth = 1280;
    const int screenHeight = 720;



struct player
{
    std::string name;
    int wins;
    int losses;
    int position;
};

struct player player1;
struct player player2;
struct player player3;
struct player player4;

// randomly generate from 1-6
int roll()
{
    int num =GetRandomValue(1 , 6);
    return num;
}

int generated = 0;
float boxsize = 70;
float initialpositionx = 260;
float initialpositiony = 666;
float temp;

bool menu_state1;
bool menu_state2;
bool menu_state3;
bool menu_state4;
bool menu_state5;
bool menu_state6;
bool menu_state7;
bool menu_state8;

bool player1in = false;
bool player2in = false;
bool player3in = false;
bool player4in = false;

bool player1turn = true;
bool player2turn = false;
bool player3turn = false;
bool player4turn = false;

char player1_name[MAX_NAME_CHAR + 1] = "\0";
char player2_name[MAX_NAME_CHAR + 1] = "\0";
char player3_name[MAX_NAME_CHAR + 1] = "\0";
char player4_name[MAX_NAME_CHAR + 1] = "\0";

bool mouseOnTextBox = false;
bool mouseOnTextBox1 = false;
bool mouseOnTextBox2 = false;
bool mouseOnTextBox3 = false;
bool mouseOnTextBox4 = false;

int numberofchar = 0;
int numberofchar1 = 0;
int numberofchar2 = 0;
int numberofchar3 = 0;
int numberofchar4 = 0;

bool multi = false;


bool name1= false;
bool name2= false;
bool name3= false;
bool name4= false;


std::vector<Vector2> coordinates;

std::vector<int> snakehead = {32, 36, 48, 62, 88, 95, 97};
std::vector<int> snaketail = {10, 6, 26, 18, 24, 56, 78};
std::vector<int> laddertop = {14, 30, 38, 42, 67, 76, 92, 99};
std::vector<int> ladderbottom = {4, 8, 1, 21, 50, 28, 71, 80};

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

            if ((counter - 1) % 10 == 0 && (counter - 1) != 0)
            {
                coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                continue;
            }
            else if (counter % 10 == 0)
            {
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
            if ((counter - 1) % 10 == 0 && (counter - 1) != 0)
            {
                coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                continue;
            }
            else if (counter % 10 == 0)
            {
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
std::vector<player> players;
void leaderboardSort()
{
    for (unsigned int i = 0; i < players.size(); i++)
    {
        for (unsigned int j = 0; j < players.size() - 1; j++)
        {
            if (players[j].wins < players[j + 1].wins)
                std::swap(players[j], players[j + 1]);
        }
    }
}


void loadPlayerData()
{
    std::ifstream inputFile("player_data.txt");
    if (inputFile.is_open())
    {
        players.clear(); // Clear the vector before loading data
        player playerr;
        while (inputFile >> playerr.name >> playerr.wins >> playerr.losses)
        {
            players.push_back(playerr);
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file for reading." << std::endl;
    }
    leaderboardSort();
}
void savePlayerData()
{
    
    std::ofstream outputFile("player_data.txt");
    if (outputFile.is_open())
    {
        for (player &playerr : players)
        {
            
            outputFile << playerr.name << " " << playerr.wins << " " << playerr.losses << " " << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

void playerexist(){
    for (int i = 0; i < players.size(); i++)
    {
        if (player1_name == players[i].name && player1in)
        {
            name1 = true;
            players[i].name = player1.name;
            players[i].wins = player1.wins;
            players[i].losses = player1.losses;
        }
        if (player2_name == players[i].name && player2in)
        {
            name2 = true;
            players[i].name = player2.name;
            players[i].wins = player2.wins;
            players[i].losses = player2.losses;
        }
        if (player3_name == players[i].name && player3in)
        {
            name3 = true;
            players[i].name = player3.name;
            players[i].wins = player3.wins;
            players[i].losses = player3.losses;
        }
        if (player4_name == players[i].name && player4in)
        {
            name4 = true;
            players[i].name = player4.name;
            players[i].wins = player4.wins;
            players[i].losses = player4.losses;
        }
    }
}

void initializePlayer(player &newPlayer, char* name)
{
    newPlayer.name = name;
    newPlayer.wins = 0;
    newPlayer.losses = 0;
    players.push_back(newPlayer);
}

void checksnakeorladder(player &player)
{
    for (int i = 0; i <= 6; i++)
    {
        if (player.position == snakehead[i])
        {
            player.position = snaketail[i];
        }
    }
    for (int i = 0; i <= 7; i++)
    {
        if (player.position == ladderbottom[i])
        {
            player.position = laddertop[i];
        }
    }
}
 
 int num_of_player;
int checkwin(player &player)
{
    bool loss = false;
  static int count = 0;

     if (player.position == 100)
        {
            loss = true;
            player.wins++;
            savePlayerData();
            return 1;
        }
    else return 0;
        if(player.position != 100 && loss){
            if(count < 3){
            player.losses++;
            count++;
            }
        }
    
  
}

   //remove player name
   
         void removenames(char* name_of_player){
            for(int i = 0; i < sizeof(name_of_player); i++){
                 name_of_player[i]  = '\0';}
                    }

    //change background function

    void change_background(){

    }

Color trans_green = {0, 228, 48, 50};

int main(void)
{

  

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();

    //     // Textures

    Texture2D snakeimage = LoadTexture("src/img/snl.png");       // board image
    Texture2D blue_sprite = LoadTexture("src/sprite/blue.png");  // player piece
    Texture2D bg_squares = LoadTexture("src/img/bg_check.png");  // cyan backgroun
    Texture2D menu_title = LoadTexture("src/img/snl_title.png"); // title of game
    Texture2D play_button = LoadTexture("src/img/play.png");     // play button
    Texture2D setting_button = LoadTexture("src/img/gear.png");  // settings button
    Texture2D single_player = LoadTexture("src/img/single_player.png");
    Texture2D multi_player = LoadTexture("src/img/multi_player.png");
    Texture2D option_bg = LoadTexture("src/img/option_bg.png");
    Texture2D submit_button = LoadTexture("src/img/submit.png");
    Texture2D main_menu_bg = LoadTexture("src/img/main_menu_bg.png");
    Texture2D plus_button = LoadTexture("src/img/plus_button.png");
    Texture2D minus_button = LoadTexture("src/img/minus_button.png");
    Texture2D sprite_image = LoadTexture("src/img/sprite_image.png");
    Texture2D next_color_right = LoadTexture("src/img/next_color_right.png");
    Texture2D next_color_left = LoadTexture("src/img/next_color_left.png");
    Texture2D pause_button = LoadTexture("src/img/pause_button.png");
    Texture2D profile_button = LoadTexture("src/img/profile_button.png");
    


    Image window_icon = LoadImage("src/img/dice_menu.png");

    //     // Sounds

    Sound backgroundsound = LoadSound("src/audio/royalty_free_bg_sound.mp3");
    Sound dice = LoadSound("src/audio/dice.mp3");

    SetTargetFPS(30); // Set our game to run at 60 frames-per-second

    // void SetWindowIcon(Image window_icon);

    SetWindowIcon(window_icon);

    // PlaySound(backgroundsound);

    //      //generate coordinates before game starts
    generatecoordinates();

    Rectangle player1_single_name_box = {514, 241, 300, 50};

    Rectangle player1_name_box = {400, 200, 300, 50};
    Rectangle player2_name_box = {400, 300, 300, 50};
    Rectangle player3_name_box = {400, 400, 300, 50};
    Rectangle player4_name_box = {400, 500, 300, 50};

    int num_of_ai = 1;
    int num_of_humans = 1;

    int volumeofbg = 4;
    int volumeofsfx = 4;

    // menu states

    menu_state1 = true;

    //     // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        loadPlayerData();

        // Get the coordinates of the mouse by pressing SPACE
        Vector2 mouseposition = GetMousePosition();
        if (IsKeyReleased(KEY_SPACE))
        {

            std::cout << "x:" << mouseposition.x << "   y: " << mouseposition.y << std::endl;
        }

        // if(player1);

        for (int i = 0; i <= 6; i++)
        {
            if (player1.position == snakehead[i])
            {
                player1.position = snaketail[i];
            }
        }
        for (int i = 0; i <= 7; i++)
        {
            if (player1.position == ladderbottom[i])
            {
                player1.position = laddertop[i];
            }
        }

        // Text logic

        //         // Draw
        //         //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle source = (Rectangle){0, 0, snakeimage.width, snakeimage.height};
        Rectangle Dest = (Rectangle){screenWidth / 2, screenHeight / 2, source.width * 1.5, source.height * 1.5};

        Rectangle bluesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle bluedestination = (Rectangle){coordinates[player1.position].x, coordinates[player1.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle greensource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle greendestination = (Rectangle){coordinates[player2.position].x + 15, coordinates[player2.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle redsource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle reddestination = (Rectangle){coordinates[player3.position].x + 5, coordinates[player3.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle orangesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle orangedestination = (Rectangle){coordinates[player4.position].x + 10, coordinates[player4.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};


Rectangle profile_button_src = (Rectangle){0, 0, profile_button.width, profile_button.height};

        Rectangle profile_button_des= (Rectangle){screenWidth-150,screenHeight-120,profile_button_src.width*0.2,profile_button_src.height*0.2};




static int sprite_index = 0;

static int sprite_index1 = 0;

static int sprite_index2 = 0;

static int sprite_index3 = 0;

static int sprite_index4 = 0;



 Rectangle spritesource = {sprite_index,0,sprite_image.width/10,sprite_image.height};

 Rectangle spritesource1 = {sprite_index1,0,sprite_image.width/10,sprite_image.height};
 Rectangle spritesource2 = {sprite_index2,0,sprite_image.width/10,sprite_image.height};
 Rectangle spritesource3 = {sprite_index3,0,sprite_image.width/10,sprite_image.height};
 Rectangle spritesource4  = {sprite_index4,0,sprite_image.width/10,sprite_image.height};

 if(mouseOnTextBox){
         if((IsKeyPressed(KEY_RIGHT)) && (menu_state5 || menu_state4)){
                
             sprite_index += (sprite_image.width/10);
}
else if((IsKeyPressed(KEY_LEFT)) && menu_state5) {
    sprite_index -= (sprite_image.width/10);
}}

 if(mouseOnTextBox1){
         if((IsKeyPressed(KEY_RIGHT)) && (menu_state5 || menu_state4)){
                
             sprite_index += (sprite_image.width/10);
}
else if((IsKeyPressed(KEY_LEFT)) && menu_state5) {
    sprite_index -= (sprite_image.width/10);
}}

        Rectangle spritedestinationsingle = {player1_single_name_box.x-100,player1_single_name_box.y,spritesource.width/5,spritesource.height/5};

        Rectangle spritedestination = {player1_single_name_box.x-200,player1_name_box.y,spritesource.width/5,spritesource.height/5};

        Rectangle spritedestination2 = {player1_single_name_box.x-200,player2_name_box.y,spritesource.width/5,spritesource.height/5};

          Rectangle spritedestination3 = {player1_single_name_box.x-200,player3_name_box.y,spritesource.width/5,spritesource.height/5};

           Rectangle spritedestination4 = {player1_single_name_box.x-200,player4_name_box.y,spritesource.width/5,spritesource.height/5};


        


        //--- MENU UI ---//

        Rectangle option_bg_src = {0, 0, option_bg.width, option_bg.height};
        Rectangle option_bg_des = {0, 0, option_bg.width, option_bg.height};

        Rectangle single_player_src = {0, 0, single_player.width, single_player.height};
        Rectangle single_player_des = {150, 150, single_player_src.width, single_player_src.height};

        Rectangle multi_player_src = {0, 0, multi_player.width, multi_player.height};
        Rectangle multi_player_des = {single_player_des.x + single_player_des.width + 50, single_player_des.y, multi_player_src.width, multi_player_src.height};

        Rectangle play_button_src = {0, 0, play_button.width, play_button.height};
        Rectangle play_button_des = {screenWidth / 2 - 40, screenHeight / 2 + 60, 100, 100};

        Rectangle setting_button_src = {0, 0, setting_button.width, setting_button.height};
        Rectangle setting_button_des = {50, 600, 100, 100};

        Rectangle submit_button_src = {0, 0, submit_button.width, submit_button.height};

          Rectangle submit_button_des = {615,497, submit_button.width * 0.3, submit_button.height * 0.3};


if(menu_state5){
          submit_button_des = (Rectangle){835, 340, submit_button.width * 0.3, submit_button.height * 0.3}; //change position of submit button in single and multiplayer options
}

       

        Rectangle pause_rec = {0,0, pause_button.width,pause_button.height};


        // menu state 1  main menu
        if (menu_state1)
        {
            menu_state2, menu_state3, menu_state4, menu_state5, menu_state6, menu_state7 = false;
            DrawTexture(main_menu_bg, 0, 0, RAYWHITE);                                                   // background
            DrawTexturePro(play_button, play_button_src, play_button_des, {0, 0}, 0, RAYWHITE);          // playbutton
            DrawTexturePro(setting_button, setting_button_src, setting_button_des, {0, 0}, 0, RAYWHITE); // setting_button

            DrawTexturePro(profile_button, profile_button_src, profile_button_des, {0, 0}, 0, RAYWHITE); // profile_button

            // checks if play_button is clicked
            if (CheckCollisionPointRec(mouseposition, play_button_des) && menu_state2 != true)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    menu_state3 = true;
            }
            // checks if setting_button is clicked
            if (CheckCollisionPointRec(mouseposition, setting_button_des))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    menu_state2 = true;
            }
        }

        // menu state 2 settings menu
        if (menu_state2)
        {
            menu_state1, menu_state3, menu_state4, menu_state5, menu_state6, menu_state7 = false;
            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);

            // volume controllers

            SetSoundVolume(backgroundsound, (float)volumeofbg / 10);

            // if (volumeofbg > MAX_VOLUME) volumeofbg = MAX_VOLUME;
            // else if (volumeofbg < MAX_VOLUME) volumeofbg = MIN_VOLUME;

            // if (volumeofsfx > MAX_VOLUME) volumeofsfx = MAX_VOLUME;
            // else if (volumeofsfx < MAX_VOLUME) volumeofsfx = MIN_VOLUME;
            DrawText("Settings", screenWidth / 2 - 130, 100, 70, GRAY);
            DrawText("Music", 250, 170, 40, RED);
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofbg)
                    DrawRectangle(250 + 70 * i, 205, 70, 30, RED);
                DrawRectangleLines(250 + 70 * i, 205, 70, 30, MAROON);
            }
            DrawText("SFX", 250, 285, 40, RED);
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofsfx)
                    DrawRectangle(250 + 70 * i, 321, 70, 30, GREEN);
                DrawRectangleLines(250 + 70 * i, 321, 70, 30, MAROON);
            }

            if ((IsKeyPressed(KEY_NINE)) && menu_state2 == true)
                volumeofsfx--;
            else if ((IsKeyPressed(KEY_ZERO)) && menu_state2 == true)
                volumeofsfx++;

            if ((IsKeyPressed(KEY_EQUAL)) && menu_state2 == true)
                volumeofbg++;
            else if ((IsKeyPressed(KEY_MINUS)) && menu_state2 == true)
                volumeofbg--;

            SetSoundVolume(backgroundsound, volumeofbg / 10);

            // press backspace to return to the main menu
            if (IsKeyPressed(KEY_BACKSPACE) && menu_state2 == true)
            {
                menu_state1 = true;
                menu_state2 = false;
            }
        }

        // menu state 3 choose b/n single player or multiplayer
        if (menu_state3)
        {
            menu_state1 = false;
            menu_state2 = false;
            menu_state4 = false;
            menu_state5 = false;
            menu_state6 = false;
            menu_state7 = false;
            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
            DrawTexturePro(single_player, single_player_src, single_player_des, {0, 0}, 0, RAYWHITE);

            DrawTexturePro(multi_player, multi_player_src, multi_player_des, {0, 0}, 0, RAYWHITE);

            // single Player button
            if (CheckCollisionPointRec(mouseposition, single_player_des) && menu_state1 != true && menu_state2 != true && menu_state5 != true)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    menu_state4 = true;
                    num_of_ai = 1;
                    num_of_humans = 1;
                      multi = false;
                    player2in=false;
                    player3in=false;
                    player4in=false;
                  
                }
            }
            // multiplayer button
            if (CheckCollisionPointRec(mouseposition, multi_player_des) && menu_state1 != true && menu_state2 != true && menu_state4 != true)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    menu_state5 = true;
                multi = true;
                num_of_ai = 1;
                num_of_humans = 2;}
            }

            if (IsKeyPressed(KEY_BACKSPACE) && menu_state3 == true)
            {
                menu_state1 = true;
                menu_state3 = false;
            }
        }

        // menu state 4  single player options
        if (menu_state4)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state5 = menu_state6 = menu_state7 = false;
            
            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
            DrawText("Single player options", 400, 100, 50, LIGHTGRAY);

            DrawText("player name", player1_single_name_box.x, player1_single_name_box.y - 30, 20, GRAY);

            DrawRectangleRec(player1_single_name_box, WHITE);
            if (mouseOnTextBox && menu_state4)
                DrawRectangleLines(player1_single_name_box.x, player1_single_name_box.y, player1_single_name_box.width, player1_single_name_box.height, RED);
            else
                DrawRectangleLines(player1_single_name_box.x, player1_single_name_box.y, player1_single_name_box.width, player1_single_name_box.height, DARKGRAY);

            DrawText(player1_name, player1_single_name_box.x + 5, player1_single_name_box.y + 8, 40, BLUE);

            DrawText("ai players", 533, 360, 40, BLACK);
            DrawText(TextFormat("%i", num_of_ai), 620, 420, 40, BLACK);

            DrawTextureEx(plus_button, {700, 400}, 0, 1, RAYWHITE);
            DrawTextureEx(minus_button, {500, 400}, 0, 1, RAYWHITE);

            DrawTexturePro(submit_button, submit_button_src, submit_button_des, {0, 0}, 0, RAYWHITE);

            DrawTexturePro(sprite_image,spritesource,spritedestinationsingle,{0,0},0,RAYWHITE); // Sprite pieces color selection

DrawTextureEx(next_color_right,{player1_single_name_box.x-50,player1_single_name_box.y},0,1.0f,RAYWHITE);// next color button right
DrawTextureEx(next_color_left,{player1_single_name_box.x-150,player1_single_name_box.y},0,1.0f,RAYWHITE);// next color button left

            if (CheckCollisionPointRec(mouseposition, player1_single_name_box) && menu_state4 == true)
                mouseOnTextBox = true;
            else mouseOnTextBox = false;
            if (mouseOnTextBox && menu_state4)
            {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0)
                {
                    if (numberofchar < MAX_NAME_CHAR)
                    {
                        player1_name[numberofchar] = (char)key;
                        player1_name[numberofchar + 1] = '\0';
                        numberofchar++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_RIGHT_SHIFT))
                {
                    numberofchar--;
                    if (numberofchar < 0)
                        numberofchar = 0;
                    player1_name[numberofchar] = '\0';
                }
            }
            else
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (IsKeyPressed(KEY_EQUAL) && menu_state4 == true)
            {
                num_of_ai++;
            }

            if (IsKeyPressed(KEY_MINUS) && menu_state4 == true)
            {
                num_of_ai--;
            }

            if (num_of_ai > 3)
                num_of_ai--;
            else if (num_of_ai < 1)
                num_of_ai++;

            if (CheckCollisionPointRec(mouseposition, submit_button_des) && menu_state4 == true)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {   

                 
                   


                    menu_state6 = true;
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE) && menu_state4 == true)
            {
                menu_state3 = true;
                menu_state4 = false;
                multi = false;
            }
        }

        // menu state 5 multiplayer option
        if (menu_state5)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state6 = menu_state7 = menu_state8= false;
            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
            DrawText("multiplayer options", 450, 100, 50, LIGHTGRAY);

        loadPlayerData();

            if (num_of_humans == 2)
            {
                DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
                DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
                   DrawText("multiplayer options", 450, 100, 50, LIGHTGRAY);
                DrawText("player 1 name", player1_name_box.x, player1_name_box.y - 30, 20, GRAY);
                DrawText("player 2 name", player2_name_box.x, player2_name_box.y - 30, 20, GRAY);
                DrawRectangleRec(player1_name_box, WHITE);
                DrawRectangleRec(player2_name_box, WHITE);
   
                DrawTexturePro(sprite_image,spritesource,spritedestination,{0,0},0,RAYWHITE); 
                DrawTexturePro(sprite_image,spritesource,spritedestination2,{0,0},0,RAYWHITE); 
          
                // Sprite pieces color selection

                if (mouseOnTextBox1 && menu_state5)
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, RED);
                else
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, DARKGRAY);
                if (mouseOnTextBox2 && menu_state5)
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, RED);
                else
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, DARKGRAY);

                DrawText(player1_name, player1_name_box.x + 5, player1_name_box.y + 8, 40, BLUE);
                DrawText(player2_name, player2_name_box.x + 5, player2_name_box.y + 8, 40, BLUE);
            }
            else if (num_of_humans == 3)
            {
                DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
                DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
                   DrawText("multiplayer options", 450, 100, 50, LIGHTGRAY);
                   
                DrawText("player 1 name", player1_name_box.x, player1_name_box.y - 30, 20, GRAY);
                DrawText("player 2 name", player2_name_box.x, player2_name_box.y - 30, 20, GRAY);
                DrawText("player 3 name", player3_name_box.x, player3_name_box.y - 30, 20, GRAY);
                DrawRectangleRec(player1_name_box, WHITE);
                DrawRectangleRec(player2_name_box, WHITE);
                DrawRectangleRec(player3_name_box, WHITE);

                   DrawTexturePro(sprite_image,spritesource,spritedestination,{0,0},0,RAYWHITE); 
                     DrawTexturePro(sprite_image,spritesource,spritedestination2,{0,0},0,RAYWHITE); 
                    DrawTexturePro(sprite_image,spritesource,spritedestination3,{0,0},0,RAYWHITE); 


                if (mouseOnTextBox1 && menu_state5)
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, RED);
                else
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, DARKGRAY);
                if (mouseOnTextBox2 && menu_state5)
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, RED);
                else
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, DARKGRAY);
                if (mouseOnTextBox3 && menu_state5)
                    DrawRectangleLines(player3_name_box.x, player3_name_box.y, player3_name_box.width, player3_name_box.height, RED);
                else
                    DrawRectangleLines(player3_name_box.x, player3_name_box.y, player3_name_box.width, player3_name_box.height, DARKGRAY);

                DrawText(player1_name, player1_name_box.x + 5, player1_name_box.y + 8, 40, BLUE);
                DrawText(player2_name, player2_name_box.x + 5, player2_name_box.y + 8, 40, BLUE);
                DrawText(player3_name, player3_name_box.x + 5, player3_name_box.y + 8, 40, BLUE);
            }
            else if (num_of_humans == 4)
            {
                DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
                DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
                   DrawText("multiplayer options", 450, 100, 50, LIGHTGRAY);

            DrawTexturePro(sprite_image,spritesource,spritedestination,{0,0},0,RAYWHITE); 
            DrawTexturePro(sprite_image,spritesource,spritedestination2,{0,0},0,RAYWHITE); 
            DrawTexturePro(sprite_image,spritesource,spritedestination3,{0,0},0,RAYWHITE); 
            DrawTexturePro(sprite_image,spritesource,spritedestination4,{0,0},0,RAYWHITE); 

                DrawText("player 1 name", player1_name_box.x, player1_name_box.y - 30, 20, GRAY);
                DrawText("player 3 name", player3_name_box.x, player3_name_box.y - 30, 20, GRAY);
                DrawText("player 2 name", player2_name_box.x, player2_name_box.y - 30, 20, GRAY);
                DrawText("player 4 name", player4_name_box.x, player4_name_box.y - 30, 20, GRAY);

                DrawRectangleRec(player1_name_box, WHITE);
                DrawRectangleRec(player2_name_box, WHITE);
                DrawRectangleRec(player3_name_box, WHITE);
                DrawRectangleRec(player4_name_box, WHITE);

                if (mouseOnTextBox1 && menu_state5)
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, RED);
                else
                    DrawRectangleLines(player1_name_box.x, player1_name_box.y, player1_name_box.width, player1_name_box.height, DARKGRAY);
                if (mouseOnTextBox2 && menu_state5)
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, RED);
                else
                    DrawRectangleLines(player2_name_box.x, player2_name_box.y, player2_name_box.width, player2_name_box.height, DARKGRAY);
                if (mouseOnTextBox3 && menu_state5)
                    DrawRectangleLines(player3_name_box.x, player3_name_box.y, player3_name_box.width, player3_name_box.height, RED);
                else
                    DrawRectangleLines(player3_name_box.x, player3_name_box.y, player3_name_box.width, player3_name_box.height, DARKGRAY);
                if (mouseOnTextBox4 && menu_state5)
                    DrawRectangleLines(player4_name_box.x, player4_name_box.y, player4_name_box.width, player4_name_box.height, RED);
                else
                    DrawRectangleLines(player4_name_box.x, player4_name_box.y, player4_name_box.width, player4_name_box.height, DARKGRAY);

                DrawText(player1_name, player1_name_box.x + 5, player1_name_box.y + 8, 40, BLUE);
                DrawText(player2_name, player2_name_box.x + 5, player2_name_box.y + 8, 40, BLUE);
                DrawText(player3_name, player3_name_box.x + 5, player3_name_box.y + 8, 40, BLUE);
                DrawText(player4_name, player4_name_box.x + 5, player4_name_box.y + 8, 40, BLUE);
            }

            DrawText("players", 822, 209, 40, BLACK);
            DrawText(TextFormat("%i", num_of_humans), 874, 260, 40, BLACK);

            DrawTextureEx(plus_button, {744, 274}, 0, 1, RAYWHITE);
            DrawTextureEx(minus_button, {944, 274}, 0, 1, RAYWHITE);

            if (CheckCollisionPointRec(mouseposition, player1_name_box) && menu_state5)
                mouseOnTextBox1 = true;
            else
                mouseOnTextBox1 = false;

            if (CheckCollisionPointRec(mouseposition, player2_name_box) && menu_state5)
                mouseOnTextBox2 = true;
            else
                mouseOnTextBox2 = false;

            if (CheckCollisionPointRec(mouseposition, player3_name_box) && menu_state5)
                mouseOnTextBox3 = true;
            else
                mouseOnTextBox3 = false;

            if (CheckCollisionPointRec(mouseposition, player4_name_box) && menu_state5)
                mouseOnTextBox4 = true;
            else
                mouseOnTextBox4 = false;



            if (menu_state5)
            {

                // if((mouseOnTextBox1 || mouseOnTextBox2 || mouseOnTextBox3 || mouseOnTextBox4 )  && menu_state5){
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0)
                {
                    if (numberofchar1 < MAX_NAME_CHAR && mouseOnTextBox1)
                    {
                        player1_name[numberofchar1] = (char)key;
                        player1_name[numberofchar1 + 1] = '\0';
                        numberofchar1++;
                    }
                    else if (numberofchar2 < MAX_NAME_CHAR && mouseOnTextBox2)
                    {
                        player2_name[numberofchar2] = (char)key;
                        player2_name[numberofchar2 + 1] = '\0';
                        numberofchar2++;
                    }
                    else if (numberofchar3 < MAX_NAME_CHAR && mouseOnTextBox3)
                    {
                        player3_name[numberofchar3] = (char)key;
                        player3_name[numberofchar3 + 1] = '\0';
                        numberofchar3++;
                    }
                    else if (numberofchar4 < MAX_NAME_CHAR && mouseOnTextBox4)
                    {
                        player4_name[numberofchar4] = (char)key;
                        player4_name[numberofchar4 + 1] = '\0';
                        numberofchar4++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_RIGHT_SHIFT) && mouseOnTextBox1)
                {
                    numberofchar1--;
                    if (numberofchar1 < 0)
                        numberofchar1 = 0;
                    player1_name[numberofchar1] = '\0';
                }
                else if (IsKeyPressed(KEY_RIGHT_SHIFT) && mouseOnTextBox2)
                {
                    numberofchar2--;
                    if (numberofchar2 < 0)
                        numberofchar2 = 0;
                    player2_name[numberofchar2] = '\0';
                }
                else if (IsKeyPressed(KEY_RIGHT_SHIFT) && mouseOnTextBox3)
                {
                    numberofchar3--;
                    if (numberofchar3 < 0)
                        numberofchar3 = 0;
                    player3_name[numberofchar3] = '\0';
                }
                else if (IsKeyPressed(KEY_RIGHT_SHIFT) && mouseOnTextBox4)
                {
                    numberofchar4--;
                    if (numberofchar4 < 0)
                        numberofchar4 = 0;
                    player4_name[numberofchar4] = '\0';
                }
            }
            else
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (IsKeyPressed(KEY_EQUAL) && menu_state5 == true)
            {
                num_of_humans++;
            }

            DrawTexturePro(submit_button, submit_button_src, submit_button_des, {0, 0}, 0, RAYWHITE);

            if (IsKeyPressed(KEY_MINUS) && menu_state5 == true)
            {
                num_of_humans--;
            }

            if (num_of_humans > 4)
                num_of_humans--;
            else if (num_of_humans < 2)
                num_of_humans++;

            if (CheckCollisionPointRec(mouseposition, submit_button_des))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    
        playerexist();
           
        if(!name1){
            initializePlayer(player1, player1_name);
        }
         if(!name2){
            initializePlayer(player2, player2_name);
        }
         if(!name3){
            initializePlayer(player3, player3_name);
        }
         if(!name4){
            initializePlayer(player4, player4_name);
        }
        savePlayerData();

                    menu_state6 = true;
                     num_of_player = num_of_humans;
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE) && menu_state5 == true)
            {
                menu_state3 = true;
                menu_state5 = false;
            }
        }

        // menu state 6 game screen
        if (menu_state6)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state7 = menu_state8 = false;

            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
             DrawTextureEx(option_bg,{10,50},-90,0.3f,RAYWHITE); //white background on player name 
            DrawTexturePro(snakeimage, source, Dest, (Vector2){Dest.width / 2, (Dest.height / 2)}, 0, WHITE);

            if (num_of_humans == 1)
            {
                player1in = true;
            }
            else if (num_of_humans == 2)
            {
                player1in = true;
                player2in = true;
            }
            else if (num_of_humans == 3)
            {
                player1in = true;
                player2in = true;
                player3in = true;
            }
            else if (num_of_humans == 4)
            {
                player1in = true;
                player2in = true;
                player3in = true;
                player4in = true;
            }

           


            DrawText("press R to roll", 100, 110, 20, GREEN);

            DrawText(TextFormat("%i", generated), 100, 120, 80, LIGHTGRAY);

            DrawText( player1_name, 100, 180, 20, LIGHTGRAY);

            DrawText(TextFormat("%i", player1.position), 100, 220, 80, LIGHTGRAY);

            DrawText( player2_name, 100, 280, 20, LIGHTGRAY);

            DrawText(TextFormat("%i", player2.position), 100, 320, 80, LIGHTGRAY);

            DrawText(player3_name, 100, 380, 20, LIGHTGRAY);

            DrawText(TextFormat("%i", player3.position), 100, 420, 80, LIGHTGRAY);

            DrawText(player4_name, 100, 480, 20, LIGHTGRAY);
            
            DrawText(TextFormat("%i", player4.position), 100, 520, 80, LIGHTGRAY);




            if (IsKeyReleased(KEY_SPACE) && player1in && player1turn && !multi)
            {
              PlaySound(dice);

            //   WaitTime(2);
                generated = roll();
                
                 
                if (player1.position + generated > 100)
                    continue;
                player1.position += generated;
                
                checksnakeorladder(player1);
                checkwin(player1);
                   if(checkwin(player1) == 3){
                    DrawText("Game OVER",screenHeight/2,screenWidth/2,80,BLUE);
                }
              
                
                player1turn = false;
                player2turn = true;
                player3turn = false;
                player4turn = false;
            }

            else if (!player2in && player2turn)
            {
           
                generated = roll();

                if (player2.position + generated > 100)
                    continue;
                player2.position += generated;
                //  WaitTime(3);
                checksnakeorladder(player2);
                checkwin(player2);
                 if(checkwin(player2) == 1){
                    DrawText("Game OVER",screenHeight/2,screenWidth/2,80,BLUE);
                }
                PlaySound(dice);
                player1turn = false;
                player2turn = false;
                player4turn = false;
                if (num_of_ai == 2 || num_of_ai == 3)
                {
                    player3turn = true;
                }
                else
                {
                    player1turn = true;
                }
            }

            else if (!player3in && player3turn)
            {
            
                generated = roll();

                if (player3.position + generated > 100)
                    continue;
                player3.position += generated;
            //    WaitTime(3);
                checksnakeorladder(player3);
                checkwin(player3);
                   if(checkwin(player3) == 1){
                    DrawText("Game OVER",screenHeight/2,screenWidth/2,80,BLUE);
                }
                PlaySound(dice);
                player1turn = false;
                player2turn = false;
                player3turn = false;
                if (num_of_ai == 3)
                {
                    player4turn = true;
                }
                else
                {
                    player1turn = true;
                }
            }

            else if (!player4in && player4turn)
            {
               
                generated = roll();

                if (player3.position + generated > 100)
                    continue;
                player4.position += generated;
                //  WaitTime(3);
                checksnakeorladder(player4);
                 checkwin(player4);
                   if(checkwin(player4) == 1){
                    DrawText("Game OVER",screenHeight/2,screenWidth/2,80,BLUE);
                }
               
                PlaySound(dice);
                player1turn = true;
                player2turn = false;
                player3turn = false;
                player4turn = false;
            }

            // humans
            if (IsKeyReleased(KEY_SPACE) && player1in && player1turn && multi)
            {
                generated = roll();
                if ((player1.position + generated) <= 100){
                     player1.position += generated;
                }
               
                
                checksnakeorladder(player1);
                checkwin(player1);
                
                   if(checkwin(player1) == 1){
                    DrawText("Game OVER",screenHeight/2,screenWidth/2,80,BLUE);
                    menu_state8 = true;
                }
                PlaySound(dice);
                player1turn = false;
                player2turn = true;
                player3turn = false;
                player4turn = false;
            }

            else if (IsKeyReleased(KEY_SPACE) && player2in && player2turn)
            {
                generated = roll();
                if ((player2.position + generated) <= 100){
                     player2.position += generated;
                }
               
                checksnakeorladder(player2);
                checkwin(player2);
                      if(checkwin(player2) == 1){
                   menu_state8 = true;
                }
                PlaySound(dice);
                player1turn = false;
                player2turn = false;
                player4turn = false;
                if (player3in)
                {
                    player3turn = true;
                }
                else
                {
                    player1turn = true;
                }
            }

            else if (IsKeyReleased(KEY_SPACE) && player3in && player3turn)
            {
                generated = roll();
                 if ((player3.position + generated) <= 100){
                     player3.position += generated;
                }
                checksnakeorladder(player3);
                checkwin(player3);
                 if(checkwin(player3) == 1){
                    menu_state8 = true;
                }
                PlaySound(dice);
                player1turn = false;
                player2turn = false;
                player3turn = false;
                if (player4in)
                {
                    player4turn = true;
                }
                else
                {
                    player1turn = true;
                }
            }

            else if (IsKeyReleased(KEY_SPACE) && player4in && player4turn)
            {
                generated = roll();
               if ((player4.position + generated) <= 100){
                    player4.position += generated;
                }
               
               checksnakeorladder(player4);
                 checkwin(player4);
                if(checkwin(player4) == 1){
                menu_state8;
                }
                PlaySound(dice);
                player1turn = true;
                player2turn = false;
                player3turn = false;
                player4turn = false;
            }

            DrawTexturePro(pause_button,pause_rec,pause_rec,{0,0},0,RAYWHITE);

if(!multi){
            switch(num_of_ai+1){
                case 2:  
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                    break;
                case 3:
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                    DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
                    break;
                ;
                case 4:
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                    DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
                    DrawTexturePro(blue_sprite, orangesource, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, ORANGE);
                    break;
            }
}

if(multi){
            switch(num_of_humans){
                case 2: 
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                   break;
                case 3: 
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                    DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
                    break;
                case 4: 
                    DrawTexturePro(blue_sprite, bluesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(blue_sprite, greensource, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, GREEN);
                    DrawTexturePro(blue_sprite, redsource, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RED);
                    DrawTexturePro(blue_sprite, orangesource, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, ORANGE);
                    break;
            }

}
         
            if (IsKeyPressed(KEY_BACKSPACE) && menu_state6 == true)
            {
                menu_state3 = true;
                menu_state6 = false;
            }
        }

        // menu state 7 pause screen
        if (menu_state7)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = false;
        }

        // menu state 8 Profiles /highscore
           if (menu_state8)
        {
            menu_state2 = menu_state1 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = false;
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
        }

        // std::cout << GetTime() << std::endl;
        savePlayerData();
        EndDrawing();
        
    }
     
    UnloadSound(backgroundsound); // Unload sound
    UnloadSound(dice);
    CloseAudioDevice(); // Close audio device

    CloseWindow();
    return 0;
}