Project Assignment: PA7

Group Member Names:
  Maxwell Johnston
  Ryan Kim
  Ryan Poston

Date: 10/18/19

Project Directions: The instructions for this project was to load and render a solar system.

Description on changes:
  A Texture class was created through the texture.cpp and texture.h files. This texture class has a constructor which includes a filepath as a parameter, and has a load method
  which loads the texture from the image specified by the filepath. The shader files were also modified to be able to pass the texture coordinates and render the textures.
We created a subclass Moon which inherited from Objects which allowed us to create a vector of Satellites around each planet. We offset each moon so that they don't overlap
in the same spot.
We created a Camera::Update() function to help with camera control using a keyboard.
Included obj and mtl files to load and texture all planets.

config file controls:
json_obj ["Planets"][nameOfPlanet]
			["Filepath"] gives the path to the object file that needs to be loaded.
			["Size"] gives the size in relation to the sun.
			["RotationDirection"] is a Boolean that tells if the planet rotates clockwise or counter-clockwise.
			["OrbitSpeed"] gives the speed that the planet orbits around the sun in relation to Earth.
			["RotateSpeed"] gives the amount of time it takes to rotate once in relation to Earth.
			["DistanceFromOrigin"] gives ranking of the planets for distance from the Sun.
			["NumSatellites"] gives the number of moons a planet has.



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



Required Libraries:
  sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw3-dev

Instructions on compiling:
In CS480/PA6$

  mkdir build/

  cd build/

  cmake ..

  make

  ./PA7 -f ../shaders/fragment.txt -v ../shaders/vertex.txt -c ../config.json
