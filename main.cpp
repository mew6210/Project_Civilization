#include <SFML/Window.hpp>
#include "map/map.hpp"

int main(){
    
    Map map;
    map.loadMapData("map_test.txt");
    map.saveMapData();
    sf::Window window(sf::VideoMode({ 800, 600 }), "My window");

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
    }
}