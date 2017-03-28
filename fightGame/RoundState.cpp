#include "RoundState.h"
#include "FontHolder.h"
#include "Utility.h"
#include "PlayerControl.h"

#include "TextureHolder.h"


namespace GEX
{
	RoundState::RoundState(StateStack & stack, Context context) :
		State(stack, context),
		_roundNumberText(),
		_elapsedTime(sf::Time::Zero),
		_numberOfRoudPlay(0)
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f windowSize = context.window->getView().getSize();

		_roundNumberText.setFont(font);
		
		if (context.player->getFightStatus() == FightStatus::RoundOne)
		{
			_roundNumberText.setString("Round One Fight");
		}
		if (context.player->getFightStatus() == FightStatus::RoundTwo)
		{
			_roundNumberText.setString("Round Two Fight");
		}
		if (context.player->getFightStatus() == FightStatus::RoundThree)
		{
			_roundNumberText.setString("Last Round Fight");
		}

		_roundNumberText.setCharacterSize(100);
		centerOrigin(_roundNumberText);
		_roundNumberText.setPosition(0.5f * windowSize.x, 0.5f * windowSize.y);

	}

	void RoundState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroudShape;
		backgroudShape.setFillColor(sf::Color(100, 0, 0, 150));
		backgroudShape.setSize(window.getView().getSize());

		window.draw(backgroudShape);
		window.draw(_roundNumberText);
	}
	bool RoundState::update(sf::Time dt)
	{
		// 3 secound countdwon timer
		_elapsedTime += dt;
		if (_elapsedTime > sf::seconds(2))
		{

			requestStateClear();
			requestStackPush(StateID::Game);
		}
		return false;
	}
	bool RoundState::handleEvent(const sf::Event & event)
	{
		return false;
	}
}
