#include "Character.h"
#include "Category.h"
#include "DataTables.h"
#include "Utility.h"
#include <memory>
#include "JsonFrameParser.hpp"



namespace GEX
{
	const std::map<Character::Type, CharacterData> table = initializeCharacterData();
	const std::map<Projectile::Type, ProjectileDate> tableProjectil = initializeProjectileDate();
	const int HEIGHT = 151;
	const int WIDTH = 151;
	const float GRAVITY = 8;

	Character::Character(Type type) :
		Entity(),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), sf::IntRect(0,0,HEIGHT, WIDTH)),
		_state(State::Idle),
		_moveRight(false),
		_isFiring(false),
		_fireRateLevel(1),
		_fireCountdown(sf::Time::Zero)
		
	{
		centerOrigin(_sprite);

		JsonFrameParser frame("../Media/Textures/AnaAtlas.json");

		// set up animation for the idel state

		_animations[State::Idle] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Idle]->addFrameSet(frame.getFramesFor("Idle"));
		_animations[State::Idle]->setDurationAsSeconds(0.8f);

		_animations[State::Run] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Run]->addFrameSet(frame.getFramesFor("Run"));
		_animations[State::Run]->setDurationAsSeconds(0.8f);

		_animations[State::Dead] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Dead]->addFrameSet(frame.getFramesFor("Dead"));
		_animations[State::Dead]->setDurationAsSeconds(0.8f);

		_animations[State::Jump] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Jump]->addFrameSet(frame.getFramesFor("Jump"));
		_animations[State::Jump]->setDurationAsSeconds(1.f);

		_animations[State::Melee] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Melee]->addFrameSet(frame.getFramesFor("Melee"));
		_animations[State::Melee]->setDurationAsSeconds(0.8f);

		_animations[State::Shoot] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Shoot]->addFrameSet(frame.getFramesFor("Shoot"));
		_animations[State::Shoot]->setDurationAsSeconds(0.7f);	


	}

	unsigned int Character::getCategory() const
	{
		return Category::PlayerCharacterOne;
	}

	float Character::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	sf::FloatRect Character::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	bool Character::isStateJump()
	{
		if (_state == State::Jump)
			return true;
		else
			return false;
	}

	void Character::move(float x, float y)
	{
		std::cerr << "Vy: " << getVelocity().y << std::endl;
		// rotate the sprite dependent of the dirrection the user chose

		if (x < -15)
		{
			// if the state is in shoot we don't wont to change the direction of the charater
			if (_state != State::Shoot)
			{
				// facing left
				this->setScale({ -1, 1 });
				_moveRight = false;
				_moveLeft = true;
				if (_state != State::Jump && this->getVelocity().y == GRAVITY)
				{
					_state = State::Run;
					this->setVelocity(x, GRAVITY);
				}

				if (_state == State::Jump)
				{
					this->setVelocity(x, getVelocity().y);
				}
				if (_state == State::Run)
					this->setVelocity(x, GRAVITY);
			}

		}

		else if (x > 15)
		{
			
			// if the state is in shoot we don't wont to change the direction of the charater
			if (_state != State::Shoot)
			{
				// facing right
				this->setScale({ 1, 1 });
				_moveRight = true;
				_moveLeft = false;

				if (_state == State::Run)
					this->setVelocity(x, GRAVITY);

				else if (_state != State::Jump && this->getVelocity().y == GRAVITY)
				{
					_state = State::Run;
					this->setVelocity(x, GRAVITY);
				}

				else if (_state == State::Jump)
				{
					this->setVelocity(x, getVelocity().y);
				}
			}

		}		

		// wen the player don't touche anythink on the controller get in the idel state
		else if (x == 0 && y == 0)
		{
			if (_state != State::Jump && _state != State::Shoot && _state != State::Melee)
			{
				this->setVelocity(x, this->getVelocity().y);
				_state = State::Idle;
			}
		}
				
		std::cerr << "Vy: " << getVelocity().y << std::endl;
		
	}

	void Character::fire()
	{
		if (_state == State::Idle || _state == State::Run)
		{			
			if (_fireCountdown <= sf::Time::Zero)
			{
				this->setVelocity(0, GRAVITY);
				_isFiring = true;
				_animations[State::Shoot]->start();
				_state = State::Shoot;
			}
		}
	}

	void Character::jump()
	{
		if (_state == State::Run || _state == State::Idle)
		{
			_state = State::Jump;
			_animations[State::Jump]->start();
			this->accelerate(this->getVelocity().x, -380.f);
		}
	}

	void Character::attack()
	{
		if (_state == State::Run || _state == State::Idle)
		{
			this->setVelocity(0, GRAVITY);
			_state = State::Melee;
			_animations[State::Melee]->start();
		}
	}



	bool Character::isMovingRight()
	{
		return _moveRight;
	}

	bool Character::isMovingLeft()
	{
		return _moveLeft;
	}

	void Character::setState(State state)
	{
		_state = state;
	}

	void Character::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Character::movementUpdate(sf::Time dt)
	{
		if (_state == State::Jump)
		{			
			if(_animations[_state]->getNumberOfCurrentFrame() < _animations[_state]->getNumberOfFrames())
				_sprite.setTextureRect(_animations.at(_state)->update(dt));	
		}	

		else if (_state == State::Shoot)
		{
			if (_animations[_state]->getNumberOfCurrentFrame() < _animations[_state]->getNumberOfFrames())
				_sprite.setTextureRect(_animations.at(_state)->update(dt));			

			if (_animations[_state]->getNumberOfCurrentFrame() == _animations[_state]->getNumberOfFrames() - 1)
				_state = State::Idle;		
		}

		else if (_state == State::Melee)
		{
			if (_animations[_state]->getNumberOfCurrentFrame() < _animations[_state]->getNumberOfFrames())
				_sprite.setTextureRect(_animations.at(_state)->update(dt));

			if (_animations[_state]->getNumberOfCurrentFrame() == _animations[_state]->getNumberOfFrames() - 1)
				_state = State::Idle;
		}

		else if (this->getVelocity().y > GRAVITY)
		{
			_sprite.setTextureRect(_animations.at(State::Jump)->getFrameByNumber(_animations.at(State::Jump)->getNumberOfFrames() - 1));
		}

		else 		
			_sprite.setTextureRect(_animations.at(_state)->update(dt));

	}

	void Character::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		sf::Vector2f velocity = getVelocity();
		
		if (_state == State::Jump)
		{
			this->accelerate(0, GRAVITY);
		}
		else if (_state == State::Idle)
		{
			this->accelerate(velocity.x, GRAVITY); 
		}
		

		movementUpdate(dt);
		checkProjectileLaunch(dt, commands);
		Entity::updateCurrent(dt, commands);
	}
	void Character::checkProjectileLaunch(sf::Time dt, CommandeQueue & commands)
	{
		//fire();
		if (_isFiring && _fireCountdown <= sf::Time::Zero)
		{
			//commands.push(_fireCommand);
			//playLocalSound(commands, isAllied() ? SoundEffectID::AlliedGunFire : SoundEffectID::EnemyGunFire);
			_isFiring = false;
			_fireCountdown += table.at(_type).fireInterval / (_fireRateLevel + 1.f);			
		}
		else if (_fireCountdown >= sf::Time::Zero)
		{
			_fireCountdown -= dt;
			_isFiring = false;			
		}
	}
}
