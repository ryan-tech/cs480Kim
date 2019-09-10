PA1

Name: Ryan Kim

Date: 09/01/19

Project Directions: Make the cube spin while orbiting the center. Also pass shaders in through command line arguments using -f and -v flags for "fragment" and "vertex", respectively.

Description on changes:
 The cube rotates as given. Then, the cube is translated with respect to a vector whose components are the angle converted into rectangular vector components. To keep the cube rotating, the cube object is passed into the initial parameter for the translate() method. The y component is kept at 0 to simulate a rotation about the y-axis.

Shader Files:
 The shaders are saved as .txt files in CS480/PA1/src/shaders and are loaded in main() and initialized to string variables. These string variables are then passed into the engine, graphics, and finally the shader class to be loaded when calling the addShader method.

Instructions on compiling:

In CS480/PA1$

  mkdir build/

  cd build/

  cp ../makefile .

  make clean

  make

  ./Tutorial -f ../src/shaders/fragment.txt -v ../src/shaders/vertex.txt
