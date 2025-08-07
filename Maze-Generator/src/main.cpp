#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "../include/Grid.h"
#include "../include/Recursive_backtracker.h"
#include <iostream>

constexpr float Gui_margin = 0.0f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1900u, 1000u), "Maze Generator", sf::Style::Close);
	ImGui::SFML::Init(window);

	sf::Vector2f window_size =
		[&window]() -> sf::Vector2f {
		auto size_u = window.getSize();
		return sf::Vector2f({ static_cast<float>(size_u.x), static_cast<float>(size_u.y) });
		}();


	sf::RectangleShape displayArea;
	displayArea.setSize({ window_size.x - Gui_margin, window_size.y });
	displayArea.setFillColor(sf::Color::White);
	displayArea.setPosition({ 0.0f, 0.0f });

	Grid grid(window);
	MazeGenerator mazeGenerator(grid);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.key.code == sf::Keyboard::Space)
				mazeGenerator.generateMaze();

		}

		ImGui::SFML::Update(window, deltaClock.restart());


		window.clear();
		window.draw(displayArea);
		grid.draw();
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}