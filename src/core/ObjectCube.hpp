#pragma once

struct Objectclass;

class OBJECT_CUBE
{
private:
    /////////////////////////////////////////
    float x, y, z;
    float R, G, B;
    float width;
    float length;
    float height;

    float door_x;
    float door_z;
    bool rotated;

    Objectclass& objectclass;

    /////////////////////////////////////////

    void CreateBars();

public:
    void CreateWall() const;
    /////////////////////////////////////////
    OBJECT_CUBE(Objectclass&,
                float x,
                float y,
                float z,
                float widht,
                float length,
                float height,
                float R,
                float G,
                float B,
                bool door,
                bool rotated = false);
    OBJECT_CUBE(Objectclass&,
                float x,
                float y,
                float z,
                float widht,
                float length,
                float height,
                float R,
                float G,
                float B);
    ~OBJECT_CUBE();

    void CreateDoor(bool front);
    void Move(bool);
};
