#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

using namespace std;

class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void Move(int row, int col);
	void Rotate();
	void undoRotate();
	vector<Position> getCellPosition();

	int id;
	map<int, vector<Position>> cells;

private:
	int cellSize;
	int rotationState;
	vector<Color> colors;

	int rowOffset;
	int colOffset;
};

