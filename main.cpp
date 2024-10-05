#include "Game.hpp"
#include <iostream>

int main()
{
	std::cout << "Main menu" << std::endl;
	std::cout << "To control the game, use the following keys:" << std::endl;
	std::cout << "Q - Rotate left" << std::endl;
	std::cout << "E - Rotate right" << std::endl;
	std::cout << "A - Move left" << std::endl;
	std::cout << "D - Move right" << std::endl;
	std::cout << "S - Move down" << std::endl;
	std::cout << "X - to stop the game" << std::endl;
	std::cout << "Press any key to start the game" << std::endl;

	if (std::cin.get())
	{
		Game game(20, 10);
		game.run();
	}
}