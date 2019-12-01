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
  dynamicsWorld->setGravity(btVector3(0, -.5, -.6)); // sets gravity
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
  loadBoardCover();
  loadSphere();
  loadPlunger();
  loadLeftHinge();
  loadLeftBumpers();
  loadRightBumpers();

  loadCylinder1();
  loadCylinder2();
  loadCylinder3();
  loadCylinder4();
}

void Physics::Update(unsigned int dt, int keyboardButton)
{
  board->Update(dt, keyboardButton);
  sphere->Update(dt, keyboardButton);
  plunger->model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
  plunger->Update(dt, keyboardButton);
  leftBumper->Update(dt, keyboardButton);
  rightBumper->Update(dt, keyboardButton);
  leftHinge->Update(dt, keyboardButton);

  cylinder1->Update(dt, keyboardButton);
  cylinder2->Update(dt, keyboardButton);
  cylinder3->Update(dt, keyboardButton);
  cylinder4->Update(dt, keyboardButton);

  if(keyboardButton == SDLK_COMMA) //left bumper
  {
    glm::mat4 leftBumper_t = leftBumper->GetModel();
    glm::vec3 leftBumper_m = glm::vec3(leftBumper_t[3]);

    btScalar scalarMatrix[16];
    btTransform transform;
    btQuaternion quaternion;
    leftBumperAngle += 0.2f;
    leftBumper->rigidBody->getMotionState()->getWorldTransform(transform);
    quaternion.setEuler(leftBumperAngle, 0.0, 0.0);
		transform.setRotation(quaternion);
	  transform.getOpenGLMatrix(scalarMatrix);
	  leftBumper->rigidBody->getMotionState()->setWorldTransform(transform);
		leftBumper->rigidBody->setMotionState(leftBumper->rigidBody->getMotionState());
  }
  if(keyboardButton == SDLK_PERIOD) //left bumper
  {
    glm::mat4 rightBumper_t = rightBumper->GetModel();
    glm::vec3 rightBumper_m = glm::vec3(rightBumper_t[3]);


    btScalar scalarMatrix[16];
    btTransform transform;
    btQuaternion quaternion;

    rightBumperAngle -= 0.2f;
    rightBumper->rigidBody->getMotionState()->getWorldTransform(transform);
    quaternion.setEuler(rightBumperAngle, 0.0, 0.0);
		transform.setRotation(quaternion);
	  transform.getOpenGLMatrix(scalarMatrix);
	  rightBumper->rigidBody->getMotionState()->setWorldTransform(transform);
		rightBumper->rigidBody->setMotionState(rightBumper->rigidBody->getMotionState());
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

void Physics::loadBoardCover()
{
  boardCover = new Object(json_obj, "Board");
  boardCover->world = this;
  boardCover->shapeMotionState = NULL;
  boardCover->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(0.0f, -14.5f, 0.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(0,0,0);
  boardCover->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, boardCover->shapeMotionState, boardCover->collisionShape, inertia);
  boardCover->rigidBody = new btRigidBody(shapeRigidBodyCI);
  //rigidBody->setLinearFactor(btVector3(0,0,0));
  dynamicsWorld->addRigidBody(boardCover->rigidBody, 1, 1);
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
  sphere->rigidBody->setActivationState( DISABLE_DEACTIVATION );
}

void Physics::loadPlunger()
{
  plunger = new Object(json_obj, "Plunger");
  plunger->world = this;
  plunger->collisionShape = new btCylinderShape(btVector3(1, 2, 1));

  plunger->shapeMotionState = NULL;
  plunger->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 45.0f, 45.0f, 1),
    btVector3(-21.0f, -15.0f, -34.0f)
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
  btTypedConstraint* p2p = new btPoint2PointConstraint(*leftBumper->rigidBody, *leftHinge->rigidBody, btVector3(4.5f, -15.0f, -28.0f), btVector3(4.5f, -15.0f, -28.0f) );
  //btTypedConstraint* p2p = new btPoint2PointConstraint(*body0,*body1,pivotInA,pivotInB);
  //btHingeConstraint* leftBumperHinge = new btHingeConstraint(*leftBumper->rigidBody, btVector3(4.5f, -15.0f, -28.0f), btVector3(0, 1, 0));
//btHingeConstraint* hinge = new btHingeConstraint(*body0, pivotInA, axisInA);
  //leftBumperHinge->setLimit(0, SIMD_HALF_PI);
  dynamicsWorld->addConstraint(p2p);
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
  btHingeConstraint* rightBumperHinge = new btHingeConstraint(*rightBumper->rigidBody, btVector3(-4.5f, -15.0f, -28.0f), btVector3(0.0f, 1.0f, 0.0f));
  rightBumperHinge->setLimit(0, SIMD_HALF_PI);
  dynamicsWorld->addConstraint(rightBumperHinge);
}

void Physics::loadLeftHinge()
{
  leftHinge = new Object(json_obj, "Cube");
  leftHinge->world = this;

  leftHinge->collisionShape = new btBoxShape(btVector3(1,1,1));

  leftHinge->shapeMotionState = NULL;
  leftHinge->shapeMotionState = new btDefaultMotionState(btTransform(
    btQuaternion(0.0f, 0.0f, 0.0f, 1),
    btVector3(4.5f, -15.0f, -28.0f)
    ));
  btScalar mass(0);
  btVector3 inertia(1,1,1);
  leftHinge->collisionShape->calculateLocalInertia(mass, inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, leftHinge->shapeMotionState, leftHinge->collisionShape, inertia);
  leftHinge->rigidBody = new btRigidBody(shapeRigidBodyCI4);
  dynamicsWorld->addRigidBody(leftHinge->rigidBody, 1, 1);
}




void Physics::loadCylinder1()
{
  cylinder1 = new Object(json_obj, "Cylinder");
  cylinder1->world = this;
  cylinder1->collisionShape = new btCylinderShape(btVector3(2, 2, 2));

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
