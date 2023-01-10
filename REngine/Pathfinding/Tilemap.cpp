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

	//TODO
	mGridBasedGraph.Initialize(mColumns, mRows);
	//for()
	//	for()
	//		//Connect the nodes to it's neighbors
	//		mGridBasedGraph.GetNode(4, 5)->neighbors[AI::GridBasedGraph::Directions::East] = mGridBasedGraph.GetNode(5, 5);
}

void Tilemap::LoadTiles(const char* tilesPath)
{
	//Implement this
}

void Tilemap::Render()
{
	//Implement This

	//DrawLine()
}