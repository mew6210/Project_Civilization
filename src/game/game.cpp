#include "game.hpp"

Game::Game(const std::string& f): map(f),mView(map),sim(map.getMapData()),iView() {}

void Game::printUserManual() {
    std::cout << "=================================================================\n";
    std::cout << "|                PROJECT CIVILIZATION - MANUAL                  |\n";
    std::cout << "=================================================================\n\n";

    std::cout << "  [ STEROWANIE SYMULACJA ]\n";
    std::cout << "  * Klawisz [0] - Pauza (Zatrzymanie czasu)\n";
    std::cout << "  * Klawisz [9] - Zwolnione tempo (0.5x)\n";
    std::cout << "  * Klawisz [8] - Normalne tempo (1.0x)\n";
    std::cout << "  * Klawisz [7] - Szybkie tempo (2.0x)\n";
    std::cout << "  * Klawisz [6] - Najszybsze tempo (4.0x)\n\n";

    std::cout << "  [ NARZEDZIA I STAWIANIE OBIEKTOW ]\n";
    std::cout << "  * Klawisz [1] - Tryb: Brak narzedzia (None)\n";
    std::cout << "  * Klawisz [2] - Tryb: Postaw Jednostke (Entity)\n";
    std::cout << "  * Klawisz [3] - Tryb: Postaw Drzewo (Tree)\n";
    std::cout << "  * Klawisz [4] - Tryb: Postaw Krzak (Bush)\n\n";

    std::cout << "  [ MYSZKA ]\n";
    std::cout << "  * Lewy Przycisk (LPM) - Uzycie wybranego narzedzia na mapie\n\n";

    std::cout << "  [ ZNACZENIE LOGOW ]\n";
    std::cout << "  ";
    defaultLogger.infoLog("Informacja");
    std::cout << "  ";
    defaultLogger.successLog("Powodzenie");
    std::cout << "  ";
    defaultLogger.warningLog("Ostrzezenie");
    std::cout << "  ";
    defaultLogger.errorLog(false,"Error");
    std::cout << "\n";

    std::cout << "=================================================================\n";
    std::cout << "| ";
    defaultLogger.infoLog("Logi systemowe i zmiany statusu beda widoczne ponizej:    |");
    std::cout << "| ";
    defaultLogger.infoLog("HINT: Postaw 1 drzewo i 2 krzaki i zobacz co sie stanie   |");
    std::cout << "=================================================================\n\n";
}

void Game::mainLoop() {

    sf::Clock cl;
    float acc = 0.0f;
    const float dt = 1.0f / sim.getTickRate();

    const uint16_t windowWidth = map.getMapData().getWidth();
    const uint16_t windowHeight = map.getMapData().getHeight();

    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "Civilisation");
    window.setFramerateLimit(60);

    printUserManual();

    while (window.isOpen()) {
        inHandler.handleInput(window, sim);
        advanceSimulation(cl, acc, dt);
        render(window);
    }
}

void Game::advanceSimulation(sf::Clock& cl, float& accumulator, const float& dt) {
    
    float frameTime = cl.restart().asSeconds();
    if (frameTime > 0.25f) frameTime = 0.25f;

    accumulator += frameTime * inHandler.getTimeScale();

    while (accumulator >= dt) {
        sim.simulate();
        accumulator -= dt;
    }
}

void Game::render(sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    mView.drawMap(window);
    sim.render(window);
    iView.render(window,sim,map.getMapData().getMapSize());
    window.display();
}