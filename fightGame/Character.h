#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "SFML\Graphics.hpp"
#include "Command.h"
#include "CommandeQueue.h"
#include "Animation.h"
#include "Category.h"
#include "MusicPlayer.h"
#include "Projectile.h"

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
			Dead,
			Block
		};

	public:
		Character(Type type, Category::Type category);

		unsigned int									getCategory() const override;
		float											getMaxSpeed() const;
		sf::FloatRect									getBoundingRect() const override;
		void											setHealth();
		int												getHealth()const;
		bool											isStateJump();
		void											move(float x, float y);
		void											fire();
		void											jump();
		void											attack();
		void											block();
		bool											isMovingRight() const;
		bool											isMovingLeft();
		void											setState(State state);

	private:
		void											drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		
		void											movementUpdate(sf::Time dt);
		virtual void									updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void											calculateHealth()const ;
		void											checkProjectileLaunch(sf::Time dt, CommandeQueue& commands);
		void											checkJumping(CommandeQueue& commands);
		void											checkRunning(CommandeQueue& commands);
		void											checkAttack(CommandeQueue& commands);
		void											playLocalSound(CommandeQueue & commands, SoundEffectID effect);
		void											playLocalSoundRunning(CommandeQueue& commands, SoundEffectID effect);
		void											stopLocalSoundRunning(CommandeQueue& commands, SoundEffectID effect);
		void											createBullets(SceneNode& node, Projectile::Type type, float xOffSet, float yOffSet) const;

	private:
		Type											_type;
		sf::Sprite										_sprite;
		State											_state;
		int												_dirrectionIndex;
		bool											_moveRight;
		bool											_moveLeft;
		bool											_isFiring;
		bool											_isJumping;
		bool											_isAttacking;
		bool											_isRunningSoungPlay;
		bool											_isRunningSoungStop;
		MusicPlayer										_musicRunning;
		sf::Time										_fireCountdown;
		Command											_fireCommand;
		std::size_t										_fireRateLevel;
		Category::Type									_category;
		int												_health;
		sf::RectangleShape								_healthBarMaxHealth;
		mutable sf::RectangleShape						_healthBarCurrentHealth;

		std::map<State, std::unique_ptr<Animation>>		_animations;
	};
}

