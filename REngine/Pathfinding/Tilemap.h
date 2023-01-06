#pragma once

#include <vector>
#include <REngine.h>

class Tilemap
{
public:
	void LoadTileMap(const char* tileMap, int tileSize);
	void LoadTiles(const char* tilesPath);
	void Render();

private:
	std::vector<int> mTileMap;
	std::vector<Texture2D> mTileMapTextures;
	int mRows;
	int mColumns;
	int mTileSize;
};