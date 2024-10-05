#include "Game.hpp"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#endif

Game::Game(int boardHeight, int boardWidth)
	: Scene("Tetris")
	, board(new Board(boardWidth, boardHeight))
	, score(0)
	, currentX(0)
	, currentY(0)
	, isGameOver(false)
{
	currentTetromino = Tetromino::generateRandomTetromino();
	nextTetromino = Tetromino::generateRandomTetromino();

	initCommands();
}

Game::~Game()
{
	delete board;
	delete currentTetromino;
	delete nextTetromino;
}

void Game::run()
{
	std::cout << MenuTitle << std::endl;
	spawnTetromino();

	while (!isGameOver)
	{
		draw();
		handleEvents();
		update();
	}

	std::cout << "Game Over!" << std::endl;
	std::cout << "Score: " << score << std::endl;
}

void Game::draw()
{
	#ifdef _WIN32
		system("cls");
	#else 
		system("clear");
	#endif

	board->draw();
}

void Game::handleEvents()
{
	Command::ID command = getCommand();
	
	if (command != Command::ID::Invalid)
	{
		commands[command]();
	}
	else 
	{
		std::cout << "Invalid command!" << std::endl;
	}
}

void Game::update()
{
	if (board->isGameOver())
	{
		isGameOver = true;
	}

	board->clearOldPosition(*currentTetromino, currentX, currentY);

	if (!board->canPlaceTetromino(*currentTetromino, currentX, currentY + 1))
	{
		board->placeTetromino(*currentTetromino, currentX, currentY);
		board->clearAllRows(score);

		delete currentTetromino;
		currentTetromino = nextTetromino;
		nextTetromino = Tetromino::generateRandomTetromino();

		spawnTetromino();
	}
	else {
		++currentY;
		board->placeTetromino(*currentTetromino, currentX, currentY);
	}
}

void Game::spawnTetromino()
{
	currentX = board->getWidth() / 2 - currentTetromino->getShape()[0].size() / 2;
	currentY = 0;

	if (!board->canPlaceTetromino(*currentTetromino, currentX, currentY))
	{
		isGameOver = true;
	}
	else
	{
		board->placeTetromino(*currentTetromino, currentX, currentY);
	}
}

void Game::moveTetromino(int dx, int dy)
{
	board->clearOldPosition(*currentTetromino, currentX, currentY);
	if (board->canPlaceTetromino(*currentTetromino, currentX + dx, currentY + dy))
	{
		currentX += dx;
		currentY += dy;
		board->placeTetromino(*currentTetromino, currentX, currentY);
	} 
}

void Game::rotateTetromino(bool clockwise)
{
	Tetromino* rotatedTetromino = new Tetromino(*currentTetromino);

	if (clockwise)
		rotatedTetromino->rotateClockwise();
	else
		rotatedTetromino->rotateCounterClockwise();

	board->clearOldPosition(*currentTetromino, currentX, currentY);

	if (board->canPlaceTetromino(*rotatedTetromino, currentX, currentY))
	{
		delete currentTetromino;
		currentTetromino = rotatedTetromino;
		board->placeTetromino(*currentTetromino, currentX, currentY);
	}
	else 
		delete rotatedTetromino;
}

void Game::dropTetromino()
{
	int oldY = currentY;
	board->clearOldPosition(*currentTetromino, currentX, oldY);

	while (board->canPlaceTetromino(*currentTetromino, currentX, currentY + 1))
	{
		++currentY;
	}

	board->placeTetromino(*currentTetromino, currentX, currentY);
}

char Game::getInput()
{
	#ifdef _WIN32
		return _getch();
	#else
		struct termios oldt, newt;
		char ch;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		return ch;
	#endif
}

Command::ID Game::getCommand()
{
	char input = getInput();

	switch (input)
	{
		case 'a': return Command::ID::MoveLeft;
		case 'd': return Command::ID::MoveRight;
		case 'e': return Command::ID::RotateClockwise;
		case 'q': return Command::ID::RotateCounterClockwise;
		case 's': return Command::ID::Drop;
		case 'x': return Command::ID::Quit;
		default: return Command::ID::Invalid;
	}
}

void Game::initCommands()
{
	commands[Command::ID::MoveLeft] = [this]() { moveTetromino(-1, 0); };
	commands[Command::ID::MoveRight] = [this]() { moveTetromino(1, 0); };
	commands[Command::ID::RotateClockwise] = [this]() { rotateTetromino(true); };
	commands[Command::ID::RotateCounterClockwise] = [this]() { rotateTetromino(false); };
	commands[Command::ID::Drop] = [this]() { dropTetromino(); };
	commands[Command::ID::Quit] = [this]() { isGameOver = true; };
}