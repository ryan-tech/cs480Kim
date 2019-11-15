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
  dynamicsWorld->setGravity(btVector3(0, -.8, -.1)); // sets gravity
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
  loadSphere();
  loadPlunger();
  loadLeftBumpers();
  loadRightBumpers();
  loadCylinder1();
  loadCylinder2();
  loadCylinder3();
}

void Physics::Update(unsigned int dt, int keyboardButton)
{
  board->Update(dt, keyboardButton);
  sphere->Update(dt, keyboardButton);
  plunger->model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
  plunger->Update(dt, keyboardButton);
  leftBumper->Update(dt, keyboardButton);
  rightBumper->Update(dt, keyboardButton);

  cylinder1->Update(dt, keyboardButton);
  cylinder2->Update(dt, keyboardButton);
  cylinder3->Update(dt, keyboardButton);
  if(keyboardButton == SDLK_UP)
  {
    cout << "up was pressed" << endl;
    sphere->rigidBody->applyImpulse(btVector3(0,0,10), btVector3(0,0,0));
  }

}


void Physics::loadBoard()
{
  board = new Object(json_obj, "Board");
  board->world = this;
  board->shapeMotionState = NULL;
  board->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
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


void Physics::loadSphere()
{
  sphere = new Object(json_obj, "Sphere");
  sphere->world = this;

  sphere->collisionShape = new btSphereShape(btScalar(1));

  sphere->shapeMotionState = NULL;
  sphere->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-20.0f, -13.5f, -27.0f)
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
  plunger->world = this;
  plunger->collisionShape = new btCylinderShape(btVector3(1, 2, 1));

  plunger->shapeMotionState = NULL;
  plunger->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 45.0f, 45.0f, 1),
    btVector3(-21.0f, -15.0f, -33.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  plunger->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, plunger->shapeMotionState, plunger->collisionShape, inertia);
  plunger->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(plunger->rigidBody, 1, 1);
}

void Physics::loadLeftBumpers()
{
  leftBumper = new Object(json_obj, "LeftBumper");
  leftBumper->world = this;

  leftBumper->collisionShape = new btBoxShape(btVector3(1,2.5,1));

  leftBumper->shapeMotionState = NULL;
  leftBumper->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(30.0f, 0.0f, 45.0f, 1),
    btVector3(4.0f, -15.0f, -28.0f)
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
    btQuaternion(45.0f, 0.0f, 30.0f, 1),
    btVector3(-4.0f, -15.0f, -28.0f)
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


void Physics::loadCylinder1()
{
  cylinder1 = new Object(json_obj, "Cylinder");
  cylinder1->world = this;
  cylinder1->collisionShape = new btCylinderShape(btVector3(1, 1, 1));

  cylinder1->shapeMotionState = NULL;
  cylinder1->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, -15.0f, 2.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder1->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder1->shapeMotionState, cylinder1->collisionShape, inertia);
  cylinder1->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder1->rigidBody, 1, 1);
}

void Physics::loadCylinder2()
{
  cylinder2 = new Object(json_obj, "Cylinder");
  cylinder2->world = this;
  cylinder2->collisionShape = new btCylinderShape(btVector3(1, 1, 1));

  cylinder2->shapeMotionState = NULL;
  cylinder2->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(4.0f, -15.0f, 6.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder2->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder2->shapeMotionState, cylinder2->collisionShape, inertia);
  cylinder2->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder2->rigidBody, 1, 1);
}

void Physics::loadCylinder3()
{
  cylinder3 = new Object(json_obj, "Cylinder");
  cylinder3->world = this;
  cylinder3->collisionShape = new btCylinderShape(btVector3(1, 1, 1));

  cylinder3->shapeMotionState = NULL;
  cylinder3->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-4.0f, -15.0f, 6.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder3->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder3->shapeMotionState, cylinder3->collisionShape, inertia);
  cylinder3->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder3->rigidBody, 1, 1);
}
