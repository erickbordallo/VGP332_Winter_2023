#include <iostream>
#include <string>
#include <REngine.h>

#include "Tilemap.h"

REng::Math::Vector2 position;
Texture2D myTexture;
Rectangle rect;
float offsetY = 94;
float offsetX = 80;
int frames = 6;
int currentFrame = 0;

float animMaxTime = 0.2f;
float currentTime = 0.0f;

Tilemap myTileMap;

void GameInit()
{
	std::string fullPath;
	REng::ResourcesFullPath("hero_spritesheet.png", fullPath);
	rect.x = 0.0f;
	rect.y = offsetY;
	rect.width = offsetX;
	rect.height = offsetY;

	myTexture = LoadTexture(fullPath.c_str());

	myTileMap.LoadTileMap("tilemap.txt", 32);
	myTileMap.LoadTiles("tiles.txt");
}

bool GameUpdate()
{
	myTileMap.Render();
	float moveSpeed = 200.0f;
	if (IsKeyDown(KeyboardKey::KEY_RIGHT))
	{
		position.x += moveSpeed * GetFrameTime();
		currentTime += GetFrameTime();

		if (currentTime > animMaxTime)
		{
			currentFrame++;
			currentFrame = currentFrame % frames;
			rect.x = currentFrame * offsetX;
			currentTime = 0.0f;
			rect.width = offsetX;
		}
	}

	if (IsKeyDown(KeyboardKey::KEY_LEFT))
	{
		position.x -= moveSpeed * GetFrameTime();
		currentTime += GetFrameTime();

		if (currentTime > animMaxTime)
		{
			currentFrame++;
			currentFrame = currentFrame % frames;
			rect.x = currentFrame * offsetX;
			currentTime = 0.0f;
			rect.width = -offsetX;
		}
	}

	if (IsKeyDown(KeyboardKey::KEY_DOWN))
	{
		position.y += moveSpeed * GetFrameTime();
	}

	if (IsKeyDown(KeyboardKey::KEY_UP))
	{
		position.y -= moveSpeed * GetFrameTime();
	}

	//DrawTexture(myTexture, position.x, position.y, WHITE);
	DrawTextureRec(myTexture, rect, { position.x, position.y }, WHITE);
	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{
	ImGui::Begin("myimguiWindow");
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