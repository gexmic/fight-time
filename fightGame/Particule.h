#pragma once
#include "SFML\Graphics.hpp"

namespace GEX
{
	struct Particule
	{
		enum class Type {
			Propellant,
			Smoke
		};

		sf::Vector2f	possition;
		sf::Color		color;
		sf::Time		lifeTime;
	};
}
