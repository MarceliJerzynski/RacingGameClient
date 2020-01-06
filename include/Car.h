#ifndef CAR_H
#define CAR_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Markup.h"
#include "shaderprogram.h"

const float max_wheel_angle = 45;
const float turn_angle = 0.75;
const float turn_wheel_angle = turn_angle*3;

class Car
{
    public:
        Car();
        void loadFromPath(string pathBody,string pathChassis,string pathHeadlit,string pathLicense,string pathWheel, string texPathBody,string texPathChassis,string texPathheadlit,string texPathLicense, string texPathWheel, float apower, float abpower,vec3 aposition,
            float rotX, float rotY, float rotZ, float ascale);
        Object * getBody();
        void setV(float av);
        float getV();
        vec3 getPosition();
        float getRotation();
        void setRotation(float rotX, float rotY, float rotZ);
        float getWheelRotation();
        Markup * getMarkup();
        bool checkpointReached();
        void render(mat4 V, mat4 P, ShaderProgram *sp);
        void turnLeft();
        void turnRight();
        void turnWheelLeft();
        void turnWheelRight();
        int isMoving(); //1 - do przodu, -1 - do tylu, 0 - stoi
        void move(int going);   //0 - nie klika nic, 1 - trzyma W, 2 - trzyma S
        void AI();
        Object * collision(Car * object);
    protected:
        Object *body, *chassis, *headlit, *license;
        Object *FLW,*FRW,*RLW,*RRW;
        float Power;
        float backPower;
        float temporaryPower;
        float v;
        float acceleration;
        bool goForward;
        bool goBackward;
        float wheelRotation;
        Markup *markup;
    private:
};

#endif // CAR_H
