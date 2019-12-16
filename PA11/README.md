PA11 - Pinball Game

Group:
Maxwell Johnston
Ryan Kim
Ryan Poston

Overview: We created the board, pins and ball and marked the ball and pins as dynamic, we have a spotlight following the ball and camera movement in place, as well as a way to make the ball move down the lane. We still need to implement a game loop and scoring mechanism that works similarly to a normal game of bowling.


User Manual:
Game Controls:


q - zoom in
e - zoom out
w - move camera up
a - move camera left
s - move camera down
d - move camera right
z - rotate camera left
x - rotate camera up
c - rotate camera down
v - rotate camera right


/ - restarts game


Lighting:
Ambient: Y increases H decreases

Diffuse: U increases J decreases

Specular: I increase K decreases

Spotlight size: N makes spotlight bigger, M makes spotlight smaller.

f switches between per vertex and per fragment (per vertex is the default)

Space - shoots ball forward
Up - Increase power
Down - Decrease power
Left - shift left
Right - shift right

Code Documentation:
Required Libraries: sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev libbullet-dev
Instructions on compiling: In CS480/PA11$
mkdir build/
cd build/
cmake ..
make
./PA11 -c ../config.json
