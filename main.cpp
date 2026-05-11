#include "game/game.hpp"
#include "map/mapGeneration/mapgeneration.hpp"

int main() {
    generateMap("map_test.txt", 3721);
    Game game("map_test.txt");
    game.mainLoop();
}
