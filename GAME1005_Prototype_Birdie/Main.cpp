#include "Engine.h"
#define wwidth 1024
#define wheight 768
int main(int argc, char*args[])
{
	Engine game;
	BACKGROUND bg;
	game.init("Birdie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wwidth, wheight, 0);

	while (game.running())
	{
		game.handleEvents();
		if (game.tick())
		{
			game.update();
			game.render(bg);
		}
	}
	game.clean();
	system("pause");
	return 0;
}