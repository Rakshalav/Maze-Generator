#include "Application.hpp"

Application::Application() : event()
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

        if (event.key.code == sf::Keyboard::Space) {
            mazeGenerator.init();
        }

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
    float mazeAccumulator = 0.f;
    const float mazeUpdateRate = 10.f; // ms

    while (window.isOpen())
    {
        eventHandler();

        auto frameTime = deltaClock.restart();
        float dt = frameTime.asMilliseconds();
        mazeAccumulator += dt;
        if (mazeAccumulator >= mazeUpdateRate) {
            mazeGenerator.update();
            mazeAccumulator = 0.f;
        }

        ImGui::SFML::Update(window, frameTime);
        render();
    }
    ImGui::SFML::Shutdown();
}