#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "vector.h"
#include "game.h"
#include "matrix.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>
#include <crtdbg.h>
#include "fps.h"
#include <sstream>

fps fpsCounter;
const auto steps = 50;
const auto screen_width = 800;
const auto screen_height = 800;
bool is_grid_visible = true;
bool is_label_visible = true;
bool is_vector_visible = true;
bool is_projection_visible = true;
bool is_center_visible = true;
sf::Font font;


vector calculate_drawing_point(vector point)
{
	const auto width_center = screen_width / 2;
	const auto height_center = screen_height / 2;

	const auto x_step = width_center / steps;
	const auto y_step = height_center / steps;

	const auto real_x = width_center + x_step * point.get_x();
	const auto real_y = height_center + y_step * point.get_y() * -1;

	return vector{real_x, real_y};
}

void draw_point(const vector& vector, sf::RenderWindow& window)
{
	auto drawing_point = calculate_drawing_point(vector);
	sf::CircleShape circle(1.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(drawing_point.get_x(), drawing_point.get_y());
	window.draw(circle);
}

void draw_cartesian_coordinate_grid(sf::RenderWindow& window)
{
	const auto screen_width = window.getSize().x;
	const auto screen_height = window.getSize().y;
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

	window.draw(line_y);
	window.draw(line_x);

	sf::Text text;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(10);
	text.setFont(font);

	text.setString("0");
	text.setPosition(screen_width / 2, screen_height / 2);
	window.draw(text);

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
		window.draw(text);

		// write negative x values
		text.setPosition(screen_width / 2, x_position_negative);
		text.setString("-" + std::to_string(i));
		window.draw(text);

		// write negative y values
		text.setPosition(y_position_negative, screen_height / 2);
		text.setString("-" + std::to_string(i));
		window.draw(text);

		// write positive x values
		text.setPosition(screen_width / 2, x_position_positive);
		text.setString(std::to_string(i));
		window.draw(text);
	}
}

void draw_vector(const vector& vector, sf::RenderWindow& window)
{
	if (!is_vector_visible && !is_label_visible) return;

	const auto base_x = window.getSize().x / 2;
	const auto base_y = window.getSize().y / 2;

	const auto x_step = base_x / steps;
	const auto y_step = base_y / steps;

	const auto end_x = base_x + x_step * vector.get_x();
	const auto end_y = base_y + y_step * vector.get_y() * -1;
	if (is_vector_visible)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(base_x, base_y);
		line[0].color = sf::Color::Red;
		line[1].position = sf::Vector2f(end_x, end_y);
		line[1].color = sf::Color::Green;
		window.draw(line);
	}

	// draw label
	if (is_label_visible)
	{
		sf::Font font;
		if (!font.loadFromFile("hack.ttf"))
		{
			std::cerr << "Font could not be loaded";
		}
		sf::Text text;
		text.setFillColor(sf::Color::Green);
		text.setCharacterSize(10);
		text.setFont(font);

		text.setString(vector.get_notation());
		text.setPosition(end_x, end_y);
		window.draw(text);
	}
};

void draw_connection_lines(const vector a, const vector b, sf::RenderWindow& window)
{
	sf::VertexArray line{sf::Lines, 2};
	const auto point_a = calculate_drawing_point(a);
	line[0].position = sf::Vector2f(point_a.get_x(), point_a.get_y());
	line[0].color = sf::Color::Blue;
	const auto point_b = calculate_drawing_point(b);
	line[1].position = sf::Vector2f(point_b.get_x(), point_b.get_y());
	line[1].color = sf::Color::Blue;
	window.draw(line);
}

void draw_matrix(matrix& matrix, sf::RenderWindow& window)
{
	for (auto i = 0; i < matrix.count(); ++i)
	{
		const auto vector = matrix.get_vector(i);
		draw_vector(vector, window);
		if (is_projection_visible)
		{
			const auto prev_vector = matrix.get_vector(i - 1 >= 0 ? i - 1 : matrix.count() - 1);
			draw_connection_lines(vector, prev_vector, window);
		}
	}
	if (is_center_visible)
	{
		draw_point(matrix.get_center(), window);
	}
}


void toggle_grid()
{
	is_grid_visible = !is_grid_visible;
}

void toggle_labels()
{
	is_label_visible = !is_label_visible;
}

void toggle_vectors()
{
	is_vector_visible = !is_vector_visible;
}

void toggle_projections()
{
	is_projection_visible = !is_projection_visible;
}

void toggle_centers()
{
	is_center_visible = !is_center_visible;
}

int main()
{
	sf::ContextSettings settings;
	// settings.antialiasingLevel = 8;

	// create the window
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Linal Opdracht", sf::Style::Default,
	                        settings);
	window.setFramerateLimit(140);

	matrix polygon;
	// polygon.add_vector(vector{0, 0});
	// polygon.add_vector(vector{0, 3});
	// polygon.add_vector(vector{1, 2});
	// polygon.add_vector(vector{3, 2});
	// polygon.add_vector(vector{4, 3});
	// polygon.add_vector(vector{4, 0});
	// polygon.add_vector(vector{3, 1});
	// polygon.add_vector(vector{1, 1});

	polygon.add_vector(vector{0, 0});
	polygon.add_vector(vector{0, 6});
	polygon.add_vector(vector{1, 6});
	polygon.add_vector(vector{1, 4});
	polygon.add_vector(vector{2, 6});
	polygon.add_vector(vector{3, 6});
	polygon.add_vector(vector{1.5, 3});
	polygon.add_vector(vector{3, 0});
	polygon.add_vector(vector{2, 0});
	polygon.add_vector(vector{1, 2});
	polygon.add_vector(vector{1, 0});

	// game main_game;q

	// run the program as long as the window is open
	while (window.isOpen())
	{
		fpsCounter.update();
		std::ostringstream ss;
		ss << fpsCounter.get_fps() << " FPS";
		window.setTitle(ss.str());

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::G)
				{
					toggle_grid();
				}
				if (event.key.code == sf::Keyboard::L)
				{
					toggle_labels();
				}
				if (event.key.code == sf::Keyboard::P)
				{
					toggle_projections();
				}
				if (event.key.code == sf::Keyboard::V)
				{
					toggle_vectors();
				}
				if (event.key.code == sf::Keyboard::M)
				{
					toggle_centers();
				}
				if (event.key.code == sf::Keyboard::Equal)
				{
					polygon.multiply(2);
				}
				if (event.key.code == sf::Keyboard::Dash)
				{
					polygon.multiply(0.5);
				}
				if (event.key.code == sf::Keyboard::LBracket)
				{
					polygon.multiply(0.5, polygon.get_center());
				}
				if (event.key.code == sf::Keyboard::RBracket)
				{
					polygon.multiply(2, polygon.get_center());
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					polygon.translate(0, 1);
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					polygon.translate(0, -1);
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					polygon.translate(1, 0);
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					polygon.translate(-1, 0);
				}
				if (event.key.code == sf::Keyboard::Q)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Comma)
				{
					polygon.rotate(1);
				}
				if (event.key.code == sf::Keyboard::Period)
				{
					polygon.rotate(-1);
				}
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		if (is_grid_visible)
		{
			draw_cartesian_coordinate_grid(window);
		}

		// Draw from matrix
		draw_matrix(polygon, window);


		// end the current frame
		window.display();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
