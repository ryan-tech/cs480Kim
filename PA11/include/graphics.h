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
    bool Initialize();
    void Update(unsigned int dt, int keyboardButton);
    void Render();
		void Display();
		void resetPins();

  private:
    std::string ErrorString(GLenum error);
    nlohmann::json m_config;
    Physics* m_world;
    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    //per fragment shader variables

    GLint m_ambientProd;
    GLint m_diffuseProd;
    GLint m_specularProd;
    GLint m_lightPos;
    GLint m_shininess;

    bool flag = true; //flag = true : per vertex lighting
                      //flag = false: per fragment lighting

    bool plungerReleased = false;
    bool died = false;
    int width, height;
    int num_balls = 4;
    int num_plunger = 0;
    //int score = 0;
    //values to be used for lighting variables
    float ambientVal;
    float diffuseVal;
    float specularVal;
    float shininess;

		int score[10];
		char result[10];
		int frame;
		int roll;
		int pins_remaining;

		int updates_passed;

    //spotlight values

    GLint m_sl_position;
    GLint m_sl_direction;
    GLint m_sl_cutoff;

    float sl_cutoff;
    /*
    float sl_ambientVal;
    float sl_diffuseVal;
    float sl_specularVal;
    float sl_shininess;
    float sl_cutoff;
*/

		bool reset_initial_position;

    string fragmentShader, vertexShader;

};

#endif /* GRAPHICS_H */
