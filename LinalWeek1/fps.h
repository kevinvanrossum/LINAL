#pragma once
#include <SFML/System/Clock.hpp>

class fps
{
public:
	fps();

	void update();
	unsigned int get_fps() const;
	~fps();


private:
	unsigned int frame_{0};
	unsigned int fps_{0};
	sf::Clock clock_;
};
