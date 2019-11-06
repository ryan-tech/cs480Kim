#version 330

  // per vertex vertex shader
  layout (location = 0) in vec3 v_position;
  layout (location = 1) in vec2 v_texture;
  layout (location = 2) in vec3 v_color;

  vec4 vPosition = vec4(v_position, 1.0);
  in vec3 vNormal;

  smooth out vec4 color;
  smooth out vec2 texture;

  // light and material properties
  uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;

  uniform mat4 Model, View, Projection;

  uniform vec4 LightPosition;
  uniform float Shininess;

  void main()
  {
      // Transform vertex  position into eye coordinates
      vec3 pos = (Projection*View*Model*vPosition).xyz;

      vec3 L = normalize( LightPosition.xyz - pos );
      vec3 E = normalize( -pos );
      vec3 H = normalize( L + E );

      // Transform vertex normal into eye coordinates
      vec3 N = normalize( Projection*View*Model*vec4(vNormal, 0.0) ).xyz;
      // Compute terms in the illumination equation
      vec4 ambient = AmbientProduct;

      float Kd = max( dot(L, N), 0.0 );
      vec4  diffuse = Kd*DiffuseProduct;
      float Ks = pow( max(dot(N, H), 0.0), Shininess );
      vec4  specular = Ks * SpecularProduct;
      if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 1.0);
      gl_Position = Projection*View*Model*vPosition;

      color = ambient + diffuse + specular;
      color.a = 1.0;

      texture = v_texture;
  }
