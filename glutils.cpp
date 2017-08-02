#include "glutils.h"
#include "common.h"

void GLERRORS(const char* label) {
  //#ifndef __EMSCRIPTEN__
  while(true) {
    GLenum err = glGetError();
    if(err == GL_NO_ERROR) { break; }
    fprintf(stderr, "%s glGetError returned %d \n", label, err);
  }
  //#endif
}

void FAIL(const char* label) {
  GLERRORS(label);
  fprintf(stderr, "%s failed : %s \n", label, SDL_GetError());
  exit(EXIT_FAILURE);
}

ShaderProgram::ShaderProgram(const char* vert, const char* frag) {
  id = glCreateProgram();
  if(id == 0) { FAIL("glCreateProgram");}

  auto attachShader = [&](GLenum type, const GLchar* source)
  {
    GLuint shader_id = glCreateShader(type);
    if(shader_id == 0) { FAIL("load shader"); }

    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    GLint compile_status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if(!compile_status)
    {
      GLint log_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
      GLchar log[log_length];
      glGetShaderInfoLog(shader_id, log_length, nullptr, log);
      fprintf(stderr, "%s\n", log);
      FAIL("compile shader");
    }

    glAttachShader(id, shader_id);
    glDeleteShader(shader_id);
    GLERRORS("AttachShaders()");
  };

  attachShader(GL_VERTEX_SHADER, vert);
  attachShader(GL_FRAGMENT_SHADER, frag);
  glLinkProgram(id);

  GLint link_status;
  glGetProgramiv(id, GL_LINK_STATUS, &link_status);
  if(!link_status)
  {
    GLint log_length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
    GLchar log[log_length];
    glGetProgramInfoLog(id, log_length, nullptr, log);
    fprintf(stderr, "%s\n", log);
    FAIL("link shaders");
  }
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(id);
}

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &id);
}


GlContext::GlContext(SDL_Window* window) {
  id = SDL_GL_CreateContext(window);
  if(id == nullptr) { FAIL("SDL_GL_CreateContext"); }
}

GlContext::~GlContext() {
  SDL_GL_DeleteContext(id);
}
