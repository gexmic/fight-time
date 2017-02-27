/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

world class

*/
#pragma once
#include "Particule.h"
#include "SceneNode.h"
#include "ParticuleNode.h"

namespace GEX
{
	class EmmitterNode : public SceneNode
	{
	public:
		explicit EmmitterNode(Particule::Type type);

	private:

		void		updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void		emitParticules(sf::Time dt);

	private:

		sf::Time			_accumalatedTime;
		Particule::Type		_type;
		ParticuleNode*		_particaleSystem;
	};
}