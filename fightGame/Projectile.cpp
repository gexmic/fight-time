/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

airplane class

*/

#include "Projectile.h"
#include "Category.h"
#include <cassert>
#include "TextNode.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>
#include <map>
#include "EmmitterNode.h"


namespace GEX
{

	const std::map<Projectile::Type, ProjectileDate> table = initializeProjectileDate();

	Projectile::Projectile(Type type) :
		Entity(table.at(type).damege),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).location)
	{
		centerOrigin(_sprite);
		if (isGuided())
		{
			std::unique_ptr<EmmitterNode> smoke(new EmmitterNode(Particule::Type::Smoke));
			smoke->setPosition(0.f, getBoundingRect().height / 2.f);
			attachChild(std::move(smoke));

			std::unique_ptr<EmmitterNode> fire(new EmmitterNode(Particule::Type::Propellant));
			fire->setPosition(0.f, getBoundingRect().height / 2.f);
			attachChild(std::move(fire));
		}
	}

	bool Projectile::isGuided()
	{
		return _type == Type::Missile;
	}

	void Projectile::guideTowards(sf::Vector2f position)
	{
		assert(isGuided());
		_targerDirection = unitVector(position - getWorldPosition());
	}

	unsigned int Projectile::getCategory() const
	{
		switch (_type)		
		{
		case Type::EnemyBullet:
			return Category::EnemyProjectile;
			break;
		case Type::AlliedBullet:		
		case Type::Missile:
			return Category::AlliedProjectile;
			break;
		default:
			assert(0);
			return Category::None;
			break;
		}		
	}


	void Projectile::updateCurrent(sf::Time dt, CommandeQueue& commands)
	{		
		if (isGuided())
		{
			
			sf::Vector2f newVelocity = unitVector( table.at(_type).approachRate * dt.asSeconds() * _targerDirection + getVelocity());
			setVelocity( newVelocity * getMaxSpeed());
			setRotation(arctan2(newVelocity.x, newVelocity.y * -1));
		}
		Entity::updateCurrent(dt, commands);
	}

	sf::FloatRect Projectile::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}
	

	float Projectile::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}
}