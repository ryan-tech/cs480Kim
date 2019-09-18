#ifndef OBJECT_H
#define OBJECT_H
#include <SDL2/SDL.h>
#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update_planet(unsigned int dt, int keyboardButton);
    void Update_moon(unsigned int dt, int keyboardButton);
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float planet_translation_angle;
    float planet_rotation_angle;
    float moon_translation_angle;
    float moon_rotation_angle;

    bool planet_clockwise_translation;
    bool planet_clockwise_rotation;
    bool moon_clockwise_translation;
    bool moon_clockwise_rotation;

};

#endif /* OBJECT_H */
