#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;
class Camera
{
    public:
        Camera();
        void move(float dx, float dy, float dz);
        mat4 getV();
    protected:

    private:
        mat4 V;

        float x = 0;
        float y = 0;
        float z = -5;
};

#endif // CAMERA_H
