#include "raylib.h"
#include "iostream"
#include "vector"
#include <string>
#include <fstream>

#define MAX_VOLUME 10
#define MIN_VOLUME 0
#define MAX_NAME_CHAR 15

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

std::vector<player> listofplayers;

// randomly generate from 1-6
int roll()
{
    int num = GetRandomValue(1, 6);
    return num;
}

int generated = 0;
float boxsize = 70;
float initialpositionx = 260;
float initialpositiony = 666;
float temp;

bool menu_state1; // start menu
bool menu_state2; // settings
bool menu_state3; // select b/n single vs multi
bool menu_state4; // single options
bool menu_state5; // multiplayer optinos
bool menu_state6; // game
bool menu_state7; //  pause
bool menu_state8; // win screen
bool menu_state9; // profiles

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

bool gameover = false;

bool name1 = false;
bool name2 = false;
bool name3 = false;
bool name4 = false;

int num_of_ai = 1;
int num_of_humans = 1;

int win_count = 0;

Vector2 dice_position = {};

std::vector<Vector2> coordinates;

int snakehead[] = {32, 36, 48, 62, 88, 95, 97};
int snaketail[] = {10, 6, 26, 18, 24, 56, 78};
int laddertop[] = {14, 30, 38, 42, 67, 76, 92, 99};
int ladderbottom[] = {4, 8, 1, 21, 50, 28, 71, 80};

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
                // std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                continue;
            }
            else if (counter % 10 == 0)
            {
                coordinates.push_back({coordinates[counter - 1].x - boxsize, coordinates[counter - 1].y});
                // std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
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
                // std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                continue;
            }
            else if (counter % 10 == 0)
            {
                coordinates.push_back({coordinates[counter - 1].x + boxsize, coordinates[counter - 1].y});
                // std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                continue;
            }

            coordinates.push_back({coordinates[counter - 1].x - boxsize, coordinates[counter - 1].y});
        }
        // Print out the output of the above code
        // std::cout << "at " << counter << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
    }
}

std::vector<player> players;

std::vector<std::string> names;

void leaderboardSort()
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < players.size() - 1; j++)
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
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < players.size(); j++)
        {
            if (players[i].name == players[j].name && (i != j))
            {
                players[i].wins += players[j].wins;
                players[i].losses += players[j].losses;
                std::swap(players[j], players[players.size() - 1]);
                players.pop_back();
            }
        }
    }
    leaderboardSort();
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

void ai_name()
{
    std::string x;
    int name_index;
    int temp;
    std::ifstream inputFile("ai_names_men.txt");
    if (inputFile.is_open())
    {

        while (inputFile >> x)
        {
            names.push_back(x);
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file for reading." << std::endl;
    }

    if (num_of_ai == 1)
    {
        name_index = GetRandomValue(0, names.size() - 1);
        x = names[name_index];

        for (int i = 0; i < x.length(); i++)
        {
            player2_name[i] = x[i];
        }
    }
    if (num_of_ai == 2)
    {
        name_index = GetRandomValue(0, names.size() - 1);
        x = names[name_index];

        for (int i = 0; i < x.length(); i++)
        {
            player2_name[i] = x[i];
        }

        temp = GetRandomValue(0, names.size() - 1);

        while (temp == name_index)
        {

            temp = GetRandomValue(0, names.size() - 1);
        }
        name_index = temp;
        x = names[name_index];

        for (int i = 0; i < x.length(); i++)
        {
            player3_name[i] = x[i];
        }
    }
    if (num_of_ai == 3)
    {
        name_index = GetRandomValue(0, names.size() - 1);
        x = names[name_index];

        for (int i = 0; i < x.length(); i++)
        {
            player2_name[i] = x[i];
        }

        temp = GetRandomValue(0, names.size() - 1);

        while (temp == name_index)
        {

            temp = GetRandomValue(0, names.size() - 1);
        }

        x = names[temp];

        for (int i = 0; i < x.length(); i++)
        {
            player3_name[i] = x[i];
        }

        name_index = GetRandomValue(0, names.size() - 1);
        while (temp == name_index)
        {

            name_index = GetRandomValue(0, names.size() - 1);
        }
        x = names[name_index];
        for (int i = 0; i < x.length(); i++)
        {
            player4_name[i] = x[i];
        }
    }
}

void initializePlayer(player &newPlayer, char *name)
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

void removenames(char *name_of_player)
{
    for (int i = 0; i < sizeof(name_of_player); i++)
    {
        name_of_player[i] = '\0';
    }
    numberofchar = numberofchar1 = numberofchar2 = numberofchar3 = numberofchar4 = 0;
}
void restartgame(bool gameoverstate)
{
    if (gameoverstate == true && (menu_state8 || menu_state7))
    {
        player1.position = player2.position = player3.position = player4.position = 0;

        removenames(player1_name);
        removenames(player2_name);
        removenames(player3_name);
        removenames(player4_name);
        gameover = false;
    }
    else
    {
        player1turn = true;
        player1.position = player2.position = player3.position = player4.position = 0;
    }
}

// int num_of_player;
int checkwin(player &playr)
{
    bool loss = false;
    // static int count = 0;

    if (playr.position == 100)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (playr.name == players[i].name && (win_count == 0) && multi)
            {
                players[i].wins++;
                win_count++;
                loss = true;
                savePlayerData();
                // player1in = player2in = player3in = player1in = false;
                gameover = true;
                break;
            }
        }

        return 1;
    }

    savePlayerData();
    return 0;
}

