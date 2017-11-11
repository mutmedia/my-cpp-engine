#include "shader.h"

#include "glutils.h"

Shader::Shader(const char* vert, const char* frag) {
  id_ = glCreateProgram();
  if(id_ == 0) { FAIL("glCreateProgram");}

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

    glAttachShader(id_, shader_id);
    glDeleteShader(shader_id);
    GLERRORS("AttachShaders()");
  };

  attachShader(GL_VERTEX_SHADER, vert);
  attachShader(GL_FRAGMENT_SHADER, frag);
  glLinkProgram(id_);

  GLint link_status;
  glGetProgramiv(id_, GL_LINK_STATUS, &link_status);
  if(!link_status)
  {
    GLint log_length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_length);
    GLchar log[log_length];
    glGetProgramInfoLog(id_, log_length, nullptr, log);
    fprintf(stderr, "%s\n", log);
    FAIL("link shaders");
  }

  // set default uniforms
  uniform_mvp_ = glGetUniformLocation(id_, "u_mvp");
  uniform_screenSize_ = glGetUniformLocation(id_, "u_screenSize");
  uniform_time_ = glGetUniformLocation(id_, "u_time");
}

Shader::~Shader() {
  glDeleteProgram(id_);
}