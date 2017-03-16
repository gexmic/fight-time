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
	const int BUFFER = 54;
	const int TILE_HIGHT = 128;
	const int NUM_ROW = 10;
	const int NUM_COL = 10;

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
		adapPlayerPosition(_characterOne);
		adapPlayerPosition(_characterTwo);
	}


	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);

	}

	void World::adapPlayerPosition(Character* character)
	{
		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = BUFFER;

		// adapte position for player
		
		sf::Vector2f playerPosition = character->getPosition();
		playerPosition.x = std::max(playerPosition.x, viewBounds.left + borderDistance);
		playerPosition.x = std::min(playerPosition.x, viewBounds.left + viewBounds.width - borderDistance);
		playerPosition.y = std::max(playerPosition.y, viewBounds.top + borderDistance);
		playerPosition.y = std::min(playerPosition.y, viewBounds.top + viewBounds.height - borderDistance);
		character->setPosition(playerPosition);	
	}

	void World::adapPlayerPositionFromTileRight(int tileNumber, Character* character)
	{
		sf::Vector2i tilePos;
		tilePos.x = (tileNumber % NUM_ROW) * TILE_HIGHT;
		tilePos.y = (tileNumber / NUM_COL) * TILE_HIGHT;

		sf::Vector2f CharacterPosition = character->getPosition();

		// adapt position for player 
		if (CharacterPosition.x + BUFFER >= tilePos.x)
		{
			character->setPosition(tilePos.x - BUFFER, CharacterPosition.y);
		}

		else
			character->setPosition(CharacterPosition);
	}

	void World::adapPlayerPositionFromTileLeft(int tileNumber, Character* character)
	{
		sf::Vector2i tilePos;
		tilePos.x = (tileNumber % NUM_ROW) * TILE_HIGHT;
		tilePos.y = (tileNumber / NUM_COL) * TILE_HIGHT;

		// adapte position for player
		sf::Vector2f CharacterPosition = character->getPosition();

		if (CharacterPosition.x - BUFFER <= tilePos.x + TILE_HIGHT)
		{
			character->setPosition(tilePos.x + TILE_HIGHT + BUFFER, CharacterPosition.y);
		}

		else
			character->setPosition(CharacterPosition);
	}

	void World::adapPlayerPositionFromTileBottom(int tileNumber, Character* character)
	{
		sf::Vector2i tilePos;
		tilePos.x = (tileNumber % NUM_ROW) * TILE_HIGHT;
		tilePos.y = (tileNumber / NUM_COL) * TILE_HIGHT;

		// adapte position for player one
		sf::Vector2f CharacterPosition = character->getPosition();

		
		if (CharacterPosition.y + BUFFER >= tilePos.y)
		{
			if (character->isStateJump() == false)
			{
				character->setPosition(CharacterPosition.x, tilePos.y - BUFFER);
				character->setVelocity(character->getVelocity().x, 0);
			}

			// set the buffer -1 to make sure the character jump and do not get stuck
			if (character->isStateJump() == true && CharacterPosition.y + BUFFER - 1 >= tilePos.y)
			{
				character->setState(character->Idle);
				character->setPosition(CharacterPosition.x, tilePos.y - BUFFER);
				character->setVelocity(character->getVelocity().x, 0);
			}
			
		}
		else
			character->setPosition(CharacterPosition);		
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
		std::unique_ptr<Character> playerOne(new Character(_characterOne->Ana, Category::Type::PlayerCharacterOne));
		_characterOne = playerOne.get();
		_characterOne->setPosition(300, 300);
		_sceneLayers[Ground]->attachChild(std::move(playerOne));

		std::unique_ptr<Character> playerTwo(new Character(_characterTwo->Fungi, Category::Type::PlayerCharacterTwo));
		_characterTwo = playerTwo.get();
		_characterTwo->setPosition(800, 300);
		_characterTwo->setScale({ -1, 1 });
		_sceneLayers[Ground]->attachChild(std::move(playerTwo));


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

		// add SoundNode

		std::unique_ptr<SoundNode> soundEffectNode(new SoundNode(_soundPlayer));
		_sceneGraph.attachChild(std::move(soundEffectNode));

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
		// for player one handle collision for tile
		int tileOnPlayerOne = _map->getTileNumber(_characterOne->getPosition());
		int tileToTheRightPlayerOne = _map->getTileOnRight(_characterOne->getPosition());
		int tileToTheLeftPlayerOne = _map->getTileOnLeft(_characterOne->getPosition());
		int tileToTheBottomPlayerOne = _map->getTileOnBottom(_characterOne->getPosition());

		if (_map->isItSolid(tileToTheRightPlayerOne) && _characterOne->isMovingRight() == true)
		{			
			adapPlayerPositionFromTileRight(tileToTheRightPlayerOne, _characterOne);
		}

		else if (_map->isItSolid(tileToTheLeftPlayerOne) && _characterOne->isMovingLeft() == true)
		{
			
				adapPlayerPositionFromTileLeft(tileToTheLeftPlayerOne, _characterOne);
		}

		if(_map->isItSolid(tileToTheBottomPlayerOne))
		adapPlayerPositionFromTileBottom(tileToTheBottomPlayerOne, _characterOne);


		// handle collision for player two
		int tileOnPlayerTwo = _map->getTileNumber(_characterTwo->getPosition());
		int tileToTheRightPlayerTwo = _map->getTileOnRight(_characterTwo->getPosition());
		int tileToTheLeftPlayerTwo = _map->getTileOnLeft(_characterTwo->getPosition());
		int tileToTheBottomPlayerTwo = _map->getTileOnBottom(_characterTwo->getPosition());

		if (_map->isItSolid(tileToTheRightPlayerTwo) && _characterTwo->isMovingRight() == true)
		{
			adapPlayerPositionFromTileRight(tileToTheRightPlayerTwo, _characterTwo);
		}

		else if (_map->isItSolid(tileToTheLeftPlayerTwo) && _characterTwo->isMovingLeft() == true)
		{

			adapPlayerPositionFromTileLeft(tileToTheLeftPlayerTwo, _characterTwo);
		}

		if (_map->isItSolid(tileToTheBottomPlayerTwo))
			adapPlayerPositionFromTileBottom(tileToTheBottomPlayerTwo, _characterTwo);

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


