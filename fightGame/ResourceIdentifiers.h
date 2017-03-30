/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This is a enum for all the resource the game have, plane, backgoud, button.

*/

#pragma once

namespace GEX
{
	enum class TextureID
	{
		MapDessertEntety,
		MapDessertObject,
		MapDessertBackground,
		TitleScreen,
		MenuScreen,		
		Particale,
		AnaEntity,
		RobotEntity,
		KnightEntity,
		NinjaEntity,
		NinjaGirlEntity,
		Bullet,
		FightTimeLogo,
		Ana,
		NinjaBoy,
		NinjaGirl,
		Robot,
		Knight
		
	};

	enum class FontID
	{
		Main
	};

	enum class SoundEffectID {
		AnaGunFire,
		AnaJump,
		Run,
		AnaSword
	};
}
