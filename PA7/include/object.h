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
    void Render();
    void loadObject();
    void loadTextures();
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
		vector<Mesh> meshes;
    Object* moon;
    float angle;
    std::string filePath;                 //object file path

    vector<Texture*> m_Textures;
};

#endif /* OBJECT_H */
