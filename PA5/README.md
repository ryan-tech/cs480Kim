Project Assignment: PA5

Group Member Names:
  Ryan Kim
  Maxwell Johnston
  Ryan Poston

Date: 10/1/19

Project Directions: The instructions were to load an object using the assimp library.

Description on changes:
  In the object class, the loadObject method creates an aiScene object, and is then processed to load the vertices and indices from the object. The Indices vertex was not shifted in the object constructor because Assimp already offsets the indices.


Instructions on compiling:

In CS480/PA5$

  sudo apt-get install libassimp-dev

  mkdir build/

  cd build/

  cmake ..

  make

  ./PA5 -f ../shaders/fragment.txt -v ../shaders/vertex.txt -o ../blender_object/board.obj
