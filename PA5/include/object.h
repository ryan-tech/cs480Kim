#ifndef OBJECT_H
#define OBJECT_H
#include <SDL2/SDL.h>
#include <vector>
#include "graphics_headers.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

class Object
{
  public:
    Object();
    Object(string path);
    ~Object();
    void Update(unsigned int dt, int keyboardButton);
    void Update_planet(unsigned int dt, int keyboardButton);
    void Update_moon(unsigned int dt, int keyboardButton);
    void Render();
    void loadObject();
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    //std::vector<Vertex> Vertices;
    //std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;

    float planet_translation_angle;
    float planet_rotation_angle;
    float moon_translation_angle;
    float moon_rotation_angle;

    bool planet_clockwise_translation;
    bool planet_clockwise_rotation;
    bool moon_clockwise_translation;
    bool moon_clockwise_rotation;

    vector<Vertex> Vertices;           //holds the vertices (v)
    vector<glm::vec2> textureCoordinates; //holds the texture coordinate (vt)
    vector<glm::vec3> normalVectors;      //hodls the normal vectors (vn)


    vector<unsigned int> Indices;

    //vector<vector<Triangle_vertex>> triangles;

    std::string filePath;

};

#endif /* OBJECT_H */
