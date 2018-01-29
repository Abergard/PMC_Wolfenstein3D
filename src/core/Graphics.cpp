#include "Graphics.hpp"

// #include <unordered_map>
#include <iostream>
// #include <set>
#include <array>

#include "ObjectCube.hpp"
#include "Window.hpp"

namespace
{
const float wall_size = 10.0f;

enum class MO
{
    Wall,
    RWall,
    LWall,
    Corner,
    RCorner,
    Door,
    Prison,
    Empty
};
constexpr std::size_t width_walls = 13;
constexpr std::size_t height_walls = 14;

// clang-format off
const std::array<MO, width_walls * height_walls> map_objects{
  MO::Corner,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall, MO::RCorner,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty,MO::RWall,
  MO::LWall, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::Empty, MO::RWall,
  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall,  MO::Wall, MO::Wall};
// clang-format on
}

///////////////////////////////////

Graphics::Graphics()
{
    WallCreate();
}

///////////////////////////////////
void Graphics::Display(Window& window, Camera& camera)
{
    //
    glEnable(GL_TEXTURE_2D); // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH); // Enable Smooth Shading
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);  // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,
           GL_NICEST); // Really Nice Perspective

    camera.Hud(window.get_id());

    glClearColor(0.2f, 0.2f, 0.2f, 0.2f); // Black Background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f); // Depth Buffer Setup

    if (!objectclass.loadBMP_custom(hud, 4))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

    glTranslatef(0, 0, 0);

    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(camera.width, 0);
    glVertex2f(camera.width, camera.height / 8);
    glVertex2f(0, camera.height / 8);

    glColor3f(1, 0, 0);
    glVertex2f(0, camera.height - camera.height / 4);
    glVertex2f(camera.width, camera.height - camera.height / 4);
    glVertex2f(camera.width, camera.height);
    glVertex2f(0, camera.height);

    glVertex2f(0, 0);
    glVertex2f(0, camera.height);
    glVertex2f(camera.width / 10, camera.height);
    glVertex2f(camera.width / 10, 0);

    glVertex2f(camera.width - camera.width / 10, 0);
    glVertex2f(camera.width - camera.width / 10, camera.height);
    glVertex2f(camera.width, camera.height);
    glVertex2f(camera.width, 0);

    glColor3f(0.8, 0.8, 0.8);
    // pasek HP itp
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(10, camera.height - camera.height / 5);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(camera.width - 10, camera.height - camera.height / 5);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(camera.width - 10, camera.height - 5);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(10, camera.height - 5);

    glEnd();

    camera.Move(window.get_id());

    //
    glDisable(GL_TEXTURE_2D);
    SceneDraw(20.0f, 20.0f);
    glEnable(GL_TEXTURE_2D);

    if (!objectclass.loadBMP_custom(walls, 0))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

    WallDraw();
    // Doors(camera);
    // BarsCreate();

    glFlush();
    window.swapBuffer();
}

void Graphics::SceneDraw(GLfloat, GLfloat)
{
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    glEnd();

    glBegin(GL_QUADS);

    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex3f(0, 0.0f, 0.0f);
    glVertex3f(0, 0.0f, lenght_scene);
    glVertex3f(width_scene, 0.0f, lenght_scene);
    glVertex3f(width_scene, 0.0f, 0);

    glEnd();

    glPopMatrix();
}

void Graphics::addCommonWall(float x, float y, float z, bool rotated = false)
{
    wall.emplace_back(objectclass,
                      x,
                      y,
                      z,
                      size_quads,
                      size_quads,
                      size_quads,
                      0.8f,
                      0.8f,
                      0.8f,
                      false,
                      rotated);
}

void Graphics::WallCreate() // 14
{
    std::size_t i = 0;
    for (auto&& object : map_objects)
    {
        std::size_t row = i / width_walls;
        std::size_t column = i - (row * width_walls);

        switch (object)
        {
        case MO::LWall:
            addCommonWall(column * wall_size, 0.0f, row * wall_size, false);
            break;
        case MO::RWall:
            addCommonWall(column * wall_size + wall_size, 0.0f, row * wall_size, false);
            break;
        case MO::Corner:
            addCommonWall(column * wall_size, 0.0f, row * wall_size, false);
            addCommonWall(column * wall_size, 0.0f, row * wall_size, true);
            break;
        case MO::RCorner:
            addCommonWall(column * wall_size + wall_size, 0.0f, row * wall_size, false);
            addCommonWall(column * wall_size, 0.0f, row * wall_size, true);
            break;
        case MO::Wall:
            addCommonWall(column * wall_size, 0.0f, row * wall_size, true);
            break;
        case MO::Empty:
            break;
        }
        ++i;
    }
}

void Graphics::WallDraw()
{
    std::for_each(wall.begin(), wall.end(), [](const auto& object){object.CreateWall();});
}

void Graphics::Doors(Camera& camera)
{
    int i = 0;

    door[i++] = new OBJECT_CUBE(objectclass,
                                50.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                true);

    door[i - 1]->Move(camera.CLOSE[0]);
    door[i - 1]->CreateDoor(true);

    door[i++] = new OBJECT_CUBE(objectclass,
                                100.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                true);
    door[i - 1]->Move(camera.CLOSE[2]);
    door[i - 1]->CreateDoor(true);

    door[i++] = new OBJECT_CUBE(objectclass,
                                50.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                true);
    door[i - 1]->Move(camera.CLOSE[1]);
    door[i - 1]->CreateDoor(true);

    door[i++] = new OBJECT_CUBE(objectclass,
                                100.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                true);
    door[i - 1]->Move(camera.CLOSE[3]);
    door[i - 1]->CreateDoor(true);

    door[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                80.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                true);
    door[i - 1]->CreateDoor(false);
}

void Graphics::BarsCreate()
{
    int i = 0;
    tabBar[i++] = new OBJECT_CUBE(objectclass,
                                  -10.0,
                                  0.0f,
                                  20.0f,
                                  size_quads,
                                  size_quads,
                                  size_quads,
                                  0.8f,
                                  0.8f,
                                  0.8f);
    tabBar[i++] = new OBJECT_CUBE(objectclass,
                                  -10.0,
                                  0.0f,
                                  50.0f,
                                  size_quads,
                                  size_quads,
                                  size_quads,
                                  0.8f,
                                  0.8f,
                                  0.8f);
    tabBar[i++] = new OBJECT_CUBE(objectclass,
                                  -10.0,
                                  0.0f,
                                  80.0f,
                                  size_quads,
                                  size_quads,
                                  size_quads,
                                  0.8f,
                                  0.8f,
                                  0.8f);
    tabBar[i++] = new OBJECT_CUBE(objectclass,
                                  -10.0,
                                  0.0f,
                                  110.0f,
                                  size_quads,
                                  size_quads,
                                  size_quads,
                                  0.8f,
                                  0.8f,
                                  0.8f);
    tabBar[i++] = new OBJECT_CUBE(objectclass,
                                  -10.0,
                                  0.0f,
                                  140.0f,
                                  size_quads,
                                  size_quads,
                                  size_quads,
                                  0.8f,
                                  0.8f,
                                  0.8f);
}
