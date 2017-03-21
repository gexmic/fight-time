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

		data[Character::Type::Ana].health = 300;
		data[Character::Type::Ana].attackDamage = 1 ;
		data[Character::Type::Ana].speed = 150.f;
		data[Character::Type::Ana].fireInterval = sf::seconds(1);
		data[Character::Type::Ana].texture = TextureID::AnaEntity;
		data[Character::Type::Ana].location = sf::IntRect(766, 154, 160, 136);

		data[Character::Type::Azerty].health = 300;
		data[Character::Type::Azerty].attackDamage = 1;
		data[Character::Type::Azerty].speed = 150.f;
		data[Character::Type::Azerty].fireInterval = sf::seconds(1);
		data[Character::Type::Azerty].texture = TextureID::RobotEntity;
		data[Character::Type::Azerty].location = sf::IntRect(430, 133, 142, 139);

		data[Character::Type::SirThomasWale].health = 300;
		data[Character::Type::SirThomasWale].attackDamage = 25;
		data[Character::Type::SirThomasWale].speed = 150.f;
		data[Character::Type::SirThomasWale].fireInterval = sf::seconds(1);
		data[Character::Type::SirThomasWale].texture = TextureID::KnightEntity;
		data[Character::Type::SirThomasWale].location = sf::IntRect(150, 1075, 147, 177);

		data[Character::Type::Katoka].health = 300;
		data[Character::Type::Katoka].attackDamage = 25;
		data[Character::Type::Katoka].speed = 150.f;
		data[Character::Type::Katoka].fireInterval = sf::seconds(1);
		data[Character::Type::Katoka].texture = TextureID::NinjaEntity;
		data[Character::Type::Katoka].location = sf::IntRect(61, 181, 58, 110);

		data[Character::Type::Fungi].health = 300;
		data[Character::Type::Fungi].attackDamage = 25;
		data[Character::Type::Fungi].speed = 150.f;
		data[Character::Type::Fungi].fireInterval = sf::seconds(1);
		data[Character::Type::Fungi].texture = TextureID::NinjaGirlEntity;
		data[Character::Type::Fungi].location = sf::IntRect(327, 205, 73, 125);

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


	std::map<Projectile::CharacterTypeBullet, ProjectileDate> initializeProjectileDate()
	{
		std::map<Projectile::CharacterTypeBullet, ProjectileDate> data;

		data[Projectile::CharacterTypeBullet::AnaBullet].damege		= 10;
		data[Projectile::CharacterTypeBullet::AnaBullet].speed		= 300.f;
		data[Projectile::CharacterTypeBullet::AnaBullet].texture	= TextureID::Bullet;

		data[Projectile::CharacterTypeBullet::RobotBullet].damege		= 10;
		data[Projectile::CharacterTypeBullet::RobotBullet].speed		= 300.f;
		data[Projectile::CharacterTypeBullet::RobotBullet].texture		= TextureID::Bullet;

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