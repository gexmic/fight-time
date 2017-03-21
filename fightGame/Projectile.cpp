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

	const std::map<Projectile::CharacterTypeBullet, ProjectileDate> table = initializeProjectileDate();

	Projectile::Projectile(Type type, Projectile::CharacterTypeBullet charcterTypeBullet) :
		Entity(table.at(charcterTypeBullet).damege),
		_type(type),
		_characterTypeBullet(charcterTypeBullet),
		_sprite(TextureHolder::getInstance().get(table.at(charcterTypeBullet).texture))
	{
		centerOrigin(_sprite);
		
	}

	Projectile::~Projectile()
	{
		std::cout << "Bullet destroyd" << std::endl;
	}
	


	unsigned int Projectile::getCategory() const
	{
		switch (_type)		
		{
		case Type::playerOneBullet:
			return Category::BulletPlayerOne;
			break;
		case Type::playerTwoBullet:
			return Category::BulletPlayerTwo;
			break;
		default:
			assert(0);
			return Category::None;
			break;
		}	
	}


	void Projectile::updateCurrent(sf::Time dt, CommandeQueue& commands)
	{
		Entity::updateCurrent(dt, commands);
	}

	sf::FloatRect Projectile::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}
	

	float Projectile::getMaxSpeed() const
	{
		return table.at(_characterTypeBullet).speed;
	}

	void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}
}