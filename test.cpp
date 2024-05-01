#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

struct player
{   string name;
    int position;
};

int roll(){
    int num = rand()%6 + 1;
    return num;
}
vector<int> snakehead = {23,34,56,89,92};
vector<int> snaketail = {5,20,19,22,72};
vector<int> laddertop= {21,45,59,67,88};
vector<int> ladderbottom = {7,24,9,51,78};

struct player player1;
struct player player2;
struct player player3;
struct player player4;

int main(){
while(1){
cout << "enter name player 1";
cin >> player1.name;
cout << "enter name player 2";
cin >> player2.name;
player1.position = 0;
player2.position = 0;
bool playing = true;

while(playing == true){

     // Check if player landed on snake or ladder
    for(int n: snakehead){
        if(player1.position == n){
           
            auto index = find( snakehead.begin(), snakehead.end(), n) - snakehead.begin();
            player1.position = snaketail[index];
            cout << "you landed on a snake";
            cout << "position: " << player1.position << endl;
        }
        if(player2.position == n){
      
            auto index2 = find( snakehead.begin(), snakehead.end(), n) - snakehead.begin();
            player2.position = snaketail[index2];
             cout << "you landed on a snake";
            cout << "position: " << player2.position << endl;
        }
    }
     for(int n: ladderbottom){
             if(player1.position == n){
   
            auto index = find( ladderbottom.begin(), ladderbottom.end(), n) - ladderbottom.begin();
            player1.position = laddertop[index];
             cout << "you landed on a ladder";
            cout << "position: " << player1.position << endl;
        }
    }
    for(int n: ladderbottom){
             if(player2.position == n){
   
            auto index = find( ladderbottom.begin(), ladderbottom.end(), n) - ladderbottom.begin();
            player2.position = laddertop[index];
             cout << "you landed on a ladder" << endl;
            cout << "position: " << player2.position << endl;
        }
    }

    cout << player1.name << " your turn, press a to play" << endl;
    char input;
    cin >> input;

    //press to continue
    if(input == 'a'){
        player1.position += roll();
        cout << player1.name << "position: " << player1.position <<endl;
        cout << player2.name << "your turn, press b to play" << endl;
        cin >> input;
    }

    if(input == 'b'){
        player2.position += roll();
        cout << player2.name << "position: " << player2.position <<endl;
    }

    //check win condition
  if(player1.position >= 100){
        cout << player1.name<< "won";
        return 0;
    }
else if(player2.position >= 100){
        cout << player2.name << "won";
        return 0;
    }
}
}


return 0;
}