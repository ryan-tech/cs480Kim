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
}

void Physics::loadBoard()
{
  board = new Object(json_obj, "Board");
  board->world = this;
  board->shapeMotionState = NULL;
  board->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 180.0f, -45.0f, 1),
    btVector3(0.0f, -15.0f, 0.0f)
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


void Physics::loadCylinder()
{
  cylinder = new Object(json_obj, "Cylinder");
  cylinder->world = this;
  cylinder->collisionShape = new btCylinderShape(btVector3(1, 1, 1));

  cylinder->shapeMotionState = NULL;
  cylinder->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, -4.0f, 0.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder->shapeMotionState, cylinder->collisionShape, inertia);
  cylinder->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder->rigidBody, 1, 1);
}



void Physics::Update(unsigned int dt, int keyboardButton)
{
  board->Update(dt, keyboardButton);
}
