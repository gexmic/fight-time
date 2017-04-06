#include "RoundState.h"
#include "Utility.h"
#include "PlayerControl.h"
#include "TextureHolder.h"

const int TIME_BETWEEN_ROUND = 2800;

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
			context.music->play(MusicID::RoundOne);
		}
		if (context.player->getFightStatus() == FightStatus::RoundTwo)
		{
			_round.setTexture(TextureHolder::getInstance().get(TextureID::RoundTwo));
			context.music->play(MusicID::RoundTwo);
		}
		if (context.player->getFightStatus() == FightStatus::RoundThree)
		{
			_round.setTexture(TextureHolder::getInstance().get(TextureID::FinalRound));
			context.music->play(MusicID::FinalRound);
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
		if (_context.player->getFightStatus() == FightStatus::RoundOne && _elapsedTime > sf::milliseconds(TIME_BETWEEN_ROUND))
		{
			_context.music->stop();
			requestStackPop();
			requestStateClear();
			requestStackPush(StateID::Game);
		}
		else if (_elapsedTime > sf::milliseconds(TIME_BETWEEN_ROUND))
		{
			_context.music->stop();
			requestStackPop();
		}
		return false;
	}
	bool RoundState::handleEvent(const sf::Event & event)
	{
		return false;
	}
}
