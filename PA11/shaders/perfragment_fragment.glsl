#version 330

  // per fragment fragment shader

  // per-fragment interpolated values from the vertex shader
  in vec3 fN;
  in vec3 fL;
  in vec3 fE;

  //in vec3 lightdir;

  uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
  uniform vec4 LightPosition;
  uniform float Shininess;

  smooth in vec2 texture;
  in vec3 lightdir;
  uniform sampler2D gSampler;

  // spotlight

  uniform vec3 slDirection;
  uniform float slCutoff;


  void main()
  {
      // Normalize the input lighting vectors

      vec3 N = normalize(fN);
      vec3 E = normalize(fE);
      vec3 L = normalize(fL);

      vec3 H = normalize( L + E );
      vec4 ambient = AmbientProduct;
      float Kd = max(dot(L, N), 0.0);
      vec4 diffuse = Kd*DiffuseProduct;

      float Ks = pow(max(dot(N, H), 0.0), Shininess);
      vec4 specular = Ks*SpecularProduct;

      // discard the specular highlight if the light's behind the vertex
      if( dot(L, N) < 0.0 )
  	  specular = vec4(0.0, 0.0, 0.0, 1.0);

      float theta = dot(lightdir, normalize(-slDirection));

      if(theta < slCutoff)
      {

        gl_FragColor = texture2D(gSampler, texture.xy) * (ambient + diffuse + specular);
        gl_FragColor.a = 1.0;

      }
      else  // else, use ambient light so scene isn't completely dark outside the spotlight.
      {
        gl_FragColor = texture2D(gSampler, texture.xy) * (ambient + diffuse + specular);
        gl_FragColor.a = 1.0;
      }
  }
