#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>


using namespace std;

class OBJLoader
{
    public:
        OBJLoader();
        void load(string path);
        float * getVerts();
        float * getNormals();
        float * getColors();
        unsigned int getVertexCount();
    protected:

    private:
        float *verts;
        float *normals;
        float *colors;
        unsigned int vertexCount;
};

#endif // OBJLOADER_H
