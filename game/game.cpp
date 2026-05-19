#include "game.hpp"

Game::Game(const std::string& f): map(f),mView(map),sim(map.getMapData()) {}

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

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "My window");
    window.setFramerateLimit(60);

    printUserManual();

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

    float oldScale = m_timeScale;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) m_timeScale = 0.0f; //simulation pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) m_timeScale = 0.5f; //0.5x speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) m_timeScale = 1.0f; //1x speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) m_timeScale = 2.0f; //2x speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) m_timeScale = 4.0f; //4x speed

    if (m_timeScale != oldScale) {
        std::string status = (m_timeScale == 0.0f) ? "PAUSED" : std::format("{:.1f}x", m_timeScale);;

        defaultLogger.infoLog("simulation speed changed to: " + status);
    }
}

void Game::advanceSimulation(sf::Clock& cl, float& accumulator, const float& dt) {
    
    float frameTime = cl.restart().asSeconds();
    if (frameTime > 0.25f) frameTime = 0.25f;

    accumulator += frameTime * m_timeScale;

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