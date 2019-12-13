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

  void loadCylinder1();
  void loadCylinder2();
  void loadCylinder3();
  void loadCylinder4();
	void loadCylinder5();
  void loadCylinder6();
  void loadCylinder7();
	void loadCylinder8();
  void loadCylinder9();
  void loadCylinder10();



  nlohmann::json json_obj;
  btBroadphaseInterface *broadphase;
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;

  Object* board;
  Object* sphere;
  
  Object* cylinder1;
  Object* cylinder2;
  Object* cylinder3;
  Object* cylinder4;
	Object* cylinder5;
  Object* cylinder6;
  Object* cylinder7;
	Object* cylinder8;
  Object* cylinder9;
  Object* cylinder10;

	Object* pin[11];


	float cubeMove;
	float cubeMoveVal;
	int cubeMoveDir;


  float leftBumperAngle = 2.5f;
  float rightBumperAngle = 0.6f;
};

#endif