int checkloss()
{

    if (checkwin(player1) == 1)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (player2.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player3.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player4.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
        }
    }
    if (checkwin(player2) == 1)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (player1.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player3.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player4.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
        }
    }
    if (checkwin(player3) == 1)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (player2.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player1.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player4.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
        }
    }
    if (checkwin(player4) == 1)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (player2.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player3.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
            if (player1.name == players[i].name)
            {
                players[i].losses++;

                savePlayerData();
            }
        }
    }
    savePlayerData();
    return 0;
}

std::string nameofwinner;

// display winner name on menu state 8
void displayWinner(player &playername)
{
    if (playername.position == 100)
    {

        nameofwinner = playername.name;
    }
}

//

void changesoundvol(float volume, Sound nameofsound)
{
    SetSoundVolume(nameofsound, volume);
}

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Snake And Ladders");
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
    Texture2D grass_bg = LoadTexture("src/img/grass.png");
    Texture2D initial_wood = LoadTexture("src/img/initial_wood.png");
    Texture2D restart_button = LoadTexture("src/img/restart_button.png");
    Texture2D game_white_bg = LoadTexture("src/img/game_white_bg.png");
    // Texture2D delete_button = LoadTexture("src/img/delete_user.png"); didnt use
    Texture2D exit_button = LoadTexture("src/img/exit_game.png");

    Texture2D scroll_up_button = LoadTexture("src/img/scroll_up.png");
    Texture2D scroll_down_button = LoadTexture("src/img/scroll_down.png");

    // Dice Animation Textures

    Texture2D dice_one = LoadTexture("src/animation/1_anim.png");
    Texture2D dice_two = LoadTexture("src/animation/2_anim.png");
    Texture2D dice_three = LoadTexture("src/animation/3_anim.png");
    Texture2D dice_four = LoadTexture("src/animation/4_anim.png");
    Texture2D dice_five = LoadTexture("src/animation/5_anim.png");
    Texture2D dice_six = LoadTexture("src/animation/6_anim.png");

    Image window_icon = LoadImage("src/img/dice_menu.png");

    //     // Sounds

    Sound backgroundsound = LoadSound("src/audio/royalty_free_bg_sound.mp3");
    Sound dice = LoadSound("src/audio/dice.mp3");

    SetTargetFPS(30); // Set our game to run at 60 frames-per-second

    // void SetWindowIcon(Image window_icon);

    SetWindowIcon(window_icon);
    SetExitKey(KEY_NULL);

    PlaySound(backgroundsound);

    //      //generate coordinates before game starts
    generatecoordinates();

    Rectangle player1_single_name_box = {514, 241, 300, 50};

    Rectangle player1_name_box = {400, 200, 300, 50};
    Rectangle player2_name_box = {400, 300, 300, 50};
    Rectangle player3_name_box = {400, 400, 300, 50};
    Rectangle player4_name_box = {400, 500, 300, 50};

    int volumeofbg = 2;
    int volumeofsfx = 4;

    // menu states

    menu_state1 = true;

    //     // Main game loop
    while (!WindowShouldClose()) // Detect window close button
    {

        loadPlayerData();

        // Get the coordinates of the mouse by pressing SPACE
        Vector2 mouseposition = GetMousePosition();

        if (IsKeyReleased(KEY_SPACE))
        {

            std::cout << "x:" << mouseposition.x << "   y: " << mouseposition.y << std::endl;
        }

        //         // Draw
        //         //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle source = (Rectangle){0, 0, snakeimage.width, snakeimage.height};
        Rectangle Dest = (Rectangle){screenWidth / 2, screenHeight / 2, source.width * 0.264, source.height * 0.264};

        Rectangle bluesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle bluedestination = (Rectangle){coordinates[player1.position].x, coordinates[player1.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle greensource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle greendestination = (Rectangle){coordinates[player2.position].x + 15, coordinates[player2.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle redsource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle reddestination = (Rectangle){coordinates[player3.position].x + 5, coordinates[player3.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle orangesource = (Rectangle){0, 0, blue_sprite.width, blue_sprite.height};
        Rectangle orangedestination = (Rectangle){coordinates[player4.position].x + 10, coordinates[player4.position].y, blue_sprite.width * 0.2, blue_sprite.height * 0.2};

        Rectangle profile_button_src = (Rectangle){0, 0, profile_button.width, profile_button.height};
        Rectangle profile_button_des = (Rectangle){screenWidth - 150, screenHeight - 120, profile_button_src.width * 0.2, profile_button_src.height * 0.2};

        static int sprite_index = 0;
        static int sprite_index1 = 0;
        static int sprite_index2 = (sprite_image.width / 10) * 1;
        static int sprite_index3 = (sprite_image.width / 10) * 2;
        static int sprite_index4 = (sprite_image.width / 10) * 3;

        // change sprite color
        if (mouseOnTextBox)
        {
            if ((IsKeyPressed(KEY_RIGHT)) && menu_state4)
            {

                sprite_index += (sprite_image.width / 10);
            }
            else if ((IsKeyPressed(KEY_LEFT)) && menu_state4)
            {
                sprite_index -= (sprite_image.width / 10);
            }
        }

        if (mouseOnTextBox1)
        {
            if ((IsKeyPressed(KEY_RIGHT)) && (menu_state5))
            {

                sprite_index1 += (sprite_image.width / 10);
            }
            else if ((IsKeyPressed(KEY_LEFT)) && menu_state5)
            {
                sprite_index1 -= (sprite_image.width / 10);
            }
        }

        if (mouseOnTextBox2)
        {
            if ((IsKeyPressed(KEY_RIGHT)) && (menu_state5))
            {

                sprite_index2 += (sprite_image.width / 10);
            }
            else if ((IsKeyPressed(KEY_LEFT)) && menu_state5)
            {
                sprite_index2 -= (sprite_image.width / 10);
            }
        }

        if (mouseOnTextBox3)
        {
            if ((IsKeyPressed(KEY_RIGHT)) && (menu_state5))
            {

                sprite_index3 += (sprite_image.width / 10);
            }
            else if ((IsKeyPressed(KEY_LEFT)) && menu_state5)
            {
                sprite_index3 -= (sprite_image.width / 10);
            }
        }
        if (mouseOnTextBox4)
        {
            if ((IsKeyPressed(KEY_RIGHT)) && (menu_state5))
            {

                sprite_index4 += (sprite_image.width / 10);
            }
            else if ((IsKeyPressed(KEY_LEFT)) && menu_state5)
            {
                sprite_index4 -= (sprite_image.width / 10);
            }
        }

        Rectangle spritesource = {sprite_index, 0, sprite_image.width / 10, sprite_image.height};

        Rectangle spritesource1 = {sprite_index1, 0, sprite_image.width / 10, sprite_image.height};
        Rectangle spritesource2 = {sprite_index2, 0, sprite_image.width / 10, sprite_image.height};
        Rectangle spritesource3 = {sprite_index3, 0, sprite_image.width / 10, sprite_image.height};
        Rectangle spritesource4 = {sprite_index4, 0, sprite_image.width / 10, sprite_image.height};

        Rectangle spritedestinationsingle = {player1_single_name_box.x - 100, player1_single_name_box.y, spritesource.width / 5, spritesource.height / 5};

        Rectangle spritedestination = {player1_single_name_box.x - 200, player1_name_box.y, spritesource.width / 5, spritesource.height / 5};

        Rectangle spritedestination2 = {player1_single_name_box.x - 200, player2_name_box.y, spritesource.width / 5, spritesource.height / 5};

        Rectangle spritedestination3 = {player1_single_name_box.x - 200, player3_name_box.y, spritesource.width / 5, spritesource.height / 5};

        Rectangle spritedestination4 = {player1_single_name_box.x - 200, player4_name_box.y, spritesource.width / 5, spritesource.height / 5};

        // side bar rectangles
        Rectangle sidebar_sprite = {50, 200, spritesource.width / 8, spritesource.height / 8};
        Rectangle sidebar_sprite2 = {50, 250, spritesource.width / 8, spritesource.height / 8};
        Rectangle sidebar_sprite3 = {50, 300, spritesource.width / 8, spritesource.height / 8};
        Rectangle sidebar_sprite4 = {50, 350, spritesource.width / 8, spritesource.height / 8};

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
        Rectangle submit_button_des = {580, 497, submit_button.width * 0.3, submit_button.height * 0.3};

        if (menu_state5)
        {
            submit_button_des = (Rectangle){800, 340, submit_button.width * 0.3, submit_button.height * 0.3}; // change position of submit button in single and multiplayer options
        }

        Rectangle pause_button_src = {0, 0, (float)pause_button.width, (float)pause_button.height};

        Rectangle pause_button_des = {30, 30, pause_button_src.width / 5, pause_button_src.height / 5};

        // menu state 1  main menu
        if (menu_state1)
        {
            menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = menu_state8 = menu_state9 = false;
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

            // if escape is pressed on start menu quit game
            if (IsKeyPressed(KEY_ESCAPE) && menu_state1)
            {
                break;
            }

            // profile button click
            if (CheckCollisionPointRec(mouseposition, profile_button_des))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    menu_state9 = true;
            }
        }

        // menu state 2 settings menu
        if (menu_state2)
        {
            menu_state1 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = menu_state8 = menu_state9 = false;
            DrawTextureEx(bg_squares, {0, 0}, 0, 1, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);

            // volume controllers

            DrawText("Settings", screenWidth / 2 - 130, 100, 70, GRAY);
            DrawText("Music", 250, 170, 40, RED);

            // red volume bar
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofbg)
                    DrawRectangle(250 + 70 * i, 205, 70, 30, RED);
                DrawRectangleLines(250 + 70 * i, 205, 70, 30, MAROON);
            }
            DrawText("SFX", 250, 285, 40, RED);

            // draw green baR
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofsfx)
                    DrawRectangle(250 + 70 * i, 321, 70, 30, GREEN);
                DrawRectangleLines(250 + 70 * i, 321, 70, 30, MAROON);
            }

            if ((IsKeyPressed(KEY_NINE)) && menu_state2 == true)
            {
                volumeofsfx--;
                changesoundvol((float)volumeofsfx / 10.0f, backgroundsound);
            }
            else if ((IsKeyPressed(KEY_ZERO)) && menu_state2 == true)
            {
                volumeofsfx++;
                changesoundvol((float)volumeofsfx / 10.0f, dice);
            }
            if ((IsKeyPressed(KEY_EQUAL)) && menu_state2 == true)
            {
                volumeofbg++;
                changesoundvol((float)volumeofbg / 10.0f, dice);
            }
            else if ((IsKeyPressed(KEY_MINUS)) && menu_state2 == true)
            {
                volumeofbg--;
                changesoundvol((float)volumeofbg / 10.0f, backgroundsound);
            }

            // PlaySound(backgroundsound);

            // press backspace to return to the main menu
            if (IsKeyPressed(KEY_ESCAPE) && menu_state2 == true)
            {
                menu_state1 = true;
            }
        }

        // menu state 3 choose b/n single player or multiplayer
        if (menu_state3)
        {
            menu_state1 = menu_state2 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = menu_state8 = menu_state9 = false;
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
                    player2in = false;
                    player3in = false;
                    player4in = false;
                }
            }
            // multiplayer button
            if (CheckCollisionPointRec(mouseposition, multi_player_des) && menu_state1 != true && menu_state2 != true && menu_state4 != true)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    menu_state5 = true;
                    multi = true;
                    num_of_ai = 1;
                    num_of_humans = 2;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE) && menu_state3 == true)
            {
                menu_state1 = true;
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

            DrawTexturePro(sprite_image, spritesource, spritedestinationsingle, {0, 0}, 0, RAYWHITE); // Sprite pieces color selection

            DrawTextureEx(next_color_right, {player1_single_name_box.x - 50, player1_single_name_box.y}, 0, 1.0f, RAYWHITE); // next color button right
            DrawTextureEx(next_color_left, {player1_single_name_box.x - 150, player1_single_name_box.y}, 0, 1.0f, RAYWHITE); // next color button left

            if (CheckCollisionPointRec(mouseposition, player1_single_name_box) && menu_state4 == true)
                mouseOnTextBox = true;
            else
                mouseOnTextBox = false;
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
                if (IsKeyPressed(KEY_BACKSPACE))
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
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && player1_name[0] != '\0')
                {
                    ai_name();
                    menu_state6 = true;
                }
                else if (player1_name[0] == '\0')
                {
                    DrawText("enter name to continue", 460, 580, 40, RED);
                }
            }

            if (IsKeyPressed(KEY_ESCAPE) && menu_state4 == true)
            {
                menu_state3 = true;
                menu_state4 = false;
                multi = false;
            }
        }

        // menu state 5 multiplayer option
        if (menu_state5)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state6 = menu_state7 = menu_state8 = false;
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

                DrawTexturePro(sprite_image, spritesource1, spritedestination, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource2, spritedestination2, {0, 0}, 0, RAYWHITE);

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

                DrawTexturePro(sprite_image, spritesource1, spritedestination, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource2, spritedestination2, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource3, spritedestination3, {0, 0}, 0, RAYWHITE);

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

                DrawTexturePro(sprite_image, spritesource1, spritedestination, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource2, spritedestination2, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource3, spritedestination3, {0, 0}, 0, RAYWHITE);
                DrawTexturePro(sprite_image, spritesource4, spritedestination4, {0, 0}, 0, RAYWHITE);

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
            DrawText(TextFormat("%i", num_of_humans), 864, 280, 40, BLACK);

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
                if (IsKeyPressed(KEY_BACKSPACE) && mouseOnTextBox1)
                {
                    numberofchar1--;
                    if (numberofchar1 < 0)
                        numberofchar1 = 0;
                    player1_name[numberofchar1] = '\0';
                }
                else if (IsKeyPressed(KEY_BACKSPACE) && mouseOnTextBox2)
                {
                    numberofchar2--;
                    if (numberofchar2 < 0)
                        numberofchar2 = 0;
                    player2_name[numberofchar2] = '\0';
                }
                else if (IsKeyPressed(KEY_BACKSPACE) && mouseOnTextBox3)
                {
                    numberofchar3--;
                    if (numberofchar3 < 0)
                        numberofchar3 = 0;
                    player3_name[numberofchar3] = '\0';
                }
                else if (IsKeyPressed(KEY_BACKSPACE) && mouseOnTextBox4)
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

            bool ismultitextboxempty = ((num_of_humans == 2) && ((player1_name[0] != '\0') && (player2_name[0] != '\0'))) || ((num_of_humans == 3) && ((player1_name[0] != '\0') && (player2_name[0] != '\0') && (player3_name[0] != '\0'))) || ((num_of_humans == 4) && ((player1_name[0] != '\0') && (player2_name[0] != '\0') && (player3_name[0] != '\0') && (player4_name[0] != '\0')));

            if (CheckCollisionPointRec(mouseposition, submit_button_des))
            {
                // check if text boxes are empty

                // when submit is clicked do these
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ismultitextboxempty == true)
                {

                    initializePlayer(player1, player1_name);

                    initializePlayer(player2, player2_name);

                    initializePlayer(player3, player3_name);

                    initializePlayer(player4, player4_name);
                    savePlayerData();
                    menu_state6 = true;
                }
                else if (ismultitextboxempty == false)
                {
                    DrawText("enter name to continue", 460, 580, 40, RED);
                }

                // num_of_player = num_of_humans;
            }

            if (IsKeyPressed(KEY_ESCAPE) && menu_state5 == true)
            {
                menu_state3 = true;
                menu_state5 = false;
            }
        }

        // menu state 6 game screen
        if (menu_state6)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state7 = menu_state8 = false;

            DrawTextureEx(grass_bg, {0, 0}, 0, 1, RAYWHITE);
            DrawTextureEx(game_white_bg, {10, 100}, 0, 1.0f, RAYWHITE); // white background on player name
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

            DrawText("press SPACE to roll", 30, 110, 18, BLACK);

            DrawText(TextFormat("%i", generated), 100, 120, 80, LIGHTGRAY);

            // Color turncolor = {0, 228, 48, 255}; //start with black

            // ai player turn

            if (IsKeyReleased(KEY_SPACE) && player1in && player1turn && !multi)
            {
                PlaySound(dice);

                //   WaitTime(1);
                generated = roll();

                if (player1.position + generated > 100)
                    continue;
                player1.position += generated;

                checksnakeorladder(player1);
                checkwin(player1);
                if (checkwin(player1) == 3)
                {
                    DrawText("Game OVER", screenHeight / 2, screenWidth / 2, 80, BLUE);
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
                if (checkwin(player2) == 1)
                {
                    DrawText("Game OVER", screenHeight / 2, screenWidth / 2, 80, BLUE);
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
                if (checkwin(player3) == 1)
                {
                    DrawText("Game OVER", screenHeight / 2, screenWidth / 2, 80, BLUE);
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
                if (checkwin(player4) == 1)
                {
                    DrawText("Game OVER", screenHeight / 2, screenWidth / 2, 80, BLUE);
                }

                PlaySound(dice);
                player1turn = true;
                player2turn = false;
                player3turn = false;
                player4turn = false;
            }

            // humans turn
            if (IsKeyReleased(KEY_SPACE) && player1in && player1turn && multi)
            {
                PlaySound(dice);
                WaitTime(1);
                generated = roll();

                if ((player1.position + generated) <= 100)
                {
                    player1.position += generated;
                }

                checksnakeorladder(player1);
                checkwin(player1);
                checkloss();

                if (checkwin(player1) == 1)
                {

                    menu_state8 = true;
                }

                player1turn = false;
                player2turn = true;
                player3turn = false;
                player4turn = false;
            }

            else if (IsKeyReleased(KEY_SPACE) && player2in && player2turn)
            {
                PlaySound(dice);
                WaitTime(1);
                generated = roll();
                if ((player2.position + generated) <= 100)
                {
                    player2.position += generated;
                }

                checksnakeorladder(player2);
                checkwin(player2);
                checkloss();

                if (checkwin(player2) == 1)
                {
                    menu_state8 = true;
                }

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
                PlaySound(dice);
                WaitTime(1);
                generated = roll();
                if ((player3.position + generated) <= 100)
                {
                    player3.position += generated;
                }
                checksnakeorladder(player3);
                checkwin(player3);
                checkloss();

                if (checkwin(player3) == 1)
                {
                    menu_state8 = true;
                }

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
                PlaySound(dice);
                WaitTime(1);
                generated = roll();
                if ((player4.position + generated) <= 100)
                {
                    player4.position += generated;
                }

                checksnakeorladder(player4);
                checkwin(player4);
                checkloss();

                if (checkwin(player4) == 1)
                {

                    menu_state8 = true;
                }

                player1turn = true;
                player2turn = false;
                player3turn = false;
                player4turn = false;
            }

            // color of text
            //

            if (player1turn)
            {
                DrawText(player1_name, 100, 200, 30, GREEN);
            }
            else
            {
                DrawText(player1_name, 100, 200, 30, BLACK);
            }
            if (player2turn)
            {
                DrawText(player2_name, 100, 250, 30, GREEN);
            }
            else
            {
                DrawText(player2_name, 100, 250, 30, BLACK);
            }
            if (player3turn)
            {
                DrawText(player3_name, 100, 300, 30, GREEN);
            }
            else
            {
                DrawText(player3_name, 100, 300, 30, BLACK);
            }

            if (player4turn)
            {
                DrawText(player4_name, 100, 350, 30, GREEN);
            }
            else
            {
                DrawText(player4_name, 100, 350, 30, BLACK);
            }

            DrawTextureEx(initial_wood, {80, 653}, 0, 0.8, RAYWHITE);

            if (!multi)
            {

                switch (num_of_ai + 1)
                {
                case 2:

                    DrawTexturePro(sprite_image, spritesource, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);

                    DrawTexturePro(sprite_image, spritesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);

                    break;

                case 3:
                    DrawTexturePro(sprite_image, spritesource, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, sidebar_sprite3, {0, 0}, 0, RAYWHITE);

                    DrawTexturePro(sprite_image, spritesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RAYWHITE);
                    break;
                    ;
                case 4:
                    DrawTexturePro(sprite_image, spritesource, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, sidebar_sprite3, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource4, sidebar_sprite4, {0, 0}, 0, RAYWHITE);

                    DrawTexturePro(sprite_image, spritesource, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource4, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, RAYWHITE);
                    break;
                }
            }

            if (multi)
            {
                switch (num_of_humans)
                {
                case 2:
                    // sidebar sprites

                    DrawTexturePro(sprite_image, spritesource1, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);

                    //
                    DrawTexturePro(sprite_image, spritesource1, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);
                    break;
                case 3:
                    // sidebar
                    DrawTexturePro(sprite_image, spritesource1, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, sidebar_sprite3, {0, 0}, 0, RAYWHITE);

                    DrawTexturePro(sprite_image, spritesource1, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RAYWHITE);
                    break;
                case 4:
                    DrawTexturePro(sprite_image, spritesource1, sidebar_sprite, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, sidebar_sprite2, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, sidebar_sprite3, {0, 0}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource4, sidebar_sprite4, {0, 0}, 0, RAYWHITE);

                    DrawTexturePro(sprite_image, spritesource1, bluedestination, (Vector2){bluedestination.height / 2, bluedestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource2, greendestination, (Vector2){greendestination.height / 2, greendestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource3, reddestination, (Vector2){reddestination.height / 2, reddestination.width / 2}, 0, RAYWHITE);
                    DrawTexturePro(sprite_image, spritesource4, orangedestination, (Vector2){orangedestination.height / 2, orangedestination.width / 2}, 0, RAYWHITE);
                    break;
                }
            }

            DrawTexturePro(pause_button, pause_button_src, pause_button_des, {0, 0}, 0, RAYWHITE);

            if (CheckCollisionPointRec(mouseposition, pause_button_des))
            {

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    menu_state7 = true;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE) && menu_state6 == true)
            {

                menu_state7 = true;
            }
        }

        // menu state 7 pause screen
        if (menu_state7)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state8 = menu_state9 = false;
            DrawTextureEx(grass_bg, {0, 0}, 0, 1.0f, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
            DrawText("pause", 539, 137, 70, BLACK);
            DrawTextureEx(restart_button, {555, 235}, 0, 0.45f, RAYWHITE);
            DrawTextureEx(play_button, {235, 235}, 0, 0.2f, RAYWHITE);
            DrawTextureEx(exit_button, {865, 232}, 0, 0.3f, RAYWHITE);
            DrawText("Press R to restart", 555, 375, 20, BLACK);
            DrawText("Press P to resume", 235, 375, 20, BLACK);
            DrawText("Press E to exit", 865, 375, 20, BLACK);

            // volume control
            DrawText("Music", 250, 425, 20, RED);
            DrawText("-", 224, 472, 20, RED);
            DrawText("+", 964, 472, 20, RED);
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofbg)
                    DrawRectangle(250 + 70 * i, 460, 70, 30, RED);
                DrawRectangleLines(250 + 70 * i, 460, 70, 30, MAROON);
            }
            DrawText("SFX", 250, 285 + 220, 20, RED);
            DrawText("9", 224, 550, 20, RED);
            DrawText("0", 964, 550, 20, RED);
            for (int i = 0; i < MAX_VOLUME; i++)
            {
                if (i < volumeofsfx)
                    DrawRectangle(250 + 70 * i, 321 + 220, 70, 30, GREEN);
                DrawRectangleLines(250 + 70 * i, 321 + 220, 70, 30, MAROON);
            }

            if ((IsKeyPressed(KEY_NINE)) && menu_state7 == true)
            {
                volumeofsfx--;
                changesoundvol((float)volumeofsfx / 10.0f, backgroundsound);
            }
            else if ((IsKeyPressed(KEY_ZERO)) && menu_state7 == true)
            {
                volumeofsfx++;
                changesoundvol((float)volumeofsfx / 10.0f, dice);
            }
            if ((IsKeyPressed(KEY_EQUAL)) && menu_state7 == true)
            {
                volumeofbg++;
                changesoundvol((float)volumeofbg / 10.0f, dice);
            }
            else if ((IsKeyPressed(KEY_MINUS)) && menu_state7 == true)
            {
                volumeofbg--;
                changesoundvol((float)volumeofbg / 10.0f, backgroundsound);
            }

            if ((IsKeyPressed(KEY_P)) && menu_state7 == true)
            {
                menu_state6 = true;
            }
            else if (IsKeyPressed(KEY_E))
            {
                menu_state3 = true;
                gameover = true;
                restartgame(gameover);
            }
            else if (IsKeyPressed(KEY_R))
            {
                restartgame(false);
                menu_state6 = true;
            }
        }

        // menu state 8 win screen
        if (menu_state8)
        {
            menu_state2 = menu_state1 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = false;
            DrawTextureEx(bg_squares, {0, 0}, 0, 1.0f, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
            DrawText("Game Over", 480, 133, 70, RED);
            listofplayers = {player1, player2, player3, player4};

            for (player n : listofplayers)
            {
                displayWinner(n);
            }

            DrawText(nameofwinner.c_str(), 500, screenHeight / 2, 70, GREEN);
            DrawText("is the winner", 500, (screenHeight / 2) + 100, 40, BLACK);

            if (IsKeyPressed(KEY_ESCAPE) && menu_state8 == true)
            {
                menu_state3 = true;
                restartgame(true);
            }
        }
        // menu state 9 profile screen
        if (menu_state9)
        {
            menu_state1 = menu_state2 = menu_state3 = menu_state4 = menu_state5 = menu_state6 = menu_state7 = menu_state8 = false;

            DrawTextureEx(bg_squares, {0, 0}, 0, 1.0f, RAYWHITE);
            DrawTextureEx(option_bg, {100, 100}, 0, 1.0f, RAYWHITE);
            static int mx = 150, my = 250;
            static int wrapped = 0;

            static int deletethis = 0;

            for (int i = 0; i < 6; i++)
            {
                DrawRectangleLines(150, 250 + (50) * i, 950, 50, WHITE);
            }

            if (IsKeyPressed(KEY_W))
            {
                my -= 50;
                deletethis -= 1;
            }

            else if (IsKeyPressed(KEY_S))
            {
                my += 50;
                deletethis += 1;
            }
            if (my > 500)
            {
                my = 500;
                // deletethis = 6;
            }
            if (my < 250)
            {
                my = 250;
                deletethis = 0;
            }

            loadPlayerData();
            Rectangle hoverovertextbox = {mx, my, 950, 50};
            DrawRectanglePro(hoverovertextbox, {0, 0}, 0, BLUE);
            DrawText("Profiles", 480, 133, 70, BLACK);
            DrawText("name", 150, 220, 20, BLACK);
            DrawText("wins", 720, 220, 20, BLACK);
            DrawText("losses", 1000, 220, 20, BLACK);

            if (players.size() >= 5 && my == 500 && IsKeyPressed(KEY_S))
            {

                wrapped += 1;

                std::cout << deletethis << std::endl;
            }
            else if (my == 250 && IsKeyPressed(KEY_W))
            {

                wrapped -= 1;
                // deletethis -= 1;
            }

            // limiter of bounds
            if (wrapped < 0)
            {
                wrapped = 0;
            }
            else if ((6 + wrapped) > players.size() - 1)
            {
                wrapped = 0;
            }
            // limiter of delete this

            if (players.size() >= 0)
            {

                DrawText(players[0 + wrapped].name.c_str(), 150, 250, 40, BLACK);            // first player name
                DrawText(TextFormat("%i", players[0 + wrapped].wins), 720, 260, 40, GREEN);  // firs player wins
                DrawText(TextFormat("%i", players[0 + wrapped].losses), 1000, 260, 40, RED); // first player losses
            }
            if (players.size() > 1)
            {
                DrawText(players[1 + wrapped].name.c_str(), 150, 250 + (50 * 1), 40, BLACK);
                DrawText(TextFormat("%i", players[1 + wrapped].wins), 720, 260 + (50 * 1), 40, GREEN);
                DrawText(TextFormat("%i", players[1 + wrapped].losses), 1000, 260 + (50 * 1), 40, RED);
            }
            if (players.size() > 2)
            {
                DrawText(players[2 + wrapped].name.c_str(), 150, 250 + (50 * 2), 40, BLACK);
                DrawText(TextFormat("%i", players[2 + wrapped].wins), 720, 260 + (50 * 2), 40, GREEN);
                DrawText(TextFormat("%i", players[2 + wrapped].losses), 1000, 260 + (50 * 2), 40, RED);
            }
            if (players.size() > 3)
            {
                DrawText(players[3 + wrapped].name.c_str(), 150, 250 + (50 * 3), 40, BLACK);
                DrawText(TextFormat("%i", players[3 + wrapped].wins), 720, 260 + (50 * 3), 40, GREEN);
                DrawText(TextFormat("%i", players[3 + wrapped].losses), 1000, 260 + (50 * 3), 40, RED);
            }
            if (players.size() > 4)
            {
                DrawText(players[4 + wrapped].name.c_str(), 150, 250 + (50 * 4), 40, BLACK);
                DrawText(TextFormat("%i", players[4 + wrapped].wins), 720, 260 + (50 * 4), 40, GREEN);
                DrawText(TextFormat("%i", players[4 + wrapped].losses), 1000, 260 + (50 * 4), 40, RED);
            }
            if (players.size() > 5)
            {
                DrawText(players[5 + wrapped].name.c_str(), 150, 250 + (50 * 5), 40, BLACK);
                DrawText(TextFormat("%i", players[5 + wrapped].wins), 720, 260 + (50 * 5), 40, GREEN);
                DrawText(TextFormat("%i", players[5 + wrapped].losses), 1000, 260 + (50 * 5), 40, RED);
            }
            DrawText("to delete highlighted user, press del ", 200, 550, 30, RED);

            if (IsKeyPressed(KEY_DELETE) && menu_state9)
            {
                players.erase(players.begin() + deletethis);
            }
            // limit bounds
            // if (deletethis < 0)
            // {
            //     deletethis = 0;
            // }
            // else if ((6 + deletethis) > players.size() - 1)
            // {
            //     deletethis = 0
            // }

            if (IsKeyPressed(KEY_ESCAPE) && menu_state9 == true)
            {
                menu_state1 = true;
            }
        }

        savePlayerData();
        EndDrawing();
    }

    UnloadSound(backgroundsound); // Unload sound
    UnloadSound(dice);
    CloseAudioDevice(); // Close audio device

    CloseWindow();
    return 0;
}