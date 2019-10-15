#include <iostream>
#include "engine.h"
#include "graphics_headers.h"
//These libraries are used to load the shaders from their text files.
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

string fileToString(string path);

int main(int argc, char **argv)
{
  //loads fragpath with path to fragment shader and vecpath with path to vertex shader
  string configPath = ""; //fragPath = "", verPath = "",
  if(argc > 1){
    for(int i = 0; i < argc; i++){
      string argument = argv[i];
      if(argument == "-c"){         //object obj file flag
        if( i+1 < argc ){
          configPath = argv[i+1];
        }
      }
    }
  }
  else{
    std::cerr << "ERROR: No config file specified." << endl;
    return 1;
  }

  std::ifstream config(configPath);
  nlohmann::json json_obj;
  config >> json_obj;


  // Start an engine and run it then cleanup after
  Engine *engine = new Engine(json_obj); //
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;

  return 0;
}
