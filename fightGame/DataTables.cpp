/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Data Tables class

*/

#include "DataTables.h"
#include "Projectile.h"
#include <functional>

namespace GEX
{
	Direction::Direction(float a, float b) : angle(a), distance(b)
	{}

	
	std::map<Character::Type, CharacterData> initializeCharacterData()
	{
		std::map<Character::Type, CharacterData> data;

		data[Character::Type::Ana].hitpoint = 15;
		data[Character::Type::Ana].speed = 150.f;
		data[Character::Type::Ana].fireInterval = sf::seconds(2);
		data[Character::Type::Ana].texture = TextureID::AnaEntity;
		data[Character::Type::Ana].location = sf::IntRect(613, 154, 160, 136);

		return data;
	}

	std::map<TileMap::Tile, MapDessertData> initializeMapData()
	{
		std::map<TileMap::Tile, MapDessertData>	data;

		data[TileMap::Tile::One].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::One].location = sf::IntRect(131, 482, 128, 128);
		data[TileMap::Tile::One].solid = true;
		data[TileMap::Tile::One].hitPoint = 0;

		data[TileMap::Tile::Two].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Two].location = sf::IntRect(1, 612, 128, 128);
		data[TileMap::Tile::Two].solid = true;
		data[TileMap::Tile::Two].hitPoint = 0;

		data[TileMap::Tile::Three].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Three].location = sf::IntRect(261, 742, 128, 128);
		data[TileMap::Tile::Three].solid = true;
		data[TileMap::Tile::Three].hitPoint = 0;

		data[TileMap::Tile::Four].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Four].location = sf::IntRect(131, 742, 128, 128);
		data[TileMap::Tile::Four].solid = true;
		data[TileMap::Tile::Four].hitPoint = 0;

		data[TileMap::Tile::Five].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Five].location = sf::IntRect(1, 872, 128, 128);
		data[TileMap::Tile::Five].solid = true;
		data[TileMap::Tile::Five].hitPoint = 0;

		data[TileMap::Tile::Six].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Six].location = sf::IntRect(1, 742, 128, 128);
		data[TileMap::Tile::Six].solid = true;
		data[TileMap::Tile::Six].hitPoint = 0;

		data[TileMap::Tile::Seven].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Seven].location = sf::IntRect(261, 612, 128, 128);
		data[TileMap::Tile::Seven].solid = true;
		data[TileMap::Tile::Seven].hitPoint = 0;

		data[TileMap::Tile::Eight].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Eight].location = sf::IntRect(131, 612, 128, 128);
		data[TileMap::Tile::Eight].solid = true;
		data[TileMap::Tile::Eight].hitPoint = 0;

		data[TileMap::Tile::Nine].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Nine].location = sf::IntRect(1, 352, 128, 128);
		data[TileMap::Tile::Nine].solid = true;
		data[TileMap::Tile::Nine].hitPoint = 0;

		data[TileMap::Tile::Ten].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Ten].location = sf::IntRect(261, 482, 128, 128);
		data[TileMap::Tile::Ten].solid = true;
		data[TileMap::Tile::Ten].hitPoint = 0;

		data[TileMap::Tile::Eleven].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Eleven].location = sf::IntRect(1, 482, 128, 128);
		data[TileMap::Tile::Eleven].solid = true;
		data[TileMap::Tile::Eleven].hitPoint = 0;

		data[TileMap::Tile::Twelve].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Twelve].location = sf::IntRect(131, 352, 128, 128);
		data[TileMap::Tile::Twelve].solid = true;
		data[TileMap::Tile::Twelve].hitPoint = 0;

		data[TileMap::Tile::Thirteen].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Thirteen].location = sf::IntRect(261, 352, 128, 128);
		data[TileMap::Tile::Thirteen].solid = true;
		data[TileMap::Tile::Thirteen].hitPoint = 0;

		data[TileMap::Tile::Fourteen].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Fourteen].location = sf::IntRect(88, 144, 128, 93);
		data[TileMap::Tile::Fourteen].solid = true;
		data[TileMap::Tile::Fourteen].hitPoint = 0;

		data[TileMap::Tile::Fifteen].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Fifteen].location = sf::IntRect(348, 144, 128, 93);
		data[TileMap::Tile::Fifteen].solid = true;
		data[TileMap::Tile::Fifteen].hitPoint = 0;

		data[TileMap::Tile::Sixteen].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Sixteen].location = sf::IntRect(218, 144, 128, 93);
		data[TileMap::Tile::Sixteen].solid = true;
		data[TileMap::Tile::Sixteen].hitPoint = 0;

		data[TileMap::Tile::Bush].texture = TextureID::MapDessertEntety;
		data[TileMap::Tile::Bush].location = sf::IntRect(127, 54, 131, 74);
		data[TileMap::Tile::Bush].solid = false;
		data[TileMap::Tile::Bush].hitPoint = 0;

		return data;
	}


	std::map<Projectile::Type, ProjectileDate> initializeProjectileDate()
	{
		std::map<Projectile::Type, ProjectileDate> data;

		data[Projectile::Type::AlliedBullet].damege		= 10;
		data[Projectile::Type::AlliedBullet].speed		= 300.f;
		data[Projectile::Type::AlliedBullet].location   = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::EnemyBullet].damege		= 10;
		data[Projectile::Type::EnemyBullet].speed		= 300.f;
		data[Projectile::Type::EnemyBullet].location    = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::Missile].damege			= 200;
		data[Projectile::Type::Missile].speed			= 300.f;
		data[Projectile::Type::Missile].approachRate    = 1000.f;
		data[Projectile::Type::Missile].location        = sf::IntRect(160, 64, 15, 32);

		return data;
	}

	

	std::map<Particule::Type, ParticuleData> initializeParticleData()
	{
		std::map<Particule::Type, ParticuleData> data;

		data[Particule::Type::Propellant].color = sf::Color(255, 111, 0);
		data[Particule::Type::Propellant].lifetime = sf::seconds(0.1f);

		data[Particule::Type::Smoke].color = sf::Color(64,64,64);
		data[Particule::Type::Smoke].lifetime = sf::seconds(0.5f);

		return data;
	}
}