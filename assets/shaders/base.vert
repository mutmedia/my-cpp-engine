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

attribute vec3 a_position;
attribute vec3 a_normal;
//attribute vec3 a_color;

varying vec3 v_position_cameraspace;
varying vec3 v_normal_cameraspace;

varying vec3 v_eyeDir_cameraspace;
varying vec3 v_lightDir_cameraspace[MAX_LIGHT_COUNT];

varying vec4 v_color;

uniform vec2 u_screenSize;
uniform float u_time;

// Material

// Matrices
uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_material_diffuse_color;
uniform vec3 u_material_specular_color;

uniform vec3 u_lightPos_worldspace[MAX_LIGHT_COUNT];
uniform vec3 u_lightColor[MAX_LIGHT_COUNT];
uniform lowp int u_lightCount;

void main()
{
    gl_Position = u_mvp * vec4(a_position, 1.0);
    //v_color = a_color;
    v_position_cameraspace = (u_view * u_model * vec4(a_position, 1.0)).xyz;
    v_normal_cameraspace = (u_view * u_model * vec4(a_normal, 0.0)).xyz;
    v_eyeDir_cameraspace = vec3(0.0) - v_position_cameraspace;
    for(int i = 0; i < MAX_LIGHT_COUNT; i++) {
        if(i < u_lightCount) {
            v_lightDir_cameraspace[i] = (u_view * vec4(u_lightPos_worldspace[i], 1.0)).xyz + v_eyeDir_cameraspace;
        }
    }
}

