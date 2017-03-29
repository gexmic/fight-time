#include "TileMap.h"
#include "TextureHolder.h"
#include "DataTables.h"

namespace GEX
{
	const std::map<TileMap::Tile, MapDessertData> table = initializeMapData();
	;

	TileMap::TileMap(Type type) :
		_type(type),
		_row(1),
		_column(0),
		_tile1(TextureHolder::getInstance().get(table.at(Tile::One).texture), table.at(Tile::One).location ),
		_tile2(TextureHolder::getInstance().get(table.at(Tile::Two).texture), table.at(Tile::Two).location),
		_tile3(TextureHolder::getInstance().get(table.at(Tile::Three).texture), table.at(Tile::Three).location),
		_tile4(TextureHolder::getInstance().get(table.at(Tile::Four).texture), table.at(Tile::Four).location),
		_tile5(TextureHolder::getInstance().get(table.at(Tile::Five).texture), table.at(Tile::Five).location),
		_tile6(TextureHolder::getInstance().get(table.at(Tile::Six).texture), table.at(Tile::Six).location),
		_tile7(TextureHolder::getInstance().get(table.at(Tile::Seven).texture), table.at(Tile::Seven).location),
		_tile8(TextureHolder::getInstance().get(table.at(Tile::Eight).texture), table.at(Tile::Eight).location),
		_tile9(TextureHolder::getInstance().get(table.at(Tile::Nine).texture), table.at(Tile::Nine).location),
		_tile10(TextureHolder::getInstance().get(table.at(Tile::Ten).texture), table.at(Tile::Ten).location),
		_tile11(TextureHolder::getInstance().get(table.at(Tile::Eleven).texture), table.at(Tile::Eleven).location),
		_tile12(TextureHolder::getInstance().get(table.at(Tile::Twelve).texture), table.at(Tile::Twelve).location),
		_tile13(TextureHolder::getInstance().get(table.at(Tile::Thirteen).texture), table.at(Tile::Thirteen).location),
		_tile14(TextureHolder::getInstance().get(table.at(Tile::Fourteen).texture), table.at(Tile::Fourteen).location),
		_tile15(TextureHolder::getInstance().get(table.at(Tile::Fifteen).texture), table.at(Tile::Fifteen).location),
		_tile16(TextureHolder::getInstance().get(table.at(Tile::Sixteen).texture), table.at(Tile::Sixteen).location),
		_tileObject1(TextureHolder::getInstance().get(table.at(Tile::Bush1).texture), table.at(Tile::Bush1).location),
		_tileObject2(TextureHolder::getInstance().get(table.at(Tile::Bush2).texture), table.at(Tile::Bush2).location),
		_tileObject3(TextureHolder::getInstance().get(table.at(Tile::Cactus1).texture), table.at(Tile::Cactus1).location),
		_tileObject4(TextureHolder::getInstance().get(table.at(Tile::Cactus2).texture), table.at(Tile::Cactus2).location),
		_tileObject5(TextureHolder::getInstance().get(table.at(Tile::Cactus3).texture), table.at(Tile::Cactus3).location),
		_tileObject6(TextureHolder::getInstance().get(table.at(Tile::Crate).texture), table.at(Tile::Crate).location),
		_tileObject7(TextureHolder::getInstance().get(table.at(Tile::Grass1).texture), table.at(Tile::Grass1).location),
		_tileObject8(TextureHolder::getInstance().get(table.at(Tile::Grass2).texture), table.at(Tile::Grass2).location),
		_tileObject9(TextureHolder::getInstance().get(table.at(Tile::Sign).texture), table.at(Tile::Sign).location),
		_tileObject10(TextureHolder::getInstance().get(table.at(Tile::SignArrow).texture), table.at(Tile::SignArrow).location),
		_tileObject11(TextureHolder::getInstance().get(table.at(Tile::Skeleton).texture), table.at(Tile::Skeleton).location),
		_tileObject12(TextureHolder::getInstance().get(table.at(Tile::Stone).texture), table.at(Tile::Stone).location),
		_tileObject13(TextureHolder::getInstance().get(table.at(Tile::StoneBlock).texture), table.at(Tile::StoneBlock).location),
		_tileObject14(TextureHolder::getInstance().get(table.at(Tile::Tree).texture), table.at(Tile::Tree).location)


	{
		loadMap();
	}

	unsigned int TileMap::getCategory() const
	{
		return Category::Map;
	}

	int TileMap::getTileNumber(sf::Vector2f pos)
	{		
		_row = pos.y / 128;
		_column = pos.x / 128;		
		return _currentTileOn = _row * 10 + _column;
	}

	int TileMap::getTileOnRight(sf::Vector2f pos)
	{

		if (_column > 10)
			return 0;
		else
			return _currentTileOn +1;
	}

	int TileMap::getTileOnLeft(sf::Vector2f pos)
	{
		if (_column < 0)
			return 0;
		return _currentTileOn -1;
	}

