#include <iostream>
#include "engine.h"

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
  string fragPath = "", verPath = "", objPath = "";
  if(argc > 1){
    for(int i = 0; i < argc; i++){
      string argument = argv[i];
      if(argument == "-f"){         //fragment shader flag
        if( i+1 < argc ){           //makes sure i doesn't go out of bounds
          fragPath = argv[i+1];     //filename is the argument after the flag
        }
      }
      if(argument == "-v"){         //vertex shader flag
        if( i+1 < argc ){
          verPath = argv[i+1];
        }
      }
      if(argument == "-o"){         //object obj file flag
        if( i+1 < argc ){
          objPath = argv[i+1];
        }
      }
    }
  }
  else{
    std::cerr << "ERROR: No shaders specified." << endl;
    return 1;
  }
  if(fragPath == "" || verPath == ""){
    std::cerr << "ERROR: Missing fragment or vertex shader." << endl;
    return 1;
  }
  string fragmentShader, vertexShader;
  fragmentShader = fileToString(fragPath);
  vertexShader = fileToString(verPath);

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Ryan Kim", 800, 600, fragmentShader, vertexShader, objPath); //Added fragment shader and vertex shaders as parameters for the Engine constructor.
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

//taken from stackoverflow
string fileToString(string path){

  char buf[256];
  std::ifstream t(path);
  std::string str;
  while(t.good()){
    t.getline(buf, 256);
    str += buf;
    str += '\n';
  }
  return str;
}