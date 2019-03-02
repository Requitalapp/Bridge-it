#include <iostream>
#include "Game.h"
#include "Definitions.h"

int main()
{
	/*try
	{
		bridgeit::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Bridg-IT");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::getchar();
	}*/
	bridgeit::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Bridg-IT");
	return EXIT_SUCCESS;
}