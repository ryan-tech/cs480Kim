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

class Graphics
{
  public:
    Graphics();
    Graphics(string fragment, string vertex, string path);
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, int keyboardButton);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object* planets[NUM_PLANETS];    //1 sun, 8 planets, 1 pluto

    string fragmentShader, vertexShader, objPath;

};

#endif /* GRAPHICS_H */