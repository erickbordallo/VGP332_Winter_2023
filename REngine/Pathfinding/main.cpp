#include <REngine.h>
#include "Tilemap.h"


Tilemap myTileMap;

void GameInit()
{
	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");
}

bool GameUpdate()
{
	myTileMap.Render();
	
	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{
	ImGui::Begin("Debug");
	ImGui::End();
}

int main()
{
	REng::Start("MyPathfinding");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}


