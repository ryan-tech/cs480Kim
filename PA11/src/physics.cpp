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
  cylinder1->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder1->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder1->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder1->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder1->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder1->trans.setIdentity();
	cylinder1->pCompound = new btCompoundShape();
	//add base
	cylinder1->pCompound->addChildShape(cylinder1->trans, cylinder1->pBase);
	// add body base
	cylinder1->trans.setOrigin(btVector3(0.00354227f, -0.0635913f +0.367653, 112.992f));
	cylinder1->pCompound->addChildShape(cylinder1->trans, cylinder1->pBodyBase);
	// add body
	cylinder1->trans.setOrigin(btVector3(0.00354227f, -0.0635913f +1.16031, 112.992f));
	cylinder1->pCompound->addChildShape(cylinder1->trans, cylinder1->pBody);
	// add neck
	cylinder1->trans.setOrigin(btVector3(0.00354227f, -0.0635913f +2.01677, 112.992f));
	cylinder1->pCompound->addChildShape(cylinder1->trans, cylinder1->pNeck);
	// add head
	cylinder1->trans.setOrigin(btVector3(0.00354227f, -0.0635913f +2.82553, 112.992f));
	cylinder1->pCompound->addChildShape(cylinder1->trans, cylinder1->pHead);



  cylinder1->shapeMotionState = NULL;
  cylinder1->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.00354227f, -0.0635913f, 112.992f)
		));


	cylinder1->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.00354227f, -0.0635913f, 112.992f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder1->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder1->shapeMotionState, cylinder1->pCompound, inertia);
  cylinder1->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder1->rigidBody, 1, 1);
}

void Physics::loadCylinder2()
{
  cylinder2 = new Object(json_obj, "Cylinder");
  cylinder2->world = this;
  cylinder2->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder2->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder2->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder2->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder2->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder2->trans.setIdentity();
	cylinder2->pCompound = new btCompoundShape();
	//add base
	cylinder2->pCompound->addChildShape(cylinder2->trans, cylinder2->pBase);
	// add body base
	cylinder2->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder2->pCompound->addChildShape(cylinder2->trans, cylinder2->pBodyBase);
	// add body
	cylinder2->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder2->pCompound->addChildShape(cylinder2->trans, cylinder2->pBody);
	// add neck
	cylinder2->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder2->pCompound->addChildShape(cylinder2->trans, cylinder2->pNeck);
	// add head
	cylinder2->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder2->pCompound->addChildShape(cylinder2->trans, cylinder2->pHead);




  cylinder2->shapeMotionState = NULL;
  cylinder2->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, -0.0635751f, 114.424f)
		));


	cylinder2->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, -0.0635751f, 114.424f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder2->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder2->shapeMotionState, cylinder2->pCompound, inertia);
  cylinder2->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder2->rigidBody, 1, 1);
}

void Physics::loadCylinder3()
{
  cylinder3 = new Object(json_obj, "Cylinder");
  cylinder3->world = this;
  cylinder3->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder3->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder3->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder3->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder3->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder3->trans.setIdentity();
	cylinder3->pCompound = new btCompoundShape();
	//add base
	cylinder3->pCompound->addChildShape(cylinder3->trans, cylinder3->pBase);
	// add body base
	cylinder3->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder3->pCompound->addChildShape(cylinder3->trans, cylinder3->pBodyBase);
	// add body
	cylinder3->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder3->pCompound->addChildShape(cylinder3->trans, cylinder3->pBody);
	// add neck
	cylinder3->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder3->pCompound->addChildShape(cylinder3->trans, cylinder3->pNeck);
	// add head
	cylinder3->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder3->pCompound->addChildShape(cylinder3->trans, cylinder3->pHead);




  cylinder3->shapeMotionState = NULL;
  cylinder3->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, -0.063575f, 114.504f)
		));


	cylinder3->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, -0.063575f, 114.504f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder3->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder3->shapeMotionState, cylinder3->pCompound, inertia);
  cylinder3->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder3->rigidBody, 1, 1);
}

