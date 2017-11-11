#ifdef GL_ES                        
#  ifdef GL_FRAGMENT_PRECISION_HIGH 
precision highp float;         
#  else                             
precision mediump float;       
#  endif                            
#else                               
// Ignore unsupported precision specifiers
#  define lowp                      
#  define mediump                   
#  define highp                     
#endif    

#define MAX_LIGHT_COUNT 10

varying vec3 v_position_cameraspace;
varying vec3 v_normal_cameraspace;

varying vec3 v_eyeDir_cameraspace;
varying vec3 v_lightDir_cameraspace[MAX_LIGHT_COUNT];

varying vec4 v_color;

uniform vec2 u_screenSize;
uniform float u_time;
uniform vec3 u_material_diffuse_color;
uniform vec3 u_material_specular_color;

uniform lowp int u_lightCount;
uniform vec3 u_lightColor[MAX_LIGHT_COUNT];

// TODO: make this uniform
const vec3 ambientLight = vec3(0.1, 0.1, 0.1);

void main() 
{ 
  vec3 color;

  vec3 n = normalize(v_normal_cameraspace);
  vec3 e = normalize(v_eyeDir_cameraspace);

  for(int i = 0; i < MAX_LIGHT_COUNT; i++) {
    if(i < u_lightCount) {
      // diffuse
      float d = length(v_lightDir_cameraspace[i]);
      vec3 l = normalize(v_lightDir_cameraspace[i]);
      float diffuse = clamp( dot(n, l), 0.0, 1.0);

      // specular
      vec3 r = reflect(-l, n);
      float specular = clamp( dot(e, r), 0.0, 1.0);

      color +=
        u_material_diffuse_color * ambientLight +
        u_material_diffuse_color * u_lightColor[i] * diffuse / (d * d) +
        u_material_specular_color * u_lightColor[i] * pow(specular, 5.0) / (d * d);
      }
  }
  gl_FragColor = vec4(color, 1.0);
}

