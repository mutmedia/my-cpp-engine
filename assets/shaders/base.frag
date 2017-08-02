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

void main() 
{ 
  vec2 uv = gl_FragCoord.xy/u_screenSize;
  gl_FragColor = vec4(uv, 1.0, 1.0);
}

