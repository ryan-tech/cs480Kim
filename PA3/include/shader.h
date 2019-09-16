#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    Shader(std::string fragment, std::string vertex);
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;
    std::vector<GLuint> m_shaderObjList;

    std::string vertexShader, fragmentShader;
};

#endif  /* SHADER_H */
