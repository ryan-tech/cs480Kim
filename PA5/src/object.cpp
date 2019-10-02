#include "object.h"

//The default constructor used to have the cube in it.
Object::Object()
{
  angle = 0.0f;
  planet_translation_angle = 0.0f;
  planet_rotation_angle = 0.0f;
  moon_translation_angle = 0.0f;
  moon_rotation_angle = 0.0f;
  planet_clockwise_translation = true;
  planet_clockwise_rotation = true;
  moon_clockwise_translation = true;
  moon_clockwise_rotation = true;
}

//The parameterized constructor uses the path in the parameter to call loadObject()
Object::Object(string path)
{
  filePath = path;
  loadObject();

  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  angle = 0.0f;
  planet_translation_angle = 0.0f;
  planet_rotation_angle = 0.0f;
  moon_translation_angle = 0.0f;
  moon_rotation_angle = 0.0f;
  planet_clockwise_translation = true;
  planet_clockwise_rotation = true;
  moon_clockwise_translation = true;
  moon_clockwise_rotation = true;
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}
void Object::Update(unsigned int dt, int keyboardButton)
{
  angle += dt * M_PI/10000;
  model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
  model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

//A custom update function used by the planet
void Object::Update_planet(unsigned int dt, int keyboardButton)
{
  planet_rotation_angle += dt * M_PI/1000;
  planet_translation_angle += dt * M_PI/1000;
  //translation
  switch(keyboardButton)
  {
    case SDLK_LEFT:
      planet_clockwise_translation = true;
      break;
    case SDLK_RIGHT:
      planet_clockwise_translation = false;
      break;
    case SDLK_UP:
      planet_clockwise_rotation = true;
      break;
    case SDLK_DOWN:
      planet_clockwise_rotation = false;
    case SDLK_a:
      moon_clockwise_translation = true;
      break;
    case SDLK_s:
      moon_clockwise_translation = false;
      break;
    case SDLK_d:
      moon_clockwise_rotation = true;
      break;
    case SDLK_f:
      moon_clockwise_rotation = false;
  }

  if(planet_clockwise_translation)
  {
    planet_translation_angle += 0;
  }
  else
  {
    planet_translation_angle -= dt * M_PI/500;
  }

  if(planet_clockwise_rotation)
  {
    planet_rotation_angle += 0;
  }
  else
  {
    planet_rotation_angle -= dt * M_PI/500;
  }

  //translate first
  model = glm::translate(glm::mat4(1.0f), glm::vec3(cos(planet_translation_angle)*3, 0, sin(planet_translation_angle)*3));
  //rotate second
  model = glm::rotate(model, (planet_rotation_angle), glm::vec3(0.0, 1.0, 0.0));

}


//A custom update function used by the moon
void Object::Update_moon(unsigned int dt, int keyboardButton)
{
  moon_translation_angle += dt * M_PI/800;
  moon_rotation_angle += dt * M_PI/800;
  //--------Below is same as update_planet----------//
  planet_rotation_angle += dt * M_PI/1000;
  planet_translation_angle += dt * M_PI/1000;
  //translation
  switch(keyboardButton)
  {
    case SDLK_LEFT:
      planet_clockwise_translation = true;
      break;
    case SDLK_RIGHT:
      planet_clockwise_translation = false;
      break;
    case SDLK_UP:
      planet_clockwise_rotation = true;
      break;
    case SDLK_DOWN:
      planet_clockwise_rotation = false;
      break;
    case SDLK_a:
      moon_clockwise_translation = true;
      break;
    case SDLK_s:
      moon_clockwise_translation = false;
      break;
    case SDLK_d:
      moon_clockwise_rotation = true;
      break;
    case SDLK_f:
      moon_clockwise_rotation = false;
      break;
  }

  if(planet_clockwise_translation)
  {
    planet_translation_angle += 0;
  }
  else
  {
    planet_translation_angle -= dt * M_PI/500;
  }

  if(planet_clockwise_rotation)
  {
    planet_rotation_angle += 0;
  }
  else
  {
    planet_rotation_angle -= dt * M_PI/500;
  }

  //translate first
  model = glm::translate(glm::mat4(1.0f), glm::vec3(cos(planet_translation_angle)*3, 0, sin(planet_translation_angle)*3));
  //rotate second
  model = glm::rotate(model, (planet_rotation_angle), glm::vec3(0.0, 1.0, 0.0));

  //--------Above is same as update_planet----------//

  if(moon_clockwise_translation)
  {
    moon_translation_angle += 0;
  }
  else
  {
    moon_translation_angle -= dt * M_PI/400;
  }

  if(moon_clockwise_rotation)
  {
    moon_rotation_angle += 0;
  }
  else
  {
    moon_rotation_angle -= dt * M_PI/400;
  }

  model = glm::translate(glm::mat4(1.0f), glm::vec3(cos(moon_translation_angle)*3+cos(planet_translation_angle)*3, 0, sin(moon_translation_angle)*3+sin(planet_translation_angle)*3));
  model = glm::rotate(model, (moon_rotation_angle), glm::vec3(0.0, 1.0, 0.0));

}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}


//loads the vertices and faces into their respective vertices and indices vectors.
//Each scene has a mesh, each mesh has a face, each face has aiVector3D of mVertices
//Goal: load vertices and indices vertex.
//PA5: Uses the assimp library
void Object::loadObject()
{


  Assimp::Importer importer;
  const aiScene *myScene = importer.ReadFile(filePath, aiProcess_Triangulate);    //Define aiScene pointer
  //for each mesh in the scene
  for(int i = 0; i < myScene->mNumMeshes; i++)
  {
    //for each face in the mesh
    for(int j = 0; j < myScene->mMeshes[i]->mNumFaces; j++)
    {
      //for each array of indices per face
      for(int k = 0; k < myScene->mMeshes[i]->mFaces[j]->mIndices; k++)
      {
        for(int l = 0; l < myScene->mMeshes[i]->mFaces[j]->mNumIndices; l++)
        {
          Indices.push_back(myScene->mMeshes[i]->mFaces[j]->mIndices[l]);
        }
      }
    }
  }




}
