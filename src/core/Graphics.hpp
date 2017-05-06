#pragma once
//my includes
#include "Camera.hpp"

// functions
void Display(HDC hDC, HWND hWnd, Camera&);
void DeleteQuadric(GLUquadricObj* m_object);
void SceneDraw(GLfloat width, GLfloat length);

void WallCreate();
void RoomDelete();
void Doors(Camera&);
void BarsCreate();
