// Pong.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <raylib.h>
#include <string>
using namespace std;

const int screenWidth = 1280;
const int screenHeight = 800;

int playerScore = 0;
int cpuScore = 0;

class Ball {

public:
	float ballRadius,
	      y,
	      x;
	int ballSpeedX,
	    ballSpeedY;
	Ball(int radius,float posX,float posY, int speedX,int speedY) {
		this->ballRadius = radius;
		this->y = posY;
		this->x = posX;
		this->ballSpeedX = speedX;
		this->ballSpeedY = speedY;
	}
	void drawBall() {
		DrawCircle(x,y,ballRadius,PURPLE);
	}
	void UpdateBall() {
		x += ballSpeedX;
		if ((x + 60) > screenWidth) {
			playerScore++;
			ballSpeedX *= -1;
			ballSpeedY *= -1;
		} 
		if ((x - 60) <= 0) {
			/*ballSpeedX *= -1;*/
			cpuScore++;
			ballSpeedX *= -1;
			ballSpeedY *= -1;
		}
		y += ballSpeedY;
		if (((y + 80) > screenHeight) || (y-80)<=0) {
			ballSpeedY *= -1;
		}
	}
};

class Paddle {
protected: 
	void LimitMovement() {			
		if ((y + 220)> screenHeight) {
				y = (screenHeight - 220);
			}
			if (y <= 20) {
				y = 20;
			}
	};
public:
	float 
		  height = 200,
	      width = 60,
	      x,
	      y;
	int paddleSpeedY = 6;
	Paddle(float posY, int posX) {
		this->y = posY;
		this->x = posX;
	}
	void DrawPaddle() {
		DrawRectangle(x, y, width, height, PURPLE);
	}
	//sets screen limits

	void UpdatePaddle() {
		if (IsKeyDown(KEY_DOWN) == true) {
			y += paddleSpeedY;

		}
		if (IsKeyDown(KEY_UP) == true) {
			y -= paddleSpeedY;
		}
		LimitMovement();

	}
};

class PCPaddle :public Paddle {
public:
	PCPaddle(float posY, int posX) :Paddle(posY, posX) {}
	void UpdatePaddle(int ball_y) {
		if (y < ball_y) {
			y += paddleSpeedY;
		}
		else {
			y -= paddleSpeedY;
		} 
		LimitMovement();
   }
};

int main()
{
	InitWindow(screenWidth, screenHeight, "My pong game");
	SetTargetFPS(60);
	Ball ball = Ball(30, (screenWidth/2), (screenHeight / 2), 6, 6);
	Paddle myPaddle = Paddle(((screenHeight / 2) - 100), 40);
	PCPaddle pcPaddle = PCPaddle(((screenHeight / 2) - 100), (screenWidth -80));
	while (WindowShouldClose()==false) {
		BeginDrawing();
		ball.drawBall();
		myPaddle.DrawPaddle();
		pcPaddle.DrawPaddle();
		//checking 4 collisions
           if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.ballRadius, Rectangle{ myPaddle.x, myPaddle.y,
																						  myPaddle.width, myPaddle.height }) == true) {
			ball.ballSpeedX *= -1;
			ball.ballSpeedY *= -1;

		   };
		   if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.ballRadius, Rectangle{ pcPaddle.x, pcPaddle.y,
																				  pcPaddle.width, pcPaddle.height }) == true) {
			ball.ballSpeedX *= -1;
			ball.ballSpeedY *= -1;
		    }
		ClearBackground(BLACK);
		DrawLine((screenWidth/2),0, (screenWidth / 2),screenHeight, PURPLE);
		ball.UpdateBall();
		myPaddle.UpdatePaddle();
		pcPaddle.UpdatePaddle(ball.y);
		
		DrawText(TextFormat("%d", playerScore),0,0,22,PINK);
		EndDrawing();
	}
	 
	CloseWindow();
	return 0;
}
