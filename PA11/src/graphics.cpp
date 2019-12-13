#include "graphics.h"
#include <math.h> 
#include <cmath>

Graphics::Graphics(nlohmann::json json_obj)
{
  m_config = json_obj;
  fragmentShader = m_config["Shader"]["PerVertexFragment"];

	cout << "file path: " << fragmentShader << "\n";

  vertexShader =  m_config["Shader"]["PerVertexVertex"];
  width = m_config["Window"]["Width"];
  height = m_config["Window"]["Height"];
  ambientVal = 1.0f;
  diffuseVal = 0.64f;
  specularVal = 0.5f;
  shininess = 96.078431f;
  sl_cutoff = 100.0f;

	for(int i=0; i<10; i++)
	{
		score[i] = 0;
		result[i] = 'n';
	}
	frame = 0;
	roll = 1;
	pins_remaining = 10;
	reset_initial_postion = false;
	updates_passed = 0;
	
/*
  sl_ambientVal = 1.0f;
  sl_diffuseVal = 0.64f;
  sl_specularVal = 0.5f;
  sl_shininess = 96.078431f;
  sl_cutoff = 1.0f;
  */
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

	std:cout << "about to make physics \n";

	m_world = new Physics(m_config);
  m_world->createObject();

  // Set up the shaders
  m_shader = new Shader(fragmentShader, vertexShader);
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

	cout << "shqaders initialized \n";

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

	cout << "shqaders loaded \n";

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


  //spotlight variables
  m_sl_position = m_shader -> GetUniformLocation("slPosition");
  if (m_sl_position == INVALID_UNIFORM_LOCATION)
  {
    printf("Spotlight position not found\n");
    return false;
  }

  m_sl_direction = m_shader -> GetUniformLocation("slDirection");
  if (m_sl_direction == INVALID_UNIFORM_LOCATION)
  {
    printf("Spotlight direction not found\n");
    return false;
  }

  m_sl_cutoff = m_shader -> GetUniformLocation("slCutoff");
  if (m_sl_cutoff == INVALID_UNIFORM_LOCATION)
  {
    printf("Spotlight cutoff not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

	cout << "graphics initialized \n";

  return true;
}

void Graphics::Display()
{
	cout << "+---+---+---+---+---+---+---+---+---+---+\n";
	cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n";
	cout << "+---+---+---+---+---+---+---+---+---+---+\n";
	cout << "|";
	
	for(int i=0; i<10; i++)
	{
		if(score[i] < 10)
		{
			cout << " " << score[i] << " |";
		}
		else if (score[i] < 100)
		{
			cout << " " << score[i] << "|";
		}
		else
		{
			cout << score[i] << "|";
		}
	}
	cout << "\n";
	cout << "+---+---+---+---+---+---+---+---+---+---+\n\n";
}

void Graphics::resetPins()
{
		//pin 1
		m_world->pin[1]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, 1.0f, 113.0f)
		));

		//pin 2
		m_world->pin[2]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, 1.0f, 114.5f)
		));

		//pin 3
		m_world->pin[3]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, 1.0f, 114.5f)
		));

		//pin 4
		m_world->pin[4]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(2.25f, 1.0f, 116.0f)
		));
		
		//pin 5
		m_world->pin[5]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(0.0f, 1.0f, 116.0f)
		));

		//pin 6
		m_world->pin[6]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-2.25f, 1.0f, 116.0f)
		));

		//pin 7
		m_world->pin[7]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(3.0f, 1.0f, 117.5f)
		));

		//pin 8
		m_world->pin[8]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(1.0f, 1.0f, 117.5f)
		));

		//pin 9
		m_world->pin[9]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-1.0f, 1.0f, 117.5f)
		));

		//pin 10
		m_world->pin[10]->rigidBody->setWorldTransform(btTransform(
		btQuaternion(0.0f, 0.0f, 0.0f, 1),
		btVector3(-3.0f, 1.0f, 117.5f)
		));

		btTransform trans;
		float x, y, z;

		for(int i = 1; i <= 10; i++)
		{
			x = m_world->pin[i]->intial_postion.getOrigin().getX();
			y = m_world->pin[i]->intial_postion.getOrigin().getY();
			z = m_world->pin[i]->intial_postion.getOrigin().getZ();
			
			cout << "pin " << i << " start: " << x << " " << y << " " << z << "\n";
		}
