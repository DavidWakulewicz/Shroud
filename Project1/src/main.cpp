#include <memory>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Game.h"
#include <iostream>

void mainLoop(void *g)
{
        ((Game *)g)->Run();
}

int main(int argc, char* args[]) {
	auto game = std::make_shared<Game>();

#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(mainLoop, &game, 0, 1);
#else
	game->Run();
#endif

	return 0;
}
