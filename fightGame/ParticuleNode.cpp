#include "ParticuleNode.h"
#include "ResourceIdentifiers.h"
#include "DataTables.h"


namespace GEX
{
	namespace
	{
		const std::map<Particule::Type, ParticuleData> Table = initializeParticleData();
	}

	ParticuleNode::ParticuleNode(Particule::Type type) :
		SceneNode(),
		_particales(),
		_textures(TextureHolder::getInstance().get(TextureID::Particale)),
		_type(type),
		_vertexArray(sf::Quads), // read on this
		_needVertexUpdate(true)
	{
	}

	void ParticuleNode::addParticule(sf::Vector2f position)
	{
		Particule particle;

		particle.possition = position;
		particle.color = Table.at(_type).color;
		particle.lifeTime = Table.at(_type).lifetime;

		_particales.push_back(particle);


	}

	Particule::Type ParticuleNode::getParticaleType() const
	{
		return _type;
	}

	unsigned int ParticuleNode::getCategory() const
	{
		return Category::ParticalSystem;
	}

	void ParticuleNode::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		// remove expire particules
		while (!_particales.empty() && _particales.front().lifeTime <= sf::Time::Zero)
		{
			_particales.pop_front();
		}

		// update

		for (auto& particle : _particales)
			particle.lifeTime -= dt;

		// make particule as dirty
		_needVertexUpdate = true;

	}

	void ParticuleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		if (_needVertexUpdate)
		{
			computeVertices();
			_needVertexUpdate = false;
		}

		state.texture = &_textures;
		target.draw(_vertexArray, state);
	}

	void ParticuleNode::addVertex(float worldx, float worldy, float texu, float texv, const sf::Color & color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(worldx, worldy);
		vertex.texCoords = sf::Vector2f(texu, texv);
		vertex.color = color;

		_vertexArray.append(vertex);
	}

	void ParticuleNode::computeVertices() const
	{
		sf::Vector2f size(_textures.getSize());
		sf::Vector2f half = size / 2.f;

		// refill vertex array

		_vertexArray.clear();
		for (const Particule& particle : _particales)
		{
			sf::Vector2f pos = particle.possition;
			sf::Color color = particle.color;

			float ratio = particle.lifeTime.asSeconds()
						/ Table.at(_type).lifetime.asSeconds();
			color.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));
			// add 4 verticies to make up a rectangle primative for partical
			addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
			addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);
		}
	}
}