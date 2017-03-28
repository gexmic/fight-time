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
			PlayerCharacterTwo		= 1 << 2,
			ParticalSystem			= 1 << 3,
			SoundEffet				= 1 << 4,
			Map						= 1 << 5,
			BulletPlayerOne			= 1 << 6,
			BulletPlayerTwo			= 1 << 7,
		
			Projectile			= BulletPlayerOne | BulletPlayerTwo,
			//ThingsPlayerCollideWith = EnnemyAircraft | EnemyProjectile | Pickup,
			//ThingsEnemyColideWith = PlayerAircraft | AlliedAircraft | AlliedProjectile

		};
	}



}
