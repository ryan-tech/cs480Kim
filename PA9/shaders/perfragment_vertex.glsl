#version 330

  // per fragment vertex shader
  in vec4 vPosition;
  in vec3 vNormal;

  // output values that will be interpolatated per-fragment
  out vec3 fN;
  out vec3 fE;
  out vec3 fL;

  uniform mat4 Model, View, Projection;
  uniform vec4 LightPosition;

  void main()
  {
      fN = vNormal;
      fE = vPosition.xyz;
      fL = LightPosition.xyz;

      if( LightPosition.w != 0.0 ) {
  	    fL = LightPosition.xyz - vPosition.xyz;
      }
      gl_Position = Projection * Model * View * vPosition;
  }
