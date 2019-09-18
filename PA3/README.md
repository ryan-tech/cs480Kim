Project Assignment: PA3

Name: Ryan Kim

Date: 09/19/19

Project Directions: There are two cubes. One will act as the planet and one will act as the moon. The planet will orbit around the origin (center of the screen), while the moon orbits around the planet. Both objects will be rotating on their respective axes at all times. Keyboard commands will be added for interactions and will be used to change the direction of the object's orbit and rotation.

Description on changes:
  The default direction of rotation or orbit for both the moon and planet is clockwise. The keyboard controls are described below.


Keyboard Controls:
Key | Description
Left   : Changes planet orbit path to clockwise
Right  : Changes planet orbit path to counter-clockwise
UP     : Changes planet rotation to clockwise
Down   : Changes planet rotation to counter-clockwise
a      : Changes moon orbit path to clockwise
s      : Changes moon orbit path to counter-clockwise
d      : Changes moon rotation to clockwise
f      : Changes moon rotation to counter-clockwise

Instructions on compiling:

In CS480/PA3$

  mkdir build/

  cd build/

  cp ../makefile .

  make clean

  make

  ./Tutorial -f ../shaders/fragment.txt -v ../shaders/vertex.txt
