#pragma once

#include <REngine.h>
#include <AI.h>

class Tilemap
{
public:
	void LoadTileMap(const char* tileMap, int tileSize);
	void LoadTiles(const char* tilesPath);
	void Render();

private:
	std::vector<int> mTileMap;
	std::vector<Texture2D> mTileMapTextures;

	AI::GridBasedGraph mGridBasedGraph;
	int mRows;
	int mColumns;
	int mTileSize;
};