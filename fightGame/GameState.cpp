/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Game state class

*/

#include "GameState.h"
#include "MusicPlayer.h"

namespace GEX
{

	GameState::GameState(StateStack & stack, Context context) :
		State(stack, context),
		_world(*context.window, *context.soundEffects),
		_player(*context.player)
		
	{
		context.music->play(MusicID::DessertMusic);
		context.player->setFightStatus(FightStatus::Fight);
		
	}

	void GameState::draw()
	{
		_world.draw();
	}

	bool GameState::update(sf::Time dt)
	{
		_world.update(dt);
		// ////////////////////////////

		/*_player.setFightStatus(FightStatus::PlayerOneWin);
		requestStackPush(StateID::GameOver);*/
		// ///////////////////////////
		if (_world.isRoundWin())
		{
			_player.setFightStatus(FightStatus::RoundTwo);
			requestStackPop();
			requestStackPush(StateID::Round);
		}
		CommandeQueue& commands = _world.getCommandQueue();
		_player.handleRealTimeInput(commands);

		return true;
	}

	bool GameState::handleEvent(const sf::Event & event)
	{
		CommandeQueue& commands = _world.getCommandQueue();
		_player.handleEvent(event, commands);

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			requestStackPush(StateID::Pause);

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		{
			requestStackPop();
			requestStackPush(StateID::Menu);
		}		
		return true;
	}
}