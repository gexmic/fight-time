/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Scene node class

*/

#include "SceneNode.h"
#include <cassert>
#include "Category.h"
#include "Utility.h"
#include <algorithm>

namespace GEX
{
	float distance(const SceneNode & lhs, const SceneNode & rhs)
	{
		return lenght(lhs.getWorldPosition() - rhs.getWorldPosition());
	}

	bool collision(const SceneNode & lhs, const SceneNode & rhs)
	{
		return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}

	SceneNode::SceneNode(Category::Type category) :
		_parent(nullptr),
		_defaultCategory(category)
	{}
	SceneNode::~SceneNode() {}

	void SceneNode::checkSceneCollision(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		this->checkNodeCollosion(node, collisionPairs);

		for (auto& child : node._children)
			this->checkSceneCollision(*child, collisionPairs);
	}

	void SceneNode::checkNodeCollosion(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		{
			collisionPairs.insert(std::minmax(this, &node));
		}

		for (auto & child : _children)
			child->checkNodeCollosion(node, collisionPairs);
	}

	void SceneNode::removeWercks()
	{
		// remove all children which request
		auto werkfieldBegin = std::remove_if(_children.begin(), _children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));

		_children.erase(werkfieldBegin, _children.end());
		// call function recursively for all remaining children
		std::for_each(_children.begin(), _children.end(), std::mem_fn(&SceneNode::removeWercks));
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	void SceneNode::attachChild(Ptr child)
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(_children.begin(),
			_children.end(),
			[&](Ptr& p)->bool {return p.get() == &node;  });

		assert(found == _children.end()); // crach if not found

		Ptr result = std::move(*found);
		result->_parent = nullptr;
		_children.erase(found);
		return result;
	}

	void SceneNode::onCommande(const Command & command, sf::Time dt)
	{
		if (command.category & getCategory())
			command.action(*this, dt);
		for (auto& child : _children)
		{
			child->onCommande(command, dt);
		}
	}

	unsigned int SceneNode::getCategory() const
	{
		return _defaultCategory;
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
		{
			transform = node->getTransform() * transform;
		}
		return transform;
	}

	sf::FloatRect SceneNode::getBoundingRect() const
	{
		return sf::FloatRect();  // defautl behavio return empty rectangle
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	void SceneNode::update(sf::Time deltaTime, CommandeQueue& commands)
	{
		// update current then children

		updateCurrent(deltaTime, commands);
		updateChildren(deltaTime, commands);
	}

	void SceneNode::updateCurrent(sf::Time deltaTime, CommandeQueue& commands)
	{
		// do nothing by default
	}

	void SceneNode::updateChildren(sf::Time deltaTime, CommandeQueue& commands)
	{
		for (const Ptr& child : _children)
		{
			child->update(deltaTime, commands);
		}
	}

	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates state) const
	{
		// apply transform 
		state.transform *= getTransform();

		// draw current then children

		drawCurrent(target, state);
		//drawBoundingRect(target, state);
		drawChildren(target, state);		
	}

	void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		// do nothing by default
	}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates state) const
	{
		for (const Ptr& child : _children)
		{
			child->draw(target, state);
		}
	}

	void SceneNode::drawBoundingRect(sf::RenderTarget & target, sf::RenderStates states) const
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);

		target.draw(shape);
	}

	
}