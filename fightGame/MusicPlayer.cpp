#include "MusicPlayer.h"
#include "MusicPlayer.h"

namespace GEX
{

	MusicPlayer::MusicPlayer() :
		_music(),
		_filenames(),
		_volume(100)
	{
		_filenames[MusicID::MenuTheme] = "../Media/Music/MenuTheme.ogg";
		_filenames[MusicID::MissionTheme] = "../Media/Music/MissionTheme.ogg";
	}

	void MusicPlayer::play(MusicID theme)
	{
		std::string filename = _filenames[theme];

		if (!_music.openFromFile(filename))
			throw std::runtime_error("Music " + filename + " could not be play");

		_music.setVolume(_volume);
		_music.setLoop(true);
		_music.play();
	}

	void MusicPlayer::stop()
	{
		_music.stop();
	}

	void MusicPlayer::setPaused(bool paused)
	{
		if (paused)
			_music.pause();
		else
			_music.play();
	}

	void MusicPlayer::setVolume(float volume)
	{
		_volume = volume;
	}	
}