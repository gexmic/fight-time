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


#include "World.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include <math.h>
#include "ResourceIdentifiers.h"
#include <algorithm>
#include "ParticuleNode.h"
#include "SoundPlayer.h"
#include "SoundNode.h"
#include "Entity.h"
#include "TileMap.h"
#include "Character.h"
#include <iostream>

namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_worldView(window.getDefaultView()),
		_soundPlayer(soundPlayer),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, 2000.f)

	{
		buildScene();
	}

	void World::update(sf::Time deltaTime)
	{


		updateSound();

		destroyEntitieOurSideView();

		while (!_commandQueue.isEmpty())
		{
			_sceneGraph.onCommande(_commandQueue.pop(), deltaTime);
		}

		handleCollisions();
		_sceneGraph.removeWercks();


		_sceneGraph.update(deltaTime, _commandQueue);
		adapPlayerPosition();
	}


	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);

	}

	void World::adapPlayerPosition()
	{
		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 55.f;

		sf::Vector2f position = _character->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_character->setPosition(position);
		_character->setVelocity(0, 0);
	}

	void World::adapPlayerPositionFromTileRight(int tileNumber)
	{
		int x = (tileNumber % 10) * 128;
		int y = (tileNumber / 10) * 128;

		sf::Vector2f position = _character->getPosition();

		if (position.x + 57 >= x)
		{
			_character->setPosition(x - 57, position.y);
			_character->setVelocity(0, 0);
		}

		else
			_character->setPosition(position);

	}

	void World::adapPlayerPositionFromTileLeft(int tileNumber)
	{
		int x = (tileNumber % 10) * 128;
		int y = (tileNumber / 10) * 128;

		sf::Vector2f position = _character->getPosition();

		if (position.x - 57 <= x + 128)
		{
			_character->setPosition(x + 128 + 57, position.y);
			_character->setVelocity(0, 0);
		}

		else
			_character->setPosition(position);
	}

	void World::adapPlayerPositionFromTileBottom(int tileNumber)
	{
		int x = (tileNumber % 10) * 128;
		int y = (tileNumber / 10) * 128;

		sf::Vector2f position = _character->getPosition();

		if (position.y + 57 >= y)
		{
			_character->setPosition(position.x,  y - 57);
			//_character->setVelocity(0, 0);
		}
		else
			_character->setPosition(position);
	}

	CommandeQueue & World::getCommandQueue()
	{
		return _commandQueue;
	}

	void World::buildScene()
	{
		// Put the layer nodes into the scene graph
		for (std::size_t i = 0; i < LayerCount; ++i)
		{
			Category::Type category = (i == Ground) ? Category::SceneGroundLayer : Category::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attachChild(std::move(layer));
		}



		//prepare background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::MapDessertBackground);
		sf::IntRect textureRect(0, 0, 1280, 960);
		texture.setRepeated(false);

		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		_sceneLayers[Backgroud]->attachChild(std::move(background));

		// add tile map
		std::unique_ptr<TileMap> map(new TileMap());
		_map = map.get();
		_sceneLayers[Ground]->attachChild(std::move(map));


		// add player to the world
		std::unique_ptr<Character> ana(new Character());
		_character = ana.get();
		_character->setPosition(300, 300);
		_sceneLayers[Ground]->attachChild(std::move(ana));


		// Add the background sprite to the scene
		//sf::Texture& finish = TextureHolder::getInstance().get(TextureID::FinishLine);
		//sf::IntRect FinishRect(0, 0, 1024, 76);
		//std::unique_ptr<SpriteNode> finishLine(new SpriteNode(finish, FinishRect));
		//_sceneLayers[FinishLine]->attachChild(std::move(finishLine));



		////particle system
		//std::unique_ptr<ParticuleNode> smokeNode(new ParticuleNode(Particule::Type::Smoke));
		//_sceneLayers[Air]->attachChild(std::move(smokeNode));

		//std::unique_ptr<ParticuleNode> fireNode(new ParticuleNode(Particule::Type::Propellant));
		//_sceneLayers[Air]->attachChild(std::move(fireNode));


		//// Add player's aircraft
		//std::unique_ptr<Airplaine> leader(new Airplaine(Airplaine::Type::Eagle));
		//_playerAircraft = leader.get();
		//_playerAircraft->setPosition(_spawnPosition);
		//_playerAircraft->setVelocity(0.f, _scrollSpeed);
		//_sceneLayers[Air]->attachChild(std::move(leader));

		//// add SoundNode

		//std::unique_ptr<SoundNode> soundEffectNode(new SoundNode(_soundPlayer));
		//_sceneGraph.attachChild(std::move(soundEffectNode));

	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattleFieldBound() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100;
		bounds.height += 100;
		return bounds;
	}



	void World::handleCollisions()
	{

		int tileOn = _map->getTileNumber(_character->getPosition());
		std::cout << "The tile is " << tileOn << std::endl;

		int tileToTheRight = _map->getTileOnRight(_character->getPosition());
		std::cout << "Right tile is " << tileToTheRight << std::endl;

		int tileToTheLeft = _map->getTileOnLeft(_character->getPosition());
		int tileToTheBottom = _map->getTileOnBottom(_character->getPosition());


		if (_map->isItSolid(tileToTheRight) && _character->isMovingRight() == true)
		{
			
			adapPlayerPositionFromTileRight(tileToTheRight);
		}

		else if (_map->isItSolid(tileToTheLeft) && _character->isMovingLeft() == true)
		{
			
				adapPlayerPositionFromTileLeft(tileToTheLeft);
		}

		if(_map->isItSolid(tileToTheBottom))
		adapPlayerPositionFromTileBottom(tileToTheBottom);





		// build a list of all pair of colloding scenenode all pair
		//std::set<SceneNode::Pair> collisionPairs;
		//_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		//// for each collision do someting
		//for (auto pair : collisionPairs)
		//{
		//	if (matchesCategories(pair, Category::PlayerAircraft, Category::EnnemyAircraft))
		//	{
		//		auto& player = static_cast<Airplaine&> (*pair.first);
		//		auto& enemy = static_cast<Airplaine&>(*pair.second);

		//		player.damage(enemy.getHitPoint());
		//		enemy.destroy();
		//	}

		//	if (matchesCategories(pair, Category::EnnemyAircraft, Category::AlliedProjectile) ||
		//		matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		//	{
		//		auto& Airplaines = static_cast<Airplaine&> (*pair.first);
		//		auto& projectile = static_cast<Projectile&>(*pair.second);

		//		Airplaines.damage(projectile.getHitPoint());
		//		projectile.destroy();
		//	}

		//	/*if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		//	{
		//		auto& playerAirplaine = static_cast<Airplaine&> (*pair.first);
		//		auto& projectile = static_cast<Projectile&>(*pair.second);

		//		playerAirplaine.damage(projectile.getHitPoint());
		//		projectile.destroy();
		//	}*/
		//	// to do
		//	if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		//	{
		//		auto& playerAirplaine = static_cast<Airplaine&> (*pair.first);
		//		auto& pickup = static_cast<Pickup&>(*pair.second);

		//		pickup.apply(playerAirplaine);
		//		pickup.destroy();
		//		playerAirplaine.playLocalSound(_commandQueue, SoundEffectID::CollectPickup);
		//	}
		//}
	}

	void World::destroyEntitieOurSideView()
	{
		Command command;
		command.category = Category::Projectile;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattleFieldBound().intersects(e.getBoundingRect()))
				e.destroy();
		});

		_commandQueue.push(command);
	}

	void World::updateSound()
	{
		/*_soundPlayer.setListenerPosition(_playerAircraft->getWorldPosition());
		_soundPlayer.removeStoppedSounds();*/
	}



	bool matchesCategories(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1 && type2 & category2)
		{
			return true;
		}
		else if (type1 & category2 && type2 & category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
			return false;
	}
}


