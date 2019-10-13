#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"
#include <string>

class Engine
{
  public:
    Engine(string name, int width, int height, string fragment, string vertex, string path);
    Engine(string name);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    unsigned int getDT();
    long long GetCurrentTimeMillis();

  private:
    // Window related variables
    Window *m_window;
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    string vertexShader, fragmentShader;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
    string m_path;

    int keyboardButton;

};

#endif // ENGINE_H
