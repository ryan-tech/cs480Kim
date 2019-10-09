Project Assignment: PA6

Group Member Names:
  Maxwell Johnston
  Ryan Kim
  Ryan Poston

Date: 10/9/19

Project Directions: The instructions were to load an object's textures using the assimp library.

Description on changes:
  A Texture class was created through the texture.cpp and texture.h files. This texture class has a constructor which includes a filepath as a parameter, and has a load method which loads the texture from the image specified by the filepath. The shader files were also modified to be able to pass the texture coordinates and render the textures.


Required Libraries:
  sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev

Instructions on compiling:
In CS480/PA6$

  mkdir build/

  cd build/

  cmake ..

  make

  ./PA6 -f ../shaders/fragment.txt -v ../shaders/vertex.txt -o ../blender_object/buddha.obj
