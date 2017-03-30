/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

State class

*/

#include "State.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "Character.h"



namespace GEX
{

	State::Context::Context(sf::RenderWindow& window, PlayerControl& player,
		MusicPlayer& music, SoundPlayer& soundEffects, Character::Type& playerOne, Character::Type& playerTwo) :
		window(&window),
		player(&player),
		music(&music),
		soundEffects(&soundEffects),
		playerOneCharacter(&playerOne),
		playerTwoCharacter(&playerTwo)
	{}


	GEX::State::State(StateStack & stack, Context context) :
		_stack(&stack),
		_context(context)
	{}

	State::~State()
	{
	}

	void State::requestStackPush(StateID stateID)
	{
		_stack->pushState(stateID);
	}

	void State::requestStackPop()
	{
		_stack->popState();
	}

	void State::requestStateClear()
	{
		_stack->clearStates();
	}

	State::Context State::getContext() const
	{
		return _context;
	}	
}