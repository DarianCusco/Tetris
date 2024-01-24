#include "Block.h"


Block::Block()
{
	this->cellSize = 30;
	this->rotationState = 0;
	this->colors = getCellColor();

	this->rowOffset = 0;
	this->colOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = getCellPosition();

	for (Position item : tiles)
	{
		DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int row, int col)
{
	this->rowOffset += row;
	this->colOffset += col;
}

void Block::Rotate()
{
	rotationState++;
	if (rotationState == (int)cells.size())
	{
		rotationState = 0;
	}
}

void Block::undoRotate()
{
	rotationState--; //Goes back to previous rotation state
	if (rotationState == -1)  //If in first rotation stat (0), undo back to last state(3)
	{
		rotationState = cells.size() - 1;
	}
}

vector<Position> Block::getCellPosition()
{
	vector<Position> tiles = cells[rotationState];
	vector<Position> movedTiles;
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.col + colOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}
