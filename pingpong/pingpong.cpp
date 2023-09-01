#include <iostream>
#include "raylib.h"

using namespace std;

int main() {

   

    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

   

    CloseWindow();
    return 0;
}