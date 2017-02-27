/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This class is for all the command that the player could do in the game for moving the plane and navigate to the menu. Also later
have the control for bullet and missel.

*/

#pragma once
#include "SFML\Graphics.hpp"
#include "CommandeQueue.h"
#include "Command.h"
#include <map>

namespace GEX
{
	enum class Action
	{
		Move,
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		FireBullet,
		launchMissile
	};

	enum class MissionStatus
	{
		Active,
		Success,
		Fail
	};

	class PlayerControl
	{
	public:
												PlayerControl();
		
		void									handleEvent(const sf::Event& event, CommandeQueue& commands);
		void									handleRealTimeInput(CommandeQueue& commands);
        void									setMissionStatus(MissionStatus status);
		MissionStatus							getMissionStatus()const;
	private:
		void									initializaKeyBindings();
		void									initializaActionBindings();
		bool									isRealTimeAction(Action action);
		

	private:
		//std::map<sf::Event::JoystickMoveEvent, Action>		_keyBindings;
		std::map<sf::Joystick::Axis, Action>		_keyBindings;
		//std::map<sf::Keyboard::Key, Action>		_keyBindings;
		std::map<Action, Command>				_actionBindings;
		MissionStatus							_missionStatus;
	};

}

