
#include "engine.h"

Engine::Engine(nlohmann::json json_obj)
{
  m_WINDOW_NAME = json_obj["Window"]["Name"];
  m_WINDOW_WIDTH = json_obj["Window"]["Width"];
  m_WINDOW_HEIGHT = json_obj["Window"]["Height"];
  m_FULLSCREEN = json_obj["Window"]["Fullscreen"];
  m_config = json_obj;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics(m_config);
  if(!m_graphics->Initialize())
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
	//cout << "engine run \n";

  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT, keyboardButton);   //added m_keypress to parameters
		//cout << "graphics updated \n";
    m_graphics->Render();
		//cout << "graphics rendered \n";

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
      // handle key down events here
  else if (m_event.type == SDL_KEYDOWN)
  {
    //Keyboard Escape key pressed
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
    keyboardButton = m_event.key.keysym.sym;

  }
  else if (m_event.type == SDL_KEYUP)
  {
    keyboardButton = 0;
  }
  //PA2: handle mouse click events here

}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
