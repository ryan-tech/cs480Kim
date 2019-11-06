#version 330
  //per vertex fragment shader

  smooth in vec4 color;
  smooth in vec2 texture;
  uniform sampler2D gSampler;


  void main(void)
  {
     gl_FragColor = texture2D(gSampler, texture.xy) * color;
     gl_FragColor.a = 1.0;
  }
