#ifndef PHYSICS_H
#define PHYSICS_H

#include "graphics_headers.h"
#include "object.h"



class Object;

class Physics
{
public:
  Physics(nlohmann::json j);
  ~Physics();
  void createObject();
  void Update(unsigned int dt, int keyboardButton);

  void loadBoard();
  void loadSphere();
  void loadCylinder();
  void loadCube();

  nlohmann::json json_obj;
  btBroadphaseInterface *broadphase;
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;

  Object* board;
  Object* sphere;
  Object* cube;
  Object* cylinder;

};

#endif
