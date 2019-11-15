#include "camera.h"

Camera::Camera()
{
	cameraPos   = glm::vec3(0.0f, 35.0f, -40.0f);
	cameraFront = glm::vec3(0.0f, -15.0f, 10.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic
  //  for this project having them static will be fine

	view = glm::lookAt( cameraPos, //Eye Position
                      cameraFront, //Focus point
                      cameraUp); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 200.0f); //Distance to the far plane,
  return true;
}


/*
 *  Function: Update(unsigned int dt, int keyPress)
 *  Parameters: int keyPress, unsigned int dt
 *  Return: void
 *  Purpose: Implements keyboard presses and camera interaction.
 */
void Camera::Update(unsigned int dt, int keyPress)
{
	float cameraSpeed = 2.5f * dt/1000;

	if(keyPress == SDLK_w)	//move forward
			cameraPos += glm::vec3(0.0f, 0.0f, cameraSpeed*10);
	if(keyPress == SDLK_s)	//move backward
			cameraPos -= glm::vec3(0.0f, 0.0f, cameraSpeed*10);
	if(keyPress == SDLK_a)	//strafe left
			cameraPos -= glm::vec3(glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*10));
	if(keyPress == SDLK_d)
			cameraPos += glm::vec3(glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*10));
	if(keyPress == SDLK_q)//go up
			cameraPos += cameraSpeed * cameraFront;
	if(keyPress == SDLK_e)//go down
			cameraPos -= cameraSpeed * cameraFront;
	if(keyPress == SDLK_z)//turn left
			cameraFront -= glm::vec3(glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*10));
	if(keyPress == SDLK_x)//turn right
			cameraFront += glm::vec3(glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*10));
	if(keyPress == SDLK_c)//look up
			cameraFront += glm::vec3(0.0f, cameraSpeed*10, 0.0f);
	if(keyPress == SDLK_v)//turn down
			cameraFront -= glm::vec3(0.0f, cameraSpeed*10, 0.0f);

//	if(keyPress == SDLK_e)//look down
//			cameraFront -= glm::vec3(0.0f, 0.0f, cameraSpeed*10);
	if(keyPress == SDLK_r)
	{
		cameraPos   = glm::vec3(0.0f, 35.0f, -40.0f);
		cameraFront = glm::vec3(0.0f, -15.0f, 10.0f);
		cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	view = glm::lookAt( cameraPos, //Eye Position
											cameraPos + cameraFront, //Focus point
											cameraUp); //Positive Y is up


}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}
