#ifndef TRACK_H
#define TRACK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"

class Track
{
public:
    void loadFromPath(string path, string texturePath, vec3 position, float rotX, float rotY, float rotZ, float scale);
    Object * getTrack();
    Object getHitbox(int index);
    unsigned int getAmountOfHitbox();
    void render(mat4 V, mat4 P, ShaderProgram *sp);

protected:
    Object *track;
    vector<Object> hitbox;

private:



};


#endif // TRACK_H
