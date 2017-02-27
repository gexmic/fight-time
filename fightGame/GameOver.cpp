/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Pause state class

*/

#include "GameOver.h"
#include "FontHolder.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "PlayerControl.h"

#include <SFML\Graphics\/RectangleShape.hpp>
#include <SFML\Graphics\View.hpp>


namespace GEX
{
	GameOverState::GameOverState(StateStack& stack, Context context) :
		State(stack, context),
		_gameOverText(),
		_elapsedTime(sf::Time::Zero)
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f windowSize = context.window->getView().getSize();

		_gameOverText.setFont(font);
		if (context.player->getMissionStatus() == MissionStatus::Fail)
		{
			_gameOverText.setString("Mission Failed!");
		}
		else
			_gameOverText.setString("Mission Successfull");
		
		_gameOverText.setCharacterSize(100);
		centerOrigin(_gameOverText);
		_gameOverText.setPosition(0.5f * windowSize.x, 0.5f * windowSize.y);

		
	}

	void GameOverState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroudShape;
		backgroudShape.setFillColor(sf::Color(100, 0, 0, 150));
		backgroudShape.setSize(window.getView().getSize());

		window.draw(backgroudShape);
		window.draw(_gameOverText);
	}

	bool GameOverState::update(sf::Time dt)
	{
		// 3 secound countdwon timer
		_elapsedTime += dt;
		if (_elapsedTime > sf::seconds(3))
		{
			requestStateClear();
			requestStackPush(StateID::Menu);
		}
		return false;
	}

	bool GameOverState::handleEvent(const sf::Event & event)
	{
		return false;
	}
}
