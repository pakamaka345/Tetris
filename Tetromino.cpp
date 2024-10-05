#include "Tetromino.hpp"
#include <random>

Tetromino::Tetromino(TetrominoType::Type type)
	: type(type)
{
	initShape();
}

Tetromino::Tetromino(const Tetromino& currentTetromino)
	: type(currentTetromino.type), shape(currentTetromino.shape)
{
}

Tetromino::grid Tetromino::getShape() const
{
	return shape;
}

char Tetromino::getType() const
{
	switch (type)
	{
		case TetrominoType::Type::I:
			return 'I';
		case TetrominoType::Type::J:
			return 'J';
		case TetrominoType::Type::L:
			return 'L';
		case TetrominoType::Type::O:
			return 'O';
		case TetrominoType::Type::S:
			return 'S';
		case TetrominoType::Type::T:
			return 'T';
		case TetrominoType::Type::Z:
			return 'Z';
		default:
			return '?';
	}
}

void Tetromino::rotateClockwise()
{
	grid rotatedShape(shape[0].size(), std::vector<int>(shape.size()));

	for (size_t i = 0; i < shape.size(); ++i)
	{
		for (size_t j = 0; j < shape[i].size(); ++j)
		{
			rotatedShape[j][shape.size() - 1 - i] = shape[i][j];
		}
	}

	shape = rotatedShape;
}

void Tetromino::rotateCounterClockwise()
{
	grid rotatedShape(shape[0].size(), std::vector<int>(shape.size()));

	for (size_t i = 0; i < shape.size(); i++)
	{
		for (size_t j = 0; j < shape[i].size(); j++)
		{
			rotatedShape[shape[i].size() - 1 - j][i] = shape[i][j];
		}
	}

	shape = rotatedShape;
}

void Tetromino::initShape()
{
	switch (type)
	{
		case TetrominoType::Type::I:
			shape = {
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 } };
			break;

		case TetrominoType::Type::J:
			shape = {
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 } };
			break;

		case TetrominoType::Type::L:
			shape = {
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 } };
			break;

		case TetrominoType::Type::O:
			shape = {
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 } };
			break;

		case TetrominoType::Type::S:
			shape = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 } };
			break;

		case TetrominoType::Type::T:
			shape = {
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 1 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 } };
			break;

		case TetrominoType::Type::Z:
			shape = {
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 0, 0 } };
			break;
	}
}

std::unique_ptr<Tetromino> Tetromino::generateRandomTetromino()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, static_cast<int>(TetrominoType::Type::countTypes) - 1);

	TetrominoType::Type type = static_cast<TetrominoType::Type>(dist(gen));

	return std::make_unique<Tetromino>(type);
}