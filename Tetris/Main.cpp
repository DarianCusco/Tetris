#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Colors.h"

using namespace std;

double lastUpdateTime = 0;
bool eventTrigger(double interval)  //Function that triggers events on a certain time interval
{                                   //Used to move blocks down
	double currentTime = GetTime();

	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() 
{
	Grid grid = Grid();
	grid.PrintGrid();
	Color Gray = { 200, 200, 200, 255 };
	InitWindow(500, 620, "Tetris");  //Window Constructor
	SetTargetFPS(60);

	Font font = LoadFontEx("fonts/Minecraft.TTF", 64, 0, 0); //Fonts used in game

	Game game = Game();
	

	while (WindowShouldClose() == false) //Main game loop
	{
		game.handleInput();
		if (eventTrigger(0.3))  //Block moves down every 3 milliseconds
		{
			game.moveBlock("down");
		}
		
		BeginDrawing();
		ClearBackground(blue);  //Prepares background for displaying game

		/* In Game Text and Features*/
		DrawTextEx(font, "Score", { 350, 15 }, 38, 2, WHITE);  
		DrawTextEx(font, "Next", { 355, 175 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.2f, 6, darkBlue);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.getGameScore());
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);

		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3f, 6, darkBlue);

		/* In Game Text and Features End*/



		game.Draw();  //draws blocks
		if (game.getGameStatus())  //If game is over, end game
		{
			DrawTextEx(font, "Game Over", { 125, 310 }, 38, 2, WHITE);  //If game is over present text
		}		
		EndDrawing();
	}

	CloseWindow();
}