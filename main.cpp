#include "game/game.hpp"
#include "map/mapGeneration/mapgeneration.hpp"

int main() {
    generateMap("map_test.txt", 2137, 1920, 1080);
    Game game("map_test.txt");
    game.mainLoop();
}
