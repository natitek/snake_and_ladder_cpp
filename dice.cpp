#include <raylib.h>
#include <iostream>

using namespace std;



// typedef struct SpriteAnimation{
//     Texture2D atlas;
//     int framePerSecond;

//     Rectangle* rectangles;
//     int rectanglesLength;
// } SpriteAnimation;

// SpriteAnimation CreateSpriteAnimation(Texture2D atlas,int framePerSecond, Rectangle rectangles[],int length){


//     SpriteAnimation SpriteAnimation = {
//         .atlas = atlas,
//         .framePerSecond = framePerSecond,
//         .rectangles = NULL,
//         .rectanglesLength = length

//     };

//     return SpriteAnimation;
// }


// void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin, float rotation, Color tint){
//     int index = (int)(GetTime()* animation.framePerSecond) % animation.rectanglesLength;

//     Rectangle source = {0};
//     DrawTextPro(animation.atlas,source,dest, origin, rotation, tint)
// }
int main(){
    int name;
    cin >> name;
    cout << GetTime() * 10 << endl;
}