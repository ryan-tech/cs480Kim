#version 330

  // per vertex vertex shader
  layout (location = 0) in vec3 v_position;
  layout (location = 1) in vec2 v_texture;
  layout (location = 2) in vec3 v_Normal;

  vec4 vPosition = vec4(v_position, 1.0);

  smooth out vec4 color;
  smooth out vec2 texture;

  // light and material properties
  uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
  uniform mat4 Model, View, Projection;
  uniform vec4 LightPosition;
  uniform float Shininess;

  // spotlight

  uniform vec3 slDirection;
  uniform float slCutoff;


  void main()
  {
      // Transform vertex  position into eye coordinates
      vec3 pos = (View*Model*vPosition).xyz;

      vec3 L = normalize( LightPosition.xyz - pos );
      vec3 E = normalize( -pos );
      vec3 H = normalize( L + E );

      // Transform vertex normal into eye coordinates
      vec3 N = normalize( View*Model*vec4(v_Normal, 0.0) ).xyz;
      // Compute terms in the illumination equation
      vec4 ambient = AmbientProduct;

      float Kd = max( dot(L, N), 0.0 );
      vec4  diffuse = Kd*DiffuseProduct;
      float Ks = pow(max(dot(N, H), 0.0), Shininess);
      vec4  specular = Ks * SpecularProduct;
      if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 1.0);
      gl_Position = Projection*View*Model*vPosition;



      //SPOTLIGHT
      vec3 lightdir = normalize( LightPosition.xyz - vPosition.xyz);

      float theta = dot(lightdir, normalize(-slDirection));

      if(theta < slCutoff)
      {
        color = ambient + diffuse + specular;
      }
      else
      {
        color = ambient + diffuse + specular;
      }



      //float theta = dot(lightdir, normalize(-slDirection));

      //if(theta > slCutoff)
      //{
      //color = ambient + diffuse + specular;
      //}
      //else  // else, use ambient light so scene isn't completely dark outside the spotlight.
      //  color = ambient;

      color.a = 1.0;

      texture = v_texture;
  }
