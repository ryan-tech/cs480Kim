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
  dynamicsWorld->setGravity(btVector3(0, -10, 0)); // sets gravity
    //std::cout << "go further" << std::endl;

	std:cout << "bullet stuff loaded \n";
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
	cout << "entered create object \n";

  loadBoard();
	cout << "got through board \n";

  loadSphere();
	cout << "got through sphere \n";

  loadCylinder1();
  /*loadCylinder2();
  loadCylinder3();
  loadCylinder4();
	loadCylinder5();
	loadCylinder6();
	loadCylinder7();
	loadCylinder8();
	loadCylinder9();
	loadCylinder10();*/
}

void Physics::Update(unsigned int dt, int keyboardButton)
{
  board->Update(dt, keyboardButton);
  sphere->Update(dt, keyboardButton);

  cylinder1->Update(dt, keyboardButton);
  /*cylinder2->Update(dt, keyboardButton);
  cylinder3->Update(dt, keyboardButton);
  cylinder4->Update(dt, keyboardButton);
	cylinder5->Update(dt, keyboardButton);
  cylinder6->Update(dt, keyboardButton);
  cylinder7->Update(dt, keyboardButton);
	cylinder8->Update(dt, keyboardButton);
  cylinder9->Update(dt, keyboardButton);
  cylinder10->Update(dt, keyboardButton);
*/
}


void Physics::loadBoard()
{
  board = new Object(json_obj, "Board");
  board->world = this;
  board->shapeMotionState = NULL;
  board->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 180.0f, 0.0f, 1),
    btVector3(0.0f, 0.0f, 1.0f)
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
    btVector3(0.0f, 2.0f, 0.0f)
    ));
  btScalar mass(15);
  btVector3 inertia(1, 1, 1);
  sphere->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, sphere->shapeMotionState, sphere->collisionShape, inertia);
  sphere->rigidBody = new btRigidBody(shapeRigidBodyCI4);

  dynamicsWorld->addRigidBody(sphere->rigidBody, 1, 1);
  sphere->rigidBody->setActivationState( DISABLE_DEACTIVATION );
  sphere->model = glm::scale(sphere->model, glm::vec3(5, 5, 5));
}

void Physics::loadCylinder1()
{
  cylinder1 = new Object(json_obj, "Cylinder");
  cylinder1->world = this;
  cylinder1->collisionShape = new btCylinderShape(btVector3(.25f, .25f, 1));

  cylinder1->shapeMotionState = NULL;
  cylinder1->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, -15.0f, 2.0f)
		));
  btScalar mass(4);
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
  cylinder2->collisionShape = new btCylinderShape(btVector3(2, 2, 2));

  cylinder2->shapeMotionState = NULL;
  cylinder2->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(6.0f, -15.0f, 8.0f)
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
  cylinder3->collisionShape = new btCylinderShape(btVector3(2, 2, 2));

  cylinder3->shapeMotionState = NULL;
  cylinder3->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-6.0f, -15.0f, 8.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder3->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder3->shapeMotionState, cylinder3->collisionShape, inertia);
  cylinder3->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder3->rigidBody, 1, 1);
}

void Physics::loadCylinder4()
{
  cylinder4 = new Object(json_obj, "Cylinder");
  cylinder4->world = this;
  cylinder4->collisionShape = new btCylinderShape(btVector3(2, 2, 2));

  cylinder4->shapeMotionState = NULL;
  cylinder4->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, -15.0f, 14.0f)
		));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  cylinder4->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder4->shapeMotionState, cylinder4->collisionShape, inertia);
  cylinder4->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder4->rigidBody, 1, 1);
}

void Physics::loadCylinder5()
{

}

void Physics::loadCylinder6()
{

}

void Physics::loadCylinder7()
{

}

void Physics::loadCylinder8()
{

}

void Physics::loadCylinder9()
{

}

void Physics::loadCylinder10()
{

}
