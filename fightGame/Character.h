#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "SFML\Graphics.hpp"
#include "Command.h"
#include "CommandeQueue.h"
#include "Animation.h"
#include "Category.h"

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
		Character(Type type, Category::Type category);

		unsigned int									getCategory() const override;
		float											getMaxSpeed() const;
		sf::FloatRect									getBoundingRect() const override;
		bool											isStateJump();
		void											move(float x, float y);
		void											fire();
		void											jump();
		void											attack();
		bool											isMovingRight();
		bool											isMovingLeft();
		void											setState(State state);

	private:
		void											drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		void											movementUpdate(sf::Time dt);
		virtual void									updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void											checkProjectileLaunch(sf::Time dt, CommandeQueue& commands);

	private:
		Type											_type;
		sf::Sprite										_sprite;
		State											_state;
		int												_dirrectionIndex;
		bool											_moveRight;
		bool											_moveLeft;
		bool											_isFiring;
		sf::Time										_fireCountdown;
		Command											_fireCommand;
		std::size_t										_fireRateLevel;
		Category::Type									_category;

		std::map<State, std::unique_ptr<Animation>>		_animations;
	};
}

