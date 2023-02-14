#pragma once

#include <REngine.h>
#include <AI.h>
#include <EMath.h>

class Tilemap
{
public:
	struct Tile
	{
		Texture2D texture;
		int weight;
	};

	void LoadTileMap(const char* tileMap);
	void LoadTiles(const char* tilesPath);
	void Render();

	bool IsBlocked(int x, int y) const;

	std::vector<EMath::Vector2> FindPath(int startX, int startY, int endX, int endY);

	float GetCost(const AI::GridBasedGraph::Node* nodeA) const;
	std::vector<EMath::Vector2> FindPathDijkstra(int startX, int startY, int endX, int endY);

private:
	EMath::Vector2 GetPixelPosition(int x, int y) const;

	std::vector<int> mTileMap;
	std::vector<Tile> mTiles;

	AI::GridBasedGraph mGridBasedGraph;
	AI::NodeList mClosedList;
	int mRows;
	int mColumns;
};

//class PureVirtual
//{
//public:
//	virtual int GetId() const = 0;
//	float GetSpeed() { return 3.0f; }
//	virtual int GetAge() { return 0; }
//};
//
//class PureVirtualChild : public PureVirtual
//{
//public:
//	int GetAge() { return 32; }
//};