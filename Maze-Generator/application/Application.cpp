#include "../include/Application.hpp"

Application::Application() : mazeGenerator(grid), event()
{
    window.create(sf::VideoMode(1800u, 1000u), "Maze Generator", sf::Style::Close);
    auto size_u = window.getSize();
    window_size = sf::Vector2f(static_cast<float>(size_u.x), static_cast<float>(size_u.y));

    Gui_margin = 0.0f;
    displayArea.setSize({ window_size.x - Gui_margin, window_size.y });
    displayArea.setFillColor(sf::Color::White);
    displayArea.setPosition({ 0.0f, 0.0f });

    ImGui::SFML::Init(window);
}

void Application::eventHandler()
{
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.key.code == sf::Keyboard::Space)
            mazeGenerator.generateMaze();

    }
}

void Application::renderImGui()
{

}

void Application::render()
{
    window.clear();
    window.draw(displayArea);
    grid.draw(window);
    ImGui::SFML::Render(window);
    window.display();
}

void Application::run()
{
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        eventHandler();
        ImGui::SFML::Update(window, deltaClock.restart());
        render();
    }
    ImGui::SFML::Shutdown();
}
