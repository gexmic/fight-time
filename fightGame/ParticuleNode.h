/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This sprite node is for the sprit object in the game.

*/

#pragma once
#include "SceneNode.h"
#include "SFML\Graphics.hpp"
#include "TextureHolder.h"
#include "Particule.h"
#include <deque>

namespace GEX
{

	class ParticuleNode : public SceneNode
	{
	public:
		explicit				ParticuleNode(Particule::Type type);

		void					addParticule(sf::Vector2f position);
		Particule::Type			getParticaleType()const;
		unsigned int			getCategory()const override;

	private:
		void					updateCurrent(sf::Time dt, CommandeQueue& commands)override;
		void					drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;

		void					addVertex(float worldx, float worldy, float texu, float texv, const sf::Color& color)const;
		void					computeVertices()const;

	private:
		std::deque<Particule>	_particales;
		const sf::Texture&		_textures;
		Particule::Type			_type;

		mutable	sf::VertexArray	_vertexArray;
		mutable bool			_needVertexUpdate;
	};
}