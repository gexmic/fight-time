#include "Character.h"
#include "Category.h"
#include "DataTables.h"
#include "Utility.h"
#include <memory>
#include "JsonFrameParser.hpp"



namespace GEX
{
	const std::map<Character::Type, CharacterData> table = initializeCharacterData();
	const int HEIGHT = 151;
	const int WIDTH = 151;
	const float GRAVITY = 400;

	Character::Character(Type type) :
		Entity(),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), sf::IntRect(0,0,HEIGHT, WIDTH)),
		_state(State::Idle),
		_moveRight(false)
	{
		centerOrigin(_sprite);

		JsonFrameParser frame("../Media/Textures/AnaAtlas.json");

		// set up animation for the idel state

		_animations[State::Idle] = std::unique_ptr<Animation>(new Animation(true));
		_animations[State::Idle]->addFrameSet(frame.getFramesFor("Run"));
		_animations[State::Idle]->setDurationAsSeconds(0.8f);
		
		_animations[State::Idle]->start();
		
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

	void Character::move(float x, float y)
	{
		// rotate the sprite dependent of the dirrection the user chose
		if (x < 0)
		{
			// going left
			this->setScale({ -1, 1 });
			_moveRight = false;
			_moveLeft = true;
		}

		else if (x > 0)
		{
			// going right
			this->setScale({ 1, 1 });
			_moveRight = true;
			_moveLeft = false;
		}
		
		this->setVelocity(x,y);
	}

	bool Character::isMovingRight()
	{
		return _moveRight;
	}

	bool Character::isMovingLeft()
	{
		return _moveLeft;
	}

	void Character::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Character::movementUpdate(sf::Time dt)
	{
		_sprite.setTextureRect(_animations.at(_state)->update(dt));

	}

	void Character::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		sf::Vector2f velocity = getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			setVelocity(velocity / std::sqrt(2.f));

		this->accelerate(0, GRAVITY);

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}
}
