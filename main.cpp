#include <SFML/Graphics/RenderWindow.hpp>
#include "map/map.hpp"
#include "map/mapView/mapview.hpp"
#include "simulation/simulation.hpp"

int main(){ 
    Map map("map_test.txt");
    MapView mView(map);
    Simulation sim(map.getMapData());

    sf::Clock cl;
    float accumulator = 0.0f;
    const float dt = 1.0f / sim.getTickRate();

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float frameTime = cl.restart().asSeconds();
        frameTime = std::min(frameTime, 0.25f);
        accumulator += frameTime;

        while (accumulator >= dt) {
            sim.simulate();
            accumulator -= dt;
        }

        window.clear(sf::Color::Black);
        mView.drawMap(window);

        window.display();
    }
}