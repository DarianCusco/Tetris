#include "Grid.h"

Grid::Grid()
{
	this->numRows = 20;
	this->numCols = 10;
	this->cellSize = 30;
	Initialize();
	colors = getCellColor();

}

void Grid::Initialize()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Grid::PrintGrid()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::drawGrid()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int cellValue = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
		
	}
}

bool Grid::isCellOutside(int row, int col)
{
	if (row >= 0 && row < numRows && col >= 0 && col < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::isCellEmpty(int row, int col)
{
	if (grid[row][col] == 0)
	{
		return true;
	}
	return false;
}

int Grid::clearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (isRowFull(row))
		{
			clearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			moveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::isRowFull(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		if (grid[row][col] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::clearRow(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row][col] = 0;
	}
}

void Grid::moveRowDown(int row, int numRows)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row + numRows][col] = grid[row][col];
		grid[row][col] = 0;
	}
}
