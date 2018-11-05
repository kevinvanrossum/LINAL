#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class game
{
#define WIDTH 800
#define HEIGHT 600

public:
	game();
	void run();

private:
	void process_events();
	void update();
	void render();
	sf::RenderWindow window_;
};
