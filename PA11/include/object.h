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

#include "physics.h"

using namespace std;
class Physics;

class Object
{
  friend class Physics;
  public:
    Object();
    Object(nlohmann::json json_obj, string name);
    ~Object();

    glm::mat4 GetModel();
    void Render();
    void Update(unsigned int dt, int keyboardButton);

    void loadObject();//btTriangleMesh*& t);
    void loadTextures();

		btTransform initial_position;
		btTransform check_position;

		btCollisionShape* pBase;
		btCollisionShape* pBodyBase;
		btCollisionShape* pBody;
		btCollisionShape* pNeck;
		btCollisionShape* pHead;
		btTransform trans;
		btCompoundShape* pCompound;

  //protected:
		vector<glm::vec3> vertexes;

    Physics* world;

    btTriangleMesh* objTriMesh;
    btCollisionShape* collisionShape;
    btRigidBody *rigidBody;
    btDefaultMotionState *shapeMotionState;

    glm::mat4 model;
		vector<Mesh> meshes;
    string filePath;                 //object file path
    nlohmann::json m_config;

    vector<Texture*> m_Textures;
};

#endif /* OBJECT_H */
