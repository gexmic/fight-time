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
	struct PlayerMover
	{
		PlayerMover(float vx, float vy) : velocity(vx, vy)
		{}
		void operator() (Character& character, sf::Time dt) const
		{
			character.move(velocity.x, velocity.y);
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
			commands.push(_actionBindings[sf::Joystick::isButtonPressed, Action::Jump]);
		}

		if (sf::Joystick::isButtonPressed(1, 1))
		{
			commands.push(_actionBindings[sf::Joystick::isButtonPressed, Action::FireBullet]);
		}
		if (sf::Joystick::isButtonPressed(1, 2))
		{
			commands.push(_actionBindings[sf::Joystick::isButtonPressed, Action::meleeAttack]);
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
				else if (speed.x > 15.f)
				{
					commands.push(_actionBindings[sf::Joystick::Axis::X, Action::MoveRight]);
				}
				
				else 
					commands.push(_actionBindings[sf::Joystick::Axis::X, Action::MoveIdel]);
				

		
		
	}

	void PlayerControl::initializaKeyBindings()
	{

		

		//_keyBindings[sf::Joystick::X] = Action::MoveLeft;
		//_keyBindings[sf::Joystick::Y] = Action::MoveUp;
		/*_keyBindings[sf::Keyboard::Left]	= Action::MoveLeft;
		_keyBindings[sf::Keyboard::Right]	= Action::MoveRight;
		_keyBindings[sf::Keyboard::Up]		= Action::MoveUp;
		_keyBindings[sf::Keyboard::Down]	= Action::MoveDown;*/
	}

	void PlayerControl::initializaActionBindings()
	{
		const float playerSpeed = 200.f;

		_actionBindings[Action::MoveLeft].action		= derivedAction<Character>(PlayerMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action		= derivedAction<Character>(PlayerMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveIdel].action		= derivedAction<Character>(PlayerMover(0, 0));
		_actionBindings[Action::Jump].action			= derivedAction<Character>([](Character& a, sf::Time& dt) {a.jump(); });
		_actionBindings[Action::FireBullet].action		= derivedAction<Character>([](Character& a, sf::Time& dt) {a.fire(); });
		_actionBindings[Action::meleeAttack].action		= derivedAction<Character>([](Character& a, sf::Time& dt) {a.attack(); });
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
		case Action::MoveIdel:
			return true;			
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


