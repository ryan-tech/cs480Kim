#version 330

  // per fragment vertex shader
  layout (location = 0) in vec3 v_position;
  layout (location = 1) in vec2 v_texture;
  layout (location = 2) in vec3 v_Normal;

  vec4 vPosition = vec4(v_position, 1.0);


  // output values that will be interpolatated per-fragment
  out vec3 fN;
  out vec3 fE;
  out vec3 fL;


  smooth out vec2 texture;
  out vec3 lightdir;


  uniform mat4 Model, View, Projection;
  uniform vec4 LightPosition;


  void main()
  {
      fN = v_Normal;
      fE = vPosition.xyz;
      fL = LightPosition.xyz;

      if( LightPosition.w != 0.0 ) {
  	    fL = LightPosition.xyz - vPosition.xyz;
      }

      lightdir = normalize( LightPosition.xyz - vec3(Model * vec4(v_position, 1.0f)));


      gl_Position = Projection * View * Model * vPosition;

      texture = v_texture;
  }
