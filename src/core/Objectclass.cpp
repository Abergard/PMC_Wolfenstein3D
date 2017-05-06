#include "Objectclass.hpp"

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

GLuint Objectclass::loadBMP_custom(
    const char* imagepath,
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
        FILE* file{nullptr};
        if (fopen_s(&file, imagepath, "rb"))
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

        // Everything is in memory now, the file can be closed
        fclose(file);

        // Create one OpenGL texture
        glGenTextures(1, &textureID[numberOfTexture]);
    }

    ChooseBMP(numberOfTexture);
    return 1;
}

void Objectclass::DeleteBMP()
{
    for (int i = 0; i < count_texture; ++i)
    {
        delete[] data[i];
        data[i] = NULL;
    }
}

void Objectclass::ChooseBMP(int numberOfTexture)
{
    // "Bind" the newly created texture : all future texture functions will
    // modify this texture
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
