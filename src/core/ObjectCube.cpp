#include "ObjectCube.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\GLU.h>

#include "Objectclass.hpp"

const char* bars = "textures/bars.bmp";
const char* door2 = "textures/door2.bmp";
const char* door_front = "textures/door.bmp";
const char* walls = "textures/walls2.bmp";

OBJECT_CUBE::OBJECT_CUBE(Objectclass& ob,
                         float x,
                         float y,
                         float z,
                         float widht,
                         float length,
                         float height,
                         float R,
                         float G,
                         float B)
    : objectclass{ob}
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = widht;
    this->length = length;
    this->height = height;
    this->R = R;
    this->G = G;
    this->B = B;

    this->door_x = 0;
    this->door_z = 0;

    CreateBars();
}
OBJECT_CUBE::OBJECT_CUBE(Objectclass& ob,
                         float x,
                         float y,
                         float z,
                         float widht,
                         float length,
                         float height,
                         float R,
                         float G,
                         float B,
                         bool door)
    : objectclass{ob}
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = widht;
    this->length = length;
    this->height = height;
    this->R = R;
    this->G = G;
    this->B = B;

    this->door_x = 0;
    this->door_z = 0;

    if (door == false)
    {
        this->CreateWall();
    }
}

OBJECT_CUBE::~OBJECT_CUBE()
{
}

void OBJECT_CUBE::CreateWall()
{
    glBegin(GL_QUADS);
    glPushMatrix();
    glColor3f(this->R, this->G, this->B);

    // front
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z + this->width);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y + this->height, z + this->width);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + this->height, z);

    // back
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x + this->length, y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + this->length, y, z + this->width);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z + this->width);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z);

    // right
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z + this->width);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + this->length, y, z + this->width);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z + this->width);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + this->height, z + this->width);

    // left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + this->length, y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + this->height, z);

    glPopMatrix();
    glEnd();
}

void OBJECT_CUBE::CreateDoor(bool front)
{
    int x_copy = x;
    int z_copy = z;

    ////////////////////////////////////////////////////////
    // change texture
    if (!objectclass.loadBMP_custom(door_front, 2))
    {
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);
        return;
    }

    glPushMatrix();
    glTranslatef(door_x, 0, door_z);
    glBegin(GL_QUADS);
    glColor3f(this->R, this->G, this->B);

    if (front == true)
    {
        // door
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z + this->width / 2);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x + this->length, y, z + this->width / 2);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x + this->length, y + this->height, z + this->width / 2);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y + this->height, z + this->width / 2);

        x += this->length;
        x_copy -= this->length;
    }
    else
    {
        // door
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x + this->length / 2, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + this->length / 2, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + this->length / 2, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x + this->length / 2, y + this->height, z);

        z += this->width;
        z_copy -= this->width;
    }

    glEnd();
    glPopMatrix();
    ////////////////////////////////////////////////////////
    // return texture
    if (!objectclass.loadBMP_custom(walls, 0))
    {
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);
        return;
    }

    glPushMatrix();
    glBegin(GL_QUADS);

    if (front == true)
    {
        ////////////////////// left ///////////////////////////////
        // back
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z + this->width);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + this->length, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + this->length, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z + this->width);

        // front
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + this->length, y, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + this->length, y + this->height, z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z);

        ////////////////////// right ///////////////////////////////
        // back
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy, y, z_copy + this->width);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z_copy + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(
            x_copy + this->length, y + this->height, z_copy + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy, y + this->height, z_copy + this->width);

        // front
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy, y, z_copy);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z_copy);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z_copy);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy, y + this->height, z_copy);
    }
    else
    {
        ////////////////////// up ///////////////////////////////
        // right
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z);

        ////////////////////// up ///////////////////////////////
        // left
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z);

        ////////////////////// down ///////////////////////////////
        // right
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z_copy);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z_copy + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y + this->height, z_copy + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z_copy);

        ////////////////////// down ///////////////////////////////
        // left
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z_copy);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z_copy + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(
            x_copy + this->length, y + this->height, z_copy + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z_copy);
    }

    glEnd();

    //////////////////////// left /////////////////////////////
    // change texture
    if (!objectclass.loadBMP_custom(door2, 1))
    {
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);
        return;
    }

    glBegin(GL_QUADS);
    if (front == true)
    {
        // right
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z);

        // left
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy + this->length, y + this->height, z);
    }
    else
    {
        // front
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + this->length, y, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + this->length, y + this->height, z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y + this->height, z);

        // back
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x_copy, y, z_copy + this->width);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x_copy + this->length, y, z_copy + this->width);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(
            x_copy + this->length, y + this->height, z_copy + this->width);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x_copy, y + this->height, z_copy + this->width);
    }

    glPopMatrix();
    glEnd();
}

void OBJECT_CUBE::CreateBars()
{
    // change texture
    if (!objectclass.loadBMP_custom(bars, 3))
    {
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);
        return;
    }

    glBegin(GL_QUADS);
    glPushMatrix();

    glColor3f(this->R, this->G, this->B);

    // bars
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x + this->length, y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + this->length, y, z + this->width);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z + this->width);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x + this->length, y + this->height, z);

    glPopMatrix();
    glEnd();
}

void OBJECT_CUBE::Move(bool CLOSE)
{
    if (CLOSE)
        this->door_x = 0;
    else
        this->door_x -= 10.0f;
}
