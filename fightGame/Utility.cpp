/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the Pacman game for my final test at NBCC Moncton programing course

@section DESCRIPTION

Utility class

*/

#include "Utility.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "SFML/Graphics.hpp"
#include <cassert>
#include <cmath>
#include <random>


namespace GEX
{

	namespace
	{
		std::default_random_engine createRandomEgine()
		{
			auto seed = static_cast<unsigned long>(std::time(nullptr));
			return std::default_random_engine(seed);
		}
		auto RandomEngine = createRandomEgine();
	}

	int randomInt(int exclusiveMax)
	{
		std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
		return distr(RandomEngine);
	}

	void centerOrigin(sf::Sprite& sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void centerOrigin(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}
	/*void centerOrigin(Animation2 & animation)
	{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}*/
	float lenght(sf::Vector2f vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}
	sf::Vector2f unitVector(sf::Vector2f vector)
	{
		assert(vector != sf::Vector2f(0.f, 0.f));

		return vector / lenght(vector);
	}
}