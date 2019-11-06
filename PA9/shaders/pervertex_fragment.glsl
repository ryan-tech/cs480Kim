#version 330
  //per vertex fragment shader
  in vec3 color;

  void main(void)
  {
     gl_FragColor = color;
  }
