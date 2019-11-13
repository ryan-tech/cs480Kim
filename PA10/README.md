Project Assignment: PA10

Group Member Names:
  Maxwell Johnston
  Ryan Kim
  Ryan Poston

Date: 11/6/19

Project Directions: We made 4 new shader files that handle per vertex and per fragment lighting. The shader also allows for checking for a spotlight, and changes the lighting model when the object is in the spotlight. 

Description on changes:
  A per vertex_vertex shader and per vertex_fragment shader was created to do lighting on a model based on where the vertex is in the world. similarly, a perfragment_vertex shader and perfragment_fragment shader was created to show knowledge of both lighting models. As expected, banding can be seen on the perfragment shader models. keyboard functionality was implemented to change the values of different lighting products.
  



Controls:

Camera:
Use W to move camera Forwards.
Use S to move camera Backwards.
Use A to strafe camera Left.
Use D to strafe camera Right.
Use Q to zoom in
Use E to zoom out
Use Z to turn camera Left.
Use X to turn camera Right.

Use R to reset the view.

Press Esc to exit.


Lighting:
Ambient: Y increases H decreases
Diffuse: U increases J decreases
Specular: I increase K decreases

Spotlight size: N makes spotlight bigger, M makes spotlight smaller.


Required Libraries:
  sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev libbullet-dev

Instructions on compiling:
In CS480/PA8$

  mkdir build/

  cd build/

  cmake ..

  make

  ./PA10 -c ../config.json
