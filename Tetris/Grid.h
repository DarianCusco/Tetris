#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "raylib.h"
#include "Colors.h"

using namespace std;

class Grid
{
public:
	Grid();
	void Initialize();
	void PrintGrid();
	void drawGrid();
	int grid[20][10];
	
	bool isCellOutside(int row, int col);
	bool isCellEmpty(int row, int col);
	int clearFullRows();

private:
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	int numRows;
	int numCols;

	int cellSize;

	vector<Color> colors;
};

