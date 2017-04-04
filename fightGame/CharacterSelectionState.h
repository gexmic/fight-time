#pragma once
#include "State.h"
#include "World.h"
#include "SFML/Graphics/Text.hpp"


namespace GEX
{
	class CharacterSelectionState : public State
	{
	

	public:
		CharacterSelectionState(StateStack& stack, Context context);

		virtual void				draw();
		virtual bool				update(sf::Time dt);
		virtual bool				handleEvent(const sf::Event& event);

		void						updateOptionText();

	private:
		enum CharacterSelectedName
		{
			Ana,
			NinjaBoy,
			Robot,
			Knight,
			NinjaGirl
		};


	private:
		sf::Sprite					_backgroundSprite;
		sf::Text					_playerSelection;
		sf::Text					_pressEnterToSelect;
		sf::Text					_pressEscToGoBack;
		bool						_isPlayerOneAsSelectCharacter;
		int							_playerOneCharaterIndex;
		Context						_context;
		std::vector<sf::Text>		_texts;
 		std::vector<sf::Sprite>		_characters;
		std::size_t					_characterIndex;

	};
	
}

