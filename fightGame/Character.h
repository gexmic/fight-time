#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "SFML\Graphics.hpp"
#include "Command.h"
#include "CommandeQueue.h"
#include "Animation.h"

namespace GEX
{
	class Character : public Entity
	{
	public:
		enum Type{
			// ana Adventure girl, sir thomas wale Knight, brain eater men zombie
			// Fungi girl zombie, Azerty robot, Zumo men ninja, Katoka girl ninja
			// Sante santa, and Jack halloween
			Ana,
			SirThomasWale,
			BrainEater,
			Fungi,
			Azerty,
			Zumo,
			Katoka,
			Santa,
			Jack
		};
		
		enum State{
			Idle,
			Jump,
			Melee,
			Shoot,
			Run,			
			Dead
		};

	public:
		Character(Type type = Type::Ana);

		unsigned int									getCategory() const override;
		float											getMaxSpeed() const;
		sf::FloatRect									getBoundingRect() const override;
		void											move(float x, float y);
		bool											isMovingRight();
		bool											isMovingLeft();
	private:
		void											drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		void											movementUpdate(sf::Time dt);
		virtual void									updateCurrent(sf::Time dt, CommandeQueue& commands) override;


	private:
		Type											_type;
		sf::Sprite										_sprite;
		State											_state;
		int												_dirrectionIndex;
		bool											_moveRight;
		bool											_moveLeft;

		std::map<State, std::unique_ptr<Animation>>		_animations;
	};
}

