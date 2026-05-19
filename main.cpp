#include "game/game.hpp"
#include "map/mapGeneration/mapgeneration.hpp"

int main() {
    generateMap("map_test.txt", 800, 600);
    Game game("map_test.txt");
    game.mainLoop();
}
