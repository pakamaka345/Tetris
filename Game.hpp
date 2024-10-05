#pragma once
#include "Scene.hpp"
#include "Tetromino.hpp"
#include "Board.hpp"
#include "CommandIdentifier.hpp"
#include <map>
#include <functional>

class Game : public Scene
{
public:
	Game(int boardHeight, int boardWidth);
	~Game();
	void run() override;

protected:
	void update() override;
	void draw() override;
	void handleEvents() override;

private:
	void spawnTetromino();

	void moveTetromino(int dx, int dy);
	void rotateTetromino(bool clockwise);
	void dropTetromino();

	char getInput();

private:
	Board* board;
	Tetromino* currentTetromino;
	Tetromino* nextTetromino;
	
	int currentX;
	int currentY;

	std::map<Command::ID, std::function<void()>> commands;

	void initCommands();
	Command::ID getCommand();

	bool isGameOver;

	int score;
};

