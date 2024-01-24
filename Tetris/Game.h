#pragma once
#include "Grid.h"
#include "Shapes.cpp"
#include <random>


class Game
{
public:
	Game();
	Grid grid;
	void Draw();
	void handleInput();
	void moveBlock(string direction);
	bool getGameStatus();
	int getGameScore();
	
private:
	bool isBlockOutside();  //Checks if block is outside screen
	void rotateBlock();  //rotates blocks
	void lockBlock();
	void Reset();
	bool blockFits();  //Checks if blocks fit
	void updateScore(int linesCleared, int moveDownPoints);  //Updates score

	vector<Block> blocks;
	Block getRandomBlock();  //returns a random block

	int previousNum;
	bool gameOver;
	int score;

	Block currentBlock;
	Block nextBlock;

};