/*
	for(int i = 1; i <= 10; i++)
	{
		m_world->pin[i]->rigidBody->setWorldTransform(m_world->pin[i]->intial_postion);
	}*/
	pins_remaining = 10;
	roll = 1;

	for(int i = 1; i <= 10; i++)
		{
			m_world->pin[i]->rigidBody->getMotionState()->getWorldTransform(trans);

			x = trans.getOrigin().getX();
			y = trans.getOrigin().getY();
			z = trans.getOrigin().getZ();
			
			cout << "pin " << i << " reset to: " << x << " " << y << " " << z << "\n";
		}

	cout << "Reset pins\n";
}

void Graphics::Update(unsigned int dt, int keyboardButton)
{
  btTransform trans;
  float x, y, z;
	float distSqr;
	glm::vec3 pos,ipos;

	pins_remaining = 10;

	if(updates_passed <=50 )
	{
		for(int i = 1; i <= 10; i++)
		{
			m_world->pin[i]->rigidBody->getMotionState()->getWorldTransform(trans);

			x = trans.getOrigin().getX();
			y = trans.getOrigin().getY();
			z = trans.getOrigin().getZ();
			
			m_world->pin[i]->check_postion = btTransform(
			btQuaternion(0.0f, 0.0f, 0.0f, 1),
			btVector3(x, y, z)
			);
			
			//cout << "pin " << i << " start: " << x << " " << y << " " << z << "\n";
		}

	}	

	updates_passed++;	

	m_world->sphere->rigidBody->getMotionState()->getWorldTransform(trans);
  x = trans.getOrigin().getX();
  y = trans.getOrigin().getY();
  z = trans.getOrigin().getZ();

	if((y < -5))
	{
		//cout << "enter reset\n";
		
		m_world->sphere->rigidBody->setWorldTransform(m_world->sphere->intial_postion);
		m_world->sphere->rigidBody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		m_world->sphere->rigidBody->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));

		for(int i = 1; i <= 10; i++)
		{
			m_world->pin[i]->rigidBody->getMotionState()->getWorldTransform(trans);

			x = trans.getOrigin().getX();
  		y = trans.getOrigin().getY();
  		z = trans.getOrigin().getZ();

			pos = glm::vec3(x, y, z);

			x = m_world->pin[i]->check_postion.getOrigin().getX();
  		y = m_world->pin[i]->check_postion.getOrigin().getY();
  		z = m_world->pin[i]->check_postion.getOrigin().getZ();

			ipos = glm::vec3(x, y, z);

			glm::vec3 temp = pos - ipos;
			distSqr = dot(temp, temp);
	

			if (distSqr > 0.01f)
			{
				m_world->pin[i]->rigidBody->setWorldTransform(btTransform(
					btQuaternion(0.0f, 0.0f, 0.0f, 1),
					btVector3(20.0f, 2.0f, 100.0f)
					));
				pins_remaining-- ;
			}
		}

		cout << "frame: " << frame << "\nroll: " << roll << "\n";
		if(roll == 1)
		{
			cout << "pins remaining: " << pins_remaining << "\n";
		}

		if(pins_remaining == 0)
		{
			if(roll == 1)
			{
				result[frame] = 'X';
			}
			if(roll == 2)
			{
				result[frame] = '/';
			}
			resetPins();
			frame++;
		}
		else
		{
			if(frame > 0)
			{
				if(result[frame-1] == '/')
				{	
					if(roll == 1)
					{
						score[frame-1] = 10 + (10 - pins_remaining);
					}
				}
			}
			for(int i = frame-1; i >= 0; i--)
			{
				if(result[i] == 'X')
				{
					if(roll == 2)
					{
						score[i] = 10 + (10 - pins_remaining);
						result[i] = 'n';
					}
				}
			}
			score[frame] = 10 - pins_remaining;
			if(frame != 0)
			{
				score[frame] += score[frame-1];
			}
		}
		
		roll++;
		if(roll > 2)
		{
			resetPins();
			frame++;
		}

		Display();
	}

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
      plungerReleased = false;
    }
    else
    {
      //cout << "Switching the per vertex shader" << endl;
      fragmentShader = m_config["Shader"]["PerVertexFragment"];
      vertexShader = m_config["Shader"]["PerVertexVertex"];
      Initialize();
      cout << "Current shader: per vertex shader" << endl;
      plungerReleased = false;
    }
  }

  if(keyboardButton == SDLK_SLASH)
  {//restarts
    Initialize();
  }

  //DEBUG controls
  if(keyboardButton == SDLK_UP)// && !plungerReleased)
  {
    //plungerReleased = true;
    m_world->sphere->rigidBody->applyImpulse(btVector3(0,0,60), btVector3(0,0,0));
  }
  if(keyboardButton == SDLK_DOWN)// && !plungerReleased)
  {
    //plungerReleased = true;
    m_world->sphere->rigidBody->applyImpulse(btVector3(0,0,-5), btVector3(0,0,0));
  }
  if(keyboardButton == SDLK_LEFT)// && !plungerReleased)
  {
    //plungerReleased = true;
    m_world->sphere->rigidBody->applyImpulse(btVector3(5,0,0), btVector3(0,0,0));
  }
  if(keyboardButton == SDLK_RIGHT)// && !plungerReleased)
  {
    //plungerReleased = true;
    m_world->sphere->rigidBody->applyImpulse(btVector3(-5,0,0), btVector3(0,0,0));
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

  if(keyboardButton == SDLK_n) sl_cutoff += 1.0f;
  if(keyboardButton == SDLK_m) sl_cutoff -= 1.0f;

  // Update the object
  m_world->Update(dt, keyboardButton);
	//cout << "world updated \n";

  m_camera->Update(dt, keyboardButton);
	//cout << "camera updated \n";

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

  // spot light
  btTransform trans;
  float x, y, z;
  m_world->sphere->rigidBody->getMotionState()->getWorldTransform(trans);
  x = trans.getOrigin().getX();
  y = trans.getOrigin().getY();
  z = trans.getOrigin().getZ();

  glUniform4f(m_lightPos, x, y+10, z, 1.0f);

  //glUniform4fv(m_lightPos, 1, glm::value_ptr(m_world->sphere->GetModel()));
  glUniform4f(m_ambientProd, ambientVal, ambientVal, ambientVal, 1.0f);
  glUniform4f(m_diffuseProd, diffuseVal, diffuseVal, diffuseVal, 1.0f);
  glUniform4f(m_specularProd, specularVal, specularVal, specularVal, 1.0f);
  glUniform1f(m_shininess, shininess);

  glUniform3f(m_sl_direction, 0.0f, -1.0f, 0.0f);
  glUniform1f(m_sl_cutoff, glm::cos(glm::radians(sl_cutoff)));


  //board
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->board->GetModel()));
  m_world->board->Render();

  //ball
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->sphere->GetModel()));
  m_world->sphere->Render();


  //10 pins
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder1->GetModel()));
  m_world->cylinder1->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder2->GetModel()));
  m_world->cylinder2->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder3->GetModel()));
  m_world->cylinder3->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder4->GetModel()));
  m_world->cylinder4->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder5->GetModel()));
  m_world->cylinder5->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder6->GetModel()));
  m_world->cylinder6->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder7->GetModel()));
  m_world->cylinder7->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder8->GetModel()));
  m_world->cylinder8->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder9->GetModel()));
  m_world->cylinder9->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->cylinder10->GetModel()));
  m_world->cylinder10->Render();


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