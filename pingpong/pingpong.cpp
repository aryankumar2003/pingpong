#include <iostream>
#include "raylib.h"
using namespace std;
int paddle1_score = 0;
int paddle2_score = 0;
class ball {
public:
    float x;
    float y;
    int radius;
    int speed_x;
    int speed_y;
    Color color;
    void draw() {
        DrawCircle(x, y, radius, color);
    }
    void update() {
        x += speed_x;
        y += speed_y;
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) { 
            speed_x *= -1;
            paddle2_score++;
        }
        if (x - radius <= 0) {
            speed_x *= -1;
            paddle1_score++;
        }
    }
};
class paddle {
public:
    float x, y;
    int speed;
    float width, height;

    void draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        if (y <= 10) {
            y = 10;
        }
        if (y +height+10>= GetScreenHeight()) {
            y = GetScreenHeight() - height-10;
        }
    }
};
class cpu :public paddle {
public:
    void update(int ball_x, int ball_y) {
        if (ball_x <= float(GetScreenWidth()/2)) {
            if (y + height / 2 > ball_y) {
                y = y - speed;
            }
            if (y + height / 2 < ball_y) {
                y = y + speed;
            }
            if (y <= 10) {
                y = 10;
            }
            if (y + height + 10 >= GetScreenHeight()) {
                y = GetScreenHeight() - height - 10;
            }
        }
    }
};

ball Ball;
paddle paddle1;
cpu paddle2;

int main() {


    cout << "Hello World" << endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    //ball
    Ball.x = screenWidth / 2;
    Ball.y = screenHeight / 2;
    Ball.radius = 12;
    Ball.color = GREEN;
    Ball.speed_x = 10;
    Ball.speed_y = 10;
    //paddle1
    paddle1.width = 15;
    paddle1.height = 100;
    paddle1.x = screenWidth - paddle1.width - 15;
    paddle1.y = screenHeight / 2 - paddle1.height / 2;
    paddle1.speed = 15;
    //cpu
    paddle2.width = 15;
    paddle2.height = 100;
    paddle2.x = 15;
    paddle2.y = screenHeight / 2 - paddle2.height / 2;
    paddle2.speed = 10;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        //update
        paddle1.update();
        Ball.update();
        paddle2.update(Ball.x,Ball.y);
        //checking
        if (CheckCollisionCircleRec(Vector2{ Ball.x,Ball.y }, Ball.radius, Rectangle{ paddle1.x,paddle1.y,paddle1.width,paddle1.height })) {
            Ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ Ball.x,Ball.y }, Ball.radius, Rectangle{ paddle2.x,paddle2.y,paddle2.width,paddle2.height })) {
            Ball.speed_x *= -1;
        }
        ClearBackground(BLACK);
        //drawing
        DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight,BLUE);
        DrawRectangle(0,0,screenWidth/2, screenHeight, RED);
        paddle1.draw();
        paddle2.draw();
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        Ball.draw();
        DrawText(TextFormat("%i", paddle2_score), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", paddle1_score), screenWidth/4  + screenWidth/2 + 20, 20, 80, WHITE);
        EndDrawing();
    }
   

    CloseWindow();
    return 0;
}