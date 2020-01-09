#include "Object.h"

Object::Object()
{
    radius = 0.4;
}

float Object::getRadius()
{
    return radius;
}

void Object::loadFromPath(string path, string texturePath,vec3 aposition, float rotX, float rotY, float rotZ, float ascale)
{
    OBJLoader loader;
    loader.load(path);
    position = aposition;
    setM(aposition, rotX, rotY, rotZ, ascale);
    verts = loader.getVerts();
    normals = loader.getNormals();
    colors = loader.getColors();
    vertexCount = loader.getVertexCount();
    tex = readTexture(texturePath);
}

void Object::loadFromPath(string path, string texturePath, float ascale)
{
    OBJLoader loader;
    loader.load(path);
    //position = aposition;
    setM(vec3(0,0,0), 0, 0, 0, ascale);
    verts = loader.getVerts();
    normals = loader.getNormals();
    colors = loader.getColors();
    vertexCount = loader.getVertexCount();
    tex = readTexture(texturePath);
}


void Object::loadFromLoader(OBJLoader loader, string texturePath,  vec3 aposition, float rotX, float rotY, float rotZ, float ascale)
{
    position = aposition;
    setM(aposition, rotX, rotY, rotZ, ascale);
    verts = loader.getVerts();
    normals = loader.getNormals();
    colors = loader.getColors();
    vertexCount = loader.getVertexCount();
    tex = readTexture(texturePath);
}

mat4 Object::getM()
{
    return M;
}

float * Object::getVerts()
{
    return verts;
}

float * Object::getNormals()
{
    return normals;
}

float * Object::getColors()
{

    return colors;
}

unsigned int Object::getVertexCount()
{
    return vertexCount;
}

vec3 Object::getPosition()
{
    return position;

}

void Object::setPosition(vec3 aposition)
{
    setM(aposition, rotationX, rotationY, rotationZ, scaling);
}

void Object::turn(float rot)
{
    setM(position, rotationX, rotationY+rot, rotationZ, scaling);
}

void Object::move(float dc)
{
    float dx = -dc * sin(rotationY*3.14f/180.0f);
    float dz = -dc * cos(rotationY*3.14f/180.0f);
    position.x+=dx;
    position.z+=dz;
    setM(position, rotationX, rotationY, rotationZ, scaling);
}

float Object::getRotationY()
{
    return (rotationY-180)*3.14f/180.0f;
}

void Object::setRotation(float rotX, float rotY, float rotZ)
{
   if (rotX != NULL) rotationX = rotX;
   if (rotY != NULL) rotationY = rotY;
   if (rotZ != NULL) rotationZ = rotZ;
   setM(position, rotationX, rotationY, rotationZ, scaling);
}

void Object::render(mat4 V, mat4 P, ShaderProgram *sp)
{
    UniformAllMatrix4(M,V, P, sp);
    sendTexture(sp);
    sendAttributes(verts,normals,colors, sp);
    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt
    disableAttributes(sp);
}

void Object::UniformAllMatrix4(mat4 M,mat4 V, mat4 P, ShaderProgram *sp)
{
    glUniformMatrix4fv(sp->u("P"),1,false,value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,value_ptr(M));
}

void Object::sendTexture(ShaderProgram *sp)
{
    glUniform1i(sp->u("textureMap"),0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
}

void Object::disableAttributes(ShaderProgram *sp)
{
    glDisableVertexAttribArray(sp->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
    glDisableVertexAttribArray(sp->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
    glDisableVertexAttribArray(sp->a("texCoord"));  //Wy³¹cz przesy³anie danych do atrybutu color
}

void Object::sendAttributes(float *verts, float *normals, float *colors, ShaderProgram *sp)
{
    glEnableVertexAttribArray(sp->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,verts); //Wska¿ tablicê z danymi dla atrybutu vertex

    glEnableVertexAttribArray(sp->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
    glVertexAttribPointer(sp->a("normal"),4,GL_FLOAT,false,0,normals); //Wska¿ tablicê z danymi dla atrybutu normal

    glEnableVertexAttribArray(sp->a("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
    glVertexAttribPointer(sp->a("texCoord"),2,GL_FLOAT,false,0,colors); //Wskaż tablicę z danymi dla atrybutu texCoord0
}

void Object::setM(vec3 aposition, float rotX, float rotY, float rotZ, float ascale)
{
    position = aposition;
    M=mat4(1.0f);
    M=translate(M, position);
    M=rotate(M, rotY*3.14f/180.0f, vec3(0.0f, 1.0f, 0.0f));
    M=rotate(M, rotX*3.14f/180.0f, vec3(1.0f, 0.0f, 0.0f));
    M=rotate(M, rotZ*3.14f/180.0f, vec3(0.0f, 0.0f, 1.0f));
    M=scale(M, vec3(ascale, ascale, ascale));
    rotationY = rotY;
    rotationX = rotX;
    rotationZ = rotZ;
    scaling=ascale;
    radius = 1.5 * ascale;
}

void Object:: rotateX(float angle)
{
    rotationX += angle;
   setM(position, rotationX, rotationY,rotationZ, scaling);
}

GLuint Object::readTexture(string path) {
  GLuint tex;
  glActiveTexture(GL_TEXTURE0);

  //Wczytanie do pamięci komputera
  std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
  unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
  //Wczytaj obrazek
  unsigned error = lodepng::decode(image, width, height, path);

  //Import do pamięci karty graficznej
  glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
  glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
  //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return tex;
}

bool Object::collision_one_object(Object object)
{
    if ( pow(this->getRadius() - object.getRadius(), 2) <
         pow(this->getPosition().x - object.getPosition().x, 2) +
         pow(this->getPosition().z - object.getPosition().z, 2)
        )
    {
        if ( pow(this->getRadius() + object.getRadius(), 2) >
             pow(this->getPosition().x - object.getPosition().x, 2) +
             pow(this->getPosition().z - object.getPosition().z, 2)
             )
                {
                    return true;
                }
    }
    return false;
}

Object * Object:: collision(Object* objects)
{
    vector<Object> help;
    for (Object o: objects)
    {
        if (collision_one_object(o))
        {
            help.push_back(o);
        }
    }

    Object *result =new Object[help.size()];

    for (int i = 0; i < help.size(); i++)
    {
        result[i] = help[i];
    }
    return result;
}
