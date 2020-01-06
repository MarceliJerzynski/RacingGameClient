#include "Track.h"

 void Track::loadFromPath(string path, string texturePath, vec3 aposition, float rotX, float rotY, float rotZ, float ascale)
 {
     track = new Object();

     track->loadFromPath(path, texturePath, aposition, rotX, rotY, rotZ, ascale);

     vec3 help_position;

     Object object;

     for(unsigned int i = 2; i < track->getVertexCount(); i = i+3)
     {
         if (track->getVerts()[i] > 30 || track->getVerts()[i] < -30)
         {
             help_position.x = track->getVerts()[i-2];
             help_position.y = track->getVerts()[i-1];
             help_position.z = track->getVerts()[i];
             hitbox.push_back(object);
             hitbox[ hitbox.size() - 1 ].setPosition( help_position );
         }
     }
 }

Object * Track::getTrack()
{
    return track;
}

Object Track::getHitbox(int index)
{
    return hitbox[index];
}

unsigned int Track::getAmountOfHitbox()
{
    return hitbox.size();
}

void Track::render(mat4 V, mat4 P, ShaderProgram *sp)
{
    track->render(V, P, sp);
}
