#include "physics.h"

Physics::Physics(nlohmann::json j)
{
  json_obj = j;
  //Bullet
  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver;
  //creating physics world
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0, -.8, 0)); // sets gravity
    //std::cout << "go further" << std::endl;

	cubeMove = 30;
	cubeMoveVal = 0;
	cubeMoveDir = 1;
}

Physics::~Physics()
{
  delete broadphase;
  broadphase = NULL;
  delete collisionConfiguration;
  collisionConfiguration = NULL;
  delete dispatcher;
  dispatcher = NULL;
  delete solver;
  solver = NULL;
  delete dynamicsWorld;
  dynamicsWorld = NULL;
}

void Physics::createObject()
{
  loadBoard();
  loadSphere();
  loadPlunger();
  loadCube();
	loadLeftBumpers();
	loadRightBumpers();
}

void Physics::loadBoard()
{
  board = new Object(json_obj, "Board");
  board->world = this;
  board->shapeMotionState = NULL;
  board->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(0.0f, -5.0f, 0.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(0,0,0);
  board->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, board->shapeMotionState, board->collisionShape, inertia);
  board->rigidBody = new btRigidBody(shapeRigidBodyCI);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(board->rigidBody, 1, 1);
  //board->model = glm::scale(board->model, glm::vec3(5,5,5));
}

void Physics::loadCube()
{
  cube = new Object(json_obj, "Cube");
  cube->world = this;

  cube->collisionShape = new btBoxShape(btVector3(1,1,1));

  cube->shapeMotionState = NULL;
  cube->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-3.0f, -4.0f, -3.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cube->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, cube->shapeMotionState, cube->collisionShape, inertia);
  cube->rigidBody = new btRigidBody(shapeRigidBodyCI4);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(cube->rigidBody, 1, 1);
  //board->model = glm::scale(board->model, glm::vec3(5,5,5));
  cube->rigidBody->setCollisionFlags(cube->rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  cube->rigidBody->setActivationState( DISABLE_DEACTIVATION );
}



void Physics::loadSphere()
{
  sphere = new Object(json_obj, "Sphere");
  sphere->world = this;

  sphere->collisionShape = new btSphereShape(btScalar(1));

  sphere->shapeMotionState = NULL;
  sphere->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(3.0f, 10.0f, 3.0f)
    ));
  btScalar mass(5);
  btVector3 inertia(1,1,1);
  sphere->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, sphere->shapeMotionState, sphere->collisionShape, inertia);
  sphere->rigidBody = new btRigidBody(shapeRigidBodyCI4);

  dynamicsWorld->addRigidBody(sphere->rigidBody, 1, 1);


}


void Physics::loadPlunger()
{
  plunger = new Object(json_obj, "Plunger");
  plunger->collisionShape = new btBoxShape(btVector3(1,1,1));

  plunger->shapeMotionState = NULL;
  plunger->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-3.0f, -4.0f, -3.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  plunger->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, plunger->shapeMotionState, plunger->collisionShape, inertia);
  plunger->rigidBody = new btRigidBody(shapeRigidBodyCI4);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(plunger->rigidBody, 1, 1);
  //board->model = glm::scale(board->model, glm::vec3(5,5,5));
  plunger->rigidBody->setCollisionFlags(plunger->rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  plunger->rigidBody->setActivationState( DISABLE_DEACTIVATION );
}

void Physics::loadLeftBumpers()
{
  leftBumper = new Object(json_obj, "LeftBumper");
  leftBumper->world = this;

  leftBumper->collisionShape = new btBoxShape(btVector3(1,1,1));

  leftBumper->shapeMotionState = NULL;
  leftBumper->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-3.0f, -4.0f, -3.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  leftBumper->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, leftBumper->shapeMotionState, leftBumper->collisionShape, inertia);
  leftBumper->rigidBody = new btRigidBody(shapeRigidBodyCI4);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(leftBumper->rigidBody, 1, 1);
  //board->model = glm::scale(board->model, glm::vec3(5,5,5));
  leftBumper->rigidBody->setCollisionFlags(leftBumper->rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  leftBumper->rigidBody->setActivationState( DISABLE_DEACTIVATION );
}
	
void Physics::loadRightBumpers()
{
	rightBumper = new Object(json_obj, "RightBumper");
  rightBumper->world = this;

  rightBumper->collisionShape = new btBoxShape(btVector3(1,1,1));

  rightBumper->shapeMotionState = NULL;
  rightBumper->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-3.0f, -4.0f, -3.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  rightBumper->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, rightBumper->shapeMotionState, rightBumper->collisionShape, inertia);
  rightBumper->rigidBody = new btRigidBody(shapeRigidBodyCI4);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(rightBumper->rigidBody, 1, 1);
  //board->model = glm::scale(board->model, glm::vec3(5,5,5));
  rightBumper->rigidBody->setCollisionFlags(rightBumper->rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  rightBumper->rigidBody->setActivationState( DISABLE_DEACTIVATION );
}



void Physics::Update(unsigned int dt, int keyboardButton)
{

  board->Update(dt, keyboardButton);
  sphere->Update(dt, keyboardButton);
  plunger->Update(dt, keyboardButton);
  cube->Update(dt, keyboardButton);
  btTransform newTrans;
  
  if((cubeMoveDir == 1)&&(cubeMoveVal < cubeMove))
  {
    cube->rigidBody->getMotionState()->getWorldTransform(newTrans);
    newTrans.getOrigin() += (btVector3(.5f, 0, 0));
    cube->rigidBody->getMotionState()->setWorldTransform(newTrans);
		cubeMoveVal += .5;
  }
  if((cubeMoveDir == -1)&&(cubeMoveVal >= 0))
  {
    cube->rigidBody->getMotionState()->getWorldTransform(newTrans);
    newTrans.getOrigin() += (btVector3(-.5f, 0, 0));
    cube->rigidBody->getMotionState()->setWorldTransform(newTrans);
		cubeMoveVal -= .5;
  }
	if(cubeMoveVal >= cubeMove)
	{
		cubeMoveDir = -1;
	}
  if(cubeMoveVal <= 0)
	{
		cubeMoveDir = 1;
	}

}
