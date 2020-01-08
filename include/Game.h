#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define _WIN32_WINNT 0x501

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


#include <cmath>
#include <vector>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Object.h"
#include "Car.h"
#include "OBJLoader.h"
#include "Track.h"

using namespace glm;
using namespace std;

const  int FPS = 60;
const  int amount_of_trees = 10;
const  int amount_of_lights = 4;
const  float max_angle = 10;
const  float changing_angle = 0.75;
const  int enemyCount =4;

class Game
{
    public:
        Game();
        void run(GLFWwindow* window, ShaderProgram* pointer);
        void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods);

    protected:

    private:
        bool collision(Car &car, Object &object);
        float toRadians(float angle);
        void setCamera(mat4 &V, Car player);
        void drawScene(GLFWwindow* window,mat4 &V, mat4 &P, Object &cube,Object &track, Car &player, Object tree[amount_of_trees], Car &enemy);
        void moving(mat4 &V,  Car &player);
        void game( string msg);//Object &cube, Object &track,Car &player,Object tree[amount_of_trees], Car &enemy);
        SOCKET getConnectionSocket(const char* serverName);
        void sendKeyInfoToServer(SOCKET ConnectSocket);
        void getInfoFromServer(SOCKET ConnectSocket);
        float distance_to_player;
        float pitch_angle;
        float angle_around_player;
        float aspectRatio;
        float speed_angle;

        bool turnLeft;
        bool turnRight;
        bool goPlayer;
        bool backPlayer;
        ShaderProgram *sp;
};

#endif // GAME_H
