#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


bool gameloop = true;
int num = 0;
int player;

vector <int> saveplayer;

void savePlayerData(){
     std::ifstream inputFile("test.txt");
     inputFile.open("text.txt");
    if (inputFile.is_open())
    {
         // Clear the vector before loading data
      
        inputFile >> num;
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file for reading." << std::endl;
    }
}
int main(){

while(gameloop){


num++;
cout << num;
     if (num > 100)
        {

            player++;
            saveplayer.push_back(player);
            
            savePlayerData();
            return 0;
            }
        
    // if(getchar() == 'x'){
    //     gameloop = false;
    
    //     }
}

    return 0;
}