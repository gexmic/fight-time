/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Player control class

*/

#include "PlayerControl.h"
#include "Category.h"
#include "Character.h"
#include <iostream>

namespace GEX
{
	struct AircraftMover
	{
		AircraftMover(float vx, float vy) : velocity(vx, vy)
		{}
		void operator() (Character& aircraft, sf::Time dt) const
		{
			aircraft.move(velocity.x, velocity.y);
		}
		sf::Vector2f velocity;
	};

	PlayerControl::PlayerControl() :
		_missionStatus(MissionStatus::Active)
	{
		initializaKeyBindings();
		initializaActionBindings();

	}

	void PlayerControl::handleEvent(const sf::Event& event, CommandeQueue& commands)
	{
		if (sf::Joystick::isButtonPressed(1, 0))
		{
			commands.push(_actionBindings[sf::Joystick::isButtonPressed, Action::MoveUp]);
		}
		
	}

	void PlayerControl::handleRealTimeInput(CommandeQueue& commands)
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Joystick::Axis(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
			sf::Vector2f speed = sf::Vector2f(sf::Joystick::getAxisPosition(1, sf::Joystick::X), 0); // move just on the x axis
		
				if (speed.x < -15.f  )
				{
					commands.push(_actionBindings[sf::Joystick::Axis::X, Action::MoveLeft]);
				}
				if (speed.x > 15.f)
				{
					commands.push(_actionBindings[sf::Joystick::Axis::X, Action::MoveRight]);
				}

				

		
		
	}

	void PlayerControl::initializaKeyBindings()
	{

		

		_keyBindings[sf::Joystick::X] = Action::MoveLeft;
		
		//_keyBindings[sf::Joystick::Y] = Action::MoveUp;
		/*_keyBindings[sf::Keyboard::Left]	= Action::MoveLeft;
		_keyBindings[sf::Keyboard::Right]	= Action::MoveRight;
		_keyBindings[sf::Keyboard::Up]		= Action::MoveUp;
		_keyBindings[sf::Keyboard::Down]	= Action::MoveDown;*/
	}

	void PlayerControl::initializaActionBindings()
	{
		const float playerSpeed = 200.f;

		_actionBindings[Action::MoveLeft].action		= derivedAction<Character>(AircraftMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action		= derivedAction<Character>(AircraftMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action			= derivedAction<Character>(AircraftMover(0, -1000.f));
		
		/*_actionBindings[Action::MoveLeft].action = derivedAction<Character>(AircraftMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action = derivedAction<Character>(AircraftMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action = derivedAction<Character>(AircraftMover(0.f, -playerSpeed));
		_actionBindings[Action::MoveDown].action = derivedAction<Character>(AircraftMover(0.f, playerSpeed));*/


		for (auto& pair : _actionBindings)
		{
			pair.second.category = Category::PlayerCharacterOne;
		}
	
	}


	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::Move:
		case Action::MoveLeft:
		case Action::MoveRight:
			return true;
		case Action::MoveUp:
			return false;
		default:
			return false;
		}
	}
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_missionStatus = status;
	}
	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}
}


