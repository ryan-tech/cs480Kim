PA10 - Pinball Game

Group:
Maxwell Johnston
Ryan Kim
Ryan Poston

Overview:
Our game loads all the basics from the rubric, starting with the board, ball, bumpers and flippers.
 We also loaded the backboard of our game. Our pinball game also runs proper collision detection for the ball on the board,
gravity is working as intended and the paddles move when inputs on the keyboard are pressed, but they do not work correctly.
For lighting, ambient and specular are adjustable and both per-vertex and per-fragment lighting is implemented as well as the functionality
 to switch between them. Also, different items have different colors with diffuse lighting.

User Manual:
Game Controls:
Restart: / before your lives hit zero, T after your lives hit zero.

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



Flipper Control:
Left Flipper: ‘,’ button activates the left flipper
Right Flipper: ‘.’ Button activates the right flipper

The game resets if the ball gets past the flippers, up to the third ball, then game over occurs.


User Manual:
Game Controls:
Restart: / before your lives hit zero, T after your lives hit zero.

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



Flipper Control:
Left Flipper: ‘,’ button activates the left flipper
Right Flipper: ‘.’ Button activates the right flipper

The game resets if the ball gets past the flippers, up to the third ball, then game over occurs.



Code Documentation:
Required Libraries: sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev libbullet-dev
Instructions on compiling: In CS480/PA10$
mkdir build/
cd build/
cmake ..
make
./PA10 -c ../config.json
