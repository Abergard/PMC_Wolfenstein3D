#include "Graphics.hpp"

#include "ObjectCube.hpp"
#include "Window.hpp"

///////////////////////////////////

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

    // ROOMS CREATING
    WallCreate();
    Doors(camera);
    BarsCreate();

    // ROOMS DESTROYING
    RoomDelete();

    glFlush();
    window.swapBuffer();
}

void Graphics::SceneDraw(GLfloat, GLfloat)
{
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 20.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(0.0f, 10.0f, 10.0f);

    glEnd();

    glBegin(GL_QUADS);

    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex3f(0, 0.0f, 20);
    glVertex3f(0, 0.0f, lenght_scene - 50);
    glVertex3f(width_scene - 70, 0.0f, lenght_scene - 50);
    glVertex3f(width_scene - 70, 0.0f, 20);

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
    addCommonWall(0.0, 0.0f, 10.0f); // poziomo // 3
    addCommonWall(10.0, 0.0f, 10.0f);
    addCommonWall(20.0, 0.0f, 10.0f);

    constexpr std::size_t number_of_prisons = 4;

    float pos = 30.0f;
    for (int i = 0; i < number_of_prisons; ++i)
    {
        addCommonWall(0.0, 0.0f, pos);
        addCommonWall(0.0, 0.0f, pos + 10.0f);
        pos += 30.0f;
    }
    constexpr float room_width = 130.0f;
    for(float pos = 0.0f; pos < room_width; pos += 10)
    {
        addCommonWall(pos, 0.0f, 140.0f, true);
        addCommonWall(pos, 0.0f, 10.0f, true);
    }
    // addCommonWall(0.0, 0.0f, 140.0f, true); // poziomo // 3
    // addCommonWall(10.0, 0.0f, 140.0f, true);
    // addCommonWall(20.0, 0.0f, 140.0f, true);

    // addCommonWall(40.0, 0.0f, 140.0f, true); // poziomo // 3
    // addCommonWall(50.0, 0.0f, 140.0f, true);
    // addCommonWall(60.0, 0.0f, 140.0f, true);

    // addCommonWall(80.0, 0.0f, 140.0f, true); // poziomo // 4
    // addCommonWall(90.0, 0.0f, 140.0f, true);
    // addCommonWall(100.0, 0.0f, 140.0f, true);
    // addCommonWall(110.0, 0.0f, 140.0f, true);

    // addCommonWall(40.0, 0.0f, 10.0f, true); // poziomo		// 3
    // addCommonWall(50.0, 0.0f, 10.0f, true);
    // addCommonWall(60.0, 0.0f, 10.0f, true);

    // addCommonWall(30.0, 0.0f, 20.0f); // pionowo	// 4
    // addCommonWall(30.0, 0.0f, 30.0f);
    // addCommonWall(30.0, 0.0f, 40.0f);
    // addCommonWall(30.0, 0.0f, 50.0f);

    // addCommonWall(70.0, 0.0f, 100.0f); // poziomo    // 2
    // addCommonWall(80.0, 0.0f, 100.0f);

    // addCommonWall(30.0, 0.0f, 100.0f); // pionow     // 5
    // addCommonWall(30.0, 0.0f, 110.0f);
    // addCommonWall(30.0, 0.0f, 120.0f);
    // addCommonWall(30.0, 0.0f, 130.0f);
    // addCommonWall(30.0, 0.0f, 140.0f);

    // addCommonWall(70.0, 0.0f, 110.0f); // pionowo    // 4
    // addCommonWall(70.0, 0.0f, 120.0f);
    // addCommonWall(70.0, 0.0f, 130.0f);
    // addCommonWall(70.0, 0.0f, 140.0f);

    // addCommonWall(120.0, 0.0f, 110.0f); // pionowo    // 4
    // addCommonWall(120.0, 0.0f, 120.0f);
    // addCommonWall(120.0, 0.0f, 130.0f);
    // addCommonWall(120.0, 0.0f, 140.0f);

    // addCommonWall(70.0, 0.0f, 20.0f); // pionowo	// 4
    // addCommonWall(70.0, 0.0f, 30.0f);
    // addCommonWall(70.0, 0.0f, 40.0f);
    // addCommonWall(70.0, 0.0f, 50.0f);

    // addCommonWall(120.0, 0.0f, 20.0f); // pionowo	// 4
    // addCommonWall(120.0, 0.0f, 30.0f);
    // addCommonWall(120.0, 0.0f, 40.0f);
    // addCommonWall(120.0, 0.0f, 50.0f);

    // addCommonWall(30.0, 0.0f, 60.0f); // poziomo    // 3
    // addCommonWall(70.0, 0.0f, 60.0f);
    // addCommonWall(80.0, 0.0f, 60.0f);

    // addCommonWall(80.0, 0.0f, 10.0f); // poziomo // 4
    // addCommonWall(90.0, 0.0f, 10.0f);
    // addCommonWall(100.0, 0.0f, 10.0f);
    // addCommonWall(110.0, 0.0f, 10.0f);
}

void Graphics::RoomDelete()
{
    // for (int i = 0; i < wall.size(); ++i)
    // {
    //     if (wall[i] != NULL)
    //     { // MessageBox(NULL, "CLEANER", NULL, NULL);
    //         delete wall[i];
    //         wall[i] = NULL;
    //     }
    // }
    wall.clear();

    for (int i = 0; i < door_size; ++i)
    {
        if (door[i] != NULL)
        { // MessageBox(NULL, "CLEANER", NULL, NULL);
            delete door[i];
            door[i] = NULL;
        }
    }

    for (int i = 0; i < bars_size; ++i)
    {
        if (tabBar[i] != NULL)
        { // MessageBox(NULL, "CLEANER", NULL, NULL);
            delete tabBar[i];
            tabBar[i] = NULL;
        }
    }
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
