#include "EmmitterNode.h"
#include "Command.h"

namespace GEX
{
	EmmitterNode::EmmitterNode(Particule::Type type) :
		_accumalatedTime(sf::Time::Zero),
		_type(type),
		_particaleSystem(nullptr)
	{}

	void EmmitterNode::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		if (_particaleSystem)
			emitParticules(dt);
		else
		{
			auto finder = [this](ParticuleNode& node, sf::Time dt)
			{
				if (node.getParticaleType() == _type)
					_particaleSystem = &node;
			};

			Command command;
			command.category = Category::ParticalSystem;
			command.action = derivedAction<ParticuleNode>(finder);

			commands.push(command);
		}
	}

	void EmmitterNode::emitParticules(sf::Time dt)
	{
		const float emmissionRate = 200.f;
		const sf::Time interval = sf::seconds(1) / emmissionRate;

		_accumalatedTime += dt;
		while (_accumalatedTime > interval)
		{
			_accumalatedTime -= interval;
			_particaleSystem->addParticule(getWorldPosition());
		}
	}
}