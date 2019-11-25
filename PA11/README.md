PA10 - Pinball Game

Group:
Maxwell Johnston
Ryan Kim
Ryan Poston

Overview:


User Manual:
Game Controls:


Camera movement:
Camera: Use W to move camera Forwards.
Use S to move camera Backwards. Use A to strafe camera Left.
Use D to strafe camera Right. Use Q to zoom in
Use E to zoom out
Use Z to turn camera Left.
 Use X to turn camera Right.
Use R to reset the view.
Press Esc to exit.
Lighting:
Lighting: Ambient: Y increases H decreases
Diffuse: U increases J decreases
Specular: I increase K decreases
Spotlight size: N makes spotlight bigger; M makes spotlight smaller.


Code Documentation:
Required Libraries: sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev libbullet-dev
Instructions on compiling: In CS480/PA10$
mkdir build/
cd build/
cmake ..
make
./PA11 -c ../config.json
