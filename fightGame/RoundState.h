#pragma once
#include "State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GEX
{
	class RoundState : public State
	{
	public:
		RoundState(StateStack& stack, Context context);

		virtual void	draw() override;
		virtual bool	update(sf::Time dt) override;
		virtual bool	handleEvent(const sf::Event& event) override;

	private:
		sf::Text		_roundNumberText;
		sf::Time		_elapsedTime;
		int				_numberOfRoudPlay;
	};
}

