#pragma once
#include <vector>
#include <memory>

namespace TetrominoType
{
	enum class Type
	{
		I,
		J,
		L,
		O,
		S,
		T,
		Z,
		countTypes
	};
}

class Tetromino
{
public:
	typedef std::vector<std::vector<int>> grid;

public:
	Tetromino(TetrominoType::Type type);
	Tetromino(const Tetromino& currentTetromino);

	grid getShape() const;
	char getType() const;

	void rotateClockwise();
	void rotateCounterClockwise();

	static std::unique_ptr<Tetromino> generateRandomTetromino();

private:
	TetrominoType::Type type;
	grid shape;

private:
	void initShape();
};

