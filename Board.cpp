#include "Board.hpp"
#include <iostream>

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;

	board = grid(height, std::vector<char>(width, ' '));
}

void Board::draw() const
{
	for (auto& row : board)
	{
		for (auto& cell : row)
		{
			std::cout << cell;
		}
		std::cout << std::endl;
	}
}

bool Board::canPlaceTetromino(const Tetromino& tetromino, int x, int y) const
{
	auto shape = tetromino.getShape();

	for (size_t i = 0; i < shape.size(); ++i)
	{
		for (size_t j = 0; j < shape[i].size(); ++j)
		{
			if (shape[i][j] != 0)
			{
				// Check if the tetromino is out of bounds
				if (x + j < 0 || x + j >= width || y + i < 0 || y + i >= height)
				{
					return false;
				}

				// Check if the tetromino collides with another tetromino
				if (board[y + i][x + j] != ' ')
				{
					return false;
				}
			}
		}
	}

	// The tetromino can be placed
	return true;
}

void Board::placeTetromino(const Tetromino& tetromino, int x, int y)
{
	auto shape = tetromino.getShape();

	for (size_t i = 0; i < shape.size(); ++i)
	{
		for (size_t j = 0; j < shape[i].size(); ++j)
		{
			if (shape[i][j] != 0)
			{
				board[y + i][x + j] = tetromino.getType();
			}
		}
	}
}

void Board::clearOldPosition(const Tetromino& tetromino, int x, int y)
{
	auto shape = tetromino.getShape();

	for (size_t i = 0; i < shape.size(); ++i)
	{
		for (size_t j = 0; j < shape[i].size(); ++j)
		{
			if (shape[i][j] != 0)
			{
				board[y + i][x + j] = ' ';
			}
		}
	}
}

void Board::clearAllRows(int& score)
{
	for (int i = height - 1; i >= 0; --i)
	{
		if (isRowFull(i))
		{
			removeRow(i);
			score += 100;
			++i;
		}
	}
}

bool Board::isGameOver() const
{
	return isRowFull(0);
}

bool Board::isRowFull(int row) const
{
	for (auto& cell : board[row])
	{
		if (cell == ' ')
		{
			return false;
		}
	}
	
	return true;
}

void Board::removeRow(int row)
{
	for (int i = row; i > 0; --i)
	{
		board[i] = board[i - 1];
	}

	board[0] = std::vector<char>(width, ' ');
}

int Board::getWidth() const
{
	return width;
}

int Board::getHeight() const
{
	return height;
}