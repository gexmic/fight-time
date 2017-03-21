/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This is the class of the game state. the game state is wen the player control the airplaine.

*/

#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "CommandeQueue.h"

namespace GEX
{
	class Projectile : public Entity
	{


	public:
		enum class Type
		{
			playerOneBullet,
			playerTwoBullet
		};

	public:
		enum class CharacterTypeBullet
		{
			AnaBullet,
			RobotBullet,
			NinjaBullet
		};

	public:
							Projectile(Type type, CharacterTypeBullet charcterTypeBullet);
							~Projectile();
		unsigned int		getCategory() const override;
		float				getMaxSpeed() const;
	
		
	private:
		void				updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		sf::FloatRect		getBoundingRect() const;
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;

	private:
		Type				_type;
		CharacterTypeBullet _characterTypeBullet;
		sf::Sprite			_sprite;
		sf::Vector2f		_targerDirection; ///<unit vector pointing at closest enemy plane.
	};
}

