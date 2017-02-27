/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

enum to have the type of airplaine

*/

#pragma once

namespace GEX
{
	namespace Category
	{
		enum Type
		{
			None = 0,			 // bit fied operator
			SceneGroundLayer		= 1 << 0,
			PlayerCharacterOne		= 1 << 1,
			playerCharacterTwo		= 1 << 2,
			EnnemyCharacter			= 1 << 3,
			AlliedProjectile		= 1 << 4,
			EnemyProjectile			= 1 << 5,
			ParticalSystem			= 1 << 6,
			SoundEffet				= 1 << 7,
			Map						= 1 << 8,

		
			Projectile			= AlliedProjectile | EnemyProjectile,
			//ThingsPlayerCollideWith = EnnemyAircraft | EnemyProjectile | Pickup,
			//ThingsEnemyColideWith = PlayerAircraft | AlliedAircraft | AlliedProjectile

		};
	}



}