void Physics::loadCylinder4()
{
  cylinder4 = new Object(json_obj, "Cylinder");
  cylinder4->world = this;
  cylinder4->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder4->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder4->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder4->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder4->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder4->trans.setIdentity();
	cylinder4->pCompound = new btCompoundShape();
	//add base
	cylinder4->pCompound->addChildShape(cylinder4->trans, cylinder4->pBase);
	// add body base
	cylinder4->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder4->pCompound->addChildShape(cylinder4->trans, cylinder4->pBodyBase);
	// add body
	cylinder4->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder4->pCompound->addChildShape(cylinder4->trans, cylinder4->pBody);
	// add neck
	cylinder4->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder4->pCompound->addChildShape(cylinder4->trans, cylinder4->pNeck);
	// add head
	cylinder4->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder4->pCompound->addChildShape(cylinder4->trans, cylinder4->pHead);




  cylinder4->shapeMotionState = NULL;
  cylinder4->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.95825f, -0.0635753f, 116.072f)
		));


	cylinder4->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.95825f, -0.0635753f, 116.072f)
  	);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder4->pCompound->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder4->shapeMotionState, cylinder4->pCompound, inertia);
  cylinder4->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder4->rigidBody, 1, 1);
}


void Physics::loadCylinder5()
{
  cylinder5 = new Object(json_obj, "Cylinder");
  cylinder5->world = this;
  cylinder5->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder5->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder5->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder5->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder5->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder5->trans.setIdentity();
	cylinder5->pCompound = new btCompoundShape();
	//add base
	cylinder5->pCompound->addChildShape(cylinder5->trans, cylinder5->pBase);
	// add body base
	cylinder5->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder5->pCompound->addChildShape(cylinder5->trans, cylinder5->pBodyBase);
	// add body
	cylinder5->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder5->pCompound->addChildShape(cylinder5->trans, cylinder5->pBody);
	// add neck
	cylinder5->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder5->pCompound->addChildShape(cylinder5->trans, cylinder5->pNeck);
	// add head
	cylinder5->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder5->pCompound->addChildShape(cylinder5->trans, cylinder5->pHead);




  cylinder5->shapeMotionState = NULL;
  cylinder5->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.00354227f, -0.0635751f, 115.942f)
		));

	cylinder5->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(0.00354227f, -0.0635751f, 115.942f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder5->pCompound->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder5->shapeMotionState, cylinder5->pCompound, inertia);
  cylinder5->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder5->rigidBody, 1, 1);
}

void Physics::loadCylinder6()
{
  cylinder6 = new Object(json_obj, "Cylinder");
  cylinder6->world = this;
  cylinder6->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder6->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder6->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder6->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder6->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder6->trans.setIdentity();
	cylinder6->pCompound = new btCompoundShape();
	//add base
	cylinder6->pCompound->addChildShape(cylinder6->trans, cylinder6->pBase);
	// add body base
	cylinder6->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder6->pCompound->addChildShape(cylinder6->trans, cylinder6->pBodyBase);
	// add body
	cylinder6->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder6->pCompound->addChildShape(cylinder6->trans, cylinder6->pBody);
	// add neck
	cylinder6->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder6->pCompound->addChildShape(cylinder6->trans, cylinder6->pNeck);
	// add head
	cylinder6->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder6->pCompound->addChildShape(cylinder6->trans, cylinder6->pHead);




  cylinder6->shapeMotionState = NULL;
  cylinder6->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.15f, -0.0635752f, 115.957f)
		));


	cylinder6->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.15f, -0.0635752f, 115.957f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder6->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder6->shapeMotionState, cylinder6->pCompound, inertia);
  cylinder6->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder6->rigidBody, 1, 1);
}


void Physics::loadCylinder7()
{
  cylinder7 = new Object(json_obj, "Cylinder");
  cylinder7->world = this;
  cylinder7->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder7->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder7->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder7->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder7->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder7->trans.setIdentity();
	cylinder7->pCompound = new btCompoundShape();
	//add base
	cylinder7->pCompound->addChildShape(cylinder7->trans, cylinder7->pBase);
	// add body base
	cylinder7->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder7->pCompound->addChildShape(cylinder7->trans, cylinder7->pBodyBase);
	// add body
	cylinder7->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder7->pCompound->addChildShape(cylinder7->trans, cylinder7->pBody);
	// add neck
	cylinder7->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder7->pCompound->addChildShape(cylinder7->trans, cylinder7->pNeck);
	// add head
	cylinder7->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder7->pCompound->addChildShape(cylinder7->trans, cylinder7->pHead);




  cylinder7->shapeMotionState = NULL;
  cylinder7->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(3.0601f, -0.0635755f, 117.509f)
		));


	cylinder7->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(3.0601f, -0.0635755f, 117.509f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder7->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder7->shapeMotionState, cylinder7->pCompound, inertia);
  cylinder7->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder7->rigidBody, 1, 1);
}


