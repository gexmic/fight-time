#include "RoundState.h"
#include "Utility.h"
#include "PlayerControl.h"
#include "TextureHolder.h"


namespace GEX
{
	RoundState::RoundState(StateStack & stack, Context context) :
		State(stack, context),
		_elapsedTime(sf::Time::Zero),
		_context(context)
	{
		sf::Vector2f windowSize = context.window->getView().getSize();

		
		if (context.player->getFightStatus() == FightStatus::RoundOne)
		{
			_round.setTexture(TextureHolder::getInstance().get(TextureID::RoundOne));
		}
		if (context.player->getFightStatus() == FightStatus::RoundTwo)
		{
			_round.setTexture(TextureHolder::getInstance().get(TextureID::RoundTwo));
		}
		if (context.player->getFightStatus() == FightStatus::RoundThree)
		{
			_round.setTexture(TextureHolder::getInstance().get(TextureID::FinalRound));
		}


	}

	void RoundState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		
		window.draw(_round);
	}
	bool RoundState::update(sf::Time dt)
	{
		// 3 secound countdwon timer
		_elapsedTime += dt;
		if (_context.player->getFightStatus() == FightStatus::RoundOne && _elapsedTime > sf::seconds(2))
		{
			requestStackPop();
			requestStateClear();
			requestStackPush(StateID::Game);
		}
		else if (_elapsedTime > sf::seconds(2))
		{
			requestStackPop();
		}
		return false;
	}
	bool RoundState::handleEvent(const sf::Event & event)
	{
		return false;
	}
}
