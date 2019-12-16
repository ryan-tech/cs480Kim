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

struct Roll
{
  int firstRoll;
  int secondRoll;
};

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
    void resetBall();
    void debug(int keyboardButton);
    void Controls(int keyboardButton);
    bool LoadShaders();
		void ShowForce();
    void CalculateStrike();
    void CalculateSpare();

  private:
    std::string ErrorString(GLenum error);
    nlohmann::json m_config;
    Physics* m_world;
    Camera *m_camera;
    Shader *m_shader;
    int width, height;

    // Uniform Values
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    // Lighting Variables
    GLint m_ambientProd;
    GLint m_diffuseProd;
    GLint m_specularProd;
    GLint m_lightPos;
    GLint m_shininess;
    //Spotlight values
    GLint m_sl_position;
    GLint m_sl_direction;
    GLint m_sl_cutoff;

    float ambientVal;
    float diffuseVal;
    float specularVal;
    float shininess;
    float sl_cutoff;


    // Lighting shader switch flag
    bool flag = true; //flag = true : per vertex lighting
                      //flag = false: per fragment lighting

		Object* arrow;
		int force;
		bool can_throw;
		int can_change_force;
		int score[10];
		Roll result[10]; //10 is spare, 11 is strike
		int frame;
		int roll;
		int pins_remaining;
		int updates_passed;
    float dx = 0;
    glm::vec3 pos;
    glm::vec3 ipos;
		bool reset_initial_position;
    string fragmentShader, vertexShader;

};




#endif /* GRAPHICS_H */
