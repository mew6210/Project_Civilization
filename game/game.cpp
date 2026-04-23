#include "game.hpp"

Game::Game(const std::string& f): map(f),mView(map),sim(map.getMapData()) {}

void Game::mainLoop() {

    sf::Clock cl;
    float acc = 0.0f;
    const float dt = 1.0f / sim.getTickRate();

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");
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
    }
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
    window.display();
}