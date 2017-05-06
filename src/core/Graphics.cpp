#include "Graphics.hpp"

#include "ObjectCube.hpp"
#include "Objectclass.hpp"
#include "Window.hpp"

///////////////////////////////////
//
GLfloat width_scene = 200;
GLfloat lenght_scene = 200;

const int wall_size = 58;
OBJECT_CUBE* wall[wall_size];

const int door_size = 5;
OBJECT_CUBE* door[door_size];

const int bars_size = 5;
OBJECT_CUBE* tabBar[bars_size];

int size_quads = 10;

extern const char* door_front;
extern const char* door2;
extern const char* walls;
extern const char* bars;
extern const char* hud;

Objectclass objectclass{};

///////////////////////////////////
void Display(Window& window, Camera& camera)
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

void SceneDraw(GLfloat, GLfloat)
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

void WallCreate() // 14
{
    int i = 0;

    wall[i++] = new OBJECT_CUBE(objectclass,
                                0.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo // 3
    wall[i++] = new OBJECT_CUBE(objectclass,
                                10.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                20.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    // kraty
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                30.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo // 2
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                40.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    // kraty
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // 2
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                70.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                00.8f,
                                0.8f,
                                0.8f,
                                false);
    // kraty
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                90.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // 2
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    // kraty
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                120.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // 2
    wall[i++] = new OBJECT_CUBE(objectclass,
                                -10.0,
                                0.0f,
                                130.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    // kraty
    wall[i++] = new OBJECT_CUBE(objectclass,
                                0.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo // 3
    wall[i++] = new OBJECT_CUBE(objectclass,
                                10.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                20.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                40.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo // 3
    wall[i++] = new OBJECT_CUBE(objectclass,
                                50.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                60.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                80.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo // 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                90.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                100.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                110.0,
                                0.0f,
                                150.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                40.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo		// 3
    wall[i++] = new OBJECT_CUBE(objectclass,
                                50.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                60.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                20.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo	// 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                30.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                40.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                50.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo    // 2
    wall[i++] = new OBJECT_CUBE(objectclass,
                                80.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                100.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionow     // 5
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                110.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                120.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                130.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                140.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                110.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo    // 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                120.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                130.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                140.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                110.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo    // 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                120.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                130.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                140.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                20.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo	// 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                30.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                40.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                50.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                20.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // pionowo	// 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                30.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                40.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                120.0,
                                0.0f,
                                50.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                30.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo    // 3
    wall[i++] = new OBJECT_CUBE(objectclass,
                                70.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                80.0,
                                0.0f,
                                60.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);

    wall[i++] = new OBJECT_CUBE(objectclass,
                                80.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false); // poziomo // 4
    wall[i++] = new OBJECT_CUBE(objectclass,
                                90.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                100.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
    wall[i++] = new OBJECT_CUBE(objectclass,
                                110.0,
                                0.0f,
                                10.0f,
                                size_quads,
                                size_quads,
                                size_quads,
                                0.8f,
                                0.8f,
                                0.8f,
                                false);
}

void RoomDelete()
{

    for (int i = 0; i < wall_size; ++i)
    {
        if (wall[i] != NULL)
        { // MessageBox(NULL, "CLEANER", NULL, NULL);
            delete wall[i];
            wall[i] = NULL;
        }
    }

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

void Doors(Camera& camera)
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

void BarsCreate()
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
