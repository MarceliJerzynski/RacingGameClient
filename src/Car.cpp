#include "Car.h"

Car::Car()
{
}

void Car::loadFromPath(string pathBody,string pathChassis,string pathHeadlit,string pathLicense,string pathWheel, string texPathBody,
                        string texPathChassis,string texPathHeadlit,string texPathLicense, string texPathWheel, float ascale)
{
//Ladowanie poszczegolnych obiektow
//----------------------------------------------------------------------------------------------------------------------
    markup = new Markup();

    body=new Object();
    body->loadFromPath(pathBody,texPathBody, ascale);

    chassis=new Object();
    chassis->loadFromPath(pathChassis,texPathChassis, ascale);

    headlit=new Object();
    headlit->loadFromPath(pathHeadlit,texPathHeadlit, ascale);

    license=new Object();
    license->loadFromPath(pathLicense,texPathLicense, ascale);

    FRW =new Object();
    FRW->loadFromPath(pathWheel,texPathWheel, ascale);

    RLW =new Object();
    RLW->loadFromPath(pathWheel,texPathWheel, ascale);

    RRW =new Object();
    RRW->loadFromPath(pathWheel,texPathWheel, ascale);

    FLW =new Object();
    FLW->loadFromPath(pathWheel,texPathWheel, ascale);

//----------------------------------------------------------------------------------------------------------------------



//Ustalanie wartosci poczatkowych
//----------------------------------------------------------------------------------------------------------------------
    // Power = apower;
    // temporaryPower = 0;
    // backPower = abpower;
    v = 0;
    acceleration = 0;
    goForward = false;
    goBackward = false;
    // c
//----------------------------------------------------------------------------------------------------------------------
}

Object * Car::getBody()
{
    return body;
}

void Car::setV(float av)
{
    v = av;
}

float Car::getV()
{
    return v;
}

vec3 Car::getPosition()
{
    return body->getPosition();
}

void Car::setPosition(vec3 aposition)
{
    body->setPosition(aposition);
    chassis->setPosition(aposition);
    headlit->setPosition(aposition);
    license->setPosition(aposition);
    FRW->setPosition(aposition);
    RLW->setPosition(aposition);
    RRW->setPosition(aposition);
    FLW->setPosition(aposition);
}


void Car::turnLeft()
{
    body->turn(turn_angle);
    chassis->turn(turn_angle);
    license->turn(turn_angle);
    headlit->turn(turn_angle);

    FLW->turn(turn_angle);
    FRW->turn(turn_angle);
    RLW->turn(turn_angle);
    RRW->turn(turn_angle);
}

void Car::turnRight()
{
    body->turn(-turn_angle);
    chassis->turn(-turn_angle);
    license->turn(-turn_angle);
    headlit->turn(-turn_angle);

    FLW->turn(-turn_angle);
    FRW->turn(-turn_angle);
    RLW->turn(-turn_angle);
    RRW->turn(-turn_angle);
}

void Car::turnWheelLeft()
{
    if ( FLW -> getRotationY() - body -> getRotationY() < max_wheel_angle*3.14f/180.0f)
    {
        FLW -> turn(turn_wheel_angle);
        FRW -> turn(turn_wheel_angle);
    }
}

void Car::turnWheelRight()
{
     if   (FLW -> getRotationY() - body -> getRotationY() >-max_wheel_angle*3.14f/180.0f)
    {
        FLW -> turn(-turn_wheel_angle);
        FRW -> turn(-turn_wheel_angle);
    }
}

int Car::isMoving()
{

//zatrzymanie samochodu
//----------------------------------------------------------------------------------------------------------------------
    if (v < 0.02 && v > -0.02)
    {
        return 0;
    }
    if (v > 0.02)
    {
        return 1;
    } else
    return -1;

//----------------------------------------------------------------------------------------------------------------------
}


