#include "game.hpp"

Game::Game(const std::string& f): map(f),mView(map),sim(map.getMapData()) {}

void Game::mainLoop() {

    sf::Clock cl;
    float acc = 0.0f;
    const float dt = 1.0f / sim.getTickRate();

    const uint16_t windowWidth = map.getMapData().getWidth();
    const uint16_t windowHeight = map.getMapData().getHeight();

    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "Civilisation");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        handleInput(window);
        advanceSimulation(cl, acc, dt);
        render(window);
    }
}

void Game::handleInput(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        checkTooltipInput();

        //Changes pixels to coordinates and lets you place entities

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {

                sf::Vector2f spawnPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sim.spawnAt(spawnPos, currentTool);
            }
        }
    }
}

void Game::checkTooltipInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) currentTool = ActiveTool::None;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) currentTool = ActiveTool::Entity;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) currentTool = ActiveTool::Tree;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) currentTool = ActiveTool::Bush;
}

void Game::advanceSimulation(sf::Clock& cl, float& accumulator, const float& dt) {
    
    float frameTime = cl.restart().asSeconds();
    frameTime = std::min(frameTime, 0.25f);
    accumulator += frameTime;

    while (accumulator >= dt) {
        sim.simulate();
        accumulator -= dt;
    }
}

void Game::render(sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    mView.drawMap(window);
    sim.render(window);
    window.display();

}