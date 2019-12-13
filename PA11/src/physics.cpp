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

	//std:cout << "bullet stuff loaded \n";
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

  loadCylinder1();
  loadCylinder2();
  loadCylinder3();
  loadCylinder4();
	loadCylinder5();
	loadCylinder6();
	loadCylinder7();
	loadCylinder8();
	loadCylinder9();
	loadCylinder10();

	pin[1] = cylinder1;
	pin[2] = cylinder2;
	pin[3] = cylinder3;
	pin[4] = cylinder4;
	pin[5] = cylinder5;
	pin[6] = cylinder6;
	pin[7] = cylinder7;
	pin[8] = cylinder8;
	pin[9] = cylinder9;
	pin[10] = cylinder10;

}

void Physics::Update(unsigned int dt, int keyboardButton)
{
  board->Update(dt, keyboardButton);
  sphere->Update(dt, keyboardButton);

  cylinder1->Update(dt, keyboardButton);
  cylinder2->Update(dt, keyboardButton);
  cylinder3->Update(dt, keyboardButton);
  cylinder4->Update(dt, keyboardButton);
	cylinder5->Update(dt, keyboardButton);
  cylinder6->Update(dt, keyboardButton);
  cylinder7->Update(dt, keyboardButton);
	cylinder8->Update(dt, keyboardButton);
  cylinder9->Update(dt, keyboardButton);
  cylinder10->Update(dt, keyboardButton);
}


void Physics::loadBoard()
{
  board = new Object(json_obj, "Board");
  board->world = this;
  board->shapeMotionState = NULL;
  board->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 180.0f, 0.0f, 1),
    btVector3(1.0f, 0.0f, 1.0f)
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

	sphere->initial_position = btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(0.0f, 2.0f, 0.0f)
    );

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
  cylinder1->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder1->shapeMotionState = NULL;
  cylinder1->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.00354227f, -0.0635913f, 112.992f)
		));


	cylinder1->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.00354227f, -0.0635913f, 112.992f)
		);

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
  cylinder2->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder2->shapeMotionState = NULL;
  cylinder2->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.09498f, -0.0635751f, 114.424f)
		));


	cylinder2->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.09498f, -0.0635751f, 114.424f)
		);

  btScalar mass(4);
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
  cylinder3->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder3->shapeMotionState = NULL;
  cylinder3->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.05537f, -0.063575f, 114.504f)
		));


	cylinder3->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.05537f, -0.063575f, 114.504f)
		);

  btScalar mass(4);
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
  cylinder4->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder4->shapeMotionState = NULL;
  cylinder4->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.95825f, -0.0635753f, 116.072f)
		));


	cylinder4->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.95825f, -0.0635753f, 116.072f)
  	);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder4->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder4->shapeMotionState, cylinder4->collisionShape, inertia);
  cylinder4->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder4->rigidBody, 1, 1);
}


void Physics::loadCylinder5()
{
  cylinder5 = new Object(json_obj, "Cylinder");
  cylinder5->world = this;
  cylinder5->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder5->shapeMotionState = NULL;
  cylinder5->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-0.0101327f, -0.0635751f, 115.942f)
		));

	cylinder5->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(-0.0101327f, -0.0635751f, 115.942f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder5->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder5->shapeMotionState, cylinder5->collisionShape, inertia);
  cylinder5->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder5->rigidBody, 1, 1);
}

void Physics::loadCylinder6()
{
  cylinder6 = new Object(json_obj, "Cylinder");
  cylinder6->world = this;
  cylinder6->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder6->shapeMotionState = NULL;
  cylinder6->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.32198f, -0.0635752f, 115.957f)
		));


	cylinder6->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.32198f, -0.0635752f, 115.957f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder6->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder6->shapeMotionState, cylinder6->collisionShape, inertia);
  cylinder6->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder6->rigidBody, 1, 1);
}


void Physics::loadCylinder7()
{
  cylinder7 = new Object(json_obj, "Cylinder");
  cylinder7->world = this;
  cylinder7->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder7->shapeMotionState = NULL;
  cylinder7->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(3.0601f, -0.0635755f, 117.509f)
		));


	cylinder7->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(3.0601f, -0.0635755f, 117.509f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder7->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder7->shapeMotionState, cylinder7->collisionShape, inertia);
  cylinder7->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder7->rigidBody, 1, 1);
}


void Physics::loadCylinder8()
{
  cylinder8 = new Object(json_obj, "Cylinder");
  cylinder8->world = this;
  cylinder8->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder8->shapeMotionState = NULL;
  cylinder8->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(.996307f, -0.0635752f, 117.42f)
		));


	cylinder8->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(.996307f, -0.0635752f, 117.42f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder8->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder8->shapeMotionState, cylinder8->collisionShape, inertia);
  cylinder8->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder8->rigidBody, 1, 1);
}


void Physics::loadCylinder9()
{
  cylinder9 = new Object(json_obj, "Cylinder");
  cylinder9->world = this;
  cylinder9->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder9->shapeMotionState = NULL;
  cylinder9->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.2551f, -0.0635754f, 117.592f)
		));


	cylinder9->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.2551f, -0.0635754f, 117.592f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder9->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder9->shapeMotionState, cylinder9->collisionShape, inertia);
  cylinder9->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder9->rigidBody, 1, 1);
}


void Physics::loadCylinder10()
{
  cylinder10 = new Object(json_obj, "Cylinder");
  cylinder10->world = this;
  cylinder10->collisionShape = new btCylinderShape(btVector3(.15f, .15f, 1));
  cylinder10->shapeMotionState = NULL;
  cylinder10->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-3.0135f, -0.0635751f, 117.573f)
		));


	cylinder10->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-3.0135f, -0.0635751f, 117.573f)
		);

  btScalar mass(4);
  btVector3 inertia(1,1,1);
  cylinder10->collisionShape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder10->shapeMotionState, cylinder10->collisionShape, inertia);
  cylinder10->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder10->rigidBody, 1, 1);
}
