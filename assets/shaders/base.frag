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

varying vec4 v_color;
uniform vec2 u_screenSize;
uniform float u_time;

float to01(float t) {
  return 0.5 * t + 0.5;
}

float cos01(float t) {
  return to01(cos(t));
}

float sin01(float t) {
  return to01(sin(t));
}

void main() 
{ 
  vec2 uv = gl_FragCoord.xy/u_screenSize;
  //gl_FragColor = vec4(uv + vec2(cos01(u_time/10.0), sin01(u_time/10.0)), 0.5, 1.0);
  gl_FragColor = v_color;
}

