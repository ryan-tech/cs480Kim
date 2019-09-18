#include "object.h"

Object::Object()
{
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  planet_translation_angle = 0.0f;
  planet_rotation_angle = 0.0f;
  moon_translation_angle = 0.0f;
  moon_rotation_angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);


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
