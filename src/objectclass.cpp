#include "objectclass.h"
#include <cstdio>
#include <cstdlib>
////////////////////////////////////////
// 0) wall
// 1) door left and right
// 2) door front
// 3) bars

////////////////////////////////////////
const int count_texture = 5;
bool notNull = true;
unsigned char* data[count_texture];
GLuint textureID[count_texture];
unsigned int width[count_texture];
unsigned int height[count_texture];
/*
const char* bars = "E:/Game Design/bitmap/bars.bmp";
const char* door2 = "E:/Game Design/bitmap/door2.bmp";
const char* door_front = "E:/Game Design/bitmap/door.bmp";
const char* walls = "E:/Game Design/bitmap/walls2.bmp";
const char* hud = "E:/Game Design/bitmap/hud24.bmp";
*/

const char* bars = "textures/bars.bmp";
const char* door2 = "textures/door2.bmp";
const char* door_front = "textures/door.bmp";
const char* walls = "textures/walls2.bmp";
const char* hud = "textures/hud24.bmp";

////////////////////////////////////////

OBJECT_CUBE::OBJECT_CUBE(float x,
                         float y,
                         float z,
                         float widht,
                         float length,
                         float height,
                         float R,
                         float G,
                         float B)
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
OBJECT_CUBE::OBJECT_CUBE(float x,
                         float y,
                         float z,
                         float widht,
                         float length,
                         float height,
                         float R,
                         float G,
                         float B,
                         bool door)
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
    if (!loadBMP_custom(door_front, 2))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

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
    if (!loadBMP_custom(walls, 0))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

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
    if (!loadBMP_custom(door2, 1))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

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
    if (!loadBMP_custom(bars, 3))
        MessageBox(NULL, "TEXTURE ERROR", NULL, MB_OK);

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

GLuint loadBMP_custom(const char* imagepath,
                      int numberOfTexture) // "E:/Game Design/bitmap/Agu.bmp"
{
    if (data[numberOfTexture] == NULL)
    {
        // Data read from the header of the BMP file
        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int
            dataPos; // Position in the file where the actual data begins
        unsigned int imageSize; // = width*height*3

        if (!imagepath)
        {
            MessageBox(NULL, "Image paht has not given", NULL, NULL);
            return 0;
        }

        // Open the file
        FILE* file = fopen(imagepath, "rb");
        if (!file)
        {
            MessageBox(NULL, "Image could not be opened", NULL, NULL);
            return 0;
        }

        if (fread(header, 1, 54, file) != 54)
        { // If not 54 bytes read : problem
            MessageBox(NULL, "Not a correct BMP file", NULL, NULL);
            return 0;
        }

        if (header[0] != 'B' || header[1] != 'M')
        {
            MessageBox(NULL, "Not a correct BMP file", NULL, NULL);
            return 0;
        }

        // Read ints from the byte array
        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);
        width[numberOfTexture] = *(int*)&(header[0x12]);
        height[numberOfTexture] = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)
            imageSize =
                width[numberOfTexture] * height[numberOfTexture] *
                3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos == 0)
            dataPos = 54; // The BMP header is done that way

        data[numberOfTexture] = new unsigned char[imageSize];

        // Read the actual data from the file into the buffer
        fread(data[numberOfTexture], 1, imageSize, file);

        //Everything is in memory now, the file can be closed
        fclose(file);

        // Create one OpenGL texture
        glGenTextures(1, &textureID[numberOfTexture]);
    }

    ChooseBMP(numberOfTexture);
    return 1;
}

void DeleteBMP()
{
    for (int i = 0; i < count_texture; ++i)
    {
        delete[] data[i];
        data[i] = NULL;
    }
}

void ChooseBMP(int numberOfTexture)
{
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID[numberOfTexture]);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width[numberOfTexture],
                 height[numberOfTexture],
                 0,
                 GL_BGR_EXT,
                 GL_UNSIGNED_BYTE,
                 data[numberOfTexture]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
