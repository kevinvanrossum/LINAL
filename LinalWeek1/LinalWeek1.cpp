#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "vector.h"
#include "game.h"

const auto steps = 20;

const auto screen_width = 800;
const auto screen_height = 600;
bool is_grid_visible = true;

void draw_cartesian_coordinate_grid(sf::RenderWindow* window)
{
	const auto screen_width = window->getSize().x;
	const auto screen_height = window->getSize().y;
	sf::Font font;
	if (!font.loadFromFile("hack.ttf"))
	{
		std::cerr << "Font could not be loaded";
	}

	sf::VertexArray line_y(sf::Lines, 2);
	line_y[0].position = sf::Vector2f(screen_width / 2, 0);
	line_y[1].position = sf::Vector2f(screen_width / 2, screen_height);

	sf::VertexArray line_x(sf::Lines, 2);
	line_x[0].position = sf::Vector2f(0, screen_height / 2);
	line_x[1].position = sf::Vector2f(screen_width, screen_height / 2);

	window->draw(line_y);
	window->draw(line_x);

	sf::Text text;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(10);
	text.setFont(font);

	text.setString("0");
	text.setPosition(screen_width / 2, screen_height / 2);
	window->draw(text);

	// Write text on grid
	for (auto i = 1; i < steps; ++i)
	{
		const auto y_position_positive = i * (screen_width / 2 / steps) + screen_width / 2;
		const auto x_position_negative = i * (screen_height / 2 / steps) + screen_height / 2;
		const auto y_position_negative = screen_width / 2 - i * (screen_width / 2 / steps);
		const auto x_position_positive = screen_height / 2 - i * (screen_height / 2 / steps);

		// write positive y values
		text.setPosition(y_position_positive, screen_height / 2);
		text.setString(std::to_string(i));
		window->draw(text);

		// write negative x values
		text.setPosition(screen_width / 2, x_position_negative);
		text.setString("-" + std::to_string(i));
		window->draw(text);

		// write negative y values
		text.setPosition(y_position_negative, screen_height / 2);
		text.setString("-" + std::to_string(i));
		window->draw(text);

		// write positive x values
		text.setPosition(screen_width / 2, x_position_positive);
		text.setString(std::to_string(i));
		window->draw(text);
	}
}

void draw_vector(vector* vector, sf::RenderWindow* window)
{
	const auto base_x = window->getSize().x / 2;
	const auto base_y = window->getSize().y / 2;

	const auto x_step = base_x / steps;
	const auto y_step = base_y / steps;

	const int end_x = base_x + x_step * vector->get_x();
	const int end_y = base_y + y_step * vector->get_y() * -1;

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(base_x, base_y);
	line[0].color = sf::Color::Red;
	line[1].position = sf::Vector2f(end_x, end_y);
	line[1].color = sf::Color::Green;
	window->draw(line);

	// draw label
	sf::Font font;
	if (!font.loadFromFile("hack.ttf"))
	{
		std::cerr << "Font could not be loaded";
	}
	sf::Text text;
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(10);
	text.setFont(font);

	text.setString(vector->get_notation());
	text.setPosition(end_x, end_y);
	window->draw(text);
};

void toggle_grid()
{
	is_grid_visible = !is_grid_visible;
}

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Linal Week 1");
	window.setFramerateLimit(60);

	// game main_game;
	// main_game.run();

	// run the program as long as the window is open
	while (window.isOpen())
	{
		std::vector<vector*> vectors;
		vectors.push_back(new vector(8, 6));
		vectors.push_back(new vector(4, -6));
		vectors.push_back(new vector(-6, -1));

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::G)
				{
					toggle_grid();
				}
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		if (is_grid_visible)
		{
			draw_cartesian_coordinate_grid(&window);
		}

		// multiply the second vector
		vectors[1]->multiply_by_scalar(2);
		// add vector to vector
		vectors[1]->add_vector(*vectors[2]);

		for (auto* vector : vectors)
		{
			draw_vector(vector, &window);
		}

		// end the current frame
		window.display();
	}

	return 0;
}
