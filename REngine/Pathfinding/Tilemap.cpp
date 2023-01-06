#include "Tilemap.h"

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void Tilemap::LoadTileMap(const char* tileMap, int tileSize)
{
	//Implement this
}

void Tilemap::LoadTiles(const char* tilesPath)
{
	//Implement this
}

void Tilemap::Render()
{
	//Implement This
}