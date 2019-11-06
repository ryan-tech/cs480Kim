#version 330
  //per vertex fragment shader
  in vec4 color;

  void main(void)
  {
     gl_FragColor = color;
  }