	int TileMap::getTileOnTop(sf::Vector2f pos)
	{
		if (_row < 0)
			return 0;
		else
			return _currentTileOn - 10;
	}

	int TileMap::getTileOnBottom(sf::Vector2f pos)
	{
		if (_row > 8)
			return 0;

		else
			return _currentTileOn + 10;
		
	}

	sf::Vector2f TileMap::getPosOnTile(int x, int y)
	{
		float xPos = x % 128;
		float yPos = y % 128;
		sf::Vector2f currentPosition(x, y);
		return currentPosition;
	}

	bool TileMap::isItSolid(int tileNumber)
	{
		int tile =_dessertMap.at(tileNumber);
		if (tile == 0)
			return false;
		else
		{
			return table.at(Tile(tile)).solid;
		}
	}

	

	void TileMap::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
	

		int x, y;
		for (int i = 0; i < 80; ++i)
		{
			x = (i % 10) * 128;
			y = (i / 10) * 128;
			sf::IntRect textureRect(0, 0, 128, 128);
			int tile = _dessertMap.at(i);

			/*_tiles[tile]setPosition(x, y); vector of tile
			target.draw(_tile[tile], state);*/

			switch (tile)
			{
			case 0:
				break;
			case 1:
				_tile1.setPosition(x, y);
				target.draw(_tile1, state);
				break;
			case 2:
				_tile2.setPosition(x, y);
				target.draw(_tile2, state);
				break;
			case 3:
				_tile3.setPosition(x, y);
				target.draw(_tile3, state);
				break;
			case 4:
				_tile4.setPosition(x, y);
				target.draw(_tile4, state);
				break;
			case 5:
				_tile5.setPosition(x, y);
				target.draw(_tile5, state);
				break;
			case 6:
				_tile6.setPosition(x, y);
				target.draw(_tile6, state);
				break;
			case 7:
				_tile7.setPosition(x, y);
				target.draw(_tile7, state);
				break;
			case 8:
				_tile8.setPosition(x, y);
				target.draw(_tile8, state);
				break;
			case 9:
				_tile9.setPosition(x, y);
				target.draw(_tile9, state);
				break;
			case 10:
				_tile10.setPosition(x, y);
				target.draw(_tile10, state);
				break;
			case 11:
				_tile11.setPosition(x, y);
				target.draw(_tile11, state);
				break;
			case 12:
				_tile12.setPosition(x, y);
				target.draw(_tile12, state);
				break;
			case 13:
				_tile13.setPosition(x, y);
				target.draw(_tile13, state);
				break;
			case 14:
				_tile14.setPosition(x, y);
				target.draw(_tile14, state);
				break;
			case 15:
				_tile15.setPosition(x, y);
				target.draw(_tile15, state);
				break;
			case 16:
				_tile16.setPosition(x, y);
				target.draw(_tile16, state);
				break;
			case 17:
				_tileObject1.setPosition(x, y+50);
				target.draw(_tileObject1, state);
				break;
			case 18:
				_tileObject2.setPosition(x, y+55);
				target.draw(_tileObject2, state);
				break;
			case 19:
				_tileObject3.setPosition(x, y + 55);
				target.draw(_tileObject3, state);
				break;
			case 20:
				_tileObject4.setPosition(x, y +100);
				target.draw(_tileObject4, state);
				break;
			case 21:
				_tileObject6.setPosition(x, y + 25);
				target.draw(_tileObject6, state);
				break;
			case 22:
				_tileObject7.setPosition(x, y+80);
				target.draw(_tileObject7, state);
				break;
			case 23:
				_tileObject9.setPosition(x, y + 80);
				target.draw(_tileObject9, state);
				break;
			case 24:
				_tileObject10.setPosition(x, y+50 );
				target.draw(_tileObject10, state);
				break;
			case 25:
				_tileObject11.setPosition(x, y + 80);
				target.draw(_tileObject11, state);
				break;
			case 26:
				_tileObject14.setPosition(x - 100 , y - 125);
				target.draw(_tileObject14, state);
				break;
			case 27:
				_tileObject5.setPosition(x , y + 35);
				target.draw(_tileObject5, state);
				break;
			case 28:
				_tileObject12.setPosition(x, y + 60);
				target.draw(_tileObject12, state);
				break;
			default:
				break;
			}
			
		}
	}
	void TileMap::loadMap()
	{
		_dessertMap =
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 24, 0, 27, 22, 0, 0, 0,
			0, 0, 0, 14, 15, 15, 16, 0, 0, 0,
			17, 0, 0, 0, 0, 0, 0, 0, 20, 28,
			15, 16, 0, 0, 0, 0, 0, 0, 14, 15,
			18, 0, 23, 25, 26, 19, 0, 0, 21, 0,
			1, 2, 2, 2, 2, 2, 2, 2, 2, 3,
			4, 5, 5, 5, 5, 5, 5, 5, 5, 6 };
	}
}
