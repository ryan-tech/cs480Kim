#include "graphics.h"

Graphics::Graphics(nlohmann::json json_obj)
{
  m_config = json_obj;
  fragmentShader = m_config["Shader"]["PerVertexFragment"];
  vertexShader =  m_config["Shader"]["PerVertexVertex"];
  width = m_config["Window"]["Width"];
  height = m_config["Window"]["Height"];
  ambientVal = 1.0f;
  diffuseVal = 0.64f;
  specularVal = 0.5f;
  shininess = 96.078431f;
}

Graphics::~Graphics()
{

}

bool Graphics::Initialize()
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  //Create Objects here
  //m_object = new Object(m_config); //board

  m_world = new Physics(m_config);
  m_world->createObject();
  // Set up the shaders
  m_shader = new Shader(fragmentShader, vertexShader);
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("Projection");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("View");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("Model");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Locate the light position in the shader
  m_lightPos = m_shader -> GetUniformLocation("LightPosition");
  if (m_lightPos == INVALID_UNIFORM_LOCATION)
  {
    printf("LightPosition not found\n");
    return false;
  }

  // Locate the ambient product in the shader
  m_ambientProd = m_shader -> GetUniformLocation("AmbientProduct");
  if (m_ambientProd == INVALID_UNIFORM_LOCATION)
  {
    printf("AmbientProduct not found\n");
    return false;
  }

  // Locate the diffuse product in the shader
  m_diffuseProd = m_shader -> GetUniformLocation("DiffuseProduct");
  if (m_diffuseProd == INVALID_UNIFORM_LOCATION)
  {
    printf("DiffuseProduct not found\n");
    return false;
  }

  // Locate the specular product in the shader
  m_specularProd = m_shader -> GetUniformLocation("SpecularProduct");
  if (m_specularProd == INVALID_UNIFORM_LOCATION)
  {
    printf("SpecularProduct not found\n");
    return false;
  }

  m_shininess = m_shader -> GetUniformLocation("Shininess");
  if (m_specularProd == INVALID_UNIFORM_LOCATION)
  {
    printf("Shininess not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt, int keyboardButton)
{
  // press f to pay respects and change the shader
  if(keyboardButton == SDLK_f)
  {
    // switch the flag
    if(flag)
    {
      flag = false;
    }
    else
    {
      flag = true;
    }
    // switch the shader
    // by default the shader is per vertex and the flag is true, so when f is pressed it switches it to false.
    if(!flag)
    {

      fragmentShader = m_config["Shader"]["PerFragmentFragment"];
      vertexShader = m_config["Shader"]["PerFragmentVertex"];
      Initialize();
      cout << "Current shader: per fragment shader" << endl;
    }
    else
    {
      //cout << "Switching the per vertex shader" << endl;
      fragmentShader = m_config["Shader"]["PerVertexFragment"];
      vertexShader = m_config["Shader"]["PerVertexVertex"];
      Initialize();
      cout << "Current shader: per vertex shader" << endl;

    }
  }
  // controls to change the lighting values
  if(keyboardButton == SDLK_y) ambientVal += 0.05f;
  if(keyboardButton == SDLK_h) ambientVal -= 0.05f;
  if(keyboardButton == SDLK_u) diffuseVal += 0.05f;
  if(keyboardButton == SDLK_j) diffuseVal -= 0.05f;
  if(keyboardButton == SDLK_i) specularVal += 0.05f;
  if(keyboardButton == SDLK_k) specularVal -= 0.05f;
  if(keyboardButton == SDLK_o) shininess += 0.05f;
  if(keyboardButton == SDLK_l) shininess += 0.05f;

  // Update the object
  m_world->Update(dt, keyboardButton);
  m_camera->Update(keyboardButton, dt);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();
  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  glUniform4f(m_lightPos, 0.0f, 5.0f, 0.0f, 1.0f);
  glUniform4f(m_ambientProd, ambientVal, ambientVal, ambientVal, 1.0f);
  glUniform4f(m_diffuseProd, diffuseVal, diffuseVal, diffuseVal, 1.0f);
  glUniform4f(m_specularProd, specularVal, specularVal, specularVal, 1.0f);
  glUniform1f(m_shininess, shininess);

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->board->GetModel()));
  m_world->board->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->sphere->GetModel()));
  m_world->sphere->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder->GetModel()));
  m_world->cylinder->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cube->GetModel()));
  m_world->cube->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
