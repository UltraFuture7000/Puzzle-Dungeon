/*
Puzzle Dungeon ((C) 2019)
@authors Omar Junaid, Sam Dockery
This work is licensed under the
Creative Commons Attribution-NonCommercial-NoDerivatives
4.0 International License. To view a copy of this license,
visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
*/

#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.hpp"



class Level {
private:
	sf::Texture brickTexture;
public:
	std::vector<Tile> tiles;
	sf::Sprite levelBackground;

	inline void setLevel(int levelNumber) {
		
		switch (levelNumber) {

		case 1: {
			
			brickTexture.loadFromFile("Textures//brick.png");

			Tile brickTile;
			brickTile.tilesprite.setTexture(brickTexture);
			tiles.push_back(brickTile);
		}

		}
	}
};
#endif