#include "inputhandler.hpp"
#include "../../utility/logger/logger.hpp"

void InputHandler::handleTooltip(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) m_currentTool = ActiveTool::None;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) m_currentTool = ActiveTool::Entity;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) m_currentTool = ActiveTool::Tree;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) m_currentTool = ActiveTool::Bush;
}
void InputHandler::handleTimeScale() {
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

void InputHandler::checkTooltipInput() {
    handleTooltip();
    handleTimeScale();
}


void InputHandler::handleMousePress(sf::RenderWindow& win, Simulation& sim, const std::optional<sf::Event> event) {
    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left) {

            sf::Vector2f spawnPos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
            sim.spawnAt(spawnPos, m_currentTool);
        }
    }
}

void InputHandler::handleInput(sf::RenderWindow& win, Simulation& sim) {

    while (const std::optional event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            win.close();

        checkTooltipInput();
        handleMousePress(win,sim,event);
    }

}