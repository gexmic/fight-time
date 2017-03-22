#pragma once
#include "SceneNode.h"
#include <vector>

namespace GEX
{
	class TileMap : public SceneNode
	{
	public:
		enum Type
		{
			Dessert,
			Factory,
			Forest,
			Graveyard,
			Winter
		};
		enum Tile
		{
			None,
			One,
			Two,
			Three,
			Four,
			Five,
			Six,
			Seven,
			Eight,
			Nine,
			Ten,
			Eleven,
			Twelve,
			Thirteen,
			Fourteen,
			Fifteen,
			Sixteen,
			Bush1,
			Bush2,
			Cactus1,
			Cactus2,
			Cactus3,
			Crate,
			Grass1,
			Grass2,
			Sign,
			SignArrow,
			Skeleton,
			Stone,
			StoneBlock,
			Tree
		};

	public:
		TileMap(Type type = Type::Dessert);
		
		unsigned int			getCategory() const override;
		int						getTileNumber(sf::Vector2f);
		int						getTileOnRight(sf::Vector2f);
		int						getTileOnLeft(sf::Vector2f);
		int						getTileOnTop(sf::Vector2f);
		int						getTileOnBottom(sf::Vector2f);
		sf::Vector2f			getPosOnTile(int x, int y);

		bool					isItSolid(int tileNumber);


	private:
		void					drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		void					loadMap();
		
	private:
		std::vector<int>		_dessertMap;
		Type					_type;
		int						_currentTileOn;
		int						_row;
		int						_column;
		mutable sf::Sprite		_tile1;
		mutable sf::Sprite		_tile2;
		mutable sf::Sprite		_tile3;
		mutable sf::Sprite		_tile4;
		mutable sf::Sprite		_tile5;
		mutable sf::Sprite		_tile6;
		mutable sf::Sprite		_tile7;
		mutable sf::Sprite		_tile8;
		mutable sf::Sprite		_tile9;
		mutable sf::Sprite		_tile10;
		mutable sf::Sprite		_tile11;
		mutable sf::Sprite		_tile12;
		mutable sf::Sprite		_tile13;
		mutable sf::Sprite		_tile14;
		mutable sf::Sprite		_tile15;
		mutable sf::Sprite		_tile16;
		mutable sf::Sprite		_tileObject1;
		mutable sf::Sprite		_tileObject2;
		mutable sf::Sprite		_tileObject3;
		mutable sf::Sprite		_tileObject4;
		mutable sf::Sprite		_tileObject5;
		mutable sf::Sprite		_tileObject6;
		mutable sf::Sprite		_tileObject7;
		mutable sf::Sprite		_tileObject8;
		mutable sf::Sprite		_tileObject9;
		mutable sf::Sprite		_tileObject10;
		mutable sf::Sprite		_tileObject11;
		mutable sf::Sprite		_tileObject12;
		mutable sf::Sprite		_tileObject13;
		mutable sf::Sprite		_tileObject14;
	};
}

