#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Game.h"
#include <iostream>

void mainLoop(void *g)
{
        ((Game *)g)->run();
}

int main(int argc, char* args[]) {
	Game game;

#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(mainLoop, &game, 0, 1);
#else
	game.run();
#endif

	return 0;
}
