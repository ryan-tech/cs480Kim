#ifndef GRAPHICS_H
#define GRAPHICS_H

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

    //Added PA3: Two cubes, one's the planet and one's the moon
    Object *m_planet;
    Object *m_moon;
    Object *m_board;

    string fragmentShader, vertexShader, objPath;

};

#endif /* GRAPHICS_H */
