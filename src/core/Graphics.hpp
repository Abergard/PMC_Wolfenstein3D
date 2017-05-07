#pragma once

#include "Camera.hpp"
#include "Objectclass.hpp"

class Window;
class OBJECT_CUBE;

class Graphics
{
public:
    // functions
    void Display(Window&, Camera&);
    void DeleteQuadric(GLUquadricObj* m_object);
    void SceneDraw(GLfloat width, GLfloat length);

    void WallCreate();
    void RoomDelete();
    void Doors(Camera&);
    void BarsCreate();

private:
    //
    GLfloat width_scene = 200;
    GLfloat lenght_scene = 200;

    static constexpr int wall_size = 58;
    OBJECT_CUBE* wall[wall_size];

    static constexpr int door_size = 5;
    OBJECT_CUBE* door[door_size];

    static constexpr int bars_size = 5;
    OBJECT_CUBE* tabBar[bars_size];

    int size_quads = 10;

    const char* hud = "textures/hud24.bmp";
    const char* walls = "textures/walls2.bmp";

    Objectclass objectclass{};
};
