#pragma once

#include "Common.h"
#include "RCore.h"
#include "RMath.h"

namespace REng
{
extern void Start(const char* windowTitle);
extern void Start(const char* windowTitle, int width, int height);
extern void Run(bool (*gameLoop)(), void (*uiDebugUpdate)());
extern void Run(bool (*gameLoop)());
extern void Stop();
extern void ResourcesFullPath(const std::string& imageName, std::string& fullPath);
}
