#include "Game.h"


Game::Game()
{
	grid = Grid();
	blocks = { Lblock(), Jblock(), Iblock(), Oblock(), Sblock(), Tblock(), Zblock() };

	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	this->gameOver = false;
	this->score = 0;
}

void Game::Draw()
{
	grid.drawGrid();
	currentBlock.Draw(11, 11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 280);
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}
}

void Game::handleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}
	switch (keyPressed)
	{
	case KEY_LEFT:
		moveBlock("left");
		break;

	case KEY_RIGHT:
		moveBlock("right");
		break;

	case KEY_DOWN:
		moveBlock("down");
		updateScore(0, 1);  //Score increased by 1 each time
		break;				// a block moves down
	
	case KEY_UP:
		rotateBlock();
		break;
	}
	

}

void Game::moveBlock(string direction)
{
	for (auto& x : direction)
	{
		x = tolower(x);
	}
	if (!gameOver)
	{
		if (direction == "left")
		{
			currentBlock.Move(0, -1);

			if (isBlockOutside() || blockFits() == false)
			{
				currentBlock.Move(0, 1);
			}
		}

		if (direction == "right")
		{
			currentBlock.Move(0, 1);

			if (isBlockOutside() || blockFits() == false)
			{
				currentBlock.Move(0, -1);
			}
		}

		if (direction == "down")
		{
			currentBlock.Move(1, 0);

			if (isBlockOutside() || blockFits() == false)
			{
				currentBlock.Move(-1, 0);
				lockBlock();
			}
		}
	}
}

bool Game::getGameStatus()
{
	return this->gameOver;
}

int Game::getGameScore()
{
	return this->score;
}

bool Game::isBlockOutside()
{
	vector<Position> tiles = currentBlock.getCellPosition();

	for (Position item : tiles)
	{
		if (grid.isCellOutside(item.row, item.col))
		{
			return true;
		}
	}
	return false;
}

void Game::rotateBlock()
{
	currentBlock.Rotate();

	if (isBlockOutside() || blockFits() == false)
	{
		currentBlock.undoRotate();
	}
}

void Game::lockBlock()
{
	vector<Position> tiles = currentBlock.getCellPosition();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (blockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = getRandomBlock();
	int rowCleared = grid.clearFullRows();
	updateScore(rowCleared, 0);  //Updates score depending on rows cleared
}

void Game::Reset()
{
	grid.Initialize();
	blocks = { Lblock(), Jblock(), Iblock(), Oblock(), Sblock(), Tblock(), Zblock() };
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	this->score = 0;

}

bool Game::blockFits()
{
	vector<Position> tiles = currentBlock.getCellPosition();
	for (Position item : tiles)
	{
		if (grid.isCellEmpty(item.row, item.col) == false)
		{
			return false;
		}
	}
	return true;

}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 200;
	case 3:
		score += 400;
	case 4:
		score += 800;
	}
	score += moveDownPoints;
}

Block Game::getRandomBlock()
{

	/*
	Implemented Classic Tetris Algorithm:

	The algorithm rolls a random number 1 through 7. 
	If the number is the same as the previous, roll again a final time
	*/

	random_device rand;
	mt19937 gen(rand());

	uniform_int_distribution<> range(0, 6); 

	int randomNum = range(gen);  //Rolls a random number between 1 and 8

	
	if (previousNum == randomNum)
	{
		randomNum = range(gen);
	}

	previousNum = randomNum;
	Block block = blocks[randomNum];

	return block;
}
