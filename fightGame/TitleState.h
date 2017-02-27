/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This is the title screen that you see wen you open the game with the text press any key.

*/

#pragma once
#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace GEX
{

	class TitleState : public State
	{
	public:
							TitleState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _text;

		bool                _showText;
		sf::Time            _textEffectTime;
	};
}