#include <cstdlib>
#include <ctime>
#include "Game.h"

int main(int argc, char** argv)
{
	srand(time(0));
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.ShutDown();
	return 0;
}