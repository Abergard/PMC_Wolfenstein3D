
#pragma once

// includes
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <gl\GLU.h>
#include <math.h>

//function
void Refresh(HWND hWnd);
void Hud(HWND hWnd);
void Move(HWND hWnd);
void MapCreate();
inline bool TestMap(float x, float z, bool door = false);
