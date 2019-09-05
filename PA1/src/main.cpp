#include <iostream>
#include "engine.h"

//These libraries are used to load the shaders from their text files.
#include <string>
#include <fstream>
#include <sstream>


string fileToString(string path);

int main(int argc, char **argv)
{
  //loads fragpath with path to fragment shader and vecpath with path to vector shader
  string fragPath = "", verPath = "";
  if(argc > 1){
    for(int i = 0; i < argc; i++){
      string argument = argv[i];
      if(argument == "-f"){
        if( i+1 < argc ){           //makes sure i doesn't go out of bounds
          fragPath = argv[i+1];     //filename is the argument after the flag
        }
      }
      if(argument == "-v"){
        if( i+1 < argc ){
          verPath = argv[i+1];
        }
      }
    }
  }
  else{
    std::cerr << "ERROR: No shaders specified." << endl;
    return 1;
  }
  if(fragPath == "" || verPath == ""){
    std::cerr << "ERROR: Missing fragment or vector shader." << endl;
    return 1;
  }
  string fragmentShader, vertexShader;
  fragmentShader = fileToString(fragPath);
  vertexShader = fileToString(verPath);

  //debug
/*
  std::cout << "-f fragment path: " << fragPath << endl;
  std::cout << "-v vertex path: " << verPath << endl;
  std::cout << "fragment shader: " << fragmentShader << endl;
  std::cout << "vertex shader: " << vertexShader << endl;

  //std::cout << "current path: " << GetCurrentWorkingDir() << endl;
*/

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600, fragmentShader, vertexShader);
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
