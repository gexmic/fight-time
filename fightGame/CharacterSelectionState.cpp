#include "CharacterSelectionState.h"
#include "FontHolder.h"
#include "Utility.h"



namespace GEX
{
	CharacterSelectionState::CharacterSelectionState(StateStack & stack, Context context) :
		State(stack, context),
		_characters(),
		_characterIndex(0),
		_playerOneCharaterIndex(NULL),
		_context(context)
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		

		sf::Vector2f windowSize = context.window->getView().getSize();


		_playerSelection.setFont(font);
		_playerSelection.setString("Player One Select you Fighter");
		centerOrigin(_playerSelection);
		_playerSelection.scale(2, 2);
		_playerSelection.setOutlineThickness(2);
		_playerSelection.setOutlineColor(sf::Color::Red);
		_playerSelection.setPosition(windowSize.x / 2, windowSize.y / 6);

		_pressEnterToSelect.setFont(font);
		_pressEnterToSelect.setString("Press enter to select your character");
		centerOrigin(_pressEnterToSelect);
		_pressEnterToSelect.scale(2, 2);
		_pressEnterToSelect.setOutlineThickness(2);
		_pressEnterToSelect.setOutlineColor(sf::Color::Red);
		_pressEnterToSelect.setPosition(windowSize.x / 2, windowSize.y / 1.25);

		_pressEscToGoBack.setFont(font);
		_pressEscToGoBack.setString("Press ESC to go back");
		centerOrigin(_pressEscToGoBack);
		_pressEscToGoBack.scale(2, 2);
		_pressEscToGoBack.setOutlineThickness(2);
		_pressEscToGoBack.setOutlineColor(sf::Color::Red);
		_pressEscToGoBack.setPosition(windowSize.x / 2, windowSize.y / 1.10);

		sf::Sprite ana;
		ana.setTexture(TextureHolder::getInstance().get(TextureID::Ana));
		centerOrigin(ana);
		ana.scale(0.35, 0.35);
		ana.setPosition(windowSize.x / 3.f, windowSize.y / 2.75f);
		_characters.push_back(ana);

		sf::Sprite ninjaBoy;
		ninjaBoy.setTexture(TextureHolder::getInstance().get(TextureID::NinjaBoy));
		centerOrigin(ninjaBoy);
		ninjaBoy.scale(0.38, 0.38);
		ninjaBoy.setPosition(windowSize.x / 2.f, windowSize.y / 2.75f);
		_characters.push_back(ninjaBoy);

		sf::Sprite robot;
		robot.setTexture(TextureHolder::getInstance().get(TextureID::Robot));
		centerOrigin(robot);
		robot.scale(0.35, 0.35);
		robot.setPosition(windowSize.x  / 1.50, windowSize.y / 2.75f);
		_characters.push_back(robot);

		sf::Sprite knight;
		knight.setTexture(TextureHolder::getInstance().get(TextureID::Knight));
		centerOrigin(knight);
		knight.scale(0.28, 0.25);
		knight.setPosition(windowSize.x / 2.40, windowSize.y / 1.75f);
		_characters.push_back(knight);

		sf::Sprite ninjaGirl;
		ninjaGirl.setTexture(TextureHolder::getInstance().get(TextureID::NinjaGirl));
		centerOrigin(ninjaGirl);
		ninjaGirl.scale(0.35, 0.35);
		ninjaGirl.setPosition(windowSize.x / 1.75, windowSize.y / 1.75f);
		_characters.push_back(ninjaGirl);




	}
	void CharacterSelectionState::draw()
	{
		sf::RenderWindow& window = *getContext().window;

		window.setView(window.getDefaultView());
		if (_isPlayerOneAsSelectCharacter)
			_playerSelection.setString("Player Two Select you Fighter");
		window.draw(_playerSelection);
		window.draw(_pressEnterToSelect);
		window.draw(_pressEscToGoBack);

		for (const sf::Sprite& sprite : _characters)
			window.draw(sprite);
	}
	bool CharacterSelectionState::update(sf::Time dt)
	{
		updateOptionText();
		return false;
	}
	bool CharacterSelectionState::handleEvent(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::Return)
		{
			if (_characterIndex == Ana)
			{
				if (_isPlayerOneAsSelectCharacter)
				{
					*_context.playerTwoCharacter = Character::Type::Ana;
					requestStackPop();
					requestStackPush(StateID::Round);
				}
				else
				{
					_playerOneCharaterIndex = Ana;
					*_context.playerOneCharacter = Character::Type::Ana;
					_isPlayerOneAsSelectCharacter = true;
				}
			}
			else if (_characterIndex == NinjaBoy)
			{
				if (_isPlayerOneAsSelectCharacter)
				{			
					*_context.playerTwoCharacter = Character::Type::Katoka;
					requestStackPop();
					requestStackPush(StateID::Round);
				}
				else
				{
					_playerOneCharaterIndex = NinjaBoy;
					*_context.playerOneCharacter = Character::Type::Katoka;
					_isPlayerOneAsSelectCharacter = true;
				}
			}
			else if (_characterIndex == Robot)
			{
				if (_isPlayerOneAsSelectCharacter)
				{
					*_context.playerTwoCharacter = Character::Type::Azerty;
					requestStackPop();
					requestStackPush(StateID::Round);
				}
				else
				{
					_playerOneCharaterIndex = Robot;
					*_context.playerOneCharacter = Character::Type::Azerty;
					_isPlayerOneAsSelectCharacter = true;
				}
			}
			else if (_characterIndex == Knight)
			{
				if (_isPlayerOneAsSelectCharacter)
				{
					*_context.playerTwoCharacter = Character::Type::SirThomasWale;
					requestStackPop();
					requestStackPush(StateID::Round);
				}
				else
				{
					_playerOneCharaterIndex = Knight;
					*_context.playerOneCharacter = Character::Type::SirThomasWale;
					_isPlayerOneAsSelectCharacter = true;
				}
			}
			else if (_characterIndex == NinjaGirl)
			{
				if (_isPlayerOneAsSelectCharacter)
				{
					*_context.playerTwoCharacter = Character::Type::Fungi;
					requestStackPop();
					requestStackPush(StateID::Round);
				}
				else
				{
					_playerOneCharaterIndex = NinjaGirl;
					*_context.playerOneCharacter = Character::Type::Fungi;
					_isPlayerOneAsSelectCharacter = true;
				}
			}			
		}

		else if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
			requestStackPush(StateID::Menu);
		}

		else if (event.key.code == sf::Keyboard::Right)
		{
			if (_characterIndex < _characters.size() - 1)
				_characterIndex++;
			else
				_characterIndex = 0;
		}

		else if (event.key.code == sf::Keyboard::Left)
		{
			if (_characterIndex > 0)
				_characterIndex--;
			else
				_characterIndex = _characters.size() - 1;

					
		}
		return false;
	}
	void CharacterSelectionState::updateOptionText()
	{
		if (_characters.empty())
			return;

		for (sf::Sprite& chatacter : _characters)
			chatacter.setColor(sf::Color::White);
		
		_characters[_characterIndex].setColor(sf::Color::Yellow);
		if (_isPlayerOneAsSelectCharacter)
		{
			_characters[_playerOneCharaterIndex].setColor(sf::Color::Transparent);
		}
	}
}