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
void Object::loadObject()
{
  //Triangle_vertex tri;

  //Vertex v;                          //buffer to push into the vertices vector
  glm::vec2 vt;
  glm::vec3 vn;

  //for the vectors (2d and 3d)
  char buf[256];
  std::ifstream t(filePath);
  std::string str;
  std::string type;
  double x=0,y=0,z=0;

  //for the triangles
  std::string delimiter = "/";
  std::string token;

  unsigned int index = 0;                        //holds the converted token


  glm::vec3 face_vertex, face_texture, face_normal;
  while(t.good()){
    if(t.eof()) break;
    t.getline(buf, 256);

    str = buf;
    std::istringstream line(str);

    line >> type;

    if(type == "v")//vertex
    {
      line >> x >> y >> z;
      Vertices.push_back( Vertex( glm::vec3(x,y,z), glm::vec3(0,255,0) ) );
    }
    else if(type == "vt")//texture
    {
      line >> x >> y;
      vt = glm::vec2(x,y);
      textureCoordinates.push_back(vt);
    }
    else if(type == "vn")//normal
    {
      line >> x >> y >> z;
      vn = glm::vec3(x,y,z);
      normalVectors.push_back(vn);
    }
    else if(type == "f")//triangle
    {
      vector<Triangle_vertex>  triangle_vertices;          //holds the triangle's vertices
      //for the three vertices in a triangle
      std::string face;

      for(int i = 0; i < 3; i++)
      {
        line >> face;
        token = face.substr(0, face.find(delimiter));                             //first value (example: face = 1/2/3)
        if(token == "") return;
        index = stoi(token);
        Indices.push_back(index);

        /* The code below was used to push back the vertices and vectors indexed by the face indices
        face = face.erase(0, face.find(delimiter) + delimiter.length());          //cuts string to next value (example: face = 2/3)
        token = face.substr(0, face.find(delimiter));                             //token = second value
        index = stoi(token);
        //std::cout<<"second: " << token << " ";
        //tri.texture = textureCoordinates.at(index-1);
        //Indices.push_back(index);

        face = face.erase(0, face.find(delimiter) + delimiter.length());          //face = 3
        token = face;                                                             //token = third value
        index = stoi(token);
        */
        //std::cout<<"third: " << token << endl;
        //tri.normal = normalVectors.at(index-1);
        //Indices.push_back(index);

        //push back the triangle
        //triangle_vertices.push_back(tri);
      }
    }
  }
  return;
}
