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
  void loadPlunger();
	void loadLeftBumpers();
	void loadRightBumpers();
  void loadLeftHinge();
  void loadRightHinge();
  void loadCylinder1();
  void loadCylinder2();
  void loadCylinder3();
  void loadCylinder4();
  void loadBoardCover();


  nlohmann::json json_obj;
  btBroadphaseInterface *broadphase;
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;

  Object* board;
  Object* sphere;
  Object* plunger;
	Object* leftBumper;
	Object* rightBumper;
  Object* leftHinge;
  Object* rightHinge;
  Object* cylinder1;
  Object* cylinder2;
  Object* cylinder3;
  Object* cylinder4;
  Object* boardCover;

	float cubeMove;
	float cubeMoveVal;
	int cubeMoveDir;


  float leftBumperAngle = 2.5f;
  float rightBumperAngle = 0.6f;
};

#endif
