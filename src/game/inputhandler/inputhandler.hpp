#include "activetool.hpp"
#include "../../simulation/simulation.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class InputHandler {

	ActiveTool m_currentTool = ActiveTool::None;
	float m_timeScale = 1.0f;
	void checkTooltipInput();
	void handleTooltip();
	void handleTimeScale();
	void handleMousePress(sf::RenderWindow& win, Simulation& sim, const std::optional<sf::Event>);

public:
	void handleInput(sf::RenderWindow& win, Simulation& sim);
	float getTimeScale() const { return m_timeScale; }
};