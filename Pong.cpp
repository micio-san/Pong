// Pong.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <raylib.h>
using namespace std;

const int width = 1280;
const int height = 800;

class Ball {
public:
    float X, Y;
    int Speed_x, Speed_y;
    int Radius;

    void drawBall() {
        //coordinates x y string
        DrawCircle(X, Y, Radius, PINK);
    }

    void changeCoordinates() {
        X += Speed_x;
        Y += Speed_y;
        if ((Y + Radius) >= height || (Y + Radius) <= 0) {
            Speed_y *= -1;
        }
        if ((X + Radius) >= width || (X + Radius) <= 0) {
            Speed_x *= -1;
        }
    }

};

Ball ball;

int main()
{
    //initializes a window with 3 arguments, wh of window
    InitWindow(width, height, "Pong");
    //game loop
    /*Decide how fast the game should run by picking fps, if not decided the pc will try to run it as
    fast as possible */
    SetTargetFPS(60);
    int paddleY = (height / 2) - 80;
    ball.X = width / 2;
    ball.Y = height / 2;
    ball.Radius = 40;
    ball.Speed_x = 7;
    ball.Speed_y = 7;

    //Window should close checks if the escape key or the close icon is pressed, return true if that happens
    while (WindowShouldClose() == false) {
        //Initialize a blank canvas
        BeginDrawing();
        ball.changeCoordinates();
        //resetting the background before drawing again
        ClearBackground(BLACK);
        //separate the two sides, start x start y end x end y color
        DrawLine((width/2),0,( width / 2), 800, WHITE);
        ball.drawBall();
        //coordinates x y width height color
        DrawRectangle(20, paddleY, 60, 180, PINK);
        DrawRectangle(1200, (height/2)-80, 60, 180, PINK);
        EndDrawing();
    }

    //every instance of window has to be destroyed
    CloseWindow();
    return 0;
}
