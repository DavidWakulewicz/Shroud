#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>

class Game
{
public:
	Game();
	~Game();

	void run();
	void stop();
private:
	bool quit;

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//The window we'll be rendering to
	SDL_Window* window;

	//The window renderer
	SDL_Renderer* renderer;

	//Current displayed texture
	SDL_Texture* texture;

	SDL_Texture* loadTexture(std::string path);

	void handleInput(SDL_Event);
};

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		std::cout << "SDL Could not be initialized, exiting" << std::endl;
		exit(1);
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	// Create window
	// SDL_WINDOW_SHOWN flag is ignored according to document.
	// Might want to eventually use SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_INPUT_GRABBED
	// https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("A cool title",
	                           SDL_WINDOWPOS_CENTERED,
	                           SDL_WINDOWPOS_CENTERED,
	                           SCREEN_WIDTH,
	                           SCREEN_HEIGHT,
	                           SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created!" << std::endl;
		exit(1);
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Renderer could not be created!" << std::endl;
		exit(1);
	}

	//Initialize renderer color (renderer, red, green, blue, alpha)
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Requires another library 'SDL_Image'
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "\n\n\n";
		std::cout << IMG_GetError() << std::endl;
		std::cout << "\n\n\n";
		exit(2);
	}

	//Load PNG texture
	texture = loadTexture("texture.png");
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		exit(1);
	}

	//Main loop flag
	quit = false;
}

Game::~Game()
{
	IMG_Quit();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Loads individual image as texture
SDL_Texture* Game::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{ std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl; }
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Game::run()
{
	double delta = 0;
	long long current = 0;
	int frames = 0;
	int updates = 0;
	int ups = 60;

	long long lastTime = SDL_GetTicks();
	long long timer = lastTime;

	const double MS_PER_FRAME = 1000.0 / ups;

	//While application is running
	while (!quit)
	{
		// Timer calculations
		current = SDL_GetTicks();
		delta += (current - lastTime) / MS_PER_FRAME;
		lastTime = current;

		while (delta >= 1) {
			// Future call to 'update' function that updates location of enemies, players, spells, etc.
			updates++;
			delta--;
		}

		// Future call to 'render' function here, will control all rendering (RenderClear, RenderCopy, RenderPresent will get moved there)
		frames++;

		//Clear screen
		SDL_RenderClear(renderer);

		//Render texture to screen
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		//Update screen
		SDL_RenderPresent(renderer);

		if (SDL_GetTicks() - timer > 1000) {
			std::ostringstream title;
			title << "Shroud" << "  |  " << updates << " UPS  " << frames << " FPS";
			SDL_SetWindowTitle(window, title.str().c_str());
			timer += 1000;
			updates = 0;
			frames = 0;
		}

		//Event handler
		SDL_Event e;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			switch(e.type)
			{
			case SDL_QUIT:
				stop();
				break;
			case SDL_KEYDOWN:
				handleInput(e);
				break;
			}
		}
	}
}

void Game::handleInput(SDL_Event e)
{
	switch(e.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		stop();
		break;
	}
	return;
}

void Game::stop()
{
	quit = true;
}

int main(int argc, char* args[]) {
	Game game;
	game.run();

	return 0;
}
