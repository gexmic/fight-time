#include "Character.h"
#include "Category.h"
#include "DataTables.h"
#include "SoundNode.h"
#include "Command.h"
#include "Utility.h"
#include <memory>
#include "JsonFrameParser.hpp"
#include "SFML\Audio\Music.hpp"

namespace GEX
{
	const std::map<Character::Type, CharacterData> table = initializeCharacterData();
	const std::map<Projectile::CharacterTypeBullet, ProjectileDate> tableProjectil = initializeProjectileDate();
	const int HEIGHT = 151;
	const int WIDTH = 151;
	const float GRAVITY = 8;
	const int MAXHEALTH = 300;
	const int JUMP = -500;

	Character::Character(Type type, Category::Type category) :
		Entity(table.at(type).health),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).location),
		_state(State::Idle),
		_moveRight(false),
		_isFiring(false),
		_fireRateLevel(1),
		_fireCountdown(sf::Time::Zero),
		_category(category),
		_isRunningSoungPlay(false),
		_isRunningSoungStop(false),
		_isAttacking(false)

	{
		centerOrigin(_sprite);

		_fireCommand.category = Category::SceneGroundLayer;
		_fireCommand.action = [this](SceneNode& node, sf::Time)
		{
			if (_type == Type::Ana)
				this->createBullets(node);
			if (_type == Type::Azerty)
				this->createBullets(node);
			if (_type == Type::Katoka || _type == Type::Fungi)
				this->createBullets(node);
		};

		std::string caracter;
		if (_type == Type::Ana)
		{
			caracter = "AnaAtlas";
			_characterTypeBullet = Projectile::CharacterTypeBullet::AnaBullet;
		}
		else if (_type == Type::Azerty)
		{
			caracter = "RobotAtlas";
			_characterTypeBullet = Projectile::CharacterTypeBullet::RobotBullet;
		}
		else if (_type == Type::SirThomasWale)
			caracter = "KnightAtlas";
		else if (_type == Type::Katoka)
		{
			caracter = "NinjaAtlas";
			_characterTypeBullet = Projectile::CharacterTypeBullet::NinjaBullet;
		}
		else if (_type == Type::Fungi)
		{
			caracter = "NinjaGirlAtlas";
			_characterTypeBullet = Projectile::CharacterTypeBullet::NinjaBullet;
		}

		JsonFrameParser frame("../Media/Textures/" + caracter + ".json");



		// set up animation for the idel state

		_animations[State::Idle] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Idle]->addFrameSet(frame.getFramesFor("Idle"));
		_animations[State::Idle]->setDurationAsSeconds(0.8f);

		_animations[State::Run] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Run]->addFrameSet(frame.getFramesFor("Run"));
		_animations[State::Run]->setDurationAsSeconds(0.8f);

		_animations[State::Dead] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Dead]->addFrameSet(frame.getFramesFor("Dead"));
		_animations[State::Dead]->setDurationAsSeconds(1.f);

		_animations[State::Jump] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Jump]->addFrameSet(frame.getFramesFor("Jump"));
		_animations[State::Jump]->setDurationAsSeconds(1.f);

		_animations[State::Melee] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Melee]->addFrameSet(frame.getFramesFor("Melee"));
		_animations[State::Melee]->setDurationAsSeconds(0.8f);

		_animations[State::Shoot] = std::unique_ptr<Animation>(new Animation(false));
		_animations[State::Shoot]->addFrameSet(frame.getFramesFor("Shoot"));
		_animations[State::Shoot]->setDurationAsSeconds(0.7f);

		_animations[State::Block] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Block]->addFrameSet(frame.getFramesFor("Block"));
		_animations[State::Block]->setDurationAsSeconds(5.f);

		if (_category == Category::PlayerCharacterOne)
			_moveRight = true;
		else
			_moveLeft = true;

		if (_category == Category::PlayerCharacterOne)
		{
			_healthBarMaxHealth.setSize(sf::Vector2f(MAXHEALTH, 25));
			_healthBarMaxHealth.setPosition(sf::Vector2f(100, 50));
			_healthBarMaxHealth.setFillColor(sf::Color::Red);
			_healthBarMaxHealth.setOutlineColor(sf::Color::Black);
			_healthBarMaxHealth.setOutlineThickness(2);

			_healthBarCurrentHealth.setSize(sf::Vector2f(getHitPoint(), 25));
			_healthBarCurrentHealth.setPosition(sf::Vector2f(100, 50));
			_healthBarCurrentHealth.setFillColor(sf::Color::Green);
		}
		if (_category == Category::PlayerCharacterTwo)
		{
			_healthBarMaxHealth.setSize(sf::Vector2f(MAXHEALTH, 25));
			_healthBarMaxHealth.setPosition(sf::Vector2f(860, 50));
			_healthBarMaxHealth.setFillColor(sf::Color::Green);
			_healthBarMaxHealth.setOutlineColor(sf::Color::Black);
			_healthBarMaxHealth.setOutlineThickness(2);

			_healthBarCurrentHealth.setSize(sf::Vector2f(getHitPoint(), 25));
			_healthBarCurrentHealth.setPosition(sf::Vector2f(860, 50));
			_healthBarCurrentHealth.setFillColor(sf::Color::Red);
		}

	}

	unsigned int Character::getCategory() const
	{
		return _category;
	}

	float Character::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	sf::FloatRect Character::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}



	int Character::getHealth() const
	{
		return getHitPoint();
	}

	int Character::getAttackDamage() const
	{
		return table.at(_type).attackDamage;
	}

	bool Character::isStateAttack() const
	{
		if (_state == State::Melee)
			return true;
		else
			return false;
	}



	bool Character::isStateJump()const
	{
		if (_state == State::Jump)
			return true;
		else
			return false;
	}

	bool Character::isAttack() const
	{
		return _isAttacking;
	}

	void Character::move(float x, float y)
	{
		//std::cerr << "Vy: " << getVelocity().y << std::endl;
		// rotate the sprite dependent of the dirrection the user chose

		if (x < -15 && _state != State::Block)
		{
			// if the state is in shoot we don't wont to change the direction of the charater
			if (_state != State::Shoot && _state != State::Dead && _state != State::Block)
			{
				// facing left
				this->setScale({ -1, 1 });
				_moveRight = false;
				_moveLeft = true;
				_isRunningSoungStop = false;

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
				{
					this->setVelocity(x, GRAVITY);
					this->accelerate(0, GRAVITY);
				}
			}
		}

		else if (x > 15)
		{

			// if the state is in shoot we don't wont to change the direction of the charater
			if (_state != State::Shoot || _state != State::Dead && _state != State::Block)
			{
				// facing right
				this->setScale({ 1, 1 });
				_moveRight = true;
				_moveLeft = false;
				_isRunningSoungStop = false;

				if (_state != State::Jump && this->getVelocity().y == GRAVITY)
				{
					_state = State::Run;
					this->setVelocity(x, GRAVITY);
				}

				else if (_state == State::Jump)
				{
					this->setVelocity(x, getVelocity().y);
				}

				if (_state == State::Run)
				{
					this->setVelocity(x, GRAVITY);
					this->accelerate(0, GRAVITY);
				}
			}

		}

		// wen the player don't touche anythink on the controller get in the idel state
		else if (x == 0 && y == 0)
		{
			if (_state != State::Jump && _state != State::Shoot && _state != State::Melee && _state != State::Dead)
			{
				this->setVelocity(x, this->getVelocity().y);
				_state = State::Idle;
				_isRunningSoungStop = true;
			}
		}

		//std::cerr << "Vy: " << getVelocity().y << std::endl;

	}

	void Character::fire()
	{
		if (_state != State::Dead)
		{
			if (_state == State::Idle || _state == State::Run)
			{
				if (_fireCountdown <= sf::Time::Zero)
				{
					this->setVelocity(0, GRAVITY);
					_isFiring = true;
					_animations[State::Shoot]->start();
					_state = State::Shoot;
					_isRunningSoungStop = true;
				}
			}
		}
	}

	void Character::jump()
	{
		if (_state != State::Dead)
		{
			if (_state == State::Run || _state == State::Idle)
			{
				_state = State::Jump;
				_animations[State::Jump]->start();
				this->accelerate(0, JUMP);
				_isJumping = true;
				_isRunningSoungStop = true;
			}
		}
	}

	void Character::attack()
	{
		if (_state != _state != State::Dead)
			if (_state == State::Run || _state == State::Idle)
			{
				this->setVelocity(0, GRAVITY);
				_state = State::Melee;
				_animations[State::Melee]->start();
				_isAttacking = true;
				_isRunningSoungStop = true;
			}
	}

	void Character::block()
	{
		if (_state != State::Dead)
			if (_state == State::Idle || _state == State::Run)
			{
				this->setVelocity(0, GRAVITY);
				_state = State::Block;
				_isRunningSoungStop = true;
			}
	}



	bool Character::isMovingRight() const
	{
		return _moveRight;
	}

	bool Character::isMovingLeft()
	{
		return _moveLeft;
	}

	bool Character::isPayerOne() const
	{
		return _category == Category::Type::PlayerCharacterOne;
	}

	bool Character::isBlocking() const
	{
		if (_state == State::Block)
			return true;
		else
			return false;
	}

	void Character::setState(State state)
	{
		_state = state;
	}

	

	int Character::getNumberofLost()
	{
		return _roundLost;
	}

	bool Character::roundFinished()
	{
		return _isRoundFinich;
	}

	bool Character::isMarkedForRemoval() const
	{
		return false;
	}

	void Character::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		if (_category == Category::PlayerCharacterTwo)
		{
			target.draw(_healthBarMaxHealth);
			target.draw(_healthBarCurrentHealth);
		}
		else
		{
			target.draw(_healthBarMaxHealth);
			target.draw(_healthBarCurrentHealth);
		}
		target.draw(_sprite, state);
	}



	void Character::movementUpdate(sf::Time dt)
	{
		if (_state == State::Jump)
		{
			if (_animations[_state]->getNumberOfCurrentFrame() < _animations[_state]->getNumberOfFrames())
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
		else if (_state == State::Block)
		{
			_sprite.setTextureRect(_animations.at(_state)->update(dt));
		}
		else if (_state == State::Dead )
		{
			if (_animations[_state]->getNumberOfCurrentFrame() < _animations[_state]->getNumberOfFrames())
				_sprite.setTextureRect(_animations.at(_state)->update(dt));
			
			if (_animations[_state]->getNumberOfCurrentFrame() == _animations[_state]->getNumberOfFrames() - 1)
			{
				_isRoundFinich = true; 
				_roundLost = _roundLost + 1;
			}
		}

		else if (this->getVelocity().y > GRAVITY)
		{
			_sprite.setTextureRect(_animations.at(State::Jump)->getFrameByNumber(_animations.at(State::Jump)->getNumberOfFrames() - 1));
			_state = State::Jump;
			_isRunningSoungStop = true;
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

		if (this->getHealth() <= 0 && _state != State::Jump)
		{
			_state = State::Dead;
			
		}


		movementUpdate(dt);
		checkRunning(commands);
		checkProjectileLaunch(dt, commands);
		checkAttack(commands);
		checkJumping(commands);
		calculateHealth();
		Entity::updateCurrent(dt, commands);
	}
	void Character::calculateHealth() const
	{
		double health = getHitPoint();
		if (health < 0)
			health = 0;
		if (_category == Category::PlayerCharacterTwo)
		{
			_healthBarCurrentHealth.setSize(sf::Vector2f(MAXHEALTH - health, 25));
		}
		else
			_healthBarCurrentHealth.setSize(sf::Vector2f(health, 25));
	}
	void Character::checkProjectileLaunch(sf::Time dt, CommandeQueue & commands)
	{
		if (_isFiring && _fireCountdown <= sf::Time::Zero)
		{
			commands.push(_fireCommand);
			playLocalSound(commands, table.at(_type).soundEffectShot);
			_isFiring = false;
			_fireCountdown += table.at(_type).fireInterval / (_fireRateLevel + 1.f);
		}
		else if (_fireCountdown >= sf::Time::Zero)
		{
			_fireCountdown -= dt;
			_isFiring = false;
		}
	}

	void Character::checkJumping(CommandeQueue & commands)
	{
		if (_isJumping)
		{
			//commands.push(_fireCommand);
			playLocalSound(commands, SoundEffectID::AnaJump);
			_isJumping = false;
		}
	}

	void Character::checkRunning(CommandeQueue & commands)
	{
		if (_state == State::Run)
		{
			if (_isRunningSoungPlay == false)
			{
				playLocalSoundRunning(commands, SoundEffectID::Run);
				_isRunningSoungPlay = true;
			}
		}

		if (_isRunningSoungStop == true && _isRunningSoungPlay == true)
		{
			stopLocalSoundRunning(commands, SoundEffectID::Run);
			_isRunningSoungPlay = false;
			_isRunningSoungStop = false;
		}
	}

	void Character::checkAttack(CommandeQueue & commands)
	{
		if (_isAttacking)
		{
			playLocalSound(commands, SoundEffectID::AnaSword);
			_isAttacking = false;
		}
	}

	void Character::playLocalSound(CommandeQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffet;
		command.action = derivedAction<SoundNode>([effect, worldPosition](SoundNode& node, sf::Time)
		{node.playSound(effect, worldPosition); });
		commands.push(command);
	}
	void Character::playLocalSoundRunning(CommandeQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffet;
		command.action = derivedAction<SoundNode>([effect, worldPosition](SoundNode& node, sf::Time)
		{node.playSoundLoop(effect, worldPosition); });
		commands.push(command);
	}
	void Character::stopLocalSoundRunning(CommandeQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffet;
		command.action = derivedAction<SoundNode>([effect, worldPosition](SoundNode& node, sf::Time)
		{node.stopSound(effect); });
		commands.push(command);
	}
	void Character::createProjectile(SceneNode& node, Projectile::Type type, float xOffSet, float yOffSet) const
	{
		// node is the ScreenAirLayer node that the command was targeted to
		std::unique_ptr<Projectile> projectile(new Projectile(type, _characterTypeBullet));

		sf::Vector2f offset(40, -5);
		sf::Vector2f velocity(projectile->getMaxSpeed(), 0);
		float sign = isMovingRight() ? 1.f : -1.f;
		projectile->setPosition(getWorldPosition() + offset * sign);
		if (_moveRight)
			projectile->setVelocity(velocity);
		else if (_moveLeft)
		{
			projectile->scale(-1, 1);
			projectile->setVelocity(-velocity);
		}
		node.attachChild(std::move(projectile));
	}

	void Character::createBullets(SceneNode & node) const
	{
		Projectile::Type type = isPayerOne() ? Projectile::Type::playerOneBullet : Projectile::Type::playerTwoBullet;

		if(_moveRight)
			createProjectile(node, type, 40, -5);
		else
			createProjectile(node, type, 40, -5);
	}
}
