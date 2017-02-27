#include "Map.h"
#include "SFML\Graphics.hpp"
#include "TextureHolder.h"

namespace GEX
{

	Map::Map()
	{
		dessertMap =
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 2, 2, 2, 3, 0, 0, 0, 0,
			0, 4, 5, 5, 5, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	}


	Map::~Map()
	{
	}

	void Map::draw()
	{


		//int x, y;
		//for (int i = 0; i < 80; ++i)
		//{
		//	x = (i % 10) * 128;
		//	y = (i / 10) * 128;

		//	if (dessertMap.at(i) == 1)
		//	{
		//		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::tile1);
		//		sf::Sprite image;
		//		image.setTexture(texture);
		//		sf::IntRect textureRect(0, 0, x, y);
		//		image.setTextureRect(textureRect);
		//		image.setPosition(x, y);
		//		sf::RenderWindow window;
		//		window.draw(image);
		//	}

		//	if (dessertMap.at(i) == 2)
		//	{
		//		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::tile2);
		//		sf::Sprite image;
		//		image.setTexture(texture);
		//		sf::IntRect textureRect(0, 0, x, y);
		//		image.setTextureRect(textureRect);
		//		image.setPosition(x, y);
		//		//texture.setRepeated(false);
		//		sf::RenderWindow window;
		//		window.draw(image);

		//	}
		//}
	}
}

