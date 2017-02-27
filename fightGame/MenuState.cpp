/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Menu state class

*/

#include "MenuState.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\View.hpp"
#include "Utility.h"
#include "MusicPlayer.h"



namespace GEX
{
	MenuState::MenuState(StateStack& stack, Context context) :
		State(stack, context),
		_options(),
		_optionIndex(0)
	{
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::MenuScreen);
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);

		_backgroundSprite.setTexture(texture);

		sf::Text playOption;
		playOption.setFont(font);
		playOption.setString("play");
		centerOrigin(playOption);
		playOption.setPosition(context.window->getView().getSize() / 2.f);
		_options.push_back(playOption);

		sf::Text exitOption;
		exitOption.setFont(font);
		exitOption.setString("Exit");
		centerOrigin(exitOption);
		exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
		_options.push_back(exitOption);

		context.music->play(MusicID::MenuTheme);
		updateOptionText();
	}

	void MenuState::draw()
	{
		sf::RenderWindow& window = *getContext().window;

		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);

		for (const sf::Text& text : _options)
			window.draw(text);
	}

	bool MenuState::update(sf::Time dt)
	{
		return true;
	}

	bool MenuState::handleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::Return)
		{
			if (_optionIndex == Play)
			{
				requestStackPop();
				requestStackPush(StateID::Game);
			}
			else if (_optionIndex == Exit)
			{
				requestStackPop();
			}
		}

			else if (event.key.code == sf::Keyboard::Up)
			{
				if (_optionIndex > 0)
					_optionIndex--;
				else
					_optionIndex = _options.size() - 1;
				updateOptionText();
			}

			else if (event.key.code == sf::Keyboard::Down)
			{
				if (_optionIndex < _options.size() - 1)
					_optionIndex++;
				else
					_optionIndex = 0;

				updateOptionText();
			}

		return false;
	}

	void MenuState::updateOptionText()
	{
		if (_options.empty())
			return;

		for (sf::Text& text : _options)
			text.setFillColor(sf::Color::White);

		_options[_optionIndex].setFillColor(sf::Color::Red);
	}
}