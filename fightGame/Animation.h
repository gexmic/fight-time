/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

*/
#pragma once



#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

namespace GEX
{
	//
	// An animaiton is a collection of frames. 
	// 

	using Frame = sf::IntRect;

	class Animation
	{
	public:
		Animation(bool repeat = true);
		~Animation();

		void						addFrame(const Frame& frame);
		void                        addFrameSet(const std::vector<Frame>);
		void						setDurationAsSeconds(float d);
		void						start();

		int							getNumberOfFrames() const;
		Frame						getFrameByNumber(int n) const;
		Frame						getCurrentFrame() const;
		Frame						update(sf::Time dt);


	private:
		std::vector<Frame>			_frames;
		std::size_t					_currentFrame;
		sf::Time					_elapsedTime;
		sf::Time					_duration;
		//sf::Time					_timePerFrame;
		bool						_repeat;

	};
}