void Physics::loadCylinder8()
{
  cylinder8 = new Object(json_obj, "Cylinder");
  cylinder8->world = this;
  cylinder8->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder8->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder8->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder8->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder8->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder8->trans.setIdentity();
	cylinder8->pCompound = new btCompoundShape();
	//add base
	cylinder8->pCompound->addChildShape(cylinder8->trans, cylinder8->pBase);
	// add body base
	cylinder8->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder8->pCompound->addChildShape(cylinder8->trans, cylinder8->pBodyBase);
	// add body
	cylinder8->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder8->pCompound->addChildShape(cylinder8->trans, cylinder8->pBody);
	// add neck
	cylinder8->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder8->pCompound->addChildShape(cylinder8->trans, cylinder8->pNeck);
	// add head
	cylinder8->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder8->pCompound->addChildShape(cylinder8->trans, cylinder8->pHead);



  cylinder8->shapeMotionState = NULL;
  cylinder8->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, -0.0635752f, 117.42f)
		));


	cylinder8->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, -0.0635752f, 117.42f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder8->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder8->shapeMotionState, cylinder8->pCompound, inertia);
  cylinder8->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder8->rigidBody, 1, 1);
}


void Physics::loadCylinder9()
{
  cylinder9 = new Object(json_obj, "Cylinder");
  cylinder9->world = this;
  cylinder9->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder9->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder9->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder9->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder9->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));


	cylinder9->trans.setIdentity();
	cylinder9->pCompound = new btCompoundShape();
	//add base
	cylinder9->pCompound->addChildShape(cylinder9->trans, cylinder9->pBase);
	// add body base
	cylinder9->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder9->pCompound->addChildShape(cylinder9->trans, cylinder9->pBodyBase);
	// add body
	cylinder9->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder9->pCompound->addChildShape(cylinder9->trans, cylinder9->pBody);
	// add neck
	cylinder9->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder9->pCompound->addChildShape(cylinder9->trans, cylinder9->pNeck);
	// add head
	cylinder9->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder9->pCompound->addChildShape(cylinder9->trans, cylinder9->pHead);


  cylinder9->shapeMotionState = NULL;
  cylinder9->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, -0.0635754f, 117.592f)
		));


	cylinder9->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, -0.0635754f, 117.592f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder9->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder9->shapeMotionState, cylinder9->pCompound, inertia);
  cylinder9->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder9->rigidBody, 1, 1);
}


void Physics::loadCylinder10()
{
  cylinder10 = new Object(json_obj, "Cylinder");
  cylinder10->world = this;
  cylinder10->pBase = new btCylinderShape(btVector3(.15f, .15f, .15f));
	cylinder10->pBody = new btCylinderShape(btVector3(.4f, 1.0f, .4f));
	cylinder10->pBodyBase = new btCylinderShape(btVector3(.3f, .59f, .3f));
	cylinder10->pHead = new btCylinderShape(btVector3(.2f, .9f, .2f));
	cylinder10->pNeck = new btCylinderShape(btVector3(.26f, .7f, .26f));

	cylinder10->trans.setIdentity();
	cylinder10->pCompound = new btCompoundShape();
	//add base
	cylinder10->pCompound->addChildShape(cylinder10->trans, cylinder10->pBase);
	// add body base
	cylinder10->trans.setOrigin(btVector3(0, 0 +0.367653, 0));
	cylinder10->pCompound->addChildShape(cylinder10->trans, cylinder10->pBodyBase);
	// add body
	cylinder10->trans.setOrigin(btVector3(0, 0 +1.16031, 0));
	cylinder10->pCompound->addChildShape(cylinder10->trans, cylinder10->pBody);
	// add neck
	cylinder10->trans.setOrigin(btVector3(0, 0 +2.01677, 0));
	cylinder10->pCompound->addChildShape(cylinder10->trans, cylinder10->pNeck);
	// add head
	cylinder10->trans.setOrigin(btVector3(0, 0 +2.82553, 0));
	cylinder10->pCompound->addChildShape(cylinder10->trans, cylinder10->pHead);




  cylinder10->shapeMotionState = NULL;
  cylinder10->shapeMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.9f, -0.0635751f, 117.573f)
		));


	cylinder10->initial_position = btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.9f, -0.0635751f, 117.573f)
		);

  btScalar mass(1);
  btVector3 inertia(1,1,1);
  cylinder10->pCompound->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, cylinder10->shapeMotionState, cylinder10->pCompound, inertia);
  cylinder10->rigidBody = new btRigidBody(shapeRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder10->rigidBody, 1, 1);
}
