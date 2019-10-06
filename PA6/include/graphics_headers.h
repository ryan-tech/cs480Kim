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

struct Vertex
{
  glm::vec3 vertex;
  glm::vec3 color;

  Vertex(glm::vec3 v, glm::vec3 c): vertex(v), color(c) {}
};

struct Triangle_vertex
{
  glm::vec3 vertex;
  glm::vec2 texture;
  glm::vec3 normal;
};

#endif /* GRAPHICS_HEADERS_H */
