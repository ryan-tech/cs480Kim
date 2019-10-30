#ifndef GRAPHICS_H
#define GRAPHICS_H
#define NUM_PLANETS 10

#include <iostream>
#include <string>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "physics.h"

class Graphics
{
  public:
    Graphics();
    Graphics(nlohmann::json json_obj);
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, int keyboardButton);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    nlohmann::json m_config;

    Physics* m_world;

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    Object* m_object;

    string fragmentShader, vertexShader;


};

#endif /* GRAPHICS_H */
