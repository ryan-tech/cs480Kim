#ifndef GRAPHICS_HEADERS_H
#define GRAPHICS_HEADERS_H
#include <SDL2/SDL.h>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#if defined(__APPLE__) || defined(MACOSX)
  #include <OpenGL/gl3.h>
  #include <OpenGL/GLU.h>
#else //linux as default
  #include <GL/glew.h>
  //#include <GL/glu.h>
#endif

// GLM for matricies
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
#define INVALID_UNIFORM_LOCATION 0x7fffffff

#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects
#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>

// JSON library
#include "json.hpp"

//Bullet Real Time Physics Library
#include <btBulletDynamicsCommon.h>


using namespace std;

struct Vertex
{
  glm::vec3 vertex;
  glm::vec3 color;
  glm::vec2 texture;
  glm::vec3 normal;
  Vertex(glm::vec3 v, glm::vec2 t, glm::vec3 c, glm::vec3 n): vertex(v), texture(t), color(c), normal(n){}
};

struct Triangle_vertex
{
  glm::vec3 vertex;
  glm::vec2 texture;
  glm::vec3 normal;
};

struct Mesh
{
	GLuint VB;
  GLuint IB;

	vector<Vertex> Vertices;              //holds the vertices (v)
  vector<glm::vec2> textureCoordinates; //holds the texture coordinate (vt)
  vector<glm::vec3> normalVectors;      //holds the normal vectors (vn)
  vector<unsigned int> Indices;         //holds the faces (f)

  unsigned int MaterialIndex;

  Mesh(){};
};

#endif /* GRAPHICS_HEADERS_H */
