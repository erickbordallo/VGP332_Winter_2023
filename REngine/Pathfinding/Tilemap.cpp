#include "Tilemap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void Tilemap::LoadTileMap(const char* tileMap)
{
	std::fstream file;
	file.open(tileMap, std::ios::in);

	assert(file.is_open());
	std::string line;
	std::string value;

	//Reading Rows------------------------------
	std::getline(file, line);
	std::stringstream sStreamRows(line);
	std::getline(sStreamRows, value, ' ');
	std::getline(sStreamRows, value, '\n');

	mRows = atoi(value.c_str());
	//-----------------------------------------
	
	//Reading Columns------------------------------
	std::getline(file, line); //Read from file
	std::stringstream sStreamColumns(line);
	std::getline(sStreamColumns, value, ' ');
	std::getline(sStreamColumns, value, '\n');

	mColumns = atoi(value.c_str());
	//--------------------------------------------
	
	while (std::getline(file, line) && line != "")
	{
		std::string lineString = line;
		while (!lineString.empty())
		{
			size_t pos = lineString.find(" ");
			std::string tileValue = lineString.substr(0, pos);
			size_t prevSize = lineString.size();
			lineString = lineString.substr(pos + 1);
			size_t newSize = lineString.size();
			mTileMap.push_back(atoi(tileValue.c_str()));
			if (prevSize == newSize)
			{
				break;
			}
		}
	}

	file.close();
	assert(static_cast<int>(mTileMap.size()) == mRows * mColumns);

	//Implement this 
	//TODO
	mGridBasedGraph.Initialize(mColumns, mRows);

	//for()
	//	for()
	//		//Connect the nodes to it's neighbors
	//		mGridBasedGraph.GetNode(4, 5)->neighbors[AI::GridBasedGraph::Directions::East] = mGridBasedGraph.GetNode(5, 5);

	auto GetNeighbor = [&](int x, int y) -> GridBasedGraph::Node*
	{
		auto node = mGridBasedGraph.GetNode(x, y);

		if (node == nullptr)
			return nullptr;

		if (IsBlocked(x, y))
			return nullptr;

		return node;
	};


	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			auto currentTile = mTiles[mTileMap[ToIndex(x, y, mColumns)]];
			if (!IsBlocked(x, y))
			{
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::East] = GetNeighbor(x + 1, y);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::West] = GetNeighbor(x - 1, y);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::North] = GetNeighbor(x, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::South] = GetNeighbor(x, y + 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthEast] = GetNeighbor(x + 1, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthWest] = GetNeighbor(x - 1, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthEast] = GetNeighbor(x + 1, y + 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthWest] = GetNeighbor(x - 1, y + 1);
			}
		}
	}
}

REng::Math::Vector2 Tilemap::GetPixelPosition(int x, int y) const
{
	return
	{
		(x + 0.5f) * 32,
		(y + 0.5f) * 32
	};
}

std::vector<REng::Math::Vector2> Tilemap::FindPath(int startX, int startY, int endX, int endY)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;

	BFS bfs;
	if (bfs.Run(mGridBasedGraph, startX, startY, endX, endY))
	{
		closedList = bfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	else
	{
		mClosedList = bfs.GetClosedList();
	}

	return path;
}
//A -> B
//B -> A

void Tilemap::LoadTiles(const char* tilesPath)
{
	//Implement this
	std::fstream file;
	file.open(tilesPath, std::ios::in);
	assert(file.is_open(), "File does not exist!");

	std::string line;
	std::string value;

	std::getline(file, line); //Read from file
	std::stringstream sStreamRows(line);
	std::getline(sStreamRows, value, ' ');
	std::getline(sStreamRows, value, '\n');

	int numberOfTiles = atoi(value.c_str());
	for (int i = 0; i < numberOfTiles; ++i)
	{
		std::getline(file, line);

		std::string path;
		std::string weightText;
		int weight;

		std::stringstream sStreamTile(line);
		std::getline(sStreamTile, path, ' ');
		std::getline(sStreamTile, weightText, '\n');

		weight = atoi(weightText.c_str());

		std::string tileFullPath;
		REng::ResourcesFullPath(path, tileFullPath);
		Tile newTile;
		newTile.texture = LoadTexture(tileFullPath.c_str());
		newTile.weight = weight;
		mTiles.push_back(newTile);
	}

	file.close();
}

void Tilemap::Render()
{
	REng::Math::Vector2 position(0.0f, 0.0f);

	/// <summary>
	/// Rendering Tiles
	/// </summary>
	for (int y = 0; y < mRows; ++y)
	{
		int tileIndex = 0;
		for (int x = 0; x < mColumns; ++x)
		{
			tileIndex = mTileMap[ToIndex(x, y, mColumns)];
			auto backGroundTile = std::find_if(mTiles.begin(), mTiles.end(), [](const Tile& tile) {return tile.weight == 0; });

			DrawTexture(backGroundTile->texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			if (tileIndex != 0)
			{
				DrawTexture(mTiles[tileIndex].texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			}
			position.x += mTiles[tileIndex].texture.width;
		}
		position.x = 0.0f;
		position.y += mTiles[tileIndex].texture.height;
	}


	/// <summary>
	/// Rendering Grid
	/// </summary>
	const int tileSize = 32;
	constexpr float halfSize = static_cast<float>(tileSize) * 0.5f;
	REng::Math::Vector2 startingPosition(halfSize, halfSize);
	float sX = startingPosition.x;
	float sY = startingPosition.y;
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)sY, BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)sY, BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			sX += static_cast<float>(tileSize);
		}
		sX = static_cast<float>(tileSize) * 0.5f;
		sY += tileSize;
	}

}

bool Tilemap::IsBlocked(int x, int y) const
{
	return mTiles[mTileMap[ToIndex(x, y, mColumns)]].weight >= 5;
}

//Physically
// [___] [___] [___] [___] [___] [___] [___] [___] [___] 

//Conceptually
// [_0__] [_1__] [_2_]
// [3___] [__4] [__5]
// [_6_] [___] [___]
// [___] [___] [___]


//Cache
//[_0_][_1][_2_][_3_][_4_]

//What is a callable?
//Is anything that can be invoked like a function

#pragma region FunctionPointer
int Add(int x, int y) { return x + y; }
int Subtract(int x, int y) { return x - y; }

int (*FunctionPtr)(int, int);

void TestFunctionPointers()
{
	FunctionPtr = Add;
	int sum = FunctionPtr(4, 7);

	FunctionPtr = Subtract;
	int sub = FunctionPtr(3, 5);
}
#pragma endregion

//Function objects
#pragma region Functor
class Adder
{
public:
	int accumulatedValue = 0;
	int operator()(int a, int b) //invocation operator
	{
		accumulatedValue += a;
		return a + b;
	}
};


struct Subtractor
{
	int operator()(int a, int b) //invocation operator
	{
		return a - b;
	}
};

void TestFunctor()
{
	Adder adder;
	int sum = adder(4, 7);
}
#pragma endregion 

#pragma region Lambda
// Lambda is just an automatically generated functor
// It is syntatic sugar (sweet syntax), that otherwise does not add anything new to the language

//Anatomy of Lambdas
//[<capture>] (<parameterList>) -> <trailing return type>
//{
//	Function definition
//};

void TestLambda()
{
	int a = 4;
	int b = 7;

	auto func = [&]() {
		return a + b;
	};

	func();

	[&] {return a + b; }();
}
#pragma endregion