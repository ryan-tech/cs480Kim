#ifndef OBJECT_H
#define OBJECT_H
#include <SDL2/SDL.h>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "graphics_headers.h"
#include "texture.h"


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
    void loadTextures();
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
		vector<Mesh> meshes;

    float angle;

    float planet_translation_angle;
    float planet_rotation_angle;
    float moon_translation_angle;
    float moon_rotation_angle;

    bool planet_clockwise_translation;
    bool planet_clockwise_rotation;
    bool moon_clockwise_translation;
    bool moon_clockwise_rotation;

    std::string filePath;                 //object file path

    vector<Texture*> m_Textures;
};

#endif /* OBJECT_H */
