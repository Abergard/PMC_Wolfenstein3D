#pragma once
//my includes
#include "Camera.hpp"

class Window;

// functions
void Display(Window&, Camera&);
void DeleteQuadric(GLUquadricObj* m_object);
void SceneDraw(GLfloat width, GLfloat length);

void WallCreate();
void RoomDelete();
void Doors(Camera&);
void BarsCreate();
