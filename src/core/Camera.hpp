#pragma once

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <gl\GLU.h>
#include <cmath>

//function
void Refresh(HWND hWnd);
void Hud(HWND hWnd);
void Move(HWND hWnd);
void MapCreate();
inline bool TestMap(float x, float z, bool door = false);
