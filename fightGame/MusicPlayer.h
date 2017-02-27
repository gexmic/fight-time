#pragma once
#include "ResourceIdentifiers.h"
#include <SFML\Audio\Music.hpp>
#include <map>
#include <string>

namespace GEX
{
	enum class MusicID
	{
		MenuTheme,
		MissionTheme,
	};
	class MusicPlayer
	{
	public:
										MusicPlayer();
										MusicPlayer(const MusicPlayer&) = delete;
		MusicPlayer&					operator =(const MusicPlayer&) = delete;

		void							play(MusicID theme);
		void							stop();

		void							setPaused(bool paused);
		void							setVolume(float volume);

	private:
		sf::Music						_music;
		std::map<MusicID, std::string>	_filenames;
		float							_volume;

	};
}