#include <memory>

#include "Game.h"

int main(int argc, char* args[]) {
	auto game = std::make_shared<Game>();
	game->Run();

	return 0;
}
