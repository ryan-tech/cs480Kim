Project Assignment: PA4

Name: Ryan Kim

Date: 09/25/19

Project Directions: The instructions were to create a model loader for a .obj file that we created on blender. The function reads the vectors and triangles and displays them on the window.

Description on changes:
  A model loader function was added to the object class and although it reads and loads the entire file, it only uses the vertices and triangles to draw the image. At first, I wouldn't see the model on the screen, but then I realized that my update function did nothing and I had to translate the model to the origin. Only then did it show up on my screen. I also added a "-o" flag to specify the .obj filepath. 

EXTRA CREDIT:
I colored all models green.


Instructions on compiling:

In CS480/PA4$

  mkdir build/

  cd build/

  cp ../makefile .

  make clean

  make

  ./Tutorial -f ../shaders/fragment.txt -v ../shaders/vertex.txt -o ../blender_object/board.obj