void Car::move(int going)
//going = 1 <- gracz naciska W
//going = 2 <- gracz naciska S
//going = 0 <- gracz nie trzyma nic
{
    if ( going == 1 )
    {   if (temporaryPower < 1)
            temporaryPower += Power;
        else
            temporaryPower = 1;
    }


    else
    if (going == 2 )
    {
        if (temporaryPower > -0.5)
            temporaryPower -= backPower;
        else
            temporaryPower = -0.5;
    }


    else
    {
       temporaryPower = 0;
    }


    float resistance = v/3*2;
    if (going == 0)
    {
        resistance = resistance*3;
    }


    acceleration = temporaryPower - resistance;
    v = v + acceleration/60;
    float s = v;

    float x1,x2,y1,y2;
    x1 = body->getPosition().x;
    y1 = body->getPosition().z;
    body->move(s);
    chassis->move(s);
    license->move(s);
    headlit->move(s);

    x2 = body->getPosition().x;
    y2 = body->getPosition().z;

    vec3 aposition;
    aposition.x = 0.786 * cos(-body->getRotationY()) - 1.257*sin(-body->getRotationY()) + body->getPosition().x;
    aposition.y = body->getPosition().y + 0.334;
    aposition.z = 0.786 * sin(-body->getRotationY()) + 1.257*cos(-body->getRotationY()) + body->getPosition().z;

    FLW->setPosition(aposition);

    aposition.x = -0.786 * cos(-body->getRotationY()) - 1.257*sin(-body->getRotationY()) + body->getPosition().x;
    aposition.y = body->getPosition().y + 0.334;
    aposition.z = -0.786 * sin(-body->getRotationY()) + 1.257*cos(-body->getRotationY()) + body->getPosition().z;

    FRW->setPosition(aposition);

    aposition.x = -0.786 * cos(-body->getRotationY()) + 1.353*sin(-body->getRotationY()) + body->getPosition().x;
    aposition.y = body->getPosition().y + 0.334;
    aposition.z = -0.786 * sin(-body->getRotationY()) - 1.353*cos(-body->getRotationY()) + body->getPosition().z;

    RRW->setPosition(aposition);

    aposition.x = 0.786 * cos(-body->getRotationY()) + 1.353*sin(-body->getRotationY()) + body->getPosition().x;
    aposition.y = body->getPosition().y + 0.334;
    aposition.z = 0.786 * sin(-body->getRotationY()) - 1.353*cos(-body->getRotationY()) + body->getPosition().z;

    RLW->setPosition(aposition);


//operacje kr�cenia ko�em
//----------------------------------------------------------------------------------------------------------------------
FLW->rotateX(-v*100);
FRW->rotateX(-v*100);
RLW->rotateX(-v*100);
RRW->rotateX(-v*100);

//----------------------------------------------------------------------------------------------------------------------


//obliczanie prostej
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
}

float Car::getRotation()
{
    return body->getRotationY();
}

void Car::setRotation(float rotX, float rotY, float rotZ)
{
    body->setRotation(rotX, rotY, rotZ);
    headlit->setRotation(rotX, rotY, rotZ);
    license->setRotation(rotX, rotY, rotZ);
    chassis->setRotation(rotX, rotY, rotZ);
    FLW->setRotation(rotX, rotY, rotZ);
    FRW->setRotation(rotX, rotY - 180, rotZ);
    RRW->setRotation(rotX, rotY - 180, rotZ);
    RLW->setRotation(rotX, rotY, rotZ);
}

float Car::getWheelRotation()
{
    return FLW ->getRotationY() - body -> getRotationY();
}

Markup * Car::getMarkup()
{
    return markup;
}

bool Car::checkpointReached()
{
    //  if ((body->getPosition().x - markup->getPosition().x)*(body->getPosition().x - markup->getPosition().x)
    //     + (body->getPosition().z - markup->getPosition().z)*(body->getPosition().z - markup->getPosition().z) <= markup->getRadius()*markup->getRadius()) //znaki w drugim zamienione bo z jest odwrotnie
    // {
    //     markup->touched();
    //     return true;
    // }

    // return false;
    markup->touched();
}

void Car::render(mat4 V, mat4 P, ShaderProgram *sp)
{
    body->render(V, P, sp);
    chassis->render(V, P, sp);
    headlit->render(V, P, sp);
    license->render(V, P, sp);
    FLW->render(V, P, sp);
    FRW->render(V, P, sp);
    RLW->render(V, P, sp);
    RRW->render(V, P, sp);
}

void Car::AI()
{
    float deltax =atan2((markup->getPosition().z- body->getPosition().z ),( markup->getPosition().x-body->getPosition().x))+3.14;
    float angle=abs(fmod(body->getRotationY()+1.57-6.28*100,6.28));
    if(temporaryPower>0.3)
    {move(0);}
    else
    {move(1);
    }
    if(angle>deltax  && angle-deltax>0.1)
    {
        if(angle>5 && deltax<2)
        {
            turnRight();
            turnWheelRight();
        }
        else
        {
            turnLeft();
           turnWheelLeft();
        }
    }
    if(angle<deltax && deltax-angle>0.1)
    {
        if(deltax>5 && angle<2)
        {
            turnLeft();
            turnWheelLeft();
        }else
        {
             turnRight();
            turnWheelRight();
        }
    }
    checkpointReached();
}
