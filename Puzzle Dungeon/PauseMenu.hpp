/*
Puzzle Dungeon ((C) 2019)
@authors Omar Junaid, Sam Dockery
This work is licensed under the
Creative Commons Attribution-NonCommercial-NoDerivatives
4.0 International License. To view a copy of this license,
visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
*/

#ifndef _PAUSEMENU_HPP_
#define _PAUSEMENU_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class PauseMenu {
public:
	/*
	@brief Get whether or not the game is paused.
	*/
	bool isPaused() const;
	/*
	@brief Toggle the paused status.
	\code
	isPaused = !isPaused
	\endcode
	@param key The key code. If ESC is pressed, the status will be toggled.
	*/
	void togglePaused(sf::Keyboard::Key key);

	/*
	@brief Draw the paused menu.
	Call this regardless of whether or not we're actually paused.
	Checks will be performed to ensure the menu's not drawn while paused.
	@param window A reference pointer to the sf::RenderWindow
	on which to draw on
	*/
	void draw(sf::RenderWindow &window);

	PauseMenu();
private:
	sf::RectangleShape rect;
	bool isGamePaused;
};


PauseMenu::PauseMenu() : rect(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width,
											(float)sf::VideoMode::getDesktopMode().height))
						{
							rect.setFillColor(sf::Color(32, 32, 32, 230));
						}

inline void PauseMenu::draw(sf::RenderWindow &window) {
	if (isGamePaused) {
		// TODO: Draw text, buttons...etc
		window.draw(rect);
	}
}


inline bool PauseMenu::isPaused() const
{
	return isGamePaused;
}

inline void PauseMenu::togglePaused(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Escape) {
		isGamePaused = !isGamePaused;
	}
}

#endif