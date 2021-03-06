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

#ifdef MACOS
#include "MacTools/ResourcePath.hpp"
#endif

#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GUIToolkit.hpp"


class PauseMenu {
public:
	sf::Texture buttonTexture;


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
    void checkShouldPause(sf::RenderWindow &window);

	/*
	@brief Draw the paused menu.
	Call this regardless of whether or not we're actually paused.
	Checks will be performed to ensure the menu's not drawn while paused.
	@param window A reference pointer to the sf::RenderWindow
	on which to draw on
	*/
	void draw(sf::RenderWindow &window);

    void checkShouldDoResizeWork(sf::RenderWindow &window);

	PauseMenu();
	
private:
	Button backToMenuButton;
	Button saveGameButton;
	Button controlsButton;
	Button quitButton;


	sf::Font textFont;
	sf::RectangleShape rect;
	bool isGamePaused;
	float blurRadius;
	sf::Uint8 alphaLevel;
	sf::Shader blurShader;
	sf::Texture windowContentsTexture;
	sf::Sprite windowContentsSprite;
};


PauseMenu::PauseMenu() {
#ifdef MACOS
	buttonTexture.loadFromFile(resourcePath() + "GUI//PauseMenuButton.png");
	textFont.loadFromFile(resourcePath() + "Fonts//Robotronica.ttf");
#else
	buttonTexture.loadFromFile("GUI//PauseMenuButton.png");
	textFont.loadFromFile("Fonts//Robotronica.ttf");
#endif

    backToMenuButton.buttonSprite.setPosition(400, 350);
	backToMenuButton.buttonSprite.setTexture(buttonTexture);
	backToMenuButton.text.setFont(textFont);
	backToMenuButton.text.setString("Back to game");
    backToMenuButton.setCallback([this](){isGamePaused = !isGamePaused; });


    quitButton.buttonSprite.setPosition(400, 475);
	quitButton.buttonSprite.setTexture(buttonTexture);
	quitButton.text.setFont(textFont);
	quitButton.text.setString("Quit to Desktop");
	quitButton.setCallback([]() {exit(0); });


	blurRadius = 0.0;
	alphaLevel = 0;
	#ifdef MACOS
		blurShader.loadFromFile(resourcePath() + "Shaders/gaussianblur.frag", sf::Shader::Fragment);
	#else
		blurShader.loadFromFile("Shaders//gaussianblur.frag", sf::Shader::Fragment);
	#endif
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
}

inline void PauseMenu::draw(sf::RenderWindow &window) {

	/*
	Here we do two things.
	1) We set the correct amount of gaussian blur via our GLSL
	fragment shader
	2) We draw a transparent box over the current scene
	*/

	


	if (!isGamePaused && blurRadius > 0)
		blurShader.setUniform("blur_radius", std::max(0.0f, blurRadius - 0.001f));

	if (isGamePaused && blurRadius < 0.35f)
		blurShader.setUniform("blur_radius", std::min(0.35f, blurRadius + 0.001f));

	if (!isGamePaused && alphaLevel > 0)
		alphaLevel = std::max(0, alphaLevel - 10);
		rect.setFillColor(sf::Color(32, 32, 32, alphaLevel));

	if (isGamePaused && alphaLevel < 90)
		alphaLevel = std::min(90, alphaLevel + 10);
		rect.setFillColor(sf::Color(32, 32, 32, alphaLevel));

	if (!isGamePaused)
		return;

	// An extremely ugly hack. We need to address this later.
	windowContentsSprite.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize() / 10000u )));
	rect.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize() / 568u)));
	rect.setSize(sf::Vector2f(window.getSize()));
	window.draw(windowContentsSprite, &blurShader);
	window.draw(rect);

	backToMenuButton.draw(window);
	quitButton.draw(window);
	
	
	

}


inline bool PauseMenu::isPaused() const
{
	return isGamePaused;
}

inline void PauseMenu::checkShouldDoResizeWork(sf::RenderWindow &window) {

	if (isGamePaused)
		return;

	
	windowContentsTexture.create(window.getSize().x + 1000,
		window.getSize().y);
	windowContentsTexture.update(window);
	windowContentsSprite.setTexture(windowContentsTexture);
	
}


inline void PauseMenu::checkShouldPause(sf::RenderWindow &window) {

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return;

	/* Even though we're not resizing, we call this anyway
	to create a texture of the current screen contents.
	*/
	checkShouldDoResizeWork(window);
	isGamePaused = !isGamePaused;
    // Ugly fix to get around repeated switches.
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
	

}

#endif
