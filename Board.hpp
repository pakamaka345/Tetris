#pragma once
#include <vector>
#include "Tetromino.hpp"

class Board
{
public:
	typedef std::vector<std::vector<char>> grid;

public:
	Board(int width, int height);

	void draw() const;
	bool canPlaceTetromino(const Tetromino& tetromino, int x, int y) const;
	void placeTetromino(const Tetromino& tetromino, int x, int y);
	void clearOldPosition(const Tetromino& tetromino, int x, int y);
	void clearAllRows(int& score);
	bool isGameOver() const;

	int getWidth() const;
	int getHeight() const;

private:
	int width;
	int height;
	grid board;

private:
	bool isRowFull(int row) const;
	void removeRow(int row);
};

