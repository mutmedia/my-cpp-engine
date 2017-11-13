#ifndef SHADER_H
#define SHADER_H

#include <SDL_opengles2.h>

#include "common.h"

class Shader : nocopy {
public:
  Shader(const char *vert, const char *frag);
  ~Shader();

  GLint uniform_time() { return uniform_time_; }
  GLint uniform_screenSize() { return uniform_screenSize_; }
  GLint uniform_mvp() { return uniform_mvp_; }
  GLint uniform_model() { return uniform_model_; }
  GLint uniform_view() { return uniform_view_; }
  GLint uniform_projection() { return uniform_projection_; }

  GLint uniform_material_diffuse_color() {
    return uniform_material_diffuse_color_;
  }
  GLint uniform_material_specular_color() {
    return uniform_material_specular_color_;
  }

  GLint uniform_lightCount() { return uniform_lightCount_; }
  GLint uniform_lightPos_worldspace() { return uniform_lightPos_worldspace_; }
  GLint uniform_lightColor() { return uniform_lightColor_; }

  GLint uniform_ambientLight() { return uniform_ambientLight_; }

  GLuint id() { return id_; }

private:
  GLuint id_;

  // default uniforms
  GLint uniform_time_;
  GLint uniform_screenSize_;
  GLint uniform_mvp_;
  GLint uniform_model_;
  GLint uniform_view_;
  GLint uniform_projection_;

  GLint uniform_material_diffuse_color_;
  GLint uniform_material_specular_color_;

  GLint uniform_lightCount_;
  GLint uniform_lightPos_worldspace_;
  GLint uniform_lightColor_;

  GLint uniform_ambientLight_;
};

#endif
