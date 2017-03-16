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
		_sprite(TextureHolder::getInstance().get(table.at(type).texture))
	{
		centerOrigin(_sprite);
		
	}

	

	void Projectile::guideTowards(sf::Vector2f position)
	{
		/*assert(isGuided());
		_targerDirection = unitVector(position - getWorldPosition());*/
	}

	unsigned int Projectile::getCategory() const
	{
		switch (_type)		
		{
		case Type::AnaBullet:
			return Category::EnemyProjectile;
			break;
		default:
			assert(0);
			return Category::None;
			break;
		}	
	}


	void Projectile::updateCurrent(sf::Time dt, CommandeQueue& commands)
	{		
		/*if (isGuided())
		{
			
			sf::Vector2f newVelocity = unitVector( table.at(_type).approachRate * dt.asSeconds() * _targerDirection + getVelocity());
			setVelocity( newVelocity * getMaxSpeed());
			setRotation(arctan2(newVelocity.x, newVelocity.y * -1));
		}*/
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