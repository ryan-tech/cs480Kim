#PA1
#Name: Ryan Kim
#Date: 09/01/19
#Project Directions: Make the cube spin while orbiting the center. Also pass shaders in through command line arguments using -f and -v flags for "fragment" and "vertex", respectively.

Instructions on compiling:
  cd build/
  make clean
  ./Tutorial -f ../src/shaders/fragment.txt -v ../src/shaders/vertex.txt

Had to add -lstdc++fs as a gcc flag
  #./Tutorial -f <path_to_fragment_shader.txt> -v <path_to_vertex_shader.txt>
