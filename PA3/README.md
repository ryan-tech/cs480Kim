Project Assignment: PA2

Name: Ryan Kim

Date: 09/09/19

Project Directions: Make the cube spin while orbiting the center. Implement keyboard and mouse interactions such that a keyboard button press or a mouse button click will cause the cube to spin in the other direction.

Description on changes:
 There were a few additions to the source classes. First, the engine class has a method called Keyboard(), which is called inside a while loop in the Run() method while the SDL_PollEvent is not equal to 0. There was already an implementation of an escape key press stopping the engine, and that was inside an if statement that checked if a keyboard button was pressed. I added an if statement that set a m_keypress boolean variable that I added to the engine.h header file, and m_keypress is a simple flag that alternates between keypresses. I also added this statement if the SDL event was a mouse button down.
 m_keypress is then passed into Graphics::Update() which calls the Object::Update() method. Depending on the flag's value, it alternates between incrementing and decrementing the angle to the cube's rotation. This causes the cube to spin in the other direction when a (mouse or keyboard) button is pressed. A separate float variable was created for the translation of the cube to account for a consistent rotation

Update on Shaders:
  Shaders were moved outside of the src directory in their own directory in PA2/shaders . The instructions on compiling reflect this change and should work as intended.

Instructions on compiling:

In CS480/PA2$

  mkdir build/

  cd build/

  cp ../makefile .

  make clean

  make

  ./Tutorial -f ../shaders/fragment.txt -v ../shaders/vertex.txt
