#include "Application.hpp"

Application::Application() : event()
{
    window.create(sf::VideoMode(1800u, 1000u), "Maze Generator", sf::Style::Close);
    auto size_u = window.getSize();
    window_size = sf::Vector2f(static_cast<float>(size_u.x), static_cast<float>(size_u.y));
    window.setFramerateLimit(63);

    view.setSize({ 1800.f, 1000.f });
    view.setCenter({ 900.f, 500.f });
    window.setView(view);

    Gui_margin = 0.0f;
    ImGui::SFML::Init(window);
}

sf::Vector2f Application::getMousePos()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return worldPos;
}

void Application::eventHandler(float dt)
{
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.key.code == sf::Keyboard::Space)
            mazeGenerator.init();

        if (event.key.code == sf::Keyboard::Enter)
            aStar.init();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            dragging = true;
            lastMousePos = getMousePos();
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            dragging = false;
        
        if (event.type == sf::Event::MouseMoved && dragging) {
            float mouseSensitivity = 15.f;
            sf::Vector2f newMousePos = getMousePos();
            sf::Vector2f delta = lastMousePos - newMousePos;
            view.move({ delta.x * dt * mouseSensitivity, delta.y * dt * mouseSensitivity});
            window.setView(view);
            lastMousePos = newMousePos;
        }
    }
}

void Application::renderImGui()
{

}

void Application::render()
{
    window.clear();
    grid.draw(window);
    ImGui::SFML::Render(window);
    window.display();
}

void Application::run()
{
    float mazeAccumulator = 0.f;
    const float mazeUpdateRate = 0.01f; 

    float aStarAccumulator = 0.f;
    const float aStarupdateRate = 0.01f;

    while (window.isOpen())
    {
        auto frameTime = deltaClock.restart();
        float dt = frameTime.asSeconds();
        int fps = static_cast<int>(1.f / dt);
        printf("FPS: %i\n", fps);

        eventHandler(dt);

        mazeAccumulator += dt;
        if (mazeAccumulator >= mazeUpdateRate) {
            mazeGenerator.update();
            mazeAccumulator = 0.f;
        }

        aStarAccumulator += dt;
        if (aStarAccumulator >= aStarupdateRate) {
            if (!aStar.foundDest)
                aStar.update();
            aStarAccumulator = 0.f;
        }

        mazeGenerator.generate();

        ImGui::SFML::Update(window, frameTime);
        render();
    }
    ImGui::SFML::Shutdown();
}
