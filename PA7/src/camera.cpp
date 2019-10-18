#include "camera.h"

Camera::Camera()
{
	cameraPos   = glm::vec3(0.0f, 8.0f,  -16.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
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
                                 100.0f); //Distance to the far plane, 
  return true;
}

void Camera::Update(int keyPress)
{
	float cameraSpeed = .0005f;

	if(keyPress == SDLK_w)
		cameraPos += cameraSpeed * cameraFront;
    	if(keyPress == SDLK_s)
        	cameraPos -= cameraSpeed * cameraFront;
    	if(keyPress == SDLK_a)
        	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    	if(keyPress == SDLK_d)
        	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	view = glm::lookAt( cameraPos, //Eye Position
                       cameraFront, //Focus point
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


