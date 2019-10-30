Project Assignment: PA8

Group Member Names:
  Maxwell Johnston
  Ryan Kim
  Ryan Poston

Date: 10/30/19

Project Directions: We had to load a board, sphere, cube, and cylinder. We made the Cylinder Static, the sphere dynamic, and the cube kinematic. We also loaded the board using triangle meshes.

Description on changes:
  A Physics class was created in order to handle loading objects and rigidbodies into Bullet. We put the cylinder in the middle of the board to make it easier to collide with and make the cylinder static. Then we made the sphere a dynamic object so that forces applied to the sphere make the sphere move. The cube is a kinematic object that only moves when the controls are pressed and only collides with dynamic objects, therefore our cube currently clips through the board but does collide with the sphere and make it move.
  
Extra Credit:
We loaded the board using triangle meshes.



Controls:

Camera:
Use W to move camera Forwards.
Use S to move camera Backwards.
Use A to strafe camera Left.
Use D to strafe camera Right.
Use Q to rotate camera Up.
Use E to rotate camera Down.
Use Z to turn camera Left.
Use X to turn camera Right.

Use R to reset the view.

Press Esc to exit.

Cube Controls:

Up Arrow: 	Move the cube forward on the z axis

Down Arrow: 	Move the cube backwards on the z axis

Left Arrow:	Move the cube Left

Right Arrow:	Move the cube Right

Enter:		Move the cube Up (y-axis)

Right_Ctrl:	Move the cube Down (y-axis)



Required Libraries:
  sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev libbullet-dev

Instructions on compiling:
In CS480/PA8$

  mkdir build/

  cd build/

  cmake ..

  make

  ./PA8 -c ../config.json
