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

class Moon;


class Object
{
  public:
    Object();
    Object(nlohmann::json json_obj, string object_name);
    ~Object();
    virtual void Update(unsigned int dt, int keyboardButton);
    virtual void Render();
    void loadObject();
    void loadTextures();
    glm::mat4 GetModel();
	  vector<Moon*> moons;
	  int numMoons;
    float orbit_angle;
		float rotate_angle;
	  float distanceFromOrigin;
	  string name;
	  float size;


  protected:
    glm::mat4 model;
		vector<Mesh> meshes;

    string filePath;                 //object file path

    nlohmann::json m_config;
    //string name;

    vector<Texture*> m_Textures;

   // float distanceFromOrigin;
   // float orbit_angle;
		//float rotate_angle;
    //float size;
    float scaled_size;
		float orbit_speed;
		float rotate_speed;
		bool counterClockwise;
		//vector<Moon*> moons;
		//int numMoons;

};

class Moon : public Object
{
public:
    friend class object;
    Moon(nlohmann::json json_obj, Object* planet, int index);
    virtual void Update(unsigned int dt, int keyboardButton);
    virtual void Render();
    Object* m_planet;


};

#endif /* OBJECT_H */
